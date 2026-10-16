/* AutoPC application lifetime, as the Auto PC SDK's samples do it: register
   with the Forms Manager, start a visible form with an event sink, take the
   faceplate keys from WM_REMOTE_KEYDOWN and WM_REMOTE_KEYUP, and draw through
   the form's IFMDraw. GUIDs, FC_MAINFACEPLATE, the message numbers and the
   vtable orders are from the SDK's asfc.h, apcmsg.h and keypad.h. */
#include "autopc_app.h"

typedef struct {
    DWORD data1;
    WORD data2, data3;
    BYTE data4[8];
} autopc_guid_t;

typedef HRESULT (*CoInitializeEx_t)(void *, DWORD);
typedef void (*CoUninitialize_t)(void);
typedef HRESULT (*CoCreateInstance_t)(const autopc_guid_t *, void *, DWORD, const autopc_guid_t *, void **);
typedef WCHAR *(*SysAllocString_t)(const WCHAR *);
typedef void (*SysFreeString_t)(WCHAR *);
typedef HRESULT (*FormsManagerCall_t)(void);
typedef int (*LoadStringW_t)(HINSTANCE, UINT, WCHAR *, int);
typedef BOOL (*PeekMessageW_t)(MSG *, HWND, UINT, UINT, UINT);
typedef LRESULT (*DispatchMessageW_t)(const MSG *);
typedef BOOL (*PostThreadMessageW_t)(DWORD, UINT, WPARAM, LPARAM);

typedef ULONG (*Release_t)(void *);
typedef HRESULT (*Start_t)(void *, void *);
typedef HRESULT (*MoveAppToForeground_t)(void *, LONG, LONG *, LONG);
typedef HRESULT (*RegisterStartedApplication_t)(void *, DWORD, WCHAR *, LONG, LONG);
typedef HRESULT (*DeregisterStartedApplication_t)(void *, DWORD, WCHAR *);
typedef HRESULT (*FormInit_t)(void *, short, void *, void *);
typedef HRESULT (*FormClose_t)(void *);
typedef HRESULT (*PutBool_t)(void *, BOOL);
typedef HRESULT (*PutString_t)(void *, WCHAR *);
typedef HRESULT (*GetIFMDraw_t)(void *, void **, long, long, long, long);
typedef HRESULT (*GetDC_t)(void *, long *);
typedef HRESULT (*HandleCall_t)(void *, long);

#define COINIT_MULTITHREADED_FLAG 0
#define CLSCTX_INPROC 1
#define FC_MAINFACEPLATE 0xFFFFFFFDu
#define WM_REMOTE_KEYDOWN 0xBD00
#define WM_REMOTE_KEYUP   0xBD01
#define WM_QUIT_MESSAGE   0x0012
#define PM_REMOVE_FLAG    1
#define KEY_ESCAPE        0x1B
#define FORM_ID           1
#define APP_NAME_STRING   1
#define APP_NAME_LENGTH   64
#define HANDLED           0
#define NOT_HANDLED       1
#define NO_INTERFACE      ((HRESULT)0x80004002L)
#define NOT_IMPLEMENTED   ((HRESULT)0x80004001L)

#define SLOT_RELEASE 2
#define SLOT_MANAGE_START 7
#define SLOT_MOVE_APP_TO_FOREGROUND 12
#define SLOT_REGISTER_STARTED_APPLICATION 15
#define SLOT_DEREGISTER_STARTED_APPLICATION 16
#define SLOT_FORM_INIT 7
#define SLOT_FORM_CLOSE 9
#define SLOT_FORM_PUT_VISIBLE 33
#define SLOT_FORM_PUT_CAPTION 63
#define SLOT_FORM_GET_IFMDRAW 79
#define SLOT_DRAW_GET_DC 7
#define SLOT_DRAW_COMMIT 8
#define SLOT_DRAW_RELEASE_DC 10

