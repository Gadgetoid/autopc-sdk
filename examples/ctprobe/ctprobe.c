#include "autopc.h"
#include "autopc_app.h"

#define PCI_CONFIGURATION  4
#define PCI_BUSES          256
#define PCI_DEVICES        32
#define PCI_FUNCTIONS      8
#define FUNCTION_SHIFT     5
#define CONFIG_HEADER      64
#define CONFIG_SPACE       256
#define NO_DEVICE          0xFFFF
#define CHIPS_VENDOR       0x102C
#define MULTIFUNCTION      0x80
#define BAR_COUNT          6

#define XR_INDEX           0x3D6
#define FR_INDEX           0x3D0
#define MR_INDEX           0x3D2
#define SR_INDEX           0x3C4
#define GR_INDEX           0x3CE
#define MISC_OUTPUT_READ   0x3CC
#define CR_INDEX_COLOUR    0x3D4
#define CR_INDEX_MONO      0x3B4
#define MISC_COLOUR        0x01
#define BANK_SIZE          256
#define SR_COUNT           8
#define GR_COUNT           9
#define CR_COUNT           0x80
#define BYTES_PER_LINE     16
#define FRAME_MS           200

typedef ULONG (*HalGetBusDataByOffset_t)(ULONG type, ULONG bus, ULONG slot, void *buffer, ULONG offset, ULONG length);

static const char HEX[] = "0123456789ABCDEF";
static HANDLE log_file = INVALID_HANDLE_VALUE;
static WCHAR summary[64] = L"Probing...";

