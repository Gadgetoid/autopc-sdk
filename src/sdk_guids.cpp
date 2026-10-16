/* Define the Auto PC SDK's GUIDs once per program, as the SDK's asfcguid.lib and uuid.lib did. */
#include <windows.h>
#include <objbase.h>
#include <initguid.h>
#include <coguid.h>
#include <olectl.h>
#include <asfc.h>
#include <ascmnctl.h>
#include <asctlext.h>
#include <apcspch.h>
#include <speech.h>

DEFINE_GUID(IID_IDispatch, 0x00020400, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
DEFINE_GUID(IID_IFont, 0xBEF6E002, 0xA874, 0x101A, 0x8B, 0xBA, 0x00, 0xAA, 0x00, 0x30, 0x0C, 0xAB);