static const autopc_guid_t CLSID_FMMANAGE = { 0x196F4760, 0x5F84, 0x11D1, { 0x9B, 0x27, 0x00, 0x00, 0xF8, 0x75, 0x7D, 0x96 } };
static const autopc_guid_t IID_FMMANAGE = { 0x1FB926E1, 0xA17C, 0x11D0, { 0x88, 0xE0, 0x00, 0x00, 0xF8, 0x04, 0x01, 0xD1 } };
static const autopc_guid_t CLSID_ASFORM = { 0x37C23051, 0x997F, 0x11D0, { 0x88, 0xDC, 0x00, 0x00, 0xF8, 0x04, 0x01, 0xD1 } };
static const autopc_guid_t IID_ASFORM = { 0x6D318C43, 0x9343, 0x11D0, { 0xB5, 0x12, 0x00, 0xA0, 0x24, 0xA6, 0x52, 0xFA } };
static const autopc_guid_t IID_ASEVENTSINK = { 0x6D318C42, 0x9343, 0x11D0, { 0xB5, 0x12, 0x00, 0xA0, 0x24, 0xA6, 0x52, 0xFA } };
static const autopc_guid_t IID_UNKNOWN = { 0x00000000, 0x0000, 0x0000, { 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };
static const autopc_guid_t IID_DISPATCH = { 0x00020400, 0x0000, 0x0000, { 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };

typedef struct {
    void *const *vtable;
    LONG references;
} event_sink_t;

static void *manage, *form, *draw;
static WCHAR *app_name;
static BOOL running, com_started, forms_started;
static autopc_key_fn key_handler;
static void *key_context;
static DWORD app_thread;
static CoUninitialize_t co_uninitialize;
static SysFreeString_t sys_free_string;
static FormsManagerCall_t uninit_forms_manager;
static PeekMessageW_t peek_message;
static DispatchMessageW_t dispatch_message;
static PostThreadMessageW_t post_thread_message;

static void *method(void *object, int slot) {
    return (*(void ***)object)[slot];
}

static BOOL same_guid(const autopc_guid_t *a, const autopc_guid_t *b) {
    const BYTE *x = (const BYTE *)a, *y = (const BYTE *)b;
    int i;
    for (i = 0; i < (int)sizeof *a; i++) {
        if (x[i] != y[i]) return FALSE;
    }
    return TRUE;
}

static ULONG sink_add_ref(event_sink_t *sink) {
    return (ULONG)++sink->references;
}

static ULONG sink_release(event_sink_t *sink) {
    return (ULONG)(sink->references > 0 ? --sink->references : 0);
}

static HRESULT sink_query_interface(event_sink_t *sink, const autopc_guid_t *riid, void **out) {
    if (!out) return E_INVALIDARG;
    if (!same_guid(riid, &IID_ASEVENTSINK) && !same_guid(riid, &IID_UNKNOWN) && !same_guid(riid, &IID_DISPATCH)) {
        *out = 0;
        return NO_INTERFACE;
    }
    *out = sink;
    sink_add_ref(sink);
    return S_OK;
}

static HRESULT sink_not_implemented(void) {
    return NOT_IMPLEMENTED;
}

static HRESULT sink_receive_message(event_sink_t *sink, long message, long wparam, long lparam) {
    BOOL down = message == WM_REMOTE_KEYDOWN;
    (void)sink;
    (void)lparam;
    if (message != WM_REMOTE_KEYDOWN && message != WM_REMOTE_KEYUP) return NOT_HANDLED;
    if (key_handler && key_handler(key_context, (UINT)wparam, down)) return HANDLED;
    if (wparam == KEY_ESCAPE) {
        if (down) autopc_app_quit();
        return HANDLED;
    }
    return NOT_HANDLED;
}

static void *const sink_vtable[8] = {
    (void *)sink_query_interface, (void *)sink_add_ref, (void *)sink_release,
    (void *)sink_not_implemented, (void *)sink_not_implemented, (void *)sink_not_implemented, (void *)sink_not_implemented,
    (void *)sink_receive_message,
};

static event_sink_t event_sink = { sink_vtable, 1 };

BOOL autopc_app_start(HINSTANCE instance, autopc_key_fn on_key, void *context) {
    HINSTANCE coredll = LoadLibraryW(L"coredll.dll");
    HINSTANCE ole32 = LoadLibraryW(L"ole32.dll");
    HINSTANCE oleaut32 = LoadLibraryW(L"oleaut32.dll");
    HINSTANCE asfc = LoadLibraryW(L"asfc.dll");
    CoInitializeEx_t co_initialize;
    CoCreateInstance_t co_create_instance;
    SysAllocString_t sys_alloc_string;
    FormsManagerCall_t init_forms_manager;
    LoadStringW_t load_string;
    WCHAR name[APP_NAME_LENGTH];

    if (running) return TRUE;
    if (!coredll || !ole32 || !oleaut32 || !asfc) return FALSE;
    co_initialize = (CoInitializeEx_t)GetProcAddressW(ole32, L"CoInitializeEx");
    co_uninitialize = (CoUninitialize_t)GetProcAddressW(ole32, L"CoUninitialize");
    co_create_instance = (CoCreateInstance_t)GetProcAddressW(ole32, L"CoCreateInstance");
    sys_alloc_string = (SysAllocString_t)GetProcAddressW(oleaut32, L"SysAllocString");
    sys_free_string = (SysFreeString_t)GetProcAddressW(oleaut32, L"SysFreeString");
    init_forms_manager = (FormsManagerCall_t)GetProcAddressW(asfc, L"InitASFormsManager");
    uninit_forms_manager = (FormsManagerCall_t)GetProcAddressW(asfc, L"UnInitASFormsManager");
    load_string = (LoadStringW_t)GetProcAddressW(coredll, L"LoadStringW");
    peek_message = (PeekMessageW_t)GetProcAddressW(coredll, L"PeekMessageW");
    dispatch_message = (DispatchMessageW_t)GetProcAddressW(coredll, L"DispatchMessageW");
    post_thread_message = (PostThreadMessageW_t)GetProcAddressW(coredll, L"PostThreadMessageW");
    if (!co_initialize || !co_uninitialize || !co_create_instance || !sys_alloc_string || !sys_free_string || !init_forms_manager ||
        !uninit_forms_manager || !load_string || !peek_message || !dispatch_message || !post_thread_message) return FALSE;
    if (!load_string(instance, APP_NAME_STRING, name, APP_NAME_LENGTH)) return FALSE;

    key_handler = on_key;
    key_context = context;
    app_thread = GetCurrentThreadId();
    co_initialize(0, COINIT_MULTITHREADED_FLAG);
    com_started = TRUE;
    if (init_forms_manager() < 0) {
        autopc_app_stop();
        return FALSE;
    }
    forms_started = TRUE;
    app_name = sys_alloc_string(name);
    if (!app_name || co_create_instance(&CLSID_FMMANAGE, 0, CLSCTX_INPROC, &IID_FMMANAGE, &manage) < 0 || !manage) {
        manage = 0;
        autopc_app_stop();
        return FALSE;
    }
    ((RegisterStartedApplication_t)method(manage, SLOT_REGISTER_STARTED_APPLICATION))(manage, FC_MAINFACEPLATE, app_name, 0, 0);
    ((MoveAppToForeground_t)method(manage, SLOT_MOVE_APP_TO_FOREGROUND))(manage, (LONG)GetCurrentProcessId(), 0, 0);
    if (co_create_instance(&CLSID_ASFORM, 0, CLSCTX_INPROC, &IID_ASFORM, &form) < 0 || !form ||
        ((FormInit_t)method(form, SLOT_FORM_INIT))(form, FORM_ID, 0, &event_sink) < 0 ||
        ((Start_t)method(manage, SLOT_MANAGE_START))(manage, form) < 0) {
        autopc_app_stop();
        return FALSE;
    }
    ((PutString_t)method(form, SLOT_FORM_PUT_CAPTION))(form, app_name);
    ((PutBool_t)method(form, SLOT_FORM_PUT_VISIBLE))(form, TRUE);
    running = TRUE;
    return TRUE;
}

BOOL autopc_app_running(void) {
    MSG message;
    while (running && peek_message(&message, 0, 0, 0, PM_REMOVE_FLAG)) {
        if (message.message == WM_QUIT_MESSAGE) running = FALSE;
        else dispatch_message(&message);
    }
    return running;
}

void autopc_app_quit(void) {
    if (running && post_thread_message) post_thread_message(app_thread, WM_QUIT_MESSAGE, 0, 0);
}

HDC autopc_app_begin_draw(void) {
    long dc = 0;
    if (!form) return 0;
    if (!draw && ((GetIFMDraw_t)method(form, SLOT_FORM_GET_IFMDRAW))(form, &draw, 0, 0, AUTOPC_SCREEN_WIDTH, AUTOPC_SCREEN_HEIGHT) < 0) draw = 0;
    if (!draw || ((GetDC_t)method(draw, SLOT_DRAW_GET_DC))(draw, &dc) < 0) return 0;
    return (HDC)dc;
}

void autopc_app_end_draw(HDC dc) {
    if (!draw || !dc) return;
    ((HandleCall_t)method(draw, SLOT_DRAW_COMMIT))(draw, (long)dc);
    ((HandleCall_t)method(draw, SLOT_DRAW_RELEASE_DC))(draw, (long)dc);
}

void autopc_app_stop(void) {
    running = FALSE;
    if (draw) ((Release_t)method(draw, SLOT_RELEASE))(draw);
    if (manage && app_name) ((DeregisterStartedApplication_t)method(manage, SLOT_DEREGISTER_STARTED_APPLICATION))(manage, FC_MAINFACEPLATE, app_name);
    if (form) {
        ((FormClose_t)method(form, SLOT_FORM_CLOSE))(form);
        ((Release_t)method(form, SLOT_RELEASE))(form);
    }
    if (manage) ((Release_t)method(manage, SLOT_RELEASE))(manage);
    if (app_name) sys_free_string(app_name);
    if (forms_started) uninit_forms_manager();
    if (com_started) co_uninitialize();
    draw = form = manage = 0;
    app_name = 0;
    forms_started = com_started = FALSE;
}
