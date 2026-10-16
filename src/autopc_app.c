/* AutoPC app lifetime: Forms Manager registration through IfmManage, so the
   shell keeps the program running, and relaunching outside the shell's watch
   as a fallback. GUIDs, FC_MAINFACEPLATE and the IfmManage vtable order are
   from the Auto PC SDK's asfc.h. */
#include "autopc_app.h"

typedef struct {
    DWORD data1;
    WORD data2, data3;
    BYTE data4[8];
} autopc_guid_t;

typedef HRESULT (WINAPI *CoInitializeEx_t)(void *, DWORD);
typedef void (WINAPI *CoUninitialize_t)(void);
typedef HRESULT (WINAPI *CoCreateInstance_t)(const autopc_guid_t *, void *, DWORD, const autopc_guid_t *, void **);
typedef WCHAR *(WINAPI *SysAllocString_t)(const WCHAR *);
typedef void (WINAPI *SysFreeString_t)(WCHAR *);
typedef HRESULT (WINAPI *FormsManagerCall_t)(void);
typedef int (WINAPI *LoadStringW_t)(HINSTANCE, UINT, WCHAR *, int);
typedef ULONG (WINAPI *Release_t)(void *);
typedef HRESULT (WINAPI *MoveAppToForeground_t)(void *, LONG, LONG *, LONG);
typedef HRESULT (WINAPI *RegisterStartedApplication_t)(void *, DWORD, WCHAR *, LONG, LONG);
typedef HRESULT (WINAPI *DeregisterStartedApplication_t)(void *, DWORD, WCHAR *);
typedef DWORD (WINAPI *GetModuleFileNameW_t)(HINSTANCE, WCHAR *, DWORD);
typedef BOOL (WINAPI *CreateProcessW_t)(const WCHAR *, WCHAR *, void *, void *, BOOL, DWORD, void *, const WCHAR *, void *, PROCESS_INFORMATION *);

#define COINIT_MULTITHREADED_FLAG 0
#define CLSCTX_INPROC 1
#define FC_MAINFACEPLATE 0xFFFFFFFDu
#define SLOT_RELEASE 2
#define SLOT_MOVE_APP_TO_FOREGROUND 12
#define SLOT_REGISTER_STARTED_APPLICATION 15
#define SLOT_DEREGISTER_STARTED_APPLICATION 16
#define APP_NAME_STRING 1
#define APP_NAME_LENGTH 64

static const autopc_guid_t CLSID_FMMANAGE = { 0x196F4760, 0x5F84, 0x11D1, { 0x9B, 0x27, 0x00, 0x00, 0xF8, 0x75, 0x7D, 0x96 } };
static const autopc_guid_t IID_FMMANAGE = { 0x1FB926E1, 0xA17C, 0x11D0, { 0x88, 0xE0, 0x00, 0x00, 0xF8, 0x04, 0x01, 0xD1 } };

static void *manage;
static WCHAR *app_name;
static CoUninitialize_t co_uninitialize;
static SysFreeString_t sys_free_string;
static FormsManagerCall_t uninit_forms_manager;

static void *method(void *object, int slot) {
    return (*(void ***)object)[slot];
}

BOOL autopc_register_app(HINSTANCE instance) {
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

    if (manage || !coredll || !ole32 || !oleaut32 || !asfc) return manage != 0;
    co_initialize = (CoInitializeEx_t)GetProcAddressW(ole32, L"CoInitializeEx");
    co_uninitialize = (CoUninitialize_t)GetProcAddressW(ole32, L"CoUninitialize");
    co_create_instance = (CoCreateInstance_t)GetProcAddressW(ole32, L"CoCreateInstance");
    sys_alloc_string = (SysAllocString_t)GetProcAddressW(oleaut32, L"SysAllocString");
    sys_free_string = (SysFreeString_t)GetProcAddressW(oleaut32, L"SysFreeString");
    init_forms_manager = (FormsManagerCall_t)GetProcAddressW(asfc, L"InitASFormsManager");
    uninit_forms_manager = (FormsManagerCall_t)GetProcAddressW(asfc, L"UnInitASFormsManager");
    load_string = (LoadStringW_t)GetProcAddressW(coredll, L"LoadStringW");
    if (!co_initialize || !co_uninitialize || !co_create_instance || !sys_alloc_string || !sys_free_string ||
        !init_forms_manager || !uninit_forms_manager || !load_string) return FALSE;
    if (!load_string(instance, APP_NAME_STRING, name, APP_NAME_LENGTH)) return FALSE;

    co_initialize(0, COINIT_MULTITHREADED_FLAG);
    if (init_forms_manager() < 0) {
        co_uninitialize();
        return FALSE;
    }
    if (co_create_instance(&CLSID_FMMANAGE, 0, CLSCTX_INPROC, &IID_FMMANAGE, &manage) < 0 || !manage) {
        manage = 0;
        uninit_forms_manager();
        co_uninitialize();
        return FALSE;
    }
    app_name = sys_alloc_string(name);
    if (!app_name || ((RegisterStartedApplication_t)method(manage, SLOT_REGISTER_STARTED_APPLICATION))(manage, FC_MAINFACEPLATE, app_name, 0, 0) < 0) {
        autopc_unregister_app();
        return FALSE;
    }
    ((MoveAppToForeground_t)method(manage, SLOT_MOVE_APP_TO_FOREGROUND))(manage, (LONG)GetCurrentProcessId(), 0, 0);
    return TRUE;
}

void autopc_unregister_app(void) {
    if (manage && app_name) ((DeregisterStartedApplication_t)method(manage, SLOT_DEREGISTER_STARTED_APPLICATION))(manage, FC_MAINFACEPLATE, app_name);
    if (manage) ((Release_t)method(manage, SLOT_RELEASE))(manage);
    if (app_name) sys_free_string(app_name);
    if (manage) {
        uninit_forms_manager();
        co_uninitialize();
    }
    manage = 0;
    app_name = 0;
}

BOOL autopc_detach(HINSTANCE instance, const WCHAR *command_line) {
    static const WCHAR marker[] = L"/child";
    HINSTANCE coredll = LoadLibraryW(L"coredll.dll");
    GetModuleFileNameW_t get_module_file_name = (GetModuleFileNameW_t)GetProcAddressW(coredll, L"GetModuleFileNameW");
    CreateProcessW_t create_process = (CreateProcessW_t)GetProcAddressW(coredll, L"CreateProcessW");
    WCHAR path[MAX_PATH];
    WCHAR arguments[sizeof marker / sizeof marker[0]];
    PROCESS_INFORMATION process;
    int i;
    for (i = 0; marker[i]; i++) {
        if (!command_line || command_line[i] != marker[i]) break;
    }
    if (!marker[i] || !get_module_file_name || !create_process) return FALSE;
    if (!get_module_file_name(instance, path, MAX_PATH)) return FALSE;
    for (i = 0; marker[i]; i++) arguments[i] = marker[i];
    arguments[i] = 0;
    if (!create_process(path, arguments, 0, 0, FALSE, 0, 0, 0, 0, &process)) return FALSE;
    CloseHandle(process.hThread);
    CloseHandle(process.hProcess);
    return TRUE;
}
