#pragma once

#if defined _WIN32 || defined _WIN64
#pragma pack(push, cryptoki, 1)
#endif

#include "pkcs11.h"

#if defined _WIN32 || defined _WIN64
#pragma pack(pop, cryptoki)
#endif

#if defined __linux__ || defined __APPLE__
#include <PCSC/winscard.h>
#include <PCSC/wintypes.h>
#endif

#if defined _WIN32 || defined _WIN64
#include <winscard.h>
#endif

#define MAXVAL 0xffffff
#define MAXSESSIONS MAXVAL

#define CK_ENTRY __declspec(dllexport)
#define LIBRARY_VERSION_MAJOR 2
#define LIBRARY_VERSION_MINOR 0

#define PIN_LEN 8
#define USER_PIN_ID 0x10

#define init_p11_func \
	CFuncCallInfo info(__FUNCTION__, Log); \
	try {

#define exit_p11_func } \
	catch (p11_error &p11Err) { \
		OutputDebugString("EXCLOG->"); \
		OutputDebugString(p11Err.what()); \
		OutputDebugString("<-EXCLOG");\
		return p11Err.getP11ErrorCode(); \
	} \
	catch (std::exception &err) { \
		OutputDebugString("EXCLOG->"); \
		OutputDebugString(err.what()); \
		OutputDebugString("<-EXCLOG");\
		return CKR_GENERAL_ERROR; \
	} \
catch (...) { return CKR_GENERAL_ERROR; }

extern "C" {
	CK_RV CK_ENTRY C_UpdateSlotList();
}