static unsigned char port_read(unsigned short port) {
    unsigned char value;
    __asm__ volatile("inb %w1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static void port_write(unsigned short port, unsigned char value) {
    __asm__ volatile("outb %0, %w1" : : "a"(value), "Nd"(port));
}

static void put(const char *text) {
    DWORD length = 0, written;
    while (text[length]) length++;
    if (log_file != INVALID_HANDLE_VALUE) WriteFile(log_file, text, length, &written, 0);
}

static void put_hex(DWORD value, int digits) {
    char text[9];
    int i;
    for (i = 0; i < digits; i++) text[i] = HEX[(value >> (4 * (digits - 1 - i))) & 0xF];
    text[digits] = 0;
    put(text);
}

static void flush(void) {
    if (log_file != INVALID_HANDLE_VALUE) FlushFileBuffers(log_file);
}

static void put_bytes(const unsigned char *bytes, int count) {
    int i;
    for (i = 0; i < count; i++) {
        if (i % BYTES_PER_LINE == 0) {
            put("  ");
            put_hex((DWORD)i, 2);
            put(":");
        }
        put(" ");
        put_hex(bytes[i], 2);
        if (i % BYTES_PER_LINE == BYTES_PER_LINE - 1 || i == count - 1) put("\r\n");
    }
}

static int append_hex(WCHAR *text, int at, DWORD value, int digits) {
    int i;
    for (i = 0; i < digits; i++) text[at++] = (WCHAR)HEX[(value >> (4 * (digits - 1 - i))) & 0xF];
    text[at] = 0;
    return at;
}

static int append_text(WCHAR *text, int at, const WCHAR *more) {
    while (*more) text[at++] = *more++;
    text[at] = 0;
    return at;
}

static WORD config_word(const unsigned char *config, int offset) {
    return (WORD)(config[offset] | config[offset + 1] << 8);
}

static DWORD config_dword(const unsigned char *config, int offset) {
    return config_word(config, offset) | (DWORD)config_word(config, offset + 2) << 16;
}

static void put_device(ULONG bus, ULONG device, ULONG function, const unsigned char *config) {
    int bar;
    put("pci ");
    put_hex(bus, 2);
    put(":");
    put_hex(device, 2);
    put(".");
    put_hex(function, 1);
    put(" vendor ");
    put_hex(config_word(config, 0), 4);
    put(" device ");
    put_hex(config_word(config, 2), 4);
    put(" revision ");
    put_hex(config[8], 2);
    put(" class ");
    put_hex(config[11], 2);
    put_hex(config[10], 2);
    put_hex(config[9], 2);
    put(" command ");
    put_hex(config_word(config, 4), 4);
    put(" irq ");
    put_hex(config[60], 2);
    put("\r\n   ");
    for (bar = 0; bar < BAR_COUNT; bar++) {
        put(" bar");
        put_hex((DWORD)bar, 1);
        put(" ");
        put_hex(config_dword(config, 16 + 4 * bar), 8);
    }
    put("\r\n");
}

static BOOL scan_pci(HalGetBusDataByOffset_t get_bus_data, ULONG *chips_bus, ULONG *chips_slot, unsigned char *chips_config) {
    unsigned char config[CONFIG_SPACE];
    ULONG bus, device, function;
    BOOL found = FALSE;
    for (bus = 0; bus < PCI_BUSES; bus++) {
        for (device = 0; device < PCI_DEVICES; device++) {
            for (function = 0; function < PCI_FUNCTIONS; function++) {
                ULONG slot = device | function << FUNCTION_SHIFT;
                ULONG length = get_bus_data(PCI_CONFIGURATION, bus, slot, config, 0, CONFIG_HEADER);
                if (length == 0) {
                    if (device == 0 && function == 0) return found;
                    break;
                }
                if (length < CONFIG_HEADER || config_word(config, 0) == NO_DEVICE) {
                    if (function == 0) break;
                    continue;
                }
                put_device(bus, device, function, config);
                if (config_word(config, 0) == CHIPS_VENDOR && !found) {
                    found = TRUE;
                    *chips_bus = bus;
                    *chips_slot = slot;
                    get_bus_data(PCI_CONFIGURATION, bus, slot, chips_config, 0, CONFIG_SPACE);
                }
                if (function == 0 && !(config[14] & MULTIFUNCTION)) break;
            }
        }
    }
    return found;
}

static void read_bank(unsigned short index_port, int count, unsigned char *values) {
    unsigned char saved = port_read(index_port);
    int i;
    for (i = 0; i < count; i++) {
        port_write(index_port, (unsigned char)i);
        values[i] = port_read((unsigned short)(index_port + 1));
    }
    port_write(index_port, saved);
}

static void dump_bank(const char *name, unsigned short index_port, int count) {
    unsigned char values[BANK_SIZE];
    put(name);
    put(" (index ");
    put_hex(index_port, 3);
    put(")\r\n");
    flush();
    read_bank(index_port, count, values);
    put_bytes(values, count);
    flush();
}

static void probe(void) {
    HINSTANCE wdmoem = LoadLibraryW(L"wdmoem.dll");
    HalGetBusDataByOffset_t get_bus_data = wdmoem ? (HalGetBusDataByOffset_t)GetProcAddressW(wdmoem, L"HalGetBusDataByOffset") : 0;
    unsigned char chips_config[CONFIG_SPACE], identity[4], misc;
    ULONG chips_bus = 0, chips_slot = 0;
    BOOL chips = FALSE;
    int at, byte;

    log_file = autopc_card_create(L"CTPROBE.TXT");
    put("Joyride large screen controller probe\r\n");
    if (get_bus_data) {
        chips = scan_pci(get_bus_data, &chips_bus, &chips_slot, chips_config);
    } else {
        put("wdmoem.dll HalGetBusDataByOffset: missing\r\n");
    }
    if (chips) {
        put("Chips & Technologies config space\r\n");
        put_bytes(chips_config, CONFIG_SPACE);
    } else {
        put("no Chips & Technologies device on PCI\r\n");
    }
    put("port I/O: reading XR00-XR03\r\n");
    flush();
    read_bank(XR_INDEX, 4, identity);
    put("XR00-XR03:");
    for (byte = 0; byte < 4; byte++) {
        put(" ");
        put_hex(identity[byte], 2);
    }
    put("\r\n");
    flush();
    misc = port_read(MISC_OUTPUT_READ);
    put("misc output ");
    put_hex(misc, 2);
    put("\r\n");
    dump_bank("XR", XR_INDEX, BANK_SIZE);
    dump_bank("FR", FR_INDEX, BANK_SIZE);
    dump_bank("MR", MR_INDEX, BANK_SIZE);
    dump_bank("SR", SR_INDEX, SR_COUNT);
    dump_bank("GR", GR_INDEX, GR_COUNT);
    dump_bank("CR", misc & MISC_COLOUR ? CR_INDEX_COLOUR : CR_INDEX_MONO, CR_COUNT);
    put("done\r\n");
    flush();
    if (log_file != INVALID_HANDLE_VALUE) CloseHandle(log_file);

    at = append_text(summary, 0, chips ? L"C&T " : L"No C&T PCI ");
    if (chips) {
        at = append_hex(summary, at, config_word(chips_config, 2), 4);
        at = append_text(summary, at, L" ");
    }
    at = append_text(summary, at, L"XR ");
    for (byte = 0; byte < 4; byte++) at = append_hex(summary, at, identity[byte], 2);
    if (log_file == INVALID_HANDLE_VALUE) append_text(summary, at, L" no card");
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    BOOL probed = FALSE;
    if (!autopc_app_start(instance, 0, 0)) return 1;
    autopc_init();
    while (autopc_app_running()) {
        HDC dc = autopc_app_begin_draw();
        autopc_print(dc, summary);
        autopc_app_end_draw(dc);
        if (!probed) {
            probe();
            probed = TRUE;
        }
        Sleep(FRAME_MS);
    }
    autopc_app_stop();
    return 0;
}
