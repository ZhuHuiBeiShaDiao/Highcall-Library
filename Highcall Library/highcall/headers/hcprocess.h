/*++

Module Name:

hcprocess.h

Abstract:

This module declares windows NT/WIN32 kernel "process" usermode handlers. 

Author:

Synestra 9/7/2016

Revision History:

Synestra 10/15/2016

--*/

#ifndef HC_PROCESS_H
#define HC_PROCESS_H

//
// Main definition file, i.e. HCAPI __stdcall
//
#include "hcdef.h"

#if defined (__cplusplus)
extern "C" {
#endif

	//
	// Struct used in callback for HcProcessEnumMappedImagesW, HcProcessEnumModulesW, contains information about
	// the current callback module.
	//
	typedef struct _HC_MODULE_INFORMATIONW
	{
		SIZE_T		Size;
		PVOID		Base;
		LPWSTR		Name;
		LPWSTR		Path;
	} HC_MODULE_INFORMATIONW, *PHC_MODULE_INFORMATIONW;

	//
	// Constructor for HC_MODULE_INFORMATIONW
	// Implemented in hcconstruct.c
	//
	HC_EXTERN_API PHC_MODULE_INFORMATIONW HCAPI HcInitializeModuleInformationW(SIZE_T NameBufferMax, SIZE_T PathBufferMax);

	//
	// Deconstructor for HC_MODULE_INFORMATIONW
	// Implemented in hcconstruct.c
	//
	HC_EXTERN_API VOID HCAPI HcDestroyModuleInformationW(PHC_MODULE_INFORMATIONW o);
	
	//
	// Callback for HcProcessEnumMappedImagesW, HcProcessEnumModulesW
	// 
	typedef BOOLEAN(CALLBACK* HC_MODULE_CALLBACK_EVENTW)(HC_MODULE_INFORMATIONW, LPARAM);

	//
	// Struct used in HcProcessQueryByNameExW callback, containing information about the current callback process.
	// Some information requires an open handle to the process, and even so, information is not guaranteed if having an open handle.
	//
	typedef struct _HC_PROCESS_INFORMATION_EXW
	{
		DWORD					Id;
		LPWSTR					Name;
		PHC_MODULE_INFORMATIONW	MainModule;
		BOOLEAN					CanAccess;
	} HC_PROCESS_INFORMATION_EXW, *PHC_PROCESS_INFORMATION_EXW;

	//
	// Constructor for HC_PROCESS_INFORMATION_EXW
	// Implemented in hcconstruct.c
	//
	HC_EXTERN_API PHC_PROCESS_INFORMATION_EXW HCAPI HcInitializeProcessInformationExW(SIZE_T NameBufferMax);

	//
	// Deconstructor for HC_PROCESS_INFORMATION_EXW
	// Implemented in hcconstruct.c
	//
	HC_EXTERN_API VOID HCAPI HcDestroyProcessInformationExW(PHC_PROCESS_INFORMATION_EXW o);

	//
	// Callback for HcProcessQueryByNameExW
	//
	typedef BOOLEAN(CALLBACK* HC_PROCESS_CALLBACK_EVENT_EXW)(HC_PROCESS_INFORMATION_EXW, LPARAM);

	//
	// Struct used in HcProcessQueryByNameW callback, containing information about the current callback process.
	//
	typedef struct _HC_PROCESS_INFORMATIONW
	{
		DWORD					Id;
		LPWSTR					Name;
	} HC_PROCESS_INFORMATIONW, *PHC_PROCESS_INFORMATIONW;

	//
	// Constructor for HC_PROCESS_INFORMATIONW
	// Implemented in hcconstruct.c
	//
	HC_EXTERN_API PHC_PROCESS_INFORMATIONW HCAPI HcInitializeProcessInformationW(SIZE_T NameBufferMax);

	//
	// Deconstructor for HC_PROCESS_INFORMATIONW
	// Implemented in hcconstruct.c
	//
	HC_EXTERN_API VOID HCAPI HcDestroyProcessInformationW(PHC_PROCESS_INFORMATIONW o);

	//
	// Callback for HcProcessQueryByNameW
	//
	typedef BOOLEAN(CALLBACK* HC_PROCESS_CALLBACK_EVENTW)(HC_PROCESS_INFORMATIONW, LPARAM);

	//
	// Implemented in hcprocess.c
	//

	HC_EXTERN_API BOOLEAN HCAPI HcProcessIsWow64Ex(IN HANDLE hProcess);
	HC_EXTERN_API BOOLEAN HCAPI HcProcessIsWow64(IN DWORD dwProcessId);

	HC_EXTERN_API BOOLEAN HCAPI HcProcessExitCode(IN SIZE_T dwProcessId, IN LPDWORD lpExitCode);
	HC_EXTERN_API BOOLEAN HCAPI HcProcessExitCodeEx(IN HANDLE hProcess, IN LPDWORD lpExitCode);

	HC_EXTERN_API HANDLE HCAPI HcProcessOpen(SIZE_T dwProcessId, ACCESS_MASK DesiredAccess);

	HC_EXTERN_API BOOLEAN HCAPI HcProcessWriteMemory(HANDLE hProcess, LPVOID lpBaseAddress, CONST VOID* lpBuffer, SIZE_T nSize, PSIZE_T lpNumberOfBytesWritten);
	HC_EXTERN_API BOOLEAN HCAPI HcProcessReadMemory(IN HANDLE hProcess, IN LPCVOID lpBaseAddress, IN LPVOID lpBuffer, IN SIZE_T nSize, OUT SIZE_T* lpNumberOfBytesRead);

	HC_EXTERN_API HANDLE HCAPI HcProcessCreateThread(IN HANDLE hProcess, IN LPTHREAD_START_ROUTINE lpStartAddress, IN LPVOID lpParamater, IN DWORD dwCreationFlags);

	HC_EXTERN_API BOOLEAN HCAPI HcProcessReadNullifiedString(HANDLE hProcess, PUNICODE_STRING usStringIn, LPWSTR lpStringOut, SIZE_T lpSize);

	HC_EXTERN_API BOOLEAN HCAPI HcProcessLdrModuleToHighCallModule(IN HANDLE hProcess, IN PLDR_DATA_TABLE_ENTRY Module, OUT PHC_MODULE_INFORMATIONW phcModuleOut);

	HC_EXTERN_API BOOLEAN HCAPI HcProcessQueryInformationModule(IN HANDLE hProcess, IN HMODULE hModule OPTIONAL, OUT PHC_MODULE_INFORMATIONW phcModuleOut);

	HC_EXTERN_API BOOLEAN HCAPI HcProcessEnumModulesW(HANDLE hProcess, HC_MODULE_CALLBACK_EVENTW hcmCallback, LPARAM lParam);
	HC_EXTERN_API BOOLEAN HCAPI HcProcessEnumMappedImagesW(HANDLE ProcessHandle, HC_MODULE_CALLBACK_EVENTW hcmCallback, LPARAM lParam);

	HC_EXTERN_API BOOLEAN HCAPI HcProcessReady(SIZE_T dwProcessId);
	HC_EXTERN_API BOOLEAN HCAPI HcProcessReadyEx(HANDLE hProcess);

	HC_EXTERN_API BOOLEAN HCAPI HcProcessSuspend(SIZE_T dwProcessId);
	HC_EXTERN_API BOOLEAN HCAPI HcProcessSuspendEx(HANDLE hProcess);

	HC_EXTERN_API BOOLEAN HCAPI HcProcessResume(SIZE_T dwProcessId);
	HC_EXTERN_API BOOLEAN HCAPI HcProcessResumeEx(HANDLE hProcess);

	HC_EXTERN_API SIZE_T HCAPI HcProcessModuleFileName(HANDLE hProcess, LPVOID lpv, LPWSTR lpFilename, DWORD nSize);

	HC_EXTERN_API BOOLEAN HCAPI HcProcessQueryByNameW(LPCWSTR lpProcessName, HC_PROCESS_CALLBACK_EVENTW Callback, LPARAM lParam);
	HC_EXTERN_API BOOLEAN HCAPI HcProcessQueryByNameExW(LPCWSTR lpProcessName, HC_PROCESS_CALLBACK_EVENT_EXW hcpCallback, LPARAM lParam);

	HC_EXTERN_API BOOLEAN HCAPI HcProcessSetPrivilegeA(HANDLE hProcess, LPCSTR Privilege,  BOOLEAN bEnablePrivilege);
	HC_EXTERN_API BOOLEAN HCAPI HcProcessSetPrivilegeW(HANDLE hProcess, LPCWSTR Privilege, BOOLEAN bEnablePrivilege);

	HC_EXTERN_API BOOLEAN HCAPI HcProcessGetPeb(HANDLE hProcess, PPEB pPeb);
	HC_EXTERN_API BOOLEAN HCAPI HcProcessGetCommandLineW(HANDLE hProcess, LPWSTR lpszCommandline, BOOLEAN bAlloc);
	HC_EXTERN_API BOOLEAN HCAPI HcProcessGetCurrentDirectoryW(HANDLE hProcess, LPWSTR szDirectory, PSIZE_T ptOutSize);
	HC_EXTERN_API BOOLEAN HCAPI HcProcessGetCurrentDirectoryA(HANDLE hProcess, LPSTR szDirectory);

#if defined (__cplusplus)
}
#endif

#endif