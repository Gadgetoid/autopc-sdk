#include "autopc.h"
#include "autopc_app.h"

#define FOLDER_INBOX    0xFE
#define FOLDER_TRAFFIC  0x12
#define FOLDER_NEWS     0x13
#define FRAME_MS        200

typedef struct {
    DWORD dwMsgId;
    DWORD dwFlags;
    DWORD dwMsgLen;
    WORD wBodyLen;
    FILETIME ftDate;
    LPWSTR szSvcId;
    LPWSTR szSvcNam;
    WCHAR *pwcHeaders;
    LPWSTR szBody;
    DWORD oid;
    HANDLE hHeap;
} MailMsg;

BOOL MailOpen(HANDLE *mail, BOOL allow_create);
BOOL MailClose(HANDLE mail);
BOOL MailPutFolder(HANDLE mail, BYTE id, LPWSTR name);
BOOL MailPut(HANDLE mail, MailMsg *message);
BOOL MailSetField(MailMsg *message, LPWSTR name, LPCWSTR value);
BOOL MailFree(MailMsg *message);

typedef struct {
    BYTE folder;
    const WCHAR *type;
    const WCHAR *from;
    const WCHAR *subject;
    const WCHAR *body;
} test_message_t;

static const test_message_t messages[] = {
    {FOLDER_INBOX, L"Regular", L"Pico W", L"Hello from a Pico W",
     L"This message was written into the mail store by msgtest."},
    {FOLDER_TRAFFIC, L"CUE Traffic", L"Traffic", L"M1 J10 slow traffic",
     L"Queueing traffic between J10 and J11 northbound."},
    {FOLDER_NEWS, L"Regular", L"News", L"Homebrew news",
     L"Messages can now be fed in from outside."},
};

static BOOL put_message(HANDLE mail, const test_message_t *test) {
    MailMsg message;
    SYSTEMTIME now;
    BOOL ok;
    memset(&message, 0, sizeof(message));
    message.dwFlags = test->folder;
    message.szBody = (LPWSTR)test->body;
    GetSystemTime(&now);
    SystemTimeToFileTime(&now, &message.ftDate);
    ok = MailSetField(&message, L"Type", test->type)
        && MailSetField(&message, L"From", test->from)
        && MailSetField(&message, L"Subject", test->subject)
        && MailPut(mail, &message);
    MailFree(&message);
    return ok;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    WCHAR status[64];
    HANDLE mail;
    int index, put = 0;
    if (!autopc_app_start(instance, 0, 0)) return 1;
    autopc_init();
    if (MailOpen(&mail, TRUE)) {
        MailPutFolder(mail, FOLDER_TRAFFIC, L"Traffic");
        MailPutFolder(mail, FOLDER_NEWS, L"News");
        for (index = 0; index < (int)(sizeof(messages) / sizeof(messages[0])); index++) {
            if (put_message(mail, &messages[index])) put++;
        }
        MailClose(mail);
        wsprintfW(status, L"Put %d of %d messages", put, (int)(sizeof(messages) / sizeof(messages[0])));
    } else {
        wsprintfW(status, L"MailOpen failed");
    }
    while (autopc_app_running()) {
        HDC dc = autopc_app_begin_draw();
        autopc_print(dc, status);
        autopc_app_end_draw(dc);
        Sleep(FRAME_MS);
    }
    autopc_app_stop();
    return 0;
}
