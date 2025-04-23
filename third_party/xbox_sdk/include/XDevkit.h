

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Thu Sep 05 16:44:27 2013
 */
/* Compiler settings for ..\xdevkit.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __xdevkit_h__
#define __xdevkit_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IXboxManager_FWD_DEFINED__
#define __IXboxManager_FWD_DEFINED__
typedef interface IXboxManager IXboxManager;
#endif 	/* __IXboxManager_FWD_DEFINED__ */


#ifndef __IXboxExecutableInfo_FWD_DEFINED__
#define __IXboxExecutableInfo_FWD_DEFINED__
typedef interface IXboxExecutableInfo IXboxExecutableInfo;
#endif 	/* __IXboxExecutableInfo_FWD_DEFINED__ */


#ifndef __IXboxExecutableDatabase_FWD_DEFINED__
#define __IXboxExecutableDatabase_FWD_DEFINED__
typedef interface IXboxExecutableDatabase IXboxExecutableDatabase;
#endif 	/* __IXboxExecutableDatabase_FWD_DEFINED__ */


#ifndef __IXboxConsole_FWD_DEFINED__
#define __IXboxConsole_FWD_DEFINED__
typedef interface IXboxConsole IXboxConsole;
#endif 	/* __IXboxConsole_FWD_DEFINED__ */


#ifndef __IXboxConsoles_FWD_DEFINED__
#define __IXboxConsoles_FWD_DEFINED__
typedef interface IXboxConsoles IXboxConsoles;
#endif 	/* __IXboxConsoles_FWD_DEFINED__ */


#ifndef __IXboxFile_FWD_DEFINED__
#define __IXboxFile_FWD_DEFINED__
typedef interface IXboxFile IXboxFile;
#endif 	/* __IXboxFile_FWD_DEFINED__ */


#ifndef __IXboxFiles_FWD_DEFINED__
#define __IXboxFiles_FWD_DEFINED__
typedef interface IXboxFiles IXboxFiles;
#endif 	/* __IXboxFiles_FWD_DEFINED__ */


#ifndef __IXboxUser_FWD_DEFINED__
#define __IXboxUser_FWD_DEFINED__
typedef interface IXboxUser IXboxUser;
#endif 	/* __IXboxUser_FWD_DEFINED__ */


#ifndef __IXboxUsers_FWD_DEFINED__
#define __IXboxUsers_FWD_DEFINED__
typedef interface IXboxUsers IXboxUsers;
#endif 	/* __IXboxUsers_FWD_DEFINED__ */


#ifndef __IXboxDebugTarget_FWD_DEFINED__
#define __IXboxDebugTarget_FWD_DEFINED__
typedef interface IXboxDebugTarget IXboxDebugTarget;
#endif 	/* __IXboxDebugTarget_FWD_DEFINED__ */


#ifndef __IXboxAutomation_FWD_DEFINED__
#define __IXboxAutomation_FWD_DEFINED__
typedef interface IXboxAutomation IXboxAutomation;
#endif 	/* __IXboxAutomation_FWD_DEFINED__ */


#ifndef __IXboxModule_FWD_DEFINED__
#define __IXboxModule_FWD_DEFINED__
typedef interface IXboxModule IXboxModule;
#endif 	/* __IXboxModule_FWD_DEFINED__ */


#ifndef __IXboxModules_FWD_DEFINED__
#define __IXboxModules_FWD_DEFINED__
typedef interface IXboxModules IXboxModules;
#endif 	/* __IXboxModules_FWD_DEFINED__ */


#ifndef __IXboxExecutable_FWD_DEFINED__
#define __IXboxExecutable_FWD_DEFINED__
typedef interface IXboxExecutable IXboxExecutable;
#endif 	/* __IXboxExecutable_FWD_DEFINED__ */


#ifndef __IXboxSection_FWD_DEFINED__
#define __IXboxSection_FWD_DEFINED__
typedef interface IXboxSection IXboxSection;
#endif 	/* __IXboxSection_FWD_DEFINED__ */


#ifndef __IXboxSections_FWD_DEFINED__
#define __IXboxSections_FWD_DEFINED__
typedef interface IXboxSections IXboxSections;
#endif 	/* __IXboxSections_FWD_DEFINED__ */


#ifndef __IXboxThread_FWD_DEFINED__
#define __IXboxThread_FWD_DEFINED__
typedef interface IXboxThread IXboxThread;
#endif 	/* __IXboxThread_FWD_DEFINED__ */


#ifndef __IXboxThreads_FWD_DEFINED__
#define __IXboxThreads_FWD_DEFINED__
typedef interface IXboxThreads IXboxThreads;
#endif 	/* __IXboxThreads_FWD_DEFINED__ */


#ifndef __IXboxStackFrame_FWD_DEFINED__
#define __IXboxStackFrame_FWD_DEFINED__
typedef interface IXboxStackFrame IXboxStackFrame;
#endif 	/* __IXboxStackFrame_FWD_DEFINED__ */


#ifndef __IXboxMemoryRegions_FWD_DEFINED__
#define __IXboxMemoryRegions_FWD_DEFINED__
typedef interface IXboxMemoryRegions IXboxMemoryRegions;
#endif 	/* __IXboxMemoryRegions_FWD_DEFINED__ */


#ifndef __IXboxMemoryRegion_FWD_DEFINED__
#define __IXboxMemoryRegion_FWD_DEFINED__
typedef interface IXboxMemoryRegion IXboxMemoryRegion;
#endif 	/* __IXboxMemoryRegion_FWD_DEFINED__ */


#ifndef __IXboxEventInfo_FWD_DEFINED__
#define __IXboxEventInfo_FWD_DEFINED__
typedef interface IXboxEventInfo IXboxEventInfo;
#endif 	/* __IXboxEventInfo_FWD_DEFINED__ */


#ifndef __XboxEvents_FWD_DEFINED__
#define __XboxEvents_FWD_DEFINED__
typedef interface XboxEvents XboxEvents;
#endif 	/* __XboxEvents_FWD_DEFINED__ */


#ifndef __IXboxEvents_FWD_DEFINED__
#define __IXboxEvents_FWD_DEFINED__
typedef interface IXboxEvents IXboxEvents;
#endif 	/* __IXboxEvents_FWD_DEFINED__ */


#ifndef __IXboxManager_FWD_DEFINED__
#define __IXboxManager_FWD_DEFINED__
typedef interface IXboxManager IXboxManager;
#endif 	/* __IXboxManager_FWD_DEFINED__ */


#ifndef __IXboxConsole_FWD_DEFINED__
#define __IXboxConsole_FWD_DEFINED__
typedef interface IXboxConsole IXboxConsole;
#endif 	/* __IXboxConsole_FWD_DEFINED__ */


#ifndef __IXboxConsoles_FWD_DEFINED__
#define __IXboxConsoles_FWD_DEFINED__
typedef interface IXboxConsoles IXboxConsoles;
#endif 	/* __IXboxConsoles_FWD_DEFINED__ */


#ifndef __IXboxFile_FWD_DEFINED__
#define __IXboxFile_FWD_DEFINED__
typedef interface IXboxFile IXboxFile;
#endif 	/* __IXboxFile_FWD_DEFINED__ */


#ifndef __IXboxFiles_FWD_DEFINED__
#define __IXboxFiles_FWD_DEFINED__
typedef interface IXboxFiles IXboxFiles;
#endif 	/* __IXboxFiles_FWD_DEFINED__ */


#ifndef __IXboxUser_FWD_DEFINED__
#define __IXboxUser_FWD_DEFINED__
typedef interface IXboxUser IXboxUser;
#endif 	/* __IXboxUser_FWD_DEFINED__ */


#ifndef __IXboxUsers_FWD_DEFINED__
#define __IXboxUsers_FWD_DEFINED__
typedef interface IXboxUsers IXboxUsers;
#endif 	/* __IXboxUsers_FWD_DEFINED__ */


#ifndef __IXboxDebugTarget_FWD_DEFINED__
#define __IXboxDebugTarget_FWD_DEFINED__
typedef interface IXboxDebugTarget IXboxDebugTarget;
#endif 	/* __IXboxDebugTarget_FWD_DEFINED__ */


#ifndef __IXboxModule_FWD_DEFINED__
#define __IXboxModule_FWD_DEFINED__
typedef interface IXboxModule IXboxModule;
#endif 	/* __IXboxModule_FWD_DEFINED__ */


#ifndef __IXboxModules_FWD_DEFINED__
#define __IXboxModules_FWD_DEFINED__
typedef interface IXboxModules IXboxModules;
#endif 	/* __IXboxModules_FWD_DEFINED__ */


#ifndef __IXboxSection_FWD_DEFINED__
#define __IXboxSection_FWD_DEFINED__
typedef interface IXboxSection IXboxSection;
#endif 	/* __IXboxSection_FWD_DEFINED__ */


#ifndef __IXboxSections_FWD_DEFINED__
#define __IXboxSections_FWD_DEFINED__
typedef interface IXboxSections IXboxSections;
#endif 	/* __IXboxSections_FWD_DEFINED__ */


#ifndef __IXboxThread_FWD_DEFINED__
#define __IXboxThread_FWD_DEFINED__
typedef interface IXboxThread IXboxThread;
#endif 	/* __IXboxThread_FWD_DEFINED__ */


#ifndef __IXboxThreads_FWD_DEFINED__
#define __IXboxThreads_FWD_DEFINED__
typedef interface IXboxThreads IXboxThreads;
#endif 	/* __IXboxThreads_FWD_DEFINED__ */


#ifndef __IXboxStackFrame_FWD_DEFINED__
#define __IXboxStackFrame_FWD_DEFINED__
typedef interface IXboxStackFrame IXboxStackFrame;
#endif 	/* __IXboxStackFrame_FWD_DEFINED__ */


#ifndef __IXboxMemoryRegions_FWD_DEFINED__
#define __IXboxMemoryRegions_FWD_DEFINED__
typedef interface IXboxMemoryRegions IXboxMemoryRegions;
#endif 	/* __IXboxMemoryRegions_FWD_DEFINED__ */


#ifndef __IXboxMemoryRegion_FWD_DEFINED__
#define __IXboxMemoryRegion_FWD_DEFINED__
typedef interface IXboxMemoryRegion IXboxMemoryRegion;
#endif 	/* __IXboxMemoryRegion_FWD_DEFINED__ */


#ifndef __IXboxEventInfo_FWD_DEFINED__
#define __IXboxEventInfo_FWD_DEFINED__
typedef interface IXboxEventInfo IXboxEventInfo;
#endif 	/* __IXboxEventInfo_FWD_DEFINED__ */


#ifndef __XboxEvents_FWD_DEFINED__
#define __XboxEvents_FWD_DEFINED__
typedef interface XboxEvents XboxEvents;
#endif 	/* __XboxEvents_FWD_DEFINED__ */


#ifndef __IXboxEvents_FWD_DEFINED__
#define __IXboxEvents_FWD_DEFINED__
typedef interface IXboxEvents IXboxEvents;
#endif 	/* __IXboxEvents_FWD_DEFINED__ */


#ifndef __XboxConsole_FWD_DEFINED__
#define __XboxConsole_FWD_DEFINED__

#ifdef __cplusplus
typedef class XboxConsole XboxConsole;
#else
typedef struct XboxConsole XboxConsole;
#endif /* __cplusplus */

#endif 	/* __XboxConsole_FWD_DEFINED__ */


#ifndef __XboxManager_FWD_DEFINED__
#define __XboxManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class XboxManager XboxManager;
#else
typedef struct XboxManager XboxManager;
#endif /* __cplusplus */

#endif 	/* __XboxManager_FWD_DEFINED__ */


#ifndef __XboxExecutableDatabase_FWD_DEFINED__
#define __XboxExecutableDatabase_FWD_DEFINED__

#ifdef __cplusplus
typedef class XboxExecutableDatabase XboxExecutableDatabase;
#else
typedef struct XboxExecutableDatabase XboxExecutableDatabase;
#endif /* __cplusplus */

#endif 	/* __XboxExecutableDatabase_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_xdevkit_0000 */
/* [local] */ 






















#define FACILITY_XDEVKIT 0x2da
#ifndef MAKE_HRESULT
#define MAKE_HRESULT(sev,fac,code) ((HRESULT)(((unsigned long)sev<<31)|((unsigned long)fac<<16)|((unsigned long)code)))
#endif
#define MAKE_E_XDEVKIT(code) MAKE_HRESULT(1, FACILITY_XDEVKIT, code)
#define MAKE_S_XDEVKIT(code) MAKE_HRESULT(0, FACILITY_XDEVKIT, code)
#define S_XDEVKIT_NOERR                              MAKE_S_XDEVKIT(0)
#define S_XDEVKIT_CONNECTED                          MAKE_S_XDEVKIT(1)
#define S_XDEVKIT_MULTIRESPONSE                      MAKE_S_XDEVKIT(2)
#define S_XDEVKIT_BINRESPONSE                        MAKE_S_XDEVKIT(3)
#define S_XDEVKIT_READYFORBIN                        MAKE_S_XDEVKIT(4)
#define S_XDEVKIT_DEDICATED                          MAKE_S_XDEVKIT(5)
#define S_XDEVKIT_PROFILERESTARTED                   MAKE_S_XDEVKIT(6)
#define S_XDEVKIT_FASTCAPENABLED                     MAKE_S_XDEVKIT(7)
#define S_XDEVKIT_CALLCAPENABLED                     MAKE_S_XDEVKIT(8)
#define E_XDEVKIT_UNDEFINED                          MAKE_E_XDEVKIT(0)
#define E_XDEVKIT_MAXCONNECT                         MAKE_E_XDEVKIT(1)
#define E_XDEVKIT_NOSUCHFILE                         MAKE_E_XDEVKIT(2)
#define E_XDEVKIT_NOMODULE                           MAKE_E_XDEVKIT(3)
#define E_XDEVKIT_MEMUNMAPPED                        MAKE_E_XDEVKIT(4)
#define E_XDEVKIT_NOTHREAD                           MAKE_E_XDEVKIT(5)
#define E_XDEVKIT_CLOCKNOTSET                        MAKE_E_XDEVKIT(6)
#define E_XDEVKIT_INVALIDCMD                         MAKE_E_XDEVKIT(7)
#define E_XDEVKIT_NOTSTOPPED                         MAKE_E_XDEVKIT(8)
#define E_XDEVKIT_MUSTCOPY                           MAKE_E_XDEVKIT(9)
#define E_XDEVKIT_ALREADYEXISTS                      MAKE_E_XDEVKIT(10)
#define E_XDEVKIT_DIRNOTEMPTY                        MAKE_E_XDEVKIT(11)
#define E_XDEVKIT_BADFILENAME                        MAKE_E_XDEVKIT(12)
#define E_XDEVKIT_CANNOTCREATE                       MAKE_E_XDEVKIT(13)
#define E_XDEVKIT_CANNOTACCESS                       MAKE_E_XDEVKIT(14)
#define E_XDEVKIT_DEVICEFULL                         MAKE_E_XDEVKIT(15)
#define E_XDEVKIT_NOTDEBUGGABLE                      MAKE_E_XDEVKIT(16)
#define E_XDEVKIT_BADCOUNTTYPE                       MAKE_E_XDEVKIT(17)
#define E_XDEVKIT_COUNTUNAVAILABLE                   MAKE_E_XDEVKIT(18)
#define E_XDEVKIT_NOTLOCKED                          MAKE_E_XDEVKIT(20)
#define E_XDEVKIT_KEYXCHG                            MAKE_E_XDEVKIT(21)
#define E_XDEVKIT_MUSTBEDEDICATED                    MAKE_E_XDEVKIT(22)
#define E_XDEVKIT_INVALIDARG                         MAKE_E_XDEVKIT(23)
#define E_XDEVKIT_PROFILENOTSTARTED                  MAKE_E_XDEVKIT(24)
#define E_XDEVKIT_PROFILEALREADYSTARTED              MAKE_E_XDEVKIT(25)
#define E_XDEVKIT_ALREADYSTOPPED                     MAKE_E_XDEVKIT(26)
#define E_XDEVKIT_FASTCAPNOTENABLED                  MAKE_E_XDEVKIT(27)
#define E_XDEVKIT_NOMEMORY                           MAKE_E_XDEVKIT(28)
#define E_XDEVKIT_TIMEOUT                            MAKE_E_XDEVKIT(29)
#define E_XDEVKIT_NOSUCHPATH                         MAKE_E_XDEVKIT(30)
#define E_XDEVKIT_INVALID_SCREEN_INPUT_FORMAT        MAKE_E_XDEVKIT(31)
#define E_XDEVKIT_INVALID_SCREEN_OUTPUT_FORMAT       MAKE_E_XDEVKIT(32)
#define E_XDEVKIT_CALLCAPNOTENABLED                  MAKE_E_XDEVKIT(33)
#define E_XDEVKIT_INVALIDCAPCFG                      MAKE_E_XDEVKIT(34)
#define E_XDEVKIT_CAPNOTENABLED                      MAKE_E_XDEVKIT(35)
#define E_XDEVKIT_TOOBIGJUMP                         MAKE_E_XDEVKIT(36)
#define E_XDEVKIT_OUTPUTBUFFERTOOSMALL               MAKE_E_XDEVKIT(38)
#define E_XDEVKIT_PROFILEREBOOT                      MAKE_E_XDEVKIT(39)
#define E_XDEVKIT_MAXDURATIONEXCEEDED                MAKE_E_XDEVKIT(41)
#define E_XDEVKIT_INVALIDSTATE                       MAKE_E_XDEVKIT(42)
#define E_XDEVKIT_MAXEXTENSIONS                      MAKE_E_XDEVKIT(43)
#define E_XDEVKIT_PMCSESSIONALREADYACTIVE            MAKE_E_XDEVKIT(44)
#define E_XDEVKIT_PMCSESSIONNOTACTIVE                MAKE_E_XDEVKIT(45)
#define E_XDEVKIT_LINE_TOO_LONG                      MAKE_E_XDEVKIT(46)
#define E_XDEVKIT_D3D_DEBUG_COMMAND_NOT_IMPLEMENTED  MAKE_E_XDEVKIT(0x50)
#define E_XDEVKIT_D3D_INVALID_SURFACE                MAKE_E_XDEVKIT(0x51)
#define E_XDEVKIT_CANNOTCONNECT                      MAKE_E_XDEVKIT(0x100)
#define E_XDEVKIT_CONNECTIONLOST                     MAKE_E_XDEVKIT(0x101)
#define E_XDEVKIT_FILEERROR                          MAKE_E_XDEVKIT(0x103)
#define E_XDEVKIT_ENDOFLIST                          MAKE_E_XDEVKIT(0x104)
#define E_XDEVKIT_BUFFER_TOO_SMALL                   MAKE_E_XDEVKIT(0x105)
#define E_XDEVKIT_NOTXBEFILE                         MAKE_E_XDEVKIT(0x106)
#define E_XDEVKIT_MEMSETINCOMPLETE                   MAKE_E_XDEVKIT(0x107)
#define E_XDEVKIT_NOXBOXNAME                         MAKE_E_XDEVKIT(0x108)
#define E_XDEVKIT_NOERRORSTRING                      MAKE_E_XDEVKIT(0x109)
#define E_XDEVKIT_INVALIDSTATUS                      MAKE_E_XDEVKIT(0x10A)
#define E_XDEVKIT_TASK_PENDING                       MAKE_E_XDEVKIT(0x150)
#define FACILITY_XEXECDB 0x2da
#define MAKE_E_XEXECDB(code) MAKE_HRESULT(1, FACILITY_XEXECDB, code)
#define MAKE_S_XEXECDB(code) MAKE_HRESULT(0, FACILITY_XEXECDB, code)
#define E_XEXECDB_UNRECOGNIZED_FILE                  MAKE_E_XEXECDB(0x400)
#define E_XEXECDB_WRONG_VERSION                      MAKE_E_XEXECDB(0x401)
typedef struct XBOX_PROCESS_INFO
    {
    DWORD ProcessId;
    BSTR ProgramName;
    } 	XBOX_PROCESS_INFO;

typedef struct XBOX_PROCESS_INFO *PXBOX_PROCESS_INFO;

namespace eXboxAccessFlags {
/* [v1_enum] */ 
enum XboxAccessFlags
    {	Read	= 1,
	Write	= 2,
	Control	= 4,
	Configure	= 8,
	Manage	= 16
    } ;
}
/*
typedef enum XboxAccessFlags _XboxAccessFlags;

*/ typedef int _XboxAccessFlags;
typedef struct XBOX_USER
    {
    BSTR UserName;
    _XboxAccessFlags Access;
    } 	XBOX_USER;

typedef struct XBOX_USER *PXBOX_USER;

namespace eXboxModuleInfoFlags {
/* [v1_enum] */ 
enum XboxModuleInfoFlags
    {	Main	= 1,
	Tls	= 2,
	Dll	= 4
    } ;
}
/*
typedef enum XboxModuleInfoFlags _XboxModuleInfoFlags;

*/ typedef int _XboxModuleInfoFlags;
typedef struct XBOX_MODULE_INFO
    {
    BSTR Name;
    BSTR FullName;
    DWORD BaseAddress;
    DWORD Size;
    DWORD TimeStamp;
    DWORD CheckSum;
    _XboxModuleInfoFlags Flags;
    } 	XBOX_MODULE_INFO;

typedef struct XBOX_MODULE_INFO *PXBOX_MODULE_INFO;

namespace eXboxSectionInfoFlags {
/* [v1_enum] */ 
enum XboxSectionInfoFlags
    {	Loaded	= 1,
	Readable	= 2,
	Writeable	= 4,
	Executable	= 8,
	Uninitialized	= 16
    } ;
}
/*
typedef enum XboxSectionInfoFlags _XboxSectionInfoFlags;

*/ typedef int _XboxSectionInfoFlags;
typedef struct XBOX_SECTION_INFO
    {
    BSTR Name;
    DWORD BaseAddress;
    DWORD Size;
    DWORD Index;
    _XboxSectionInfoFlags Flags;
    } 	XBOX_SECTION_INFO;

typedef struct XBOX_SECTION_INFO *PXBOX_SECTION_INFO;

typedef struct XBOX_THREAD_INFO
    {
    DWORD ThreadId;
    DWORD SuspendCount;
    DWORD Priority;
    DWORD TlsBase;
    DWORD StartAddress;
    DWORD StackBase;
    DWORD StackLimit;
    DWORD StackSlackSpace;
    VARIANT CreateTime;
    BSTR Name;
    } 	XBOX_THREAD_INFO;

typedef struct XBOX_THREAD_INFO *PXBOX_THREAD_INFO;

namespace eXboxFunctionType {
/* [v1_enum] */ 
enum XboxFunctionType
    {	NoPData	= 0xffffffff,
	SaveMillicode	= 0,
	NoHandler	= 1,
	RestoreMillicode	= 2,
	Handler	= 3
    } ;
}
/*
typedef enum XboxFunctionType _XboxFunctionType;

*/ typedef eXboxFunctionType::XboxFunctionType _XboxFunctionType;
typedef struct XBOX_FUNCTION_INFO
    {
    _XboxFunctionType FunctionType;
    DWORD BeginAddress;
    DWORD PrologEndAddress;
    DWORD FunctionEndAddress;
    } 	XBOX_FUNCTION_INFO;

typedef struct XBOX_FUNCTION_INFO *PXBOX_FUNCTION_INFO;

namespace eXboxDebugEventType {
/* [v1_enum] */ 
enum XboxDebugEventType
    {	NoEvent	= 0,
	ExecutionBreak	= NoEvent + 1,
	DebugString	= ExecutionBreak + 1,
	ExecStateChange	= DebugString + 1,
	SingleStep	= ExecStateChange + 1,
	ModuleLoad	= SingleStep + 1,
	ModuleUnload	= ModuleLoad + 1,
	ThreadCreate	= ModuleUnload + 1,
	ThreadDestroy	= ThreadCreate + 1,
	Exception	= ThreadDestroy + 1,
	AssertionFailed	= Exception + 1,
	AssertionFailedEx	= AssertionFailed + 1,
	DataBreak	= AssertionFailedEx + 1,
	RIP	= DataBreak + 1,
	SectionLoad	= RIP + 1,
	SectionUnload	= SectionLoad + 1,
	StackTrace	= SectionUnload + 1,
	FiberCreate	= StackTrace + 1,
	FiberDestroy	= FiberCreate + 1,
	BugCheck	= FiberDestroy + 1,
	PgoModuleStartup	= BugCheck + 1
    } ;
}
/*
typedef enum XboxDebugEventType _XboxDebugEventType;

*/ typedef eXboxDebugEventType::XboxDebugEventType _XboxDebugEventType;
namespace eXboxExecutionState {
/* [v1_enum] */ 
enum XboxExecutionState
    {	Stopped	= 0,
	Running	= Stopped + 1,
	Rebooting	= Running + 1,
	Pending	= Rebooting + 1,
	RebootingTitle	= Pending + 1,
	PendingTitle	= RebootingTitle + 1
    } ;
}
/*
typedef enum XboxExecutionState _XboxExecutionState;

*/ typedef eXboxExecutionState::XboxExecutionState _XboxExecutionState;
// Must match DMSTOP_ constants
namespace eXboxStopOnFlags {
/* [v1_enum] */ 
enum XboxStopOnFlags
    {	OnThreadCreate	= 0x1,
	OnFirstChanceException	= 0x2,
	OnDebugString	= 0x4,
	OnStackTrace	= 0x8,
	OnModuleLoad	= 0x10,
	OnTitleLaunch	= 0x20,
	OnPgoModuleStartup	= 0x40
    } ;
}
/*
typedef enum XboxStopOnFlags _XboxStopOnFlags;

*/ typedef int _XboxStopOnFlags;
namespace eXboxRebootFlags {
/* [v1_enum] */ 
enum XboxRebootFlags
    {	Title	= 0,
	Wait	= 1,
	Cold	= 2,
	Warm	= 4,
	Stop	= 8
    } ;
#pragma deprecated(Warm)
}
/*
typedef enum XboxRebootFlags _XboxRebootFlags;

*/ typedef int _XboxRebootFlags;
namespace eXboxExceptionFlags {
/* [v1_enum] */ 
enum XboxExceptionFlags
    {	Noncontinuable	= 1,
	FirstChance	= 2
    } ;
}
/*
typedef enum XboxExceptionFlags _XboxExceptionFlags;

*/ typedef int _XboxExceptionFlags;
typedef struct XBOX_EVENT_INFO
    {
    _XboxDebugEventType Event;
    VARIANT_BOOL IsThreadStopped;
    IXboxThread *Thread;
    IXboxModule *Module;
    IXboxSection *Section;
    _XboxExecutionState ExecState;
    BSTR Message;
    DWORD Code;
    DWORD Address;
    _XboxExceptionFlags Flags;
    DWORD ParameterCount;
    DWORD Parameters[ 15 ];
    } 	XBOX_EVENT_INFO;

typedef struct XBOX_EVENT_INFO *PXBOX_EVENT_INFO;

namespace eXboxBreakpointType {
/* [v1_enum] */ 
enum XboxBreakpointType
    {	NoBreakpoint	= 0,
	OnWrite	= NoBreakpoint + 1,
	OnRead	= OnWrite + 1,
	OnExecuteHW	= OnRead + 1,
	OnExecute	= OnExecuteHW + 1
    } ;
}
/*
typedef enum XboxBreakpointType _XboxBreakpointType;

*/ typedef eXboxBreakpointType::XboxBreakpointType _XboxBreakpointType;
namespace eXboxSelectConsoleFlags {
/* [v1_enum] */ 
enum XboxSelectConsoleFlags
    {	NoPromptIfDefaultExists	= 0,
	NoPromptIfOnlyOne	= NoPromptIfDefaultExists + 1,
	FilterByAccess	= NoPromptIfOnlyOne + 1
    } ;
}
/*
typedef enum XboxSelectConsoleFlags _XboxSelectConsoleFlags;

*/ typedef int _XboxSelectConsoleFlags;
namespace eXboxDebugConnectFlags{
/* [v1_enum] */ 
enum XboxDebugConnectFlags
    {	Force	= 0x1,
	MonitorOnly	= 0x2
    } ;
}
/*
typedef enum XboxDebugConnectFlags _XboxDebugConnectFlags;

*/ typedef int _XboxDebugConnectFlags;
namespace eXboxDumpFlags{
/* [v1_enum] */ 
enum XboxDumpFlags
    {	Normal	= 0,
	WithDataSegs	= 0x1,
	WithFullMemory	= 0x2,
	WithHandleData	= 0x4,
	FilterMemory	= 0x8,
	ScanMemory	= 0x10,
	WithUnloadedModules	= 0x20,
	WithIndirectlyReferencedMemory	= 0x40,
	FilterModulePaths	= 0x80,
	WithProcessThreadData	= 0x100,
	WithPrivateReadWriteMemory	= 0x200
    } ;
}
/*
typedef enum XboxDumpFlags _XboxDumpFlags;

*/ typedef int _XboxDumpFlags;
namespace eXboxDumpMode{
/* [v1_enum] */ 
enum XboxDumpMode
    {	Smart	= 0,
	Enabled	= 0x1,
	Disabled	= 0x2
    } ;
}
/*
typedef enum XboxDumpMode _XboxDumpMode;

*/ typedef eXboxDumpMode::XboxDumpMode _XboxDumpMode;
namespace eXboxEventDeferFlags {
/* [v1_enum] */ 
enum XboxEventDeferFlags
    {	CanDeferExecutionBreak	= 0x1,
	CanDeferDebugString	= 0x2,
	CanDeferSingleStep	= 0x4,
	CanDeferAssertionFailed	= 0x8,
	CanDeferAssertionFailedEx	= 0x10,
	CanDeferDataBreak	= 0x20,
	CanDeferRIP	= 0x40
    } ;
}
/*
typedef enum XboxEventDeferFlags _XboxEventDeferFlags;

*/ typedef int _XboxEventDeferFlags;
namespace eXboxDumpReportFlags {
/* [v1_enum] */ 
enum XboxDumpReportFlags
    {	PromptToReport	= 0,
	AlwaysReport	= 0x1,
	NeverReport	= 0x2,
	ReportGroup	= 0xf,
	LocalDestination	= 0,
	RemoteDestination	= 0x10,
	DestinationGroup	= 0xf,
	FormatFullHeap	= 0,
	FormatPartialHeap	= 0x100,
	FormatNoHeap	= 0x200,
	FormatRetail	= 0x400,
	FormatGroup	= 0xf00
    } ;
}
/*
typedef enum XboxDumpReportFlags _XboxDumpReportFlags;

*/ typedef int _XboxDumpReportFlags;
namespace eXboxConsoleType {
/* [v1_enum] */ 
enum XboxConsoleType
    {	DevelopmentKit	= 0,
	TestKit	= 1,
	ReviewerKit	= 2
    } ;
}
/*
typedef enum XboxConsoleType _XboxConsoleType;

*/ typedef eXboxConsoleType::XboxConsoleType _XboxConsoleType;
namespace eXboxConsoleFeatures {
/* [v1_enum] */ 
enum XboxConsoleFeatures
    {	Debugging	= 1,
	SecondaryNIC	= 2,
	GB_RAM	= 4
    } ;
}
/*
typedef enum XboxConsoleFeatures _XboxConsoleFeatures;

*/ typedef int _XboxConsoleFeatures;
typedef struct XBOX_DUMP_SETTINGS
    {
    _XboxDumpReportFlags Flags;
    BSTR NetworkPath;
    } 	XBOX_DUMP_SETTINGS;

typedef struct XBOX_DUMP_SETTINGS *PXBOX_DUMP_SETTINGS;



extern RPC_IF_HANDLE __MIDL_itf_xdevkit_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_xdevkit_0000_v0_0_s_ifspec;

#ifndef __IXboxManager_INTERFACE_DEFINED__
#define __IXboxManager_INTERFACE_DEFINED__

/* interface IXboxManager */
/* [helpstring][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c4c077e9-bf83-4657-ad8b-1e5abb9bb9a8")
    IXboxManager : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultConsole( 
            /* [retval][out] */ BSTR *DefaultXbox) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultConsole( 
            /* [in] */ BSTR DefaultXbox) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Consoles( 
            /* [retval][out] */ IXboxConsoles **Consoles) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AddConsole( 
            /* [in] */ BSTR Xbox) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveConsole( 
            /* [in] */ BSTR Xbox) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OpenConsole( 
            /* [in] */ BSTR XboxName,
            /* [retval][out] */ IXboxConsole **Console) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OpenDumpFile( 
            /* [in] */ BSTR FileName,
            /* [in] */ BSTR ImageSearchPath,
            /* [retval][out] */ IXboxDebugTarget **DebugTarget) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SelectConsole( 
            /* [in] */ LONG ParentWindow,
            /* [out] */ BSTR *SelectedXbox,
            /* [in] */ _XboxAccessFlags DesiredAccess,
            /* [in] */ _XboxSelectConsoleFlags Flags) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RunAddConsoleWizard( 
            /* [in] */ LONG ParentWindow,
            /* [in] */ VARIANT_BOOL Modal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OpenWindowsExplorer( 
            /* [in] */ BSTR XboxName,
            /* [in] */ BSTR Path) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TranslateError( 
            /* [in] */ HRESULT hr,
            /* [retval][out] */ BSTR *ErrorString) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SystemSymbolServerPath( 
            /* [retval][out] */ BSTR *SymbolServerPath) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SelectConsoleEx( 
            /* [in] */ LONGLONG ParentWindow,
            /* [out] */ BSTR *SelectedXbox,
            /* [in] */ _XboxAccessFlags DesiredAccess,
            /* [in] */ _XboxSelectConsoleFlags Flags) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RunAddConsoleWizardEx( 
            /* [in] */ LONGLONG ParentWindow,
            /* [in] */ VARIANT_BOOL Modal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxManager * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxManager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxManager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxManager * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultConsole )( 
            IXboxManager * This,
            /* [retval][out] */ BSTR *DefaultXbox);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultConsole )( 
            IXboxManager * This,
            /* [in] */ BSTR DefaultXbox);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Consoles )( 
            IXboxManager * This,
            /* [retval][out] */ IXboxConsoles **Consoles);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AddConsole )( 
            IXboxManager * This,
            /* [in] */ BSTR Xbox);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RemoveConsole )( 
            IXboxManager * This,
            /* [in] */ BSTR Xbox);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OpenConsole )( 
            IXboxManager * This,
            /* [in] */ BSTR XboxName,
            /* [retval][out] */ IXboxConsole **Console);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OpenDumpFile )( 
            IXboxManager * This,
            /* [in] */ BSTR FileName,
            /* [in] */ BSTR ImageSearchPath,
            /* [retval][out] */ IXboxDebugTarget **DebugTarget);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SelectConsole )( 
            IXboxManager * This,
            /* [in] */ LONG ParentWindow,
            /* [out] */ BSTR *SelectedXbox,
            /* [in] */ _XboxAccessFlags DesiredAccess,
            /* [in] */ _XboxSelectConsoleFlags Flags);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RunAddConsoleWizard )( 
            IXboxManager * This,
            /* [in] */ LONG ParentWindow,
            /* [in] */ VARIANT_BOOL Modal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OpenWindowsExplorer )( 
            IXboxManager * This,
            /* [in] */ BSTR XboxName,
            /* [in] */ BSTR Path);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *TranslateError )( 
            IXboxManager * This,
            /* [in] */ HRESULT hr,
            /* [retval][out] */ BSTR *ErrorString);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SystemSymbolServerPath )( 
            IXboxManager * This,
            /* [retval][out] */ BSTR *SymbolServerPath);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SelectConsoleEx )( 
            IXboxManager * This,
            /* [in] */ LONGLONG ParentWindow,
            /* [out] */ BSTR *SelectedXbox,
            /* [in] */ _XboxAccessFlags DesiredAccess,
            /* [in] */ _XboxSelectConsoleFlags Flags);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RunAddConsoleWizardEx )( 
            IXboxManager * This,
            /* [in] */ LONGLONG ParentWindow,
            /* [in] */ VARIANT_BOOL Modal);
        
        END_INTERFACE
    } IXboxManagerVtbl;

    interface IXboxManager
    {
        CONST_VTBL struct IXboxManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxManager_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxManager_get_DefaultConsole(This,DefaultXbox)	\
    (This)->lpVtbl -> get_DefaultConsole(This,DefaultXbox)

#define IXboxManager_put_DefaultConsole(This,DefaultXbox)	\
    (This)->lpVtbl -> put_DefaultConsole(This,DefaultXbox)

#define IXboxManager_get_Consoles(This,Consoles)	\
    (This)->lpVtbl -> get_Consoles(This,Consoles)

#define IXboxManager_AddConsole(This,Xbox)	\
    (This)->lpVtbl -> AddConsole(This,Xbox)

#define IXboxManager_RemoveConsole(This,Xbox)	\
    (This)->lpVtbl -> RemoveConsole(This,Xbox)

#define IXboxManager_OpenConsole(This,XboxName,Console)	\
    (This)->lpVtbl -> OpenConsole(This,XboxName,Console)

#define IXboxManager_OpenDumpFile(This,FileName,ImageSearchPath,DebugTarget)	\
    (This)->lpVtbl -> OpenDumpFile(This,FileName,ImageSearchPath,DebugTarget)

#define IXboxManager_SelectConsole(This,ParentWindow,SelectedXbox,DesiredAccess,Flags)	\
    (This)->lpVtbl -> SelectConsole(This,ParentWindow,SelectedXbox,DesiredAccess,Flags)

#define IXboxManager_RunAddConsoleWizard(This,ParentWindow,Modal)	\
    (This)->lpVtbl -> RunAddConsoleWizard(This,ParentWindow,Modal)

#define IXboxManager_OpenWindowsExplorer(This,XboxName,Path)	\
    (This)->lpVtbl -> OpenWindowsExplorer(This,XboxName,Path)

#define IXboxManager_TranslateError(This,hr,ErrorString)	\
    (This)->lpVtbl -> TranslateError(This,hr,ErrorString)

#define IXboxManager_get_SystemSymbolServerPath(This,SymbolServerPath)	\
    (This)->lpVtbl -> get_SystemSymbolServerPath(This,SymbolServerPath)

#define IXboxManager_SelectConsoleEx(This,ParentWindow,SelectedXbox,DesiredAccess,Flags)	\
    (This)->lpVtbl -> SelectConsoleEx(This,ParentWindow,SelectedXbox,DesiredAccess,Flags)

#define IXboxManager_RunAddConsoleWizardEx(This,ParentWindow,Modal)	\
    (This)->lpVtbl -> RunAddConsoleWizardEx(This,ParentWindow,Modal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxManager_get_DefaultConsole_Proxy( 
    IXboxManager * This,
    /* [retval][out] */ BSTR *DefaultXbox);


void __RPC_STUB IXboxManager_get_DefaultConsole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxManager_put_DefaultConsole_Proxy( 
    IXboxManager * This,
    /* [in] */ BSTR DefaultXbox);


void __RPC_STUB IXboxManager_put_DefaultConsole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxManager_get_Consoles_Proxy( 
    IXboxManager * This,
    /* [retval][out] */ IXboxConsoles **Consoles);


void __RPC_STUB IXboxManager_get_Consoles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxManager_AddConsole_Proxy( 
    IXboxManager * This,
    /* [in] */ BSTR Xbox);


void __RPC_STUB IXboxManager_AddConsole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxManager_RemoveConsole_Proxy( 
    IXboxManager * This,
    /* [in] */ BSTR Xbox);


void __RPC_STUB IXboxManager_RemoveConsole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxManager_OpenConsole_Proxy( 
    IXboxManager * This,
    /* [in] */ BSTR XboxName,
    /* [retval][out] */ IXboxConsole **Console);


void __RPC_STUB IXboxManager_OpenConsole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxManager_OpenDumpFile_Proxy( 
    IXboxManager * This,
    /* [in] */ BSTR FileName,
    /* [in] */ BSTR ImageSearchPath,
    /* [retval][out] */ IXboxDebugTarget **DebugTarget);


void __RPC_STUB IXboxManager_OpenDumpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxManager_SelectConsole_Proxy( 
    IXboxManager * This,
    /* [in] */ LONG ParentWindow,
    /* [out] */ BSTR *SelectedXbox,
    /* [in] */ _XboxAccessFlags DesiredAccess,
    /* [in] */ _XboxSelectConsoleFlags Flags);


void __RPC_STUB IXboxManager_SelectConsole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxManager_RunAddConsoleWizard_Proxy( 
    IXboxManager * This,
    /* [in] */ LONG ParentWindow,
    /* [in] */ VARIANT_BOOL Modal);


void __RPC_STUB IXboxManager_RunAddConsoleWizard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxManager_OpenWindowsExplorer_Proxy( 
    IXboxManager * This,
    /* [in] */ BSTR XboxName,
    /* [in] */ BSTR Path);


void __RPC_STUB IXboxManager_OpenWindowsExplorer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxManager_TranslateError_Proxy( 
    IXboxManager * This,
    /* [in] */ HRESULT hr,
    /* [retval][out] */ BSTR *ErrorString);


void __RPC_STUB IXboxManager_TranslateError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxManager_get_SystemSymbolServerPath_Proxy( 
    IXboxManager * This,
    /* [retval][out] */ BSTR *SymbolServerPath);


void __RPC_STUB IXboxManager_get_SystemSymbolServerPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxManager_SelectConsoleEx_Proxy( 
    IXboxManager * This,
    /* [in] */ LONGLONG ParentWindow,
    /* [out] */ BSTR *SelectedXbox,
    /* [in] */ _XboxAccessFlags DesiredAccess,
    /* [in] */ _XboxSelectConsoleFlags Flags);


void __RPC_STUB IXboxManager_SelectConsoleEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxManager_RunAddConsoleWizardEx_Proxy( 
    IXboxManager * This,
    /* [in] */ LONGLONG ParentWindow,
    /* [in] */ VARIANT_BOOL Modal);


void __RPC_STUB IXboxManager_RunAddConsoleWizardEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxManager_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_xdevkit_0262 */
/* [local] */ 

namespace eXboxShareMode {
/* [v1_enum] */ 
enum XboxShareMode
    {	ShareNone	= 0,
	ShareRead	= 0x1,
	ShareWrite	= 0x2,
	ShareDelete	= 0x4
    } ;
}
/*
typedef enum XboxShareMode _XboxShareMode;

*/ typedef int _XboxShareMode;
namespace eXboxCreateDisposition {
/* [v1_enum] */ 
enum XboxCreateDisposition
    {	CreateNew	= 1,
	CreateAlways	= 2,
	OpenExisting	= 3,
	OpenAlways	= 4
    } ;
}
/*
typedef enum XboxCreateDisposition _XboxCreateDisposition;

*/ typedef eXboxCreateDisposition::XboxCreateDisposition _XboxCreateDisposition;


extern RPC_IF_HANDLE __MIDL_itf_xdevkit_0262_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_xdevkit_0262_v0_0_s_ifspec;

#ifndef __IXboxExecutableInfo_INTERFACE_DEFINED__
#define __IXboxExecutableInfo_INTERFACE_DEFINED__

/* interface IXboxExecutableInfo */
/* [helpstring][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxExecutableInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("978B90D1-1F44-4adc-B992-12AF5DBE16E2")
    IXboxExecutableInfo : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SymbolGuid( 
            /* [retval][out] */ BSTR *Guid) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_XboxExecutablePath( 
            /* [retval][out] */ BSTR *Path) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PortableExecutablePath( 
            /* [retval][out] */ BSTR *Path) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SymbolPath( 
            /* [retval][out] */ BSTR *Path) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PublicSymbolPath( 
            /* [retval][out] */ BSTR *Path) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ModuleName( 
            /* [retval][out] */ BSTR *Name) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeDateStamp( 
            /* [retval][out] */ DWORD *Time) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SizeOfImage( 
            /* [retval][out] */ DWORD *Size) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_StoreRelativePath( 
            /* [retval][out] */ VARIANT_BOOL *RelativePath) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BasePath( 
            /* [retval][out] */ BSTR *Path) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BasePath( 
            /* [in] */ BSTR Path) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_PropGetRelativePath( 
            /* [retval][out] */ VARIANT_BOOL *Relative) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_PropGetRelativePath( 
            /* [in] */ VARIANT_BOOL Relative) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxExecutableInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxExecutableInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxExecutableInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxExecutableInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxExecutableInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxExecutableInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxExecutableInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxExecutableInfo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SymbolGuid )( 
            IXboxExecutableInfo * This,
            /* [retval][out] */ BSTR *Guid);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XboxExecutablePath )( 
            IXboxExecutableInfo * This,
            /* [retval][out] */ BSTR *Path);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PortableExecutablePath )( 
            IXboxExecutableInfo * This,
            /* [retval][out] */ BSTR *Path);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SymbolPath )( 
            IXboxExecutableInfo * This,
            /* [retval][out] */ BSTR *Path);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PublicSymbolPath )( 
            IXboxExecutableInfo * This,
            /* [retval][out] */ BSTR *Path);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ModuleName )( 
            IXboxExecutableInfo * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimeDateStamp )( 
            IXboxExecutableInfo * This,
            /* [retval][out] */ DWORD *Time);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SizeOfImage )( 
            IXboxExecutableInfo * This,
            /* [retval][out] */ DWORD *Size);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StoreRelativePath )( 
            IXboxExecutableInfo * This,
            /* [retval][out] */ VARIANT_BOOL *RelativePath);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BasePath )( 
            IXboxExecutableInfo * This,
            /* [retval][out] */ BSTR *Path);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BasePath )( 
            IXboxExecutableInfo * This,
            /* [in] */ BSTR Path);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PropGetRelativePath )( 
            IXboxExecutableInfo * This,
            /* [retval][out] */ VARIANT_BOOL *Relative);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PropGetRelativePath )( 
            IXboxExecutableInfo * This,
            /* [in] */ VARIANT_BOOL Relative);
        
        END_INTERFACE
    } IXboxExecutableInfoVtbl;

    interface IXboxExecutableInfo
    {
        CONST_VTBL struct IXboxExecutableInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxExecutableInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxExecutableInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxExecutableInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxExecutableInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxExecutableInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxExecutableInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxExecutableInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxExecutableInfo_get_SymbolGuid(This,Guid)	\
    (This)->lpVtbl -> get_SymbolGuid(This,Guid)

#define IXboxExecutableInfo_get_XboxExecutablePath(This,Path)	\
    (This)->lpVtbl -> get_XboxExecutablePath(This,Path)

#define IXboxExecutableInfo_get_PortableExecutablePath(This,Path)	\
    (This)->lpVtbl -> get_PortableExecutablePath(This,Path)

#define IXboxExecutableInfo_get_SymbolPath(This,Path)	\
    (This)->lpVtbl -> get_SymbolPath(This,Path)

#define IXboxExecutableInfo_get_PublicSymbolPath(This,Path)	\
    (This)->lpVtbl -> get_PublicSymbolPath(This,Path)

#define IXboxExecutableInfo_get_ModuleName(This,Name)	\
    (This)->lpVtbl -> get_ModuleName(This,Name)

#define IXboxExecutableInfo_get_TimeDateStamp(This,Time)	\
    (This)->lpVtbl -> get_TimeDateStamp(This,Time)

#define IXboxExecutableInfo_get_SizeOfImage(This,Size)	\
    (This)->lpVtbl -> get_SizeOfImage(This,Size)

#define IXboxExecutableInfo_get_StoreRelativePath(This,RelativePath)	\
    (This)->lpVtbl -> get_StoreRelativePath(This,RelativePath)

#define IXboxExecutableInfo_get_BasePath(This,Path)	\
    (This)->lpVtbl -> get_BasePath(This,Path)

#define IXboxExecutableInfo_put_BasePath(This,Path)	\
    (This)->lpVtbl -> put_BasePath(This,Path)

#define IXboxExecutableInfo_get_PropGetRelativePath(This,Relative)	\
    (This)->lpVtbl -> get_PropGetRelativePath(This,Relative)

#define IXboxExecutableInfo_put_PropGetRelativePath(This,Relative)	\
    (This)->lpVtbl -> put_PropGetRelativePath(This,Relative)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxExecutableInfo_get_SymbolGuid_Proxy( 
    IXboxExecutableInfo * This,
    /* [retval][out] */ BSTR *Guid);


void __RPC_STUB IXboxExecutableInfo_get_SymbolGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxExecutableInfo_get_XboxExecutablePath_Proxy( 
    IXboxExecutableInfo * This,
    /* [retval][out] */ BSTR *Path);


void __RPC_STUB IXboxExecutableInfo_get_XboxExecutablePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxExecutableInfo_get_PortableExecutablePath_Proxy( 
    IXboxExecutableInfo * This,
    /* [retval][out] */ BSTR *Path);


void __RPC_STUB IXboxExecutableInfo_get_PortableExecutablePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxExecutableInfo_get_SymbolPath_Proxy( 
    IXboxExecutableInfo * This,
    /* [retval][out] */ BSTR *Path);


void __RPC_STUB IXboxExecutableInfo_get_SymbolPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxExecutableInfo_get_PublicSymbolPath_Proxy( 
    IXboxExecutableInfo * This,
    /* [retval][out] */ BSTR *Path);


void __RPC_STUB IXboxExecutableInfo_get_PublicSymbolPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxExecutableInfo_get_ModuleName_Proxy( 
    IXboxExecutableInfo * This,
    /* [retval][out] */ BSTR *Name);


void __RPC_STUB IXboxExecutableInfo_get_ModuleName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxExecutableInfo_get_TimeDateStamp_Proxy( 
    IXboxExecutableInfo * This,
    /* [retval][out] */ DWORD *Time);


void __RPC_STUB IXboxExecutableInfo_get_TimeDateStamp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxExecutableInfo_get_SizeOfImage_Proxy( 
    IXboxExecutableInfo * This,
    /* [retval][out] */ DWORD *Size);


void __RPC_STUB IXboxExecutableInfo_get_SizeOfImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxExecutableInfo_get_StoreRelativePath_Proxy( 
    IXboxExecutableInfo * This,
    /* [retval][out] */ VARIANT_BOOL *RelativePath);


void __RPC_STUB IXboxExecutableInfo_get_StoreRelativePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxExecutableInfo_get_BasePath_Proxy( 
    IXboxExecutableInfo * This,
    /* [retval][out] */ BSTR *Path);


void __RPC_STUB IXboxExecutableInfo_get_BasePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxExecutableInfo_put_BasePath_Proxy( 
    IXboxExecutableInfo * This,
    /* [in] */ BSTR Path);


void __RPC_STUB IXboxExecutableInfo_put_BasePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxExecutableInfo_get_PropGetRelativePath_Proxy( 
    IXboxExecutableInfo * This,
    /* [retval][out] */ VARIANT_BOOL *Relative);


void __RPC_STUB IXboxExecutableInfo_get_PropGetRelativePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxExecutableInfo_put_PropGetRelativePath_Proxy( 
    IXboxExecutableInfo * This,
    /* [in] */ VARIANT_BOOL Relative);


void __RPC_STUB IXboxExecutableInfo_put_PropGetRelativePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxExecutableInfo_INTERFACE_DEFINED__ */


#ifndef __IXboxExecutableDatabase_INTERFACE_DEFINED__
#define __IXboxExecutableDatabase_INTERFACE_DEFINED__

/* interface IXboxExecutableDatabase */
/* [helpstring][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxExecutableDatabase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CB8E47BA-2673-48af-B0C5-FD5738FFCC6B")
    IXboxExecutableDatabase : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_IsDirty( 
            /* [retval][out] */ VARIANT_BOOL *DirtyFlag) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentFileName( 
            /* [retval][out] */ BSTR *Path) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE LoadDatabase( 
            /* [in] */ BSTR DatabaseFile,
            /* [in] */ VARIANT_BOOL ReadOnly,
            /* [in] */ _XboxCreateDisposition CreateDisposition,
            /* [in] */ _XboxShareMode ShareMode) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SaveDatabase( 
            /* [in] */ BSTR DatabaseFile,
            /* [in] */ VARIANT_BOOL Remember) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CloseDatabase( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ResetDatabase( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AddExecutable( 
            /* [in] */ BSTR XboxExecutablePath,
            /* [in] */ BSTR PortableExecutablePath,
            /* [in] */ BSTR SymbolPath,
            /* [in] */ BSTR PublicSymbolPath,
            /* [in] */ VARIANT_BOOL ExplictFilesOnly,
            /* [in] */ VARIANT_BOOL StoreRelativePath) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveExecutable( 
            /* [in] */ BSTR Guid) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FindExecutableByGuid( 
            /* [in] */ BSTR Guid,
            /* [out] */ IXboxExecutableInfo **Info,
            /* [retval][out] */ VARIANT_BOOL *Found) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FindExecutableForSymServ( 
            /* [in] */ BSTR ModuleName,
            /* [in] */ DWORD TimeDateStamp,
            /* [in] */ DWORD SizeOfImage,
            /* [out] */ IXboxExecutableInfo **Info,
            /* [retval][out] */ VARIANT_BOOL *Found) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxExecutableDatabaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxExecutableDatabase * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxExecutableDatabase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxExecutableDatabase * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxExecutableDatabase * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxExecutableDatabase * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxExecutableDatabase * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxExecutableDatabase * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsDirty )( 
            IXboxExecutableDatabase * This,
            /* [retval][out] */ VARIANT_BOOL *DirtyFlag);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentFileName )( 
            IXboxExecutableDatabase * This,
            /* [retval][out] */ BSTR *Path);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *LoadDatabase )( 
            IXboxExecutableDatabase * This,
            /* [in] */ BSTR DatabaseFile,
            /* [in] */ VARIANT_BOOL ReadOnly,
            /* [in] */ _XboxCreateDisposition CreateDisposition,
            /* [in] */ _XboxShareMode ShareMode);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SaveDatabase )( 
            IXboxExecutableDatabase * This,
            /* [in] */ BSTR DatabaseFile,
            /* [in] */ VARIANT_BOOL Remember);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CloseDatabase )( 
            IXboxExecutableDatabase * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ResetDatabase )( 
            IXboxExecutableDatabase * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AddExecutable )( 
            IXboxExecutableDatabase * This,
            /* [in] */ BSTR XboxExecutablePath,
            /* [in] */ BSTR PortableExecutablePath,
            /* [in] */ BSTR SymbolPath,
            /* [in] */ BSTR PublicSymbolPath,
            /* [in] */ VARIANT_BOOL ExplictFilesOnly,
            /* [in] */ VARIANT_BOOL StoreRelativePath);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RemoveExecutable )( 
            IXboxExecutableDatabase * This,
            /* [in] */ BSTR Guid);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *FindExecutableByGuid )( 
            IXboxExecutableDatabase * This,
            /* [in] */ BSTR Guid,
            /* [out] */ IXboxExecutableInfo **Info,
            /* [retval][out] */ VARIANT_BOOL *Found);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *FindExecutableForSymServ )( 
            IXboxExecutableDatabase * This,
            /* [in] */ BSTR ModuleName,
            /* [in] */ DWORD TimeDateStamp,
            /* [in] */ DWORD SizeOfImage,
            /* [out] */ IXboxExecutableInfo **Info,
            /* [retval][out] */ VARIANT_BOOL *Found);
        
        END_INTERFACE
    } IXboxExecutableDatabaseVtbl;

    interface IXboxExecutableDatabase
    {
        CONST_VTBL struct IXboxExecutableDatabaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxExecutableDatabase_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxExecutableDatabase_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxExecutableDatabase_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxExecutableDatabase_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxExecutableDatabase_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxExecutableDatabase_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxExecutableDatabase_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxExecutableDatabase_get_IsDirty(This,DirtyFlag)	\
    (This)->lpVtbl -> get_IsDirty(This,DirtyFlag)

#define IXboxExecutableDatabase_get_CurrentFileName(This,Path)	\
    (This)->lpVtbl -> get_CurrentFileName(This,Path)

#define IXboxExecutableDatabase_LoadDatabase(This,DatabaseFile,ReadOnly,CreateDisposition,ShareMode)	\
    (This)->lpVtbl -> LoadDatabase(This,DatabaseFile,ReadOnly,CreateDisposition,ShareMode)

#define IXboxExecutableDatabase_SaveDatabase(This,DatabaseFile,Remember)	\
    (This)->lpVtbl -> SaveDatabase(This,DatabaseFile,Remember)

#define IXboxExecutableDatabase_CloseDatabase(This)	\
    (This)->lpVtbl -> CloseDatabase(This)

#define IXboxExecutableDatabase_ResetDatabase(This)	\
    (This)->lpVtbl -> ResetDatabase(This)

#define IXboxExecutableDatabase_AddExecutable(This,XboxExecutablePath,PortableExecutablePath,SymbolPath,PublicSymbolPath,ExplictFilesOnly,StoreRelativePath)	\
    (This)->lpVtbl -> AddExecutable(This,XboxExecutablePath,PortableExecutablePath,SymbolPath,PublicSymbolPath,ExplictFilesOnly,StoreRelativePath)

#define IXboxExecutableDatabase_RemoveExecutable(This,Guid)	\
    (This)->lpVtbl -> RemoveExecutable(This,Guid)

#define IXboxExecutableDatabase_FindExecutableByGuid(This,Guid,Info,Found)	\
    (This)->lpVtbl -> FindExecutableByGuid(This,Guid,Info,Found)

#define IXboxExecutableDatabase_FindExecutableForSymServ(This,ModuleName,TimeDateStamp,SizeOfImage,Info,Found)	\
    (This)->lpVtbl -> FindExecutableForSymServ(This,ModuleName,TimeDateStamp,SizeOfImage,Info,Found)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxExecutableDatabase_get_IsDirty_Proxy( 
    IXboxExecutableDatabase * This,
    /* [retval][out] */ VARIANT_BOOL *DirtyFlag);


void __RPC_STUB IXboxExecutableDatabase_get_IsDirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxExecutableDatabase_get_CurrentFileName_Proxy( 
    IXboxExecutableDatabase * This,
    /* [retval][out] */ BSTR *Path);


void __RPC_STUB IXboxExecutableDatabase_get_CurrentFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxExecutableDatabase_LoadDatabase_Proxy( 
    IXboxExecutableDatabase * This,
    /* [in] */ BSTR DatabaseFile,
    /* [in] */ VARIANT_BOOL ReadOnly,
    /* [in] */ _XboxCreateDisposition CreateDisposition,
    /* [in] */ _XboxShareMode ShareMode);


void __RPC_STUB IXboxExecutableDatabase_LoadDatabase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxExecutableDatabase_SaveDatabase_Proxy( 
    IXboxExecutableDatabase * This,
    /* [in] */ BSTR DatabaseFile,
    /* [in] */ VARIANT_BOOL Remember);


void __RPC_STUB IXboxExecutableDatabase_SaveDatabase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxExecutableDatabase_CloseDatabase_Proxy( 
    IXboxExecutableDatabase * This);


void __RPC_STUB IXboxExecutableDatabase_CloseDatabase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxExecutableDatabase_ResetDatabase_Proxy( 
    IXboxExecutableDatabase * This);


void __RPC_STUB IXboxExecutableDatabase_ResetDatabase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxExecutableDatabase_AddExecutable_Proxy( 
    IXboxExecutableDatabase * This,
    /* [in] */ BSTR XboxExecutablePath,
    /* [in] */ BSTR PortableExecutablePath,
    /* [in] */ BSTR SymbolPath,
    /* [in] */ BSTR PublicSymbolPath,
    /* [in] */ VARIANT_BOOL ExplictFilesOnly,
    /* [in] */ VARIANT_BOOL StoreRelativePath);


void __RPC_STUB IXboxExecutableDatabase_AddExecutable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxExecutableDatabase_RemoveExecutable_Proxy( 
    IXboxExecutableDatabase * This,
    /* [in] */ BSTR Guid);


void __RPC_STUB IXboxExecutableDatabase_RemoveExecutable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxExecutableDatabase_FindExecutableByGuid_Proxy( 
    IXboxExecutableDatabase * This,
    /* [in] */ BSTR Guid,
    /* [out] */ IXboxExecutableInfo **Info,
    /* [retval][out] */ VARIANT_BOOL *Found);


void __RPC_STUB IXboxExecutableDatabase_FindExecutableByGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxExecutableDatabase_FindExecutableForSymServ_Proxy( 
    IXboxExecutableDatabase * This,
    /* [in] */ BSTR ModuleName,
    /* [in] */ DWORD TimeDateStamp,
    /* [in] */ DWORD SizeOfImage,
    /* [out] */ IXboxExecutableInfo **Info,
    /* [retval][out] */ VARIANT_BOOL *Found);


void __RPC_STUB IXboxExecutableDatabase_FindExecutableForSymServ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxExecutableDatabase_INTERFACE_DEFINED__ */


#ifndef __IXboxConsole_INTERFACE_DEFINED__
#define __IXboxConsole_INTERFACE_DEFINED__

/* interface IXboxConsole */
/* [helpstring][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxConsole;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("75dd80a9-5a33-42d4-8a39-ab07c9b17cc3")
    IXboxConsole : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *XboxName) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR XboxName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_IPAddress( 
            /* [retval][out] */ DWORD *IPAddress) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_IPAddressTitle( 
            /* [retval][out] */ DWORD *IPAddress) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SystemTime( 
            /* [retval][out] */ VARIANT *Date) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_SystemTime( 
            /* [in] */ VARIANT Date) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Shared( 
            /* [retval][out] */ VARIANT_BOOL *Shared) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Shared( 
            /* [in] */ VARIANT_BOOL Shared) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectTimeout( 
            /* [retval][out] */ DWORD *Timeout) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectTimeout( 
            /* [in] */ DWORD Timeout) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ConversationTimeout( 
            /* [retval][out] */ DWORD *Timeout) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ConversationTimeout( 
            /* [in] */ DWORD Timeout) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FindConsole( 
            /* [in] */ DWORD Retries,
            /* [in] */ DWORD RetryDelay) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_XboxManager( 
            /* [retval][out] */ IXboxManager **XboxManager) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DebugTarget( 
            /* [retval][out] */ IXboxDebugTarget **DebugTarget) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Reboot( 
            /* [in] */ BSTR Name,
            /* [in] */ BSTR MediaDirectory,
            /* [in] */ BSTR CmdLine,
            /* [in] */ _XboxRebootFlags Flags) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetDefaultTitle( 
            /* [in] */ BSTR TitleName,
            /* [in] */ BSTR MediaDirectory,
            /* [in] */ DWORD Flags) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_RunningProcessInfo( 
            /* [retval][out] */ PXBOX_PROCESS_INFO ProcessInfo) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OpenConnection( 
            /* [in] */ BSTR Handler,
            /* [retval][out] */ DWORD *Connection) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CloseConnection( 
            /* [in] */ DWORD Connection) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SendTextCommand( 
            /* [in] */ DWORD Connection,
            /* [in] */ BSTR Command,
            /* [out] */ BSTR *Response) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ReceiveSocketLine( 
            /* [in] */ DWORD Connection,
            /* [out] */ BSTR *Line) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ReceiveStatusResponse( 
            /* [in] */ DWORD Connection,
            /* [out] */ BSTR *Line,
            /* [retval][out] */ HRESULT *status) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SendBinary( 
            /* [in] */ DWORD Connection,
            /* [in] */ SAFEARRAY * Data,
            /* [in] */ DWORD Count) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ReceiveBinary( 
            /* [in] */ DWORD Connection,
            /* [out][in] */ SAFEARRAY * Data,
            /* [in] */ DWORD Count,
            /* [out] */ DWORD *BytesReceived) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE SendBinary_cpp( 
            /* [in] */ DWORD Connection,
            /* [size_is][in] */ BYTE *Data,
            /* [in] */ DWORD Count) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE ReceiveBinary_cpp( 
            /* [in] */ DWORD Connection,
            /* [size_is][in] */ BYTE *Data,
            /* [in] */ DWORD Count,
            /* [out] */ DWORD *BytesReceived) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Drives( 
            /* [retval][out] */ BSTR *Drives) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetDiskFreeSpace( 
            /* [in] */ WCHAR Drive,
            /* [out] */ ULONGLONG *FreeBytesAvailableToCaller,
            /* [out] */ ULONGLONG *TotalNumberOfBytes,
            /* [out] */ ULONGLONG *TotalNumberOfFreeBytes) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MakeDirectory( 
            /* [in] */ BSTR Directory) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveDirectory( 
            /* [in] */ BSTR Directory) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DirectoryFiles( 
            /* [in] */ BSTR Directory,
            /* [retval][out] */ IXboxFiles **Files) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SendFile( 
            /* [in] */ BSTR LocalName,
            /* [in] */ BSTR RemoteName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ReceiveFile( 
            /* [in] */ BSTR LocalName,
            /* [in] */ BSTR RemoteName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ReadFileBytes( 
            /* [in] */ BSTR FileName,
            /* [in] */ DWORD FileOffset,
            /* [in] */ DWORD Count,
            /* [out][in] */ SAFEARRAY * Data,
            /* [out] */ DWORD *BytesRead) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WriteFileBytes( 
            /* [in] */ BSTR FileName,
            /* [in] */ DWORD FileOffset,
            /* [in] */ DWORD Count,
            /* [in] */ SAFEARRAY * Data,
            /* [out] */ DWORD *BytesWritten) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE ReadFileBytes_cpp( 
            /* [in] */ BSTR FileName,
            /* [in] */ DWORD FileOffset,
            /* [in] */ DWORD Count,
            /* [length_is][size_is][out] */ BYTE *Data,
            /* [out] */ DWORD *BytesRead) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE WriteFileBytes_cpp( 
            /* [in] */ BSTR FileName,
            /* [in] */ DWORD FileOffset,
            /* [in] */ DWORD Count,
            /* [size_is][in] */ BYTE *Data,
            /* [out] */ DWORD *BytesWritten) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetFileSize( 
            /* [in] */ BSTR FileName,
            /* [in] */ DWORD FileOffset,
            /* [in] */ _XboxCreateDisposition CreateDisposition) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetFileObject( 
            /* [in] */ BSTR FileName,
            /* [retval][out] */ IXboxFile **FileObject) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RenameFile( 
            /* [in] */ BSTR OldName,
            /* [in] */ BSTR NewName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DeleteFile( 
            /* [in] */ BSTR FileName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ScreenShot( 
            BSTR FileName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_DumpMode( 
            /* [retval][out] */ _XboxDumpMode *DumpMode) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_DumpMode( 
            /* [in] */ _XboxDumpMode DumpMode) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetDumpSettings( 
            /* [out] */ PXBOX_DUMP_SETTINGS DumpMode) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetDumpSettings( 
            /* [in] */ PXBOX_DUMP_SETTINGS DumpMode) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_EventDeferFlags( 
            /* [retval][out] */ _XboxEventDeferFlags *EventDeferFlags) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_EventDeferFlags( 
            /* [in] */ _XboxEventDeferFlags EventDeferFlags) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ConsoleType( 
            /* [retval][out] */ _XboxConsoleType *ConsoleType) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE StartFileEventCapture( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE StopFileEventCapture( void) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_XboxAutomation( 
            /* [retval][out] */ IXboxAutomation **Automation) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE LoadDebuggerExtension( 
            /* [in] */ BSTR ExtensionName,
            /* [retval][out] */ DWORD *ModuleHandle) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UnloadDebuggerExtension( 
            /* [in] */ DWORD ModuleHandle) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ConsoleFeatures( 
            /* [retval][out] */ _XboxConsoleFeatures *ConsoleFeatures) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxConsoleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxConsole * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxConsole * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxConsole * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxConsole * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxConsole * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxConsole * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxConsole * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IXboxConsole * This,
            /* [retval][out] */ BSTR *XboxName);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IXboxConsole * This,
            /* [in] */ BSTR XboxName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IPAddress )( 
            IXboxConsole * This,
            /* [retval][out] */ DWORD *IPAddress);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IPAddressTitle )( 
            IXboxConsole * This,
            /* [retval][out] */ DWORD *IPAddress);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SystemTime )( 
            IXboxConsole * This,
            /* [retval][out] */ VARIANT *Date);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SystemTime )( 
            IXboxConsole * This,
            /* [in] */ VARIANT Date);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shared )( 
            IXboxConsole * This,
            /* [retval][out] */ VARIANT_BOOL *Shared);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Shared )( 
            IXboxConsole * This,
            /* [in] */ VARIANT_BOOL Shared);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConnectTimeout )( 
            IXboxConsole * This,
            /* [retval][out] */ DWORD *Timeout);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConnectTimeout )( 
            IXboxConsole * This,
            /* [in] */ DWORD Timeout);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConversationTimeout )( 
            IXboxConsole * This,
            /* [retval][out] */ DWORD *Timeout);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConversationTimeout )( 
            IXboxConsole * This,
            /* [in] */ DWORD Timeout);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *FindConsole )( 
            IXboxConsole * This,
            /* [in] */ DWORD Retries,
            /* [in] */ DWORD RetryDelay);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XboxManager )( 
            IXboxConsole * This,
            /* [retval][out] */ IXboxManager **XboxManager);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DebugTarget )( 
            IXboxConsole * This,
            /* [retval][out] */ IXboxDebugTarget **DebugTarget);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Reboot )( 
            IXboxConsole * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR MediaDirectory,
            /* [in] */ BSTR CmdLine,
            /* [in] */ _XboxRebootFlags Flags);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetDefaultTitle )( 
            IXboxConsole * This,
            /* [in] */ BSTR TitleName,
            /* [in] */ BSTR MediaDirectory,
            /* [in] */ DWORD Flags);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RunningProcessInfo )( 
            IXboxConsole * This,
            /* [retval][out] */ PXBOX_PROCESS_INFO ProcessInfo);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OpenConnection )( 
            IXboxConsole * This,
            /* [in] */ BSTR Handler,
            /* [retval][out] */ DWORD *Connection);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CloseConnection )( 
            IXboxConsole * This,
            /* [in] */ DWORD Connection);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SendTextCommand )( 
            IXboxConsole * This,
            /* [in] */ DWORD Connection,
            /* [in] */ BSTR Command,
            /* [out] */ BSTR *Response);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ReceiveSocketLine )( 
            IXboxConsole * This,
            /* [in] */ DWORD Connection,
            /* [out] */ BSTR *Line);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ReceiveStatusResponse )( 
            IXboxConsole * This,
            /* [in] */ DWORD Connection,
            /* [out] */ BSTR *Line,
            /* [retval][out] */ HRESULT *status);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SendBinary )( 
            IXboxConsole * This,
            /* [in] */ DWORD Connection,
            /* [in] */ SAFEARRAY * Data,
            /* [in] */ DWORD Count);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ReceiveBinary )( 
            IXboxConsole * This,
            /* [in] */ DWORD Connection,
            /* [out][in] */ SAFEARRAY * Data,
            /* [in] */ DWORD Count,
            /* [out] */ DWORD *BytesReceived);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *SendBinary_cpp )( 
            IXboxConsole * This,
            /* [in] */ DWORD Connection,
            /* [size_is][in] */ BYTE *Data,
            /* [in] */ DWORD Count);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *ReceiveBinary_cpp )( 
            IXboxConsole * This,
            /* [in] */ DWORD Connection,
            /* [size_is][in] */ BYTE *Data,
            /* [in] */ DWORD Count,
            /* [out] */ DWORD *BytesReceived);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Drives )( 
            IXboxConsole * This,
            /* [retval][out] */ BSTR *Drives);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetDiskFreeSpace )( 
            IXboxConsole * This,
            /* [in] */ WCHAR Drive,
            /* [out] */ ULONGLONG *FreeBytesAvailableToCaller,
            /* [out] */ ULONGLONG *TotalNumberOfBytes,
            /* [out] */ ULONGLONG *TotalNumberOfFreeBytes);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *MakeDirectory )( 
            IXboxConsole * This,
            /* [in] */ BSTR Directory);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RemoveDirectory )( 
            IXboxConsole * This,
            /* [in] */ BSTR Directory);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DirectoryFiles )( 
            IXboxConsole * This,
            /* [in] */ BSTR Directory,
            /* [retval][out] */ IXboxFiles **Files);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SendFile )( 
            IXboxConsole * This,
            /* [in] */ BSTR LocalName,
            /* [in] */ BSTR RemoteName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ReceiveFile )( 
            IXboxConsole * This,
            /* [in] */ BSTR LocalName,
            /* [in] */ BSTR RemoteName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ReadFileBytes )( 
            IXboxConsole * This,
            /* [in] */ BSTR FileName,
            /* [in] */ DWORD FileOffset,
            /* [in] */ DWORD Count,
            /* [out][in] */ SAFEARRAY * Data,
            /* [out] */ DWORD *BytesRead);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WriteFileBytes )( 
            IXboxConsole * This,
            /* [in] */ BSTR FileName,
            /* [in] */ DWORD FileOffset,
            /* [in] */ DWORD Count,
            /* [in] */ SAFEARRAY * Data,
            /* [out] */ DWORD *BytesWritten);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *ReadFileBytes_cpp )( 
            IXboxConsole * This,
            /* [in] */ BSTR FileName,
            /* [in] */ DWORD FileOffset,
            /* [in] */ DWORD Count,
            /* [length_is][size_is][out] */ BYTE *Data,
            /* [out] */ DWORD *BytesRead);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *WriteFileBytes_cpp )( 
            IXboxConsole * This,
            /* [in] */ BSTR FileName,
            /* [in] */ DWORD FileOffset,
            /* [in] */ DWORD Count,
            /* [size_is][in] */ BYTE *Data,
            /* [out] */ DWORD *BytesWritten);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetFileSize )( 
            IXboxConsole * This,
            /* [in] */ BSTR FileName,
            /* [in] */ DWORD FileOffset,
            /* [in] */ _XboxCreateDisposition CreateDisposition);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetFileObject )( 
            IXboxConsole * This,
            /* [in] */ BSTR FileName,
            /* [retval][out] */ IXboxFile **FileObject);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RenameFile )( 
            IXboxConsole * This,
            /* [in] */ BSTR OldName,
            /* [in] */ BSTR NewName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DeleteFile )( 
            IXboxConsole * This,
            /* [in] */ BSTR FileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ScreenShot )( 
            IXboxConsole * This,
            BSTR FileName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DumpMode )( 
            IXboxConsole * This,
            /* [retval][out] */ _XboxDumpMode *DumpMode);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DumpMode )( 
            IXboxConsole * This,
            /* [in] */ _XboxDumpMode DumpMode);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetDumpSettings )( 
            IXboxConsole * This,
            /* [out] */ PXBOX_DUMP_SETTINGS DumpMode);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetDumpSettings )( 
            IXboxConsole * This,
            /* [in] */ PXBOX_DUMP_SETTINGS DumpMode);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EventDeferFlags )( 
            IXboxConsole * This,
            /* [retval][out] */ _XboxEventDeferFlags *EventDeferFlags);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EventDeferFlags )( 
            IXboxConsole * This,
            /* [in] */ _XboxEventDeferFlags EventDeferFlags);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConsoleType )( 
            IXboxConsole * This,
            /* [retval][out] */ _XboxConsoleType *ConsoleType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *StartFileEventCapture )( 
            IXboxConsole * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *StopFileEventCapture )( 
            IXboxConsole * This);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XboxAutomation )( 
            IXboxConsole * This,
            /* [retval][out] */ IXboxAutomation **Automation);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *LoadDebuggerExtension )( 
            IXboxConsole * This,
            /* [in] */ BSTR ExtensionName,
            /* [retval][out] */ DWORD *ModuleHandle);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UnloadDebuggerExtension )( 
            IXboxConsole * This,
            /* [in] */ DWORD ModuleHandle);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConsoleFeatures )( 
            IXboxConsole * This,
            /* [retval][out] */ _XboxConsoleFeatures *ConsoleFeatures);
        
        END_INTERFACE
    } IXboxConsoleVtbl;

    interface IXboxConsole
    {
        CONST_VTBL struct IXboxConsoleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxConsole_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxConsole_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxConsole_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxConsole_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxConsole_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxConsole_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxConsole_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxConsole_get_Name(This,XboxName)	\
    (This)->lpVtbl -> get_Name(This,XboxName)

#define IXboxConsole_put_Name(This,XboxName)	\
    (This)->lpVtbl -> put_Name(This,XboxName)

#define IXboxConsole_get_IPAddress(This,IPAddress)	\
    (This)->lpVtbl -> get_IPAddress(This,IPAddress)

#define IXboxConsole_get_IPAddressTitle(This,IPAddress)	\
    (This)->lpVtbl -> get_IPAddressTitle(This,IPAddress)

#define IXboxConsole_get_SystemTime(This,Date)	\
    (This)->lpVtbl -> get_SystemTime(This,Date)

#define IXboxConsole_put_SystemTime(This,Date)	\
    (This)->lpVtbl -> put_SystemTime(This,Date)

#define IXboxConsole_get_Shared(This,Shared)	\
    (This)->lpVtbl -> get_Shared(This,Shared)

#define IXboxConsole_put_Shared(This,Shared)	\
    (This)->lpVtbl -> put_Shared(This,Shared)

#define IXboxConsole_get_ConnectTimeout(This,Timeout)	\
    (This)->lpVtbl -> get_ConnectTimeout(This,Timeout)

#define IXboxConsole_put_ConnectTimeout(This,Timeout)	\
    (This)->lpVtbl -> put_ConnectTimeout(This,Timeout)

#define IXboxConsole_get_ConversationTimeout(This,Timeout)	\
    (This)->lpVtbl -> get_ConversationTimeout(This,Timeout)

#define IXboxConsole_put_ConversationTimeout(This,Timeout)	\
    (This)->lpVtbl -> put_ConversationTimeout(This,Timeout)

#define IXboxConsole_FindConsole(This,Retries,RetryDelay)	\
    (This)->lpVtbl -> FindConsole(This,Retries,RetryDelay)

#define IXboxConsole_get_XboxManager(This,XboxManager)	\
    (This)->lpVtbl -> get_XboxManager(This,XboxManager)

#define IXboxConsole_get_DebugTarget(This,DebugTarget)	\
    (This)->lpVtbl -> get_DebugTarget(This,DebugTarget)

#define IXboxConsole_Reboot(This,Name,MediaDirectory,CmdLine,Flags)	\
    (This)->lpVtbl -> Reboot(This,Name,MediaDirectory,CmdLine,Flags)

#define IXboxConsole_SetDefaultTitle(This,TitleName,MediaDirectory,Flags)	\
    (This)->lpVtbl -> SetDefaultTitle(This,TitleName,MediaDirectory,Flags)

#define IXboxConsole_get_RunningProcessInfo(This,ProcessInfo)	\
    (This)->lpVtbl -> get_RunningProcessInfo(This,ProcessInfo)

#define IXboxConsole_OpenConnection(This,Handler,Connection)	\
    (This)->lpVtbl -> OpenConnection(This,Handler,Connection)

#define IXboxConsole_CloseConnection(This,Connection)	\
    (This)->lpVtbl -> CloseConnection(This,Connection)

#define IXboxConsole_SendTextCommand(This,Connection,Command,Response)	\
    (This)->lpVtbl -> SendTextCommand(This,Connection,Command,Response)

#define IXboxConsole_ReceiveSocketLine(This,Connection,Line)	\
    (This)->lpVtbl -> ReceiveSocketLine(This,Connection,Line)

#define IXboxConsole_ReceiveStatusResponse(This,Connection,Line,status)	\
    (This)->lpVtbl -> ReceiveStatusResponse(This,Connection,Line,status)

#define IXboxConsole_SendBinary(This,Connection,Data,Count)	\
    (This)->lpVtbl -> SendBinary(This,Connection,Data,Count)

#define IXboxConsole_ReceiveBinary(This,Connection,Data,Count,BytesReceived)	\
    (This)->lpVtbl -> ReceiveBinary(This,Connection,Data,Count,BytesReceived)

#define IXboxConsole_SendBinary_cpp(This,Connection,Data,Count)	\
    (This)->lpVtbl -> SendBinary_cpp(This,Connection,Data,Count)

#define IXboxConsole_ReceiveBinary_cpp(This,Connection,Data,Count,BytesReceived)	\
    (This)->lpVtbl -> ReceiveBinary_cpp(This,Connection,Data,Count,BytesReceived)

#define IXboxConsole_get_Drives(This,Drives)	\
    (This)->lpVtbl -> get_Drives(This,Drives)

#define IXboxConsole_GetDiskFreeSpace(This,Drive,FreeBytesAvailableToCaller,TotalNumberOfBytes,TotalNumberOfFreeBytes)	\
    (This)->lpVtbl -> GetDiskFreeSpace(This,Drive,FreeBytesAvailableToCaller,TotalNumberOfBytes,TotalNumberOfFreeBytes)

#define IXboxConsole_MakeDirectory(This,Directory)	\
    (This)->lpVtbl -> MakeDirectory(This,Directory)

#define IXboxConsole_RemoveDirectory(This,Directory)	\
    (This)->lpVtbl -> RemoveDirectory(This,Directory)

#define IXboxConsole_DirectoryFiles(This,Directory,Files)	\
    (This)->lpVtbl -> DirectoryFiles(This,Directory,Files)

#define IXboxConsole_SendFile(This,LocalName,RemoteName)	\
    (This)->lpVtbl -> SendFile(This,LocalName,RemoteName)

#define IXboxConsole_ReceiveFile(This,LocalName,RemoteName)	\
    (This)->lpVtbl -> ReceiveFile(This,LocalName,RemoteName)

#define IXboxConsole_ReadFileBytes(This,FileName,FileOffset,Count,Data,BytesRead)	\
    (This)->lpVtbl -> ReadFileBytes(This,FileName,FileOffset,Count,Data,BytesRead)

#define IXboxConsole_WriteFileBytes(This,FileName,FileOffset,Count,Data,BytesWritten)	\
    (This)->lpVtbl -> WriteFileBytes(This,FileName,FileOffset,Count,Data,BytesWritten)

#define IXboxConsole_ReadFileBytes_cpp(This,FileName,FileOffset,Count,Data,BytesRead)	\
    (This)->lpVtbl -> ReadFileBytes_cpp(This,FileName,FileOffset,Count,Data,BytesRead)

#define IXboxConsole_WriteFileBytes_cpp(This,FileName,FileOffset,Count,Data,BytesWritten)	\
    (This)->lpVtbl -> WriteFileBytes_cpp(This,FileName,FileOffset,Count,Data,BytesWritten)

#define IXboxConsole_SetFileSize(This,FileName,FileOffset,CreateDisposition)	\
    (This)->lpVtbl -> SetFileSize(This,FileName,FileOffset,CreateDisposition)

#define IXboxConsole_GetFileObject(This,FileName,FileObject)	\
    (This)->lpVtbl -> GetFileObject(This,FileName,FileObject)

#define IXboxConsole_RenameFile(This,OldName,NewName)	\
    (This)->lpVtbl -> RenameFile(This,OldName,NewName)

#define IXboxConsole_DeleteFile(This,FileName)	\
    (This)->lpVtbl -> DeleteFile(This,FileName)

#define IXboxConsole_ScreenShot(This,FileName)	\
    (This)->lpVtbl -> ScreenShot(This,FileName)

#define IXboxConsole_get_DumpMode(This,DumpMode)	\
    (This)->lpVtbl -> get_DumpMode(This,DumpMode)

#define IXboxConsole_put_DumpMode(This,DumpMode)	\
    (This)->lpVtbl -> put_DumpMode(This,DumpMode)

#define IXboxConsole_GetDumpSettings(This,DumpMode)	\
    (This)->lpVtbl -> GetDumpSettings(This,DumpMode)

#define IXboxConsole_SetDumpSettings(This,DumpMode)	\
    (This)->lpVtbl -> SetDumpSettings(This,DumpMode)

#define IXboxConsole_get_EventDeferFlags(This,EventDeferFlags)	\
    (This)->lpVtbl -> get_EventDeferFlags(This,EventDeferFlags)

#define IXboxConsole_put_EventDeferFlags(This,EventDeferFlags)	\
    (This)->lpVtbl -> put_EventDeferFlags(This,EventDeferFlags)

#define IXboxConsole_get_ConsoleType(This,ConsoleType)	\
    (This)->lpVtbl -> get_ConsoleType(This,ConsoleType)

#define IXboxConsole_StartFileEventCapture(This)	\
    (This)->lpVtbl -> StartFileEventCapture(This)

#define IXboxConsole_StopFileEventCapture(This)	\
    (This)->lpVtbl -> StopFileEventCapture(This)

#define IXboxConsole_get_XboxAutomation(This,Automation)	\
    (This)->lpVtbl -> get_XboxAutomation(This,Automation)

#define IXboxConsole_LoadDebuggerExtension(This,ExtensionName,ModuleHandle)	\
    (This)->lpVtbl -> LoadDebuggerExtension(This,ExtensionName,ModuleHandle)

#define IXboxConsole_UnloadDebuggerExtension(This,ModuleHandle)	\
    (This)->lpVtbl -> UnloadDebuggerExtension(This,ModuleHandle)

#define IXboxConsole_get_ConsoleFeatures(This,ConsoleFeatures)	\
    (This)->lpVtbl -> get_ConsoleFeatures(This,ConsoleFeatures)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_Name_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ BSTR *XboxName);


void __RPC_STUB IXboxConsole_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxConsole_put_Name_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR XboxName);


void __RPC_STUB IXboxConsole_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_IPAddress_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ DWORD *IPAddress);


void __RPC_STUB IXboxConsole_get_IPAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_IPAddressTitle_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ DWORD *IPAddress);


void __RPC_STUB IXboxConsole_get_IPAddressTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_SystemTime_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ VARIANT *Date);


void __RPC_STUB IXboxConsole_get_SystemTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxConsole_put_SystemTime_Proxy( 
    IXboxConsole * This,
    /* [in] */ VARIANT Date);


void __RPC_STUB IXboxConsole_put_SystemTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_Shared_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ VARIANT_BOOL *Shared);


void __RPC_STUB IXboxConsole_get_Shared_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxConsole_put_Shared_Proxy( 
    IXboxConsole * This,
    /* [in] */ VARIANT_BOOL Shared);


void __RPC_STUB IXboxConsole_put_Shared_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_ConnectTimeout_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ DWORD *Timeout);


void __RPC_STUB IXboxConsole_get_ConnectTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxConsole_put_ConnectTimeout_Proxy( 
    IXboxConsole * This,
    /* [in] */ DWORD Timeout);


void __RPC_STUB IXboxConsole_put_ConnectTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_ConversationTimeout_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ DWORD *Timeout);


void __RPC_STUB IXboxConsole_get_ConversationTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxConsole_put_ConversationTimeout_Proxy( 
    IXboxConsole * This,
    /* [in] */ DWORD Timeout);


void __RPC_STUB IXboxConsole_put_ConversationTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_FindConsole_Proxy( 
    IXboxConsole * This,
    /* [in] */ DWORD Retries,
    /* [in] */ DWORD RetryDelay);


void __RPC_STUB IXboxConsole_FindConsole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_XboxManager_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ IXboxManager **XboxManager);


void __RPC_STUB IXboxConsole_get_XboxManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_DebugTarget_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ IXboxDebugTarget **DebugTarget);


void __RPC_STUB IXboxConsole_get_DebugTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_Reboot_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR MediaDirectory,
    /* [in] */ BSTR CmdLine,
    /* [in] */ _XboxRebootFlags Flags);


void __RPC_STUB IXboxConsole_Reboot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_SetDefaultTitle_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR TitleName,
    /* [in] */ BSTR MediaDirectory,
    /* [in] */ DWORD Flags);


void __RPC_STUB IXboxConsole_SetDefaultTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_RunningProcessInfo_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ PXBOX_PROCESS_INFO ProcessInfo);


void __RPC_STUB IXboxConsole_get_RunningProcessInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_OpenConnection_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR Handler,
    /* [retval][out] */ DWORD *Connection);


void __RPC_STUB IXboxConsole_OpenConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_CloseConnection_Proxy( 
    IXboxConsole * This,
    /* [in] */ DWORD Connection);


void __RPC_STUB IXboxConsole_CloseConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_SendTextCommand_Proxy( 
    IXboxConsole * This,
    /* [in] */ DWORD Connection,
    /* [in] */ BSTR Command,
    /* [out] */ BSTR *Response);


void __RPC_STUB IXboxConsole_SendTextCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_ReceiveSocketLine_Proxy( 
    IXboxConsole * This,
    /* [in] */ DWORD Connection,
    /* [out] */ BSTR *Line);


void __RPC_STUB IXboxConsole_ReceiveSocketLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_ReceiveStatusResponse_Proxy( 
    IXboxConsole * This,
    /* [in] */ DWORD Connection,
    /* [out] */ BSTR *Line,
    /* [retval][out] */ HRESULT *status);


void __RPC_STUB IXboxConsole_ReceiveStatusResponse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_SendBinary_Proxy( 
    IXboxConsole * This,
    /* [in] */ DWORD Connection,
    /* [in] */ SAFEARRAY * Data,
    /* [in] */ DWORD Count);


void __RPC_STUB IXboxConsole_SendBinary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_ReceiveBinary_Proxy( 
    IXboxConsole * This,
    /* [in] */ DWORD Connection,
    /* [out][in] */ SAFEARRAY * Data,
    /* [in] */ DWORD Count,
    /* [out] */ DWORD *BytesReceived);


void __RPC_STUB IXboxConsole_ReceiveBinary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_SendBinary_cpp_Proxy( 
    IXboxConsole * This,
    /* [in] */ DWORD Connection,
    /* [size_is][in] */ BYTE *Data,
    /* [in] */ DWORD Count);


void __RPC_STUB IXboxConsole_SendBinary_cpp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_ReceiveBinary_cpp_Proxy( 
    IXboxConsole * This,
    /* [in] */ DWORD Connection,
    /* [size_is][in] */ BYTE *Data,
    /* [in] */ DWORD Count,
    /* [out] */ DWORD *BytesReceived);


void __RPC_STUB IXboxConsole_ReceiveBinary_cpp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_Drives_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ BSTR *Drives);


void __RPC_STUB IXboxConsole_get_Drives_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_GetDiskFreeSpace_Proxy( 
    IXboxConsole * This,
    /* [in] */ WCHAR Drive,
    /* [out] */ ULONGLONG *FreeBytesAvailableToCaller,
    /* [out] */ ULONGLONG *TotalNumberOfBytes,
    /* [out] */ ULONGLONG *TotalNumberOfFreeBytes);


void __RPC_STUB IXboxConsole_GetDiskFreeSpace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_MakeDirectory_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR Directory);


void __RPC_STUB IXboxConsole_MakeDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_RemoveDirectory_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR Directory);


void __RPC_STUB IXboxConsole_RemoveDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_DirectoryFiles_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR Directory,
    /* [retval][out] */ IXboxFiles **Files);


void __RPC_STUB IXboxConsole_DirectoryFiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_SendFile_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR LocalName,
    /* [in] */ BSTR RemoteName);


void __RPC_STUB IXboxConsole_SendFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_ReceiveFile_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR LocalName,
    /* [in] */ BSTR RemoteName);


void __RPC_STUB IXboxConsole_ReceiveFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_ReadFileBytes_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR FileName,
    /* [in] */ DWORD FileOffset,
    /* [in] */ DWORD Count,
    /* [out][in] */ SAFEARRAY * Data,
    /* [out] */ DWORD *BytesRead);


void __RPC_STUB IXboxConsole_ReadFileBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_WriteFileBytes_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR FileName,
    /* [in] */ DWORD FileOffset,
    /* [in] */ DWORD Count,
    /* [in] */ SAFEARRAY * Data,
    /* [out] */ DWORD *BytesWritten);


void __RPC_STUB IXboxConsole_WriteFileBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_ReadFileBytes_cpp_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR FileName,
    /* [in] */ DWORD FileOffset,
    /* [in] */ DWORD Count,
    /* [length_is][size_is][out] */ BYTE *Data,
    /* [out] */ DWORD *BytesRead);


void __RPC_STUB IXboxConsole_ReadFileBytes_cpp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_WriteFileBytes_cpp_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR FileName,
    /* [in] */ DWORD FileOffset,
    /* [in] */ DWORD Count,
    /* [size_is][in] */ BYTE *Data,
    /* [out] */ DWORD *BytesWritten);


void __RPC_STUB IXboxConsole_WriteFileBytes_cpp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_SetFileSize_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR FileName,
    /* [in] */ DWORD FileOffset,
    /* [in] */ _XboxCreateDisposition CreateDisposition);


void __RPC_STUB IXboxConsole_SetFileSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_GetFileObject_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR FileName,
    /* [retval][out] */ IXboxFile **FileObject);


void __RPC_STUB IXboxConsole_GetFileObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_RenameFile_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR OldName,
    /* [in] */ BSTR NewName);


void __RPC_STUB IXboxConsole_RenameFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_DeleteFile_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR FileName);


void __RPC_STUB IXboxConsole_DeleteFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_ScreenShot_Proxy( 
    IXboxConsole * This,
    BSTR FileName);


void __RPC_STUB IXboxConsole_ScreenShot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_DumpMode_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ _XboxDumpMode *DumpMode);


void __RPC_STUB IXboxConsole_get_DumpMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxConsole_put_DumpMode_Proxy( 
    IXboxConsole * This,
    /* [in] */ _XboxDumpMode DumpMode);


void __RPC_STUB IXboxConsole_put_DumpMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_GetDumpSettings_Proxy( 
    IXboxConsole * This,
    /* [out] */ PXBOX_DUMP_SETTINGS DumpMode);


void __RPC_STUB IXboxConsole_GetDumpSettings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_SetDumpSettings_Proxy( 
    IXboxConsole * This,
    /* [in] */ PXBOX_DUMP_SETTINGS DumpMode);


void __RPC_STUB IXboxConsole_SetDumpSettings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_EventDeferFlags_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ _XboxEventDeferFlags *EventDeferFlags);


void __RPC_STUB IXboxConsole_get_EventDeferFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxConsole_put_EventDeferFlags_Proxy( 
    IXboxConsole * This,
    /* [in] */ _XboxEventDeferFlags EventDeferFlags);


void __RPC_STUB IXboxConsole_put_EventDeferFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_ConsoleType_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ _XboxConsoleType *ConsoleType);


void __RPC_STUB IXboxConsole_get_ConsoleType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_StartFileEventCapture_Proxy( 
    IXboxConsole * This);


void __RPC_STUB IXboxConsole_StartFileEventCapture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_StopFileEventCapture_Proxy( 
    IXboxConsole * This);


void __RPC_STUB IXboxConsole_StopFileEventCapture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_XboxAutomation_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ IXboxAutomation **Automation);


void __RPC_STUB IXboxConsole_get_XboxAutomation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_LoadDebuggerExtension_Proxy( 
    IXboxConsole * This,
    /* [in] */ BSTR ExtensionName,
    /* [retval][out] */ DWORD *ModuleHandle);


void __RPC_STUB IXboxConsole_LoadDebuggerExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxConsole_UnloadDebuggerExtension_Proxy( 
    IXboxConsole * This,
    /* [in] */ DWORD ModuleHandle);


void __RPC_STUB IXboxConsole_UnloadDebuggerExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxConsole_get_ConsoleFeatures_Proxy( 
    IXboxConsole * This,
    /* [retval][out] */ _XboxConsoleFeatures *ConsoleFeatures);


void __RPC_STUB IXboxConsole_get_ConsoleFeatures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxConsole_INTERFACE_DEFINED__ */


#ifndef __IXboxConsoles_INTERFACE_DEFINED__
#define __IXboxConsoles_INTERFACE_DEFINED__

/* interface IXboxConsoles */
/* [helpstring][unique][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxConsoles;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("110980e4-f8d4-45f1-8a86-90d86fd4a879")
    IXboxConsoles : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG Index,
            /* [retval][out] */ BSTR *ConsoleName) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *Count) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IEnumVARIANT **Enumerator) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxConsolesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxConsoles * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxConsoles * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxConsoles * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxConsoles * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxConsoles * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxConsoles * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxConsoles * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IXboxConsoles * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ BSTR *ConsoleName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IXboxConsoles * This,
            /* [retval][out] */ LONG *Count);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IXboxConsoles * This,
            /* [retval][out] */ IEnumVARIANT **Enumerator);
        
        END_INTERFACE
    } IXboxConsolesVtbl;

    interface IXboxConsoles
    {
        CONST_VTBL struct IXboxConsolesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxConsoles_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxConsoles_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxConsoles_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxConsoles_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxConsoles_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxConsoles_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxConsoles_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxConsoles_get_Item(This,Index,ConsoleName)	\
    (This)->lpVtbl -> get_Item(This,Index,ConsoleName)

#define IXboxConsoles_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IXboxConsoles_get__NewEnum(This,Enumerator)	\
    (This)->lpVtbl -> get__NewEnum(This,Enumerator)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxConsoles_get_Item_Proxy( 
    IXboxConsoles * This,
    /* [in] */ LONG Index,
    /* [retval][out] */ BSTR *ConsoleName);


void __RPC_STUB IXboxConsoles_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxConsoles_get_Count_Proxy( 
    IXboxConsoles * This,
    /* [retval][out] */ LONG *Count);


void __RPC_STUB IXboxConsoles_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxConsoles_get__NewEnum_Proxy( 
    IXboxConsoles * This,
    /* [retval][out] */ IEnumVARIANT **Enumerator);


void __RPC_STUB IXboxConsoles_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxConsoles_INTERFACE_DEFINED__ */


#ifndef __IXboxFile_INTERFACE_DEFINED__
#define __IXboxFile_INTERFACE_DEFINED__

/* interface IXboxFile */
/* [helpstring][unique][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxFile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b9dbc76d-8a06-4eeb-84bd-1ad42f0afe28")
    IXboxFile : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *Name) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CreationTime( 
            /* [retval][out] */ VARIANT *CreationTime) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_CreationTime( 
            /* [in] */ VARIANT CreationTime) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ChangeTime( 
            /* [retval][out] */ VARIANT *ChangeTime) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ChangeTime( 
            /* [in] */ VARIANT ChangeTime) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ ULONGLONG *Size) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Size( 
            /* [in] */ ULONGLONG Size) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_IsReadOnly( 
            /* [retval][out] */ VARIANT_BOOL *ReadOnly) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_IsReadOnly( 
            /* [in] */ VARIANT_BOOL ReadOnly) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_IsDirectory( 
            /* [retval][out] */ VARIANT_BOOL *Directory) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxFile * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxFile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxFile * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxFile * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxFile * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxFile * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxFile * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IXboxFile * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IXboxFile * This,
            /* [in] */ BSTR Name);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CreationTime )( 
            IXboxFile * This,
            /* [retval][out] */ VARIANT *CreationTime);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CreationTime )( 
            IXboxFile * This,
            /* [in] */ VARIANT CreationTime);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChangeTime )( 
            IXboxFile * This,
            /* [retval][out] */ VARIANT *ChangeTime);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ChangeTime )( 
            IXboxFile * This,
            /* [in] */ VARIANT ChangeTime);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            IXboxFile * This,
            /* [retval][out] */ ULONGLONG *Size);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Size )( 
            IXboxFile * This,
            /* [in] */ ULONGLONG Size);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsReadOnly )( 
            IXboxFile * This,
            /* [retval][out] */ VARIANT_BOOL *ReadOnly);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsReadOnly )( 
            IXboxFile * This,
            /* [in] */ VARIANT_BOOL ReadOnly);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsDirectory )( 
            IXboxFile * This,
            /* [retval][out] */ VARIANT_BOOL *Directory);
        
        END_INTERFACE
    } IXboxFileVtbl;

    interface IXboxFile
    {
        CONST_VTBL struct IXboxFileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxFile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxFile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxFile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxFile_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxFile_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxFile_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxFile_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxFile_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define IXboxFile_put_Name(This,Name)	\
    (This)->lpVtbl -> put_Name(This,Name)

#define IXboxFile_get_CreationTime(This,CreationTime)	\
    (This)->lpVtbl -> get_CreationTime(This,CreationTime)

#define IXboxFile_put_CreationTime(This,CreationTime)	\
    (This)->lpVtbl -> put_CreationTime(This,CreationTime)

#define IXboxFile_get_ChangeTime(This,ChangeTime)	\
    (This)->lpVtbl -> get_ChangeTime(This,ChangeTime)

#define IXboxFile_put_ChangeTime(This,ChangeTime)	\
    (This)->lpVtbl -> put_ChangeTime(This,ChangeTime)

#define IXboxFile_get_Size(This,Size)	\
    (This)->lpVtbl -> get_Size(This,Size)

#define IXboxFile_put_Size(This,Size)	\
    (This)->lpVtbl -> put_Size(This,Size)

#define IXboxFile_get_IsReadOnly(This,ReadOnly)	\
    (This)->lpVtbl -> get_IsReadOnly(This,ReadOnly)

#define IXboxFile_put_IsReadOnly(This,ReadOnly)	\
    (This)->lpVtbl -> put_IsReadOnly(This,ReadOnly)

#define IXboxFile_get_IsDirectory(This,Directory)	\
    (This)->lpVtbl -> get_IsDirectory(This,Directory)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxFile_get_Name_Proxy( 
    IXboxFile * This,
    /* [retval][out] */ BSTR *Name);


void __RPC_STUB IXboxFile_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxFile_put_Name_Proxy( 
    IXboxFile * This,
    /* [in] */ BSTR Name);


void __RPC_STUB IXboxFile_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxFile_get_CreationTime_Proxy( 
    IXboxFile * This,
    /* [retval][out] */ VARIANT *CreationTime);


void __RPC_STUB IXboxFile_get_CreationTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxFile_put_CreationTime_Proxy( 
    IXboxFile * This,
    /* [in] */ VARIANT CreationTime);


void __RPC_STUB IXboxFile_put_CreationTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxFile_get_ChangeTime_Proxy( 
    IXboxFile * This,
    /* [retval][out] */ VARIANT *ChangeTime);


void __RPC_STUB IXboxFile_get_ChangeTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxFile_put_ChangeTime_Proxy( 
    IXboxFile * This,
    /* [in] */ VARIANT ChangeTime);


void __RPC_STUB IXboxFile_put_ChangeTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxFile_get_Size_Proxy( 
    IXboxFile * This,
    /* [retval][out] */ ULONGLONG *Size);


void __RPC_STUB IXboxFile_get_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxFile_put_Size_Proxy( 
    IXboxFile * This,
    /* [in] */ ULONGLONG Size);


void __RPC_STUB IXboxFile_put_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxFile_get_IsReadOnly_Proxy( 
    IXboxFile * This,
    /* [retval][out] */ VARIANT_BOOL *ReadOnly);


void __RPC_STUB IXboxFile_get_IsReadOnly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxFile_put_IsReadOnly_Proxy( 
    IXboxFile * This,
    /* [in] */ VARIANT_BOOL ReadOnly);


void __RPC_STUB IXboxFile_put_IsReadOnly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxFile_get_IsDirectory_Proxy( 
    IXboxFile * This,
    /* [retval][out] */ VARIANT_BOOL *Directory);


void __RPC_STUB IXboxFile_get_IsDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxFile_INTERFACE_DEFINED__ */


#ifndef __IXboxFiles_INTERFACE_DEFINED__
#define __IXboxFiles_INTERFACE_DEFINED__

/* interface IXboxFiles */
/* [helpstring][unique][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxFiles;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("dfcf3f84-5394-448d-bcac-e30af6c840e1")
    IXboxFiles : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG Index,
            /* [retval][out] */ IXboxFile **File) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *Count) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IEnumVARIANT **Enumerator) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxFilesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxFiles * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxFiles * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxFiles * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxFiles * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxFiles * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxFiles * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxFiles * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IXboxFiles * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ IXboxFile **File);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IXboxFiles * This,
            /* [retval][out] */ LONG *Count);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IXboxFiles * This,
            /* [retval][out] */ IEnumVARIANT **Enumerator);
        
        END_INTERFACE
    } IXboxFilesVtbl;

    interface IXboxFiles
    {
        CONST_VTBL struct IXboxFilesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxFiles_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxFiles_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxFiles_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxFiles_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxFiles_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxFiles_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxFiles_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxFiles_get_Item(This,Index,File)	\
    (This)->lpVtbl -> get_Item(This,Index,File)

#define IXboxFiles_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IXboxFiles_get__NewEnum(This,Enumerator)	\
    (This)->lpVtbl -> get__NewEnum(This,Enumerator)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxFiles_get_Item_Proxy( 
    IXboxFiles * This,
    /* [in] */ LONG Index,
    /* [retval][out] */ IXboxFile **File);


void __RPC_STUB IXboxFiles_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxFiles_get_Count_Proxy( 
    IXboxFiles * This,
    /* [retval][out] */ LONG *Count);


void __RPC_STUB IXboxFiles_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxFiles_get__NewEnum_Proxy( 
    IXboxFiles * This,
    /* [retval][out] */ IEnumVARIANT **Enumerator);


void __RPC_STUB IXboxFiles_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxFiles_INTERFACE_DEFINED__ */


#ifndef __IXboxUser_INTERFACE_DEFINED__
#define __IXboxUser_INTERFACE_DEFINED__

/* interface IXboxUser */
/* [helpstring][unique][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxUser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6bb90673-5c3c-4b63-8d3c-479a5ede82c3")
    IXboxUser : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *UserName) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR UserName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HasReadAccess( 
            /* [retval][out] */ VARIANT_BOOL *ReadAccess) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_HasReadAccess( 
            /* [in] */ VARIANT_BOOL ReadAccess) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HasWriteAccess( 
            /* [retval][out] */ VARIANT_BOOL *WriteAccess) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_HasWriteAccess( 
            /* [in] */ VARIANT_BOOL WriteAccess) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HasControlAccess( 
            /* [retval][out] */ VARIANT_BOOL *ControlAccess) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_HasControlAccess( 
            /* [in] */ VARIANT_BOOL ControlAccess) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HasConfigureAccess( 
            /* [retval][out] */ VARIANT_BOOL *ConfigureAccess) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_HasConfigureAccess( 
            /* [in] */ VARIANT_BOOL ConfigureAccess) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HasManageAccess( 
            /* [retval][out] */ VARIANT_BOOL *ManageAccess) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_HasManageAccess( 
            /* [in] */ VARIANT_BOOL ManageAccess) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxUserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxUser * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxUser * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxUser * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxUser * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxUser * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxUser * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxUser * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IXboxUser * This,
            /* [retval][out] */ BSTR *UserName);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IXboxUser * This,
            /* [in] */ BSTR UserName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasReadAccess )( 
            IXboxUser * This,
            /* [retval][out] */ VARIANT_BOOL *ReadAccess);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HasReadAccess )( 
            IXboxUser * This,
            /* [in] */ VARIANT_BOOL ReadAccess);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasWriteAccess )( 
            IXboxUser * This,
            /* [retval][out] */ VARIANT_BOOL *WriteAccess);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HasWriteAccess )( 
            IXboxUser * This,
            /* [in] */ VARIANT_BOOL WriteAccess);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasControlAccess )( 
            IXboxUser * This,
            /* [retval][out] */ VARIANT_BOOL *ControlAccess);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HasControlAccess )( 
            IXboxUser * This,
            /* [in] */ VARIANT_BOOL ControlAccess);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasConfigureAccess )( 
            IXboxUser * This,
            /* [retval][out] */ VARIANT_BOOL *ConfigureAccess);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HasConfigureAccess )( 
            IXboxUser * This,
            /* [in] */ VARIANT_BOOL ConfigureAccess);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasManageAccess )( 
            IXboxUser * This,
            /* [retval][out] */ VARIANT_BOOL *ManageAccess);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HasManageAccess )( 
            IXboxUser * This,
            /* [in] */ VARIANT_BOOL ManageAccess);
        
        END_INTERFACE
    } IXboxUserVtbl;

    interface IXboxUser
    {
        CONST_VTBL struct IXboxUserVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxUser_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxUser_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxUser_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxUser_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxUser_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxUser_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxUser_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxUser_get_Name(This,UserName)	\
    (This)->lpVtbl -> get_Name(This,UserName)

#define IXboxUser_put_Name(This,UserName)	\
    (This)->lpVtbl -> put_Name(This,UserName)

#define IXboxUser_get_HasReadAccess(This,ReadAccess)	\
    (This)->lpVtbl -> get_HasReadAccess(This,ReadAccess)

#define IXboxUser_put_HasReadAccess(This,ReadAccess)	\
    (This)->lpVtbl -> put_HasReadAccess(This,ReadAccess)

#define IXboxUser_get_HasWriteAccess(This,WriteAccess)	\
    (This)->lpVtbl -> get_HasWriteAccess(This,WriteAccess)

#define IXboxUser_put_HasWriteAccess(This,WriteAccess)	\
    (This)->lpVtbl -> put_HasWriteAccess(This,WriteAccess)

#define IXboxUser_get_HasControlAccess(This,ControlAccess)	\
    (This)->lpVtbl -> get_HasControlAccess(This,ControlAccess)

#define IXboxUser_put_HasControlAccess(This,ControlAccess)	\
    (This)->lpVtbl -> put_HasControlAccess(This,ControlAccess)

#define IXboxUser_get_HasConfigureAccess(This,ConfigureAccess)	\
    (This)->lpVtbl -> get_HasConfigureAccess(This,ConfigureAccess)

#define IXboxUser_put_HasConfigureAccess(This,ConfigureAccess)	\
    (This)->lpVtbl -> put_HasConfigureAccess(This,ConfigureAccess)

#define IXboxUser_get_HasManageAccess(This,ManageAccess)	\
    (This)->lpVtbl -> get_HasManageAccess(This,ManageAccess)

#define IXboxUser_put_HasManageAccess(This,ManageAccess)	\
    (This)->lpVtbl -> put_HasManageAccess(This,ManageAccess)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxUser_get_Name_Proxy( 
    IXboxUser * This,
    /* [retval][out] */ BSTR *UserName);


void __RPC_STUB IXboxUser_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxUser_put_Name_Proxy( 
    IXboxUser * This,
    /* [in] */ BSTR UserName);


void __RPC_STUB IXboxUser_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxUser_get_HasReadAccess_Proxy( 
    IXboxUser * This,
    /* [retval][out] */ VARIANT_BOOL *ReadAccess);


void __RPC_STUB IXboxUser_get_HasReadAccess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxUser_put_HasReadAccess_Proxy( 
    IXboxUser * This,
    /* [in] */ VARIANT_BOOL ReadAccess);


void __RPC_STUB IXboxUser_put_HasReadAccess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxUser_get_HasWriteAccess_Proxy( 
    IXboxUser * This,
    /* [retval][out] */ VARIANT_BOOL *WriteAccess);


void __RPC_STUB IXboxUser_get_HasWriteAccess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxUser_put_HasWriteAccess_Proxy( 
    IXboxUser * This,
    /* [in] */ VARIANT_BOOL WriteAccess);


void __RPC_STUB IXboxUser_put_HasWriteAccess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxUser_get_HasControlAccess_Proxy( 
    IXboxUser * This,
    /* [retval][out] */ VARIANT_BOOL *ControlAccess);


void __RPC_STUB IXboxUser_get_HasControlAccess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxUser_put_HasControlAccess_Proxy( 
    IXboxUser * This,
    /* [in] */ VARIANT_BOOL ControlAccess);


void __RPC_STUB IXboxUser_put_HasControlAccess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxUser_get_HasConfigureAccess_Proxy( 
    IXboxUser * This,
    /* [retval][out] */ VARIANT_BOOL *ConfigureAccess);


void __RPC_STUB IXboxUser_get_HasConfigureAccess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxUser_put_HasConfigureAccess_Proxy( 
    IXboxUser * This,
    /* [in] */ VARIANT_BOOL ConfigureAccess);


void __RPC_STUB IXboxUser_put_HasConfigureAccess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxUser_get_HasManageAccess_Proxy( 
    IXboxUser * This,
    /* [retval][out] */ VARIANT_BOOL *ManageAccess);


void __RPC_STUB IXboxUser_get_HasManageAccess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxUser_put_HasManageAccess_Proxy( 
    IXboxUser * This,
    /* [in] */ VARIANT_BOOL ManageAccess);


void __RPC_STUB IXboxUser_put_HasManageAccess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxUser_INTERFACE_DEFINED__ */


#ifndef __IXboxUsers_INTERFACE_DEFINED__
#define __IXboxUsers_INTERFACE_DEFINED__

/* interface IXboxUsers */
/* [helpstring][unique][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxUsers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d5ee3179-7955-41b4-a507-bd78efc462c9")
    IXboxUsers : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG Index,
            /* [retval][out] */ IXboxUser **User) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *Count) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IEnumVARIANT **Enumerator) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxUsersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxUsers * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxUsers * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxUsers * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxUsers * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxUsers * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxUsers * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxUsers * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IXboxUsers * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ IXboxUser **User);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IXboxUsers * This,
            /* [retval][out] */ LONG *Count);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IXboxUsers * This,
            /* [retval][out] */ IEnumVARIANT **Enumerator);
        
        END_INTERFACE
    } IXboxUsersVtbl;

    interface IXboxUsers
    {
        CONST_VTBL struct IXboxUsersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxUsers_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxUsers_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxUsers_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxUsers_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxUsers_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxUsers_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxUsers_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxUsers_get_Item(This,Index,User)	\
    (This)->lpVtbl -> get_Item(This,Index,User)

#define IXboxUsers_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IXboxUsers_get__NewEnum(This,Enumerator)	\
    (This)->lpVtbl -> get__NewEnum(This,Enumerator)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxUsers_get_Item_Proxy( 
    IXboxUsers * This,
    /* [in] */ LONG Index,
    /* [retval][out] */ IXboxUser **User);


void __RPC_STUB IXboxUsers_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxUsers_get_Count_Proxy( 
    IXboxUsers * This,
    /* [retval][out] */ LONG *Count);


void __RPC_STUB IXboxUsers_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxUsers_get__NewEnum_Proxy( 
    IXboxUsers * This,
    /* [retval][out] */ IEnumVARIANT **Enumerator);


void __RPC_STUB IXboxUsers_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxUsers_INTERFACE_DEFINED__ */


#ifndef __IXboxDebugTarget_INTERFACE_DEFINED__
#define __IXboxDebugTarget_INTERFACE_DEFINED__

/* interface IXboxDebugTarget */
/* [helpstring][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxDebugTarget;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("43ccafd7-4636-43aa-b468-b7f6edca6651")
    IXboxDebugTarget : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *Name) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_IsDump( 
            /* [retval][out] */ VARIANT_BOOL *IsDump) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_XboxManager( 
            /* [retval][out] */ IXboxManager **XboxManager) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Console( 
            /* [retval][out] */ IXboxConsole **Console) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ConnectAsDebugger( 
            /* [in] */ BSTR DebuggerName,
            /* [in] */ _XboxDebugConnectFlags Flags) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DisconnectAsDebugger( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsDebuggerConnected( 
            /* [out] */ BSTR *DebuggerName,
            /* [out] */ BSTR *UserName,
            /* [retval][out] */ VARIANT_BOOL *Connected) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Modules( 
            /* [retval][out] */ IXboxModules **Modules) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Threads( 
            /* [retval][out] */ IXboxThreads **Threads) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetMemory( 
            /* [in] */ DWORD Address,
            /* [in] */ DWORD BytesToRead,
            /* [out][in] */ SAFEARRAY * Data,
            /* [out] */ DWORD *BytesRead) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetMemory( 
            /* [in] */ DWORD Address,
            /* [in] */ DWORD BytesToWrite,
            /* [in] */ SAFEARRAY * Data,
            /* [out] */ DWORD *BytesWritten) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE GetMemory_cpp( 
            /* [in] */ DWORD Address,
            /* [in] */ DWORD BytesToRead,
            /* [length_is][size_is][out] */ BYTE *Data,
            /* [out] */ DWORD *BytesRead) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE SetMemory_cpp( 
            /* [in] */ DWORD Address,
            /* [in] */ DWORD BytesToWrite,
            /* [size_is][in] */ BYTE *Data,
            /* [out] */ DWORD *BytesWritten) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE InvalidateMemoryCache( 
            /* [in] */ VARIANT_BOOL ExecutablePages,
            /* [in] */ DWORD Address,
            /* [in] */ DWORD Size) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MemoryCacheEnabled( 
            /* [retval][out] */ VARIANT_BOOL *Enabled) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_MemoryCacheEnabled( 
            /* [in] */ VARIANT_BOOL Enabled) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_MemoryRegions( 
            /* [retval][out] */ IXboxMemoryRegions **MemoryRegions) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_RunningProcessInfo( 
            /* [retval][out] */ PXBOX_PROCESS_INFO ProcessInfo) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE StopOn( 
            /* [in] */ _XboxStopOnFlags StopOn,
            /* [in] */ VARIANT_BOOL Stop) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Stop( 
            /* [out] */ VARIANT_BOOL *AlreadyStopped) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Go( 
            /* [out] */ VARIANT_BOOL *NotStopped) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetBreakpoint( 
            /* [in] */ DWORD Address) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveBreakpoint( 
            /* [in] */ DWORD Address) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveAllBreakpoints( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetInitialBreakpoint( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetDataBreakpoint( 
            /* [in] */ DWORD Address,
            /* [in] */ _XboxBreakpointType Type,
            /* [in] */ DWORD Size) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsBreakpoint( 
            /* [in] */ DWORD Address,
            /* [out] */ _XboxBreakpointType *Type) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WriteDump( 
            /* [in] */ BSTR Filename,
            /* [in] */ _XboxDumpFlags Type) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE CopyEventInfo( 
            /* [out] */ XBOX_EVENT_INFO *EventInfoDest,
            /* [in] */ XBOX_EVENT_INFO *EventInfoSource) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE FreeEventInfo( 
            /* [out][in] */ XBOX_EVENT_INFO *EventInfo) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PgoStartDataCollection( 
            DWORD PgoModule) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PgoStopDataCollection( 
            DWORD PgoModule) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PgoSaveSnapshot( 
            BSTR Phase,
            VARIANT_BOOL Reset,
            DWORD PgoModule) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PgoSetAllocScale( 
            DWORD PgoModule,
            DWORD BufferAllocScale) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxDebugTargetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxDebugTarget * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxDebugTarget * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxDebugTarget * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxDebugTarget * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxDebugTarget * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxDebugTarget * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxDebugTarget * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IXboxDebugTarget * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsDump )( 
            IXboxDebugTarget * This,
            /* [retval][out] */ VARIANT_BOOL *IsDump);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XboxManager )( 
            IXboxDebugTarget * This,
            /* [retval][out] */ IXboxManager **XboxManager);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Console )( 
            IXboxDebugTarget * This,
            /* [retval][out] */ IXboxConsole **Console);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ConnectAsDebugger )( 
            IXboxDebugTarget * This,
            /* [in] */ BSTR DebuggerName,
            /* [in] */ _XboxDebugConnectFlags Flags);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DisconnectAsDebugger )( 
            IXboxDebugTarget * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *IsDebuggerConnected )( 
            IXboxDebugTarget * This,
            /* [out] */ BSTR *DebuggerName,
            /* [out] */ BSTR *UserName,
            /* [retval][out] */ VARIANT_BOOL *Connected);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Modules )( 
            IXboxDebugTarget * This,
            /* [retval][out] */ IXboxModules **Modules);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Threads )( 
            IXboxDebugTarget * This,
            /* [retval][out] */ IXboxThreads **Threads);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetMemory )( 
            IXboxDebugTarget * This,
            /* [in] */ DWORD Address,
            /* [in] */ DWORD BytesToRead,
            /* [out][in] */ SAFEARRAY * Data,
            /* [out] */ DWORD *BytesRead);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetMemory )( 
            IXboxDebugTarget * This,
            /* [in] */ DWORD Address,
            /* [in] */ DWORD BytesToWrite,
            /* [in] */ SAFEARRAY * Data,
            /* [out] */ DWORD *BytesWritten);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *GetMemory_cpp )( 
            IXboxDebugTarget * This,
            /* [in] */ DWORD Address,
            /* [in] */ DWORD BytesToRead,
            /* [length_is][size_is][out] */ BYTE *Data,
            /* [out] */ DWORD *BytesRead);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *SetMemory_cpp )( 
            IXboxDebugTarget * This,
            /* [in] */ DWORD Address,
            /* [in] */ DWORD BytesToWrite,
            /* [size_is][in] */ BYTE *Data,
            /* [out] */ DWORD *BytesWritten);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *InvalidateMemoryCache )( 
            IXboxDebugTarget * This,
            /* [in] */ VARIANT_BOOL ExecutablePages,
            /* [in] */ DWORD Address,
            /* [in] */ DWORD Size);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemoryCacheEnabled )( 
            IXboxDebugTarget * This,
            /* [retval][out] */ VARIANT_BOOL *Enabled);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemoryCacheEnabled )( 
            IXboxDebugTarget * This,
            /* [in] */ VARIANT_BOOL Enabled);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemoryRegions )( 
            IXboxDebugTarget * This,
            /* [retval][out] */ IXboxMemoryRegions **MemoryRegions);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RunningProcessInfo )( 
            IXboxDebugTarget * This,
            /* [retval][out] */ PXBOX_PROCESS_INFO ProcessInfo);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *StopOn )( 
            IXboxDebugTarget * This,
            /* [in] */ _XboxStopOnFlags StopOn,
            /* [in] */ VARIANT_BOOL Stop);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IXboxDebugTarget * This,
            /* [out] */ VARIANT_BOOL *AlreadyStopped);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Go )( 
            IXboxDebugTarget * This,
            /* [out] */ VARIANT_BOOL *NotStopped);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetBreakpoint )( 
            IXboxDebugTarget * This,
            /* [in] */ DWORD Address);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RemoveBreakpoint )( 
            IXboxDebugTarget * This,
            /* [in] */ DWORD Address);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAllBreakpoints )( 
            IXboxDebugTarget * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetInitialBreakpoint )( 
            IXboxDebugTarget * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetDataBreakpoint )( 
            IXboxDebugTarget * This,
            /* [in] */ DWORD Address,
            /* [in] */ _XboxBreakpointType Type,
            /* [in] */ DWORD Size);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *IsBreakpoint )( 
            IXboxDebugTarget * This,
            /* [in] */ DWORD Address,
            /* [out] */ _XboxBreakpointType *Type);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WriteDump )( 
            IXboxDebugTarget * This,
            /* [in] */ BSTR Filename,
            /* [in] */ _XboxDumpFlags Type);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *CopyEventInfo )( 
            IXboxDebugTarget * This,
            /* [out] */ XBOX_EVENT_INFO *EventInfoDest,
            /* [in] */ XBOX_EVENT_INFO *EventInfoSource);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *FreeEventInfo )( 
            IXboxDebugTarget * This,
            /* [out][in] */ XBOX_EVENT_INFO *EventInfo);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *PgoStartDataCollection )( 
            IXboxDebugTarget * This,
            DWORD PgoModule);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *PgoStopDataCollection )( 
            IXboxDebugTarget * This,
            DWORD PgoModule);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *PgoSaveSnapshot )( 
            IXboxDebugTarget * This,
            BSTR Phase,
            VARIANT_BOOL Reset,
            DWORD PgoModule);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *PgoSetAllocScale )( 
            IXboxDebugTarget * This,
            DWORD PgoModule,
            DWORD BufferAllocScale);
        
        END_INTERFACE
    } IXboxDebugTargetVtbl;

    interface IXboxDebugTarget
    {
        CONST_VTBL struct IXboxDebugTargetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxDebugTarget_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxDebugTarget_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxDebugTarget_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxDebugTarget_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxDebugTarget_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxDebugTarget_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxDebugTarget_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxDebugTarget_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define IXboxDebugTarget_get_IsDump(This,IsDump)	\
    (This)->lpVtbl -> get_IsDump(This,IsDump)

#define IXboxDebugTarget_get_XboxManager(This,XboxManager)	\
    (This)->lpVtbl -> get_XboxManager(This,XboxManager)

#define IXboxDebugTarget_get_Console(This,Console)	\
    (This)->lpVtbl -> get_Console(This,Console)

#define IXboxDebugTarget_ConnectAsDebugger(This,DebuggerName,Flags)	\
    (This)->lpVtbl -> ConnectAsDebugger(This,DebuggerName,Flags)

#define IXboxDebugTarget_DisconnectAsDebugger(This)	\
    (This)->lpVtbl -> DisconnectAsDebugger(This)

#define IXboxDebugTarget_IsDebuggerConnected(This,DebuggerName,UserName,Connected)	\
    (This)->lpVtbl -> IsDebuggerConnected(This,DebuggerName,UserName,Connected)

#define IXboxDebugTarget_get_Modules(This,Modules)	\
    (This)->lpVtbl -> get_Modules(This,Modules)

#define IXboxDebugTarget_get_Threads(This,Threads)	\
    (This)->lpVtbl -> get_Threads(This,Threads)

#define IXboxDebugTarget_GetMemory(This,Address,BytesToRead,Data,BytesRead)	\
    (This)->lpVtbl -> GetMemory(This,Address,BytesToRead,Data,BytesRead)

#define IXboxDebugTarget_SetMemory(This,Address,BytesToWrite,Data,BytesWritten)	\
    (This)->lpVtbl -> SetMemory(This,Address,BytesToWrite,Data,BytesWritten)

#define IXboxDebugTarget_GetMemory_cpp(This,Address,BytesToRead,Data,BytesRead)	\
    (This)->lpVtbl -> GetMemory_cpp(This,Address,BytesToRead,Data,BytesRead)

#define IXboxDebugTarget_SetMemory_cpp(This,Address,BytesToWrite,Data,BytesWritten)	\
    (This)->lpVtbl -> SetMemory_cpp(This,Address,BytesToWrite,Data,BytesWritten)

#define IXboxDebugTarget_InvalidateMemoryCache(This,ExecutablePages,Address,Size)	\
    (This)->lpVtbl -> InvalidateMemoryCache(This,ExecutablePages,Address,Size)

#define IXboxDebugTarget_get_MemoryCacheEnabled(This,Enabled)	\
    (This)->lpVtbl -> get_MemoryCacheEnabled(This,Enabled)

#define IXboxDebugTarget_put_MemoryCacheEnabled(This,Enabled)	\
    (This)->lpVtbl -> put_MemoryCacheEnabled(This,Enabled)

#define IXboxDebugTarget_get_MemoryRegions(This,MemoryRegions)	\
    (This)->lpVtbl -> get_MemoryRegions(This,MemoryRegions)

#define IXboxDebugTarget_get_RunningProcessInfo(This,ProcessInfo)	\
    (This)->lpVtbl -> get_RunningProcessInfo(This,ProcessInfo)

#define IXboxDebugTarget_StopOn(This,StopOn,Stop)	\
    (This)->lpVtbl -> StopOn(This,StopOn,Stop)

#define IXboxDebugTarget_Stop(This,AlreadyStopped)	\
    (This)->lpVtbl -> Stop(This,AlreadyStopped)

#define IXboxDebugTarget_Go(This,NotStopped)	\
    (This)->lpVtbl -> Go(This,NotStopped)

#define IXboxDebugTarget_SetBreakpoint(This,Address)	\
    (This)->lpVtbl -> SetBreakpoint(This,Address)

#define IXboxDebugTarget_RemoveBreakpoint(This,Address)	\
    (This)->lpVtbl -> RemoveBreakpoint(This,Address)

#define IXboxDebugTarget_RemoveAllBreakpoints(This)	\
    (This)->lpVtbl -> RemoveAllBreakpoints(This)

#define IXboxDebugTarget_SetInitialBreakpoint(This)	\
    (This)->lpVtbl -> SetInitialBreakpoint(This)

#define IXboxDebugTarget_SetDataBreakpoint(This,Address,Type,Size)	\
    (This)->lpVtbl -> SetDataBreakpoint(This,Address,Type,Size)

#define IXboxDebugTarget_IsBreakpoint(This,Address,Type)	\
    (This)->lpVtbl -> IsBreakpoint(This,Address,Type)

#define IXboxDebugTarget_WriteDump(This,Filename,Type)	\
    (This)->lpVtbl -> WriteDump(This,Filename,Type)

#define IXboxDebugTarget_CopyEventInfo(This,EventInfoDest,EventInfoSource)	\
    (This)->lpVtbl -> CopyEventInfo(This,EventInfoDest,EventInfoSource)

#define IXboxDebugTarget_FreeEventInfo(This,EventInfo)	\
    (This)->lpVtbl -> FreeEventInfo(This,EventInfo)

#define IXboxDebugTarget_PgoStartDataCollection(This,PgoModule)	\
    (This)->lpVtbl -> PgoStartDataCollection(This,PgoModule)

#define IXboxDebugTarget_PgoStopDataCollection(This,PgoModule)	\
    (This)->lpVtbl -> PgoStopDataCollection(This,PgoModule)

#define IXboxDebugTarget_PgoSaveSnapshot(This,Phase,Reset,PgoModule)	\
    (This)->lpVtbl -> PgoSaveSnapshot(This,Phase,Reset,PgoModule)

#define IXboxDebugTarget_PgoSetAllocScale(This,PgoModule,BufferAllocScale)	\
    (This)->lpVtbl -> PgoSetAllocScale(This,PgoModule,BufferAllocScale)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_get_Name_Proxy( 
    IXboxDebugTarget * This,
    /* [retval][out] */ BSTR *Name);


void __RPC_STUB IXboxDebugTarget_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_get_IsDump_Proxy( 
    IXboxDebugTarget * This,
    /* [retval][out] */ VARIANT_BOOL *IsDump);


void __RPC_STUB IXboxDebugTarget_get_IsDump_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_get_XboxManager_Proxy( 
    IXboxDebugTarget * This,
    /* [retval][out] */ IXboxManager **XboxManager);


void __RPC_STUB IXboxDebugTarget_get_XboxManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_get_Console_Proxy( 
    IXboxDebugTarget * This,
    /* [retval][out] */ IXboxConsole **Console);


void __RPC_STUB IXboxDebugTarget_get_Console_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_ConnectAsDebugger_Proxy( 
    IXboxDebugTarget * This,
    /* [in] */ BSTR DebuggerName,
    /* [in] */ _XboxDebugConnectFlags Flags);


void __RPC_STUB IXboxDebugTarget_ConnectAsDebugger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_DisconnectAsDebugger_Proxy( 
    IXboxDebugTarget * This);


void __RPC_STUB IXboxDebugTarget_DisconnectAsDebugger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_IsDebuggerConnected_Proxy( 
    IXboxDebugTarget * This,
    /* [out] */ BSTR *DebuggerName,
    /* [out] */ BSTR *UserName,
    /* [retval][out] */ VARIANT_BOOL *Connected);


void __RPC_STUB IXboxDebugTarget_IsDebuggerConnected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_get_Modules_Proxy( 
    IXboxDebugTarget * This,
    /* [retval][out] */ IXboxModules **Modules);


void __RPC_STUB IXboxDebugTarget_get_Modules_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_get_Threads_Proxy( 
    IXboxDebugTarget * This,
    /* [retval][out] */ IXboxThreads **Threads);


void __RPC_STUB IXboxDebugTarget_get_Threads_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_GetMemory_Proxy( 
    IXboxDebugTarget * This,
    /* [in] */ DWORD Address,
    /* [in] */ DWORD BytesToRead,
    /* [out][in] */ SAFEARRAY * Data,
    /* [out] */ DWORD *BytesRead);


void __RPC_STUB IXboxDebugTarget_GetMemory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_SetMemory_Proxy( 
    IXboxDebugTarget * This,
    /* [in] */ DWORD Address,
    /* [in] */ DWORD BytesToWrite,
    /* [in] */ SAFEARRAY * Data,
    /* [out] */ DWORD *BytesWritten);


void __RPC_STUB IXboxDebugTarget_SetMemory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_GetMemory_cpp_Proxy( 
    IXboxDebugTarget * This,
    /* [in] */ DWORD Address,
    /* [in] */ DWORD BytesToRead,
    /* [length_is][size_is][out] */ BYTE *Data,
    /* [out] */ DWORD *BytesRead);


void __RPC_STUB IXboxDebugTarget_GetMemory_cpp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_SetMemory_cpp_Proxy( 
    IXboxDebugTarget * This,
    /* [in] */ DWORD Address,
    /* [in] */ DWORD BytesToWrite,
    /* [size_is][in] */ BYTE *Data,
    /* [out] */ DWORD *BytesWritten);


void __RPC_STUB IXboxDebugTarget_SetMemory_cpp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_InvalidateMemoryCache_Proxy( 
    IXboxDebugTarget * This,
    /* [in] */ VARIANT_BOOL ExecutablePages,
    /* [in] */ DWORD Address,
    /* [in] */ DWORD Size);


void __RPC_STUB IXboxDebugTarget_InvalidateMemoryCache_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_get_MemoryCacheEnabled_Proxy( 
    IXboxDebugTarget * This,
    /* [retval][out] */ VARIANT_BOOL *Enabled);


void __RPC_STUB IXboxDebugTarget_get_MemoryCacheEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_put_MemoryCacheEnabled_Proxy( 
    IXboxDebugTarget * This,
    /* [in] */ VARIANT_BOOL Enabled);


void __RPC_STUB IXboxDebugTarget_put_MemoryCacheEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_get_MemoryRegions_Proxy( 
    IXboxDebugTarget * This,
    /* [retval][out] */ IXboxMemoryRegions **MemoryRegions);


void __RPC_STUB IXboxDebugTarget_get_MemoryRegions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_get_RunningProcessInfo_Proxy( 
    IXboxDebugTarget * This,
    /* [retval][out] */ PXBOX_PROCESS_INFO ProcessInfo);


void __RPC_STUB IXboxDebugTarget_get_RunningProcessInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_StopOn_Proxy( 
    IXboxDebugTarget * This,
    /* [in] */ _XboxStopOnFlags StopOn,
    /* [in] */ VARIANT_BOOL Stop);


void __RPC_STUB IXboxDebugTarget_StopOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_Stop_Proxy( 
    IXboxDebugTarget * This,
    /* [out] */ VARIANT_BOOL *AlreadyStopped);


void __RPC_STUB IXboxDebugTarget_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_Go_Proxy( 
    IXboxDebugTarget * This,
    /* [out] */ VARIANT_BOOL *NotStopped);


void __RPC_STUB IXboxDebugTarget_Go_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_SetBreakpoint_Proxy( 
    IXboxDebugTarget * This,
    /* [in] */ DWORD Address);


void __RPC_STUB IXboxDebugTarget_SetBreakpoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_RemoveBreakpoint_Proxy( 
    IXboxDebugTarget * This,
    /* [in] */ DWORD Address);


void __RPC_STUB IXboxDebugTarget_RemoveBreakpoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_RemoveAllBreakpoints_Proxy( 
    IXboxDebugTarget * This);


void __RPC_STUB IXboxDebugTarget_RemoveAllBreakpoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_SetInitialBreakpoint_Proxy( 
    IXboxDebugTarget * This);


void __RPC_STUB IXboxDebugTarget_SetInitialBreakpoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_SetDataBreakpoint_Proxy( 
    IXboxDebugTarget * This,
    /* [in] */ DWORD Address,
    /* [in] */ _XboxBreakpointType Type,
    /* [in] */ DWORD Size);


void __RPC_STUB IXboxDebugTarget_SetDataBreakpoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_IsBreakpoint_Proxy( 
    IXboxDebugTarget * This,
    /* [in] */ DWORD Address,
    /* [out] */ _XboxBreakpointType *Type);


void __RPC_STUB IXboxDebugTarget_IsBreakpoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_WriteDump_Proxy( 
    IXboxDebugTarget * This,
    /* [in] */ BSTR Filename,
    /* [in] */ _XboxDumpFlags Type);


void __RPC_STUB IXboxDebugTarget_WriteDump_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_CopyEventInfo_Proxy( 
    IXboxDebugTarget * This,
    /* [out] */ XBOX_EVENT_INFO *EventInfoDest,
    /* [in] */ XBOX_EVENT_INFO *EventInfoSource);


void __RPC_STUB IXboxDebugTarget_CopyEventInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_FreeEventInfo_Proxy( 
    IXboxDebugTarget * This,
    /* [out][in] */ XBOX_EVENT_INFO *EventInfo);


void __RPC_STUB IXboxDebugTarget_FreeEventInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_PgoStartDataCollection_Proxy( 
    IXboxDebugTarget * This,
    DWORD PgoModule);


void __RPC_STUB IXboxDebugTarget_PgoStartDataCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_PgoStopDataCollection_Proxy( 
    IXboxDebugTarget * This,
    DWORD PgoModule);


void __RPC_STUB IXboxDebugTarget_PgoStopDataCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_PgoSaveSnapshot_Proxy( 
    IXboxDebugTarget * This,
    BSTR Phase,
    VARIANT_BOOL Reset,
    DWORD PgoModule);


void __RPC_STUB IXboxDebugTarget_PgoSaveSnapshot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxDebugTarget_PgoSetAllocScale_Proxy( 
    IXboxDebugTarget * This,
    DWORD PgoModule,
    DWORD BufferAllocScale);


void __RPC_STUB IXboxDebugTarget_PgoSetAllocScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxDebugTarget_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_xdevkit_0271 */
/* [local] */ 

namespace eXboxAutomationButtonFlags {
/* [v1_enum] */ 
enum XboxAutomationButtonFlags
    {	DPadUp	= 0x1,
	DPadDown	= 0x2,
	DPadLeft	= 0x4,
	DPadRight	= 0x8,
	StartButton	= 0x10,
	BackButton	= 0x20,
	LeftThumbButton	= 0x40,
	RightThumbButton	= 0x80,
	LeftShoulderButton	= 0x100,
	RightShoulderButton	= 0x200,
	A_Button	= 0x1000,
	B_Button	= 0x2000,
	X_Button	= 0x4000,
	Y_Button	= 0x8000,
	Xbox360_Button	= 0x400,
	Bind_Button	= 0x800
    } ;
}
/*
typedef enum XboxAutomationButtonFlags _XboxAutomationButtonFlags;

*/ typedef int _XboxAutomationButtonFlags;
typedef struct XBOX_AUTOMATION_GAMEPAD
    {
    _XboxAutomationButtonFlags Buttons;
    DWORD LeftTrigger;
    DWORD RightTrigger;
    long LeftThumbX;
    long LeftThumbY;
    long RightThumbX;
    long RightThumbY;
    } 	XBOX_AUTOMATION_GAMEPAD;

typedef struct XBOX_AUTOMATION_GAMEPAD *PXBOX_AUTOMATION_GAMEPAD;



extern RPC_IF_HANDLE __MIDL_itf_xdevkit_0271_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_xdevkit_0271_v0_0_s_ifspec;

#ifndef __IXboxAutomation_INTERFACE_DEFINED__
#define __IXboxAutomation_INTERFACE_DEFINED__

/* interface IXboxAutomation */
/* [helpstring][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxAutomation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D81F3E2E-8304-4024-8997-BB1C893516B0")
    IXboxAutomation : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetInputProcess( 
            /* [in] */ DWORD UserIndex,
            /* [out] */ VARIANT_BOOL *SystemProcess) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE BindController( 
            /* [in] */ DWORD UserIndex,
            /* [in] */ DWORD QueueLength) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UnbindController( 
            /* [in] */ DWORD UserIndex) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ConnectController( 
            /* [in] */ DWORD UserIndex) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DisconnectController( 
            /* [in] */ DWORD UserIndex) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetGamepadState( 
            /* [in] */ DWORD UserIndex,
            /* [in] */ PXBOX_AUTOMATION_GAMEPAD Gamepad) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE QueueGamepadState_cpp( 
            /* [in] */ DWORD UserIndex,
            /* [size_is][in] */ PXBOX_AUTOMATION_GAMEPAD GamepadArray,
            /* [size_is][in] */ DWORD *TimedDurationArray,
            /* [size_is][in] */ DWORD *CountDurationArray,
            /* [in] */ DWORD ItemCount,
            /* [out] */ DWORD *ItemsAddedToQueue) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE QueueGamepadState( 
            /* [in] */ DWORD UserIndex,
            /* [in] */ XBOX_AUTOMATION_GAMEPAD *Gamepad,
            /* [in] */ DWORD TimedDuration,
            /* [in] */ DWORD CountDuration,
            /* [retval][out] */ VARIANT_BOOL *AddedToQueue) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ClearGamepadQueue( 
            /* [in] */ DWORD UserIndex) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE QueryGamepadQueue( 
            /* [in] */ DWORD UserIndex,
            /* [out] */ DWORD *QueueLength,
            /* [out] */ DWORD *ItemsInQueue,
            /* [out] */ DWORD *TimedDurationRemaining,
            /* [out] */ DWORD *CountDurationRemaining) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetUserDefaultProfile( 
            /* [out] */ LONGLONG *Xuid) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetUserDefaultProfile( 
            /* [in] */ LONGLONG Xuid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxAutomationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxAutomation * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxAutomation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxAutomation * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxAutomation * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxAutomation * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxAutomation * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxAutomation * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetInputProcess )( 
            IXboxAutomation * This,
            /* [in] */ DWORD UserIndex,
            /* [out] */ VARIANT_BOOL *SystemProcess);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *BindController )( 
            IXboxAutomation * This,
            /* [in] */ DWORD UserIndex,
            /* [in] */ DWORD QueueLength);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UnbindController )( 
            IXboxAutomation * This,
            /* [in] */ DWORD UserIndex);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ConnectController )( 
            IXboxAutomation * This,
            /* [in] */ DWORD UserIndex);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DisconnectController )( 
            IXboxAutomation * This,
            /* [in] */ DWORD UserIndex);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetGamepadState )( 
            IXboxAutomation * This,
            /* [in] */ DWORD UserIndex,
            /* [in] */ PXBOX_AUTOMATION_GAMEPAD Gamepad);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *QueueGamepadState_cpp )( 
            IXboxAutomation * This,
            /* [in] */ DWORD UserIndex,
            /* [size_is][in] */ PXBOX_AUTOMATION_GAMEPAD GamepadArray,
            /* [size_is][in] */ DWORD *TimedDurationArray,
            /* [size_is][in] */ DWORD *CountDurationArray,
            /* [in] */ DWORD ItemCount,
            /* [out] */ DWORD *ItemsAddedToQueue);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *QueueGamepadState )( 
            IXboxAutomation * This,
            /* [in] */ DWORD UserIndex,
            /* [in] */ XBOX_AUTOMATION_GAMEPAD *Gamepad,
            /* [in] */ DWORD TimedDuration,
            /* [in] */ DWORD CountDuration,
            /* [retval][out] */ VARIANT_BOOL *AddedToQueue);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ClearGamepadQueue )( 
            IXboxAutomation * This,
            /* [in] */ DWORD UserIndex);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *QueryGamepadQueue )( 
            IXboxAutomation * This,
            /* [in] */ DWORD UserIndex,
            /* [out] */ DWORD *QueueLength,
            /* [out] */ DWORD *ItemsInQueue,
            /* [out] */ DWORD *TimedDurationRemaining,
            /* [out] */ DWORD *CountDurationRemaining);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetUserDefaultProfile )( 
            IXboxAutomation * This,
            /* [out] */ LONGLONG *Xuid);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetUserDefaultProfile )( 
            IXboxAutomation * This,
            /* [in] */ LONGLONG Xuid);
        
        END_INTERFACE
    } IXboxAutomationVtbl;

    interface IXboxAutomation
    {
        CONST_VTBL struct IXboxAutomationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxAutomation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxAutomation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxAutomation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxAutomation_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxAutomation_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxAutomation_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxAutomation_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxAutomation_GetInputProcess(This,UserIndex,SystemProcess)	\
    (This)->lpVtbl -> GetInputProcess(This,UserIndex,SystemProcess)

#define IXboxAutomation_BindController(This,UserIndex,QueueLength)	\
    (This)->lpVtbl -> BindController(This,UserIndex,QueueLength)

#define IXboxAutomation_UnbindController(This,UserIndex)	\
    (This)->lpVtbl -> UnbindController(This,UserIndex)

#define IXboxAutomation_ConnectController(This,UserIndex)	\
    (This)->lpVtbl -> ConnectController(This,UserIndex)

#define IXboxAutomation_DisconnectController(This,UserIndex)	\
    (This)->lpVtbl -> DisconnectController(This,UserIndex)

#define IXboxAutomation_SetGamepadState(This,UserIndex,Gamepad)	\
    (This)->lpVtbl -> SetGamepadState(This,UserIndex,Gamepad)

#define IXboxAutomation_QueueGamepadState_cpp(This,UserIndex,GamepadArray,TimedDurationArray,CountDurationArray,ItemCount,ItemsAddedToQueue)	\
    (This)->lpVtbl -> QueueGamepadState_cpp(This,UserIndex,GamepadArray,TimedDurationArray,CountDurationArray,ItemCount,ItemsAddedToQueue)

#define IXboxAutomation_QueueGamepadState(This,UserIndex,Gamepad,TimedDuration,CountDuration,AddedToQueue)	\
    (This)->lpVtbl -> QueueGamepadState(This,UserIndex,Gamepad,TimedDuration,CountDuration,AddedToQueue)

#define IXboxAutomation_ClearGamepadQueue(This,UserIndex)	\
    (This)->lpVtbl -> ClearGamepadQueue(This,UserIndex)

#define IXboxAutomation_QueryGamepadQueue(This,UserIndex,QueueLength,ItemsInQueue,TimedDurationRemaining,CountDurationRemaining)	\
    (This)->lpVtbl -> QueryGamepadQueue(This,UserIndex,QueueLength,ItemsInQueue,TimedDurationRemaining,CountDurationRemaining)

#define IXboxAutomation_GetUserDefaultProfile(This,Xuid)	\
    (This)->lpVtbl -> GetUserDefaultProfile(This,Xuid)

#define IXboxAutomation_SetUserDefaultProfile(This,Xuid)	\
    (This)->lpVtbl -> SetUserDefaultProfile(This,Xuid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IXboxAutomation_GetInputProcess_Proxy( 
    IXboxAutomation * This,
    /* [in] */ DWORD UserIndex,
    /* [out] */ VARIANT_BOOL *SystemProcess);


void __RPC_STUB IXboxAutomation_GetInputProcess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxAutomation_BindController_Proxy( 
    IXboxAutomation * This,
    /* [in] */ DWORD UserIndex,
    /* [in] */ DWORD QueueLength);


void __RPC_STUB IXboxAutomation_BindController_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxAutomation_UnbindController_Proxy( 
    IXboxAutomation * This,
    /* [in] */ DWORD UserIndex);


void __RPC_STUB IXboxAutomation_UnbindController_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxAutomation_ConnectController_Proxy( 
    IXboxAutomation * This,
    /* [in] */ DWORD UserIndex);


void __RPC_STUB IXboxAutomation_ConnectController_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxAutomation_DisconnectController_Proxy( 
    IXboxAutomation * This,
    /* [in] */ DWORD UserIndex);


void __RPC_STUB IXboxAutomation_DisconnectController_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxAutomation_SetGamepadState_Proxy( 
    IXboxAutomation * This,
    /* [in] */ DWORD UserIndex,
    /* [in] */ PXBOX_AUTOMATION_GAMEPAD Gamepad);


void __RPC_STUB IXboxAutomation_SetGamepadState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxAutomation_QueueGamepadState_cpp_Proxy( 
    IXboxAutomation * This,
    /* [in] */ DWORD UserIndex,
    /* [size_is][in] */ PXBOX_AUTOMATION_GAMEPAD GamepadArray,
    /* [size_is][in] */ DWORD *TimedDurationArray,
    /* [size_is][in] */ DWORD *CountDurationArray,
    /* [in] */ DWORD ItemCount,
    /* [out] */ DWORD *ItemsAddedToQueue);


void __RPC_STUB IXboxAutomation_QueueGamepadState_cpp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxAutomation_QueueGamepadState_Proxy( 
    IXboxAutomation * This,
    /* [in] */ DWORD UserIndex,
    /* [in] */ XBOX_AUTOMATION_GAMEPAD *Gamepad,
    /* [in] */ DWORD TimedDuration,
    /* [in] */ DWORD CountDuration,
    /* [retval][out] */ VARIANT_BOOL *AddedToQueue);


void __RPC_STUB IXboxAutomation_QueueGamepadState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxAutomation_ClearGamepadQueue_Proxy( 
    IXboxAutomation * This,
    /* [in] */ DWORD UserIndex);


void __RPC_STUB IXboxAutomation_ClearGamepadQueue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxAutomation_QueryGamepadQueue_Proxy( 
    IXboxAutomation * This,
    /* [in] */ DWORD UserIndex,
    /* [out] */ DWORD *QueueLength,
    /* [out] */ DWORD *ItemsInQueue,
    /* [out] */ DWORD *TimedDurationRemaining,
    /* [out] */ DWORD *CountDurationRemaining);


void __RPC_STUB IXboxAutomation_QueryGamepadQueue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxAutomation_GetUserDefaultProfile_Proxy( 
    IXboxAutomation * This,
    /* [out] */ LONGLONG *Xuid);


void __RPC_STUB IXboxAutomation_GetUserDefaultProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxAutomation_SetUserDefaultProfile_Proxy( 
    IXboxAutomation * This,
    /* [in] */ LONGLONG Xuid);


void __RPC_STUB IXboxAutomation_SetUserDefaultProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxAutomation_INTERFACE_DEFINED__ */


#ifndef __IXboxModule_INTERFACE_DEFINED__
#define __IXboxModule_INTERFACE_DEFINED__

/* interface IXboxModule */
/* [helpstring][unique][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxModule;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0eee2aa0-60f0-4c18-b4ed-e3933e659847")
    IXboxModule : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ModuleInfo( 
            /* [retval][out] */ XBOX_MODULE_INFO *ModuleInfo) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Sections( 
            /* [retval][out] */ IXboxSections **Sections) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetFunctionInfo( 
            /* [in] */ DWORD Address,
            /* [out] */ XBOX_FUNCTION_INFO *FunctionInfo) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_OriginalSize( 
            /* [retval][out] */ DWORD *OriginalSize) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Executable( 
            /* [retval][out] */ IXboxExecutable **Executable) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetEntryPointAddress( 
            /* [retval][out] */ DWORD *EntryPointAddress) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxModuleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxModule * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxModule * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxModule * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxModule * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxModule * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxModule * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxModule * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ModuleInfo )( 
            IXboxModule * This,
            /* [retval][out] */ XBOX_MODULE_INFO *ModuleInfo);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sections )( 
            IXboxModule * This,
            /* [retval][out] */ IXboxSections **Sections);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetFunctionInfo )( 
            IXboxModule * This,
            /* [in] */ DWORD Address,
            /* [out] */ XBOX_FUNCTION_INFO *FunctionInfo);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OriginalSize )( 
            IXboxModule * This,
            /* [retval][out] */ DWORD *OriginalSize);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Executable )( 
            IXboxModule * This,
            /* [retval][out] */ IXboxExecutable **Executable);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetEntryPointAddress )( 
            IXboxModule * This,
            /* [retval][out] */ DWORD *EntryPointAddress);
        
        END_INTERFACE
    } IXboxModuleVtbl;

    interface IXboxModule
    {
        CONST_VTBL struct IXboxModuleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxModule_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxModule_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxModule_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxModule_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxModule_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxModule_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxModule_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxModule_get_ModuleInfo(This,ModuleInfo)	\
    (This)->lpVtbl -> get_ModuleInfo(This,ModuleInfo)

#define IXboxModule_get_Sections(This,Sections)	\
    (This)->lpVtbl -> get_Sections(This,Sections)

#define IXboxModule_GetFunctionInfo(This,Address,FunctionInfo)	\
    (This)->lpVtbl -> GetFunctionInfo(This,Address,FunctionInfo)

#define IXboxModule_get_OriginalSize(This,OriginalSize)	\
    (This)->lpVtbl -> get_OriginalSize(This,OriginalSize)

#define IXboxModule_get_Executable(This,Executable)	\
    (This)->lpVtbl -> get_Executable(This,Executable)

#define IXboxModule_GetEntryPointAddress(This,EntryPointAddress)	\
    (This)->lpVtbl -> GetEntryPointAddress(This,EntryPointAddress)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxModule_get_ModuleInfo_Proxy( 
    IXboxModule * This,
    /* [retval][out] */ XBOX_MODULE_INFO *ModuleInfo);


void __RPC_STUB IXboxModule_get_ModuleInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxModule_get_Sections_Proxy( 
    IXboxModule * This,
    /* [retval][out] */ IXboxSections **Sections);


void __RPC_STUB IXboxModule_get_Sections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxModule_GetFunctionInfo_Proxy( 
    IXboxModule * This,
    /* [in] */ DWORD Address,
    /* [out] */ XBOX_FUNCTION_INFO *FunctionInfo);


void __RPC_STUB IXboxModule_GetFunctionInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxModule_get_OriginalSize_Proxy( 
    IXboxModule * This,
    /* [retval][out] */ DWORD *OriginalSize);


void __RPC_STUB IXboxModule_get_OriginalSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxModule_get_Executable_Proxy( 
    IXboxModule * This,
    /* [retval][out] */ IXboxExecutable **Executable);


void __RPC_STUB IXboxModule_get_Executable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxModule_GetEntryPointAddress_Proxy( 
    IXboxModule * This,
    /* [retval][out] */ DWORD *EntryPointAddress);


void __RPC_STUB IXboxModule_GetEntryPointAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxModule_INTERFACE_DEFINED__ */


#ifndef __IXboxModules_INTERFACE_DEFINED__
#define __IXboxModules_INTERFACE_DEFINED__

/* interface IXboxModules */
/* [helpstring][unique][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxModules;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e4f0c350-d2da-426e-adec-3d01f60fc842")
    IXboxModules : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG Index,
            /* [retval][out] */ IXboxModule **Module) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *Count) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IEnumVARIANT **Enumerator) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxModulesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxModules * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxModules * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxModules * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxModules * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxModules * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxModules * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxModules * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IXboxModules * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ IXboxModule **Module);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IXboxModules * This,
            /* [retval][out] */ LONG *Count);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IXboxModules * This,
            /* [retval][out] */ IEnumVARIANT **Enumerator);
        
        END_INTERFACE
    } IXboxModulesVtbl;

    interface IXboxModules
    {
        CONST_VTBL struct IXboxModulesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxModules_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxModules_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxModules_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxModules_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxModules_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxModules_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxModules_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxModules_get_Item(This,Index,Module)	\
    (This)->lpVtbl -> get_Item(This,Index,Module)

#define IXboxModules_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IXboxModules_get__NewEnum(This,Enumerator)	\
    (This)->lpVtbl -> get__NewEnum(This,Enumerator)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxModules_get_Item_Proxy( 
    IXboxModules * This,
    /* [in] */ LONG Index,
    /* [retval][out] */ IXboxModule **Module);


void __RPC_STUB IXboxModules_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxModules_get_Count_Proxy( 
    IXboxModules * This,
    /* [retval][out] */ LONG *Count);


void __RPC_STUB IXboxModules_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxModules_get__NewEnum_Proxy( 
    IXboxModules * This,
    /* [retval][out] */ IEnumVARIANT **Enumerator);


void __RPC_STUB IXboxModules_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxModules_INTERFACE_DEFINED__ */


#ifndef __IXboxExecutable_INTERFACE_DEFINED__
#define __IXboxExecutable_INTERFACE_DEFINED__

/* interface IXboxExecutable */
/* [helpstring][unique][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxExecutable;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4B103593-DB52-4e18-913D-B3B17824BD76")
    IXboxExecutable : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetPEModuleName( 
            /* [retval][out] */ BSTR *ModuleName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxExecutableVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxExecutable * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxExecutable * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxExecutable * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxExecutable * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxExecutable * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxExecutable * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxExecutable * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetPEModuleName )( 
            IXboxExecutable * This,
            /* [retval][out] */ BSTR *ModuleName);
        
        END_INTERFACE
    } IXboxExecutableVtbl;

    interface IXboxExecutable
    {
        CONST_VTBL struct IXboxExecutableVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxExecutable_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxExecutable_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxExecutable_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxExecutable_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxExecutable_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxExecutable_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxExecutable_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxExecutable_GetPEModuleName(This,ModuleName)	\
    (This)->lpVtbl -> GetPEModuleName(This,ModuleName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IXboxExecutable_GetPEModuleName_Proxy( 
    IXboxExecutable * This,
    /* [retval][out] */ BSTR *ModuleName);


void __RPC_STUB IXboxExecutable_GetPEModuleName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxExecutable_INTERFACE_DEFINED__ */


#ifndef __IXboxSection_INTERFACE_DEFINED__
#define __IXboxSection_INTERFACE_DEFINED__

/* interface IXboxSection */
/* [helpstring][unique][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d6df8112-0326-4d29-a6b8-cfb0d89c358a")
    IXboxSection : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SectionInfo( 
            /* [retval][out] */ XBOX_SECTION_INFO *SectionInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxSection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxSection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxSection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxSection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxSection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxSection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SectionInfo )( 
            IXboxSection * This,
            /* [retval][out] */ XBOX_SECTION_INFO *SectionInfo);
        
        END_INTERFACE
    } IXboxSectionVtbl;

    interface IXboxSection
    {
        CONST_VTBL struct IXboxSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxSection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxSection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxSection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxSection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxSection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxSection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxSection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxSection_get_SectionInfo(This,SectionInfo)	\
    (This)->lpVtbl -> get_SectionInfo(This,SectionInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxSection_get_SectionInfo_Proxy( 
    IXboxSection * This,
    /* [retval][out] */ XBOX_SECTION_INFO *SectionInfo);


void __RPC_STUB IXboxSection_get_SectionInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxSection_INTERFACE_DEFINED__ */


#ifndef __IXboxSections_INTERFACE_DEFINED__
#define __IXboxSections_INTERFACE_DEFINED__

/* interface IXboxSections */
/* [helpstring][unique][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxSections;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9762df66-9516-4531-a507-a11034056f5e")
    IXboxSections : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG Index,
            /* [retval][out] */ IXboxSection **Section) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *Count) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IEnumVARIANT **Enumerator) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxSectionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxSections * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxSections * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxSections * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxSections * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxSections * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxSections * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxSections * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IXboxSections * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ IXboxSection **Section);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IXboxSections * This,
            /* [retval][out] */ LONG *Count);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IXboxSections * This,
            /* [retval][out] */ IEnumVARIANT **Enumerator);
        
        END_INTERFACE
    } IXboxSectionsVtbl;

    interface IXboxSections
    {
        CONST_VTBL struct IXboxSectionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxSections_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxSections_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxSections_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxSections_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxSections_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxSections_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxSections_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxSections_get_Item(This,Index,Section)	\
    (This)->lpVtbl -> get_Item(This,Index,Section)

#define IXboxSections_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IXboxSections_get__NewEnum(This,Enumerator)	\
    (This)->lpVtbl -> get__NewEnum(This,Enumerator)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxSections_get_Item_Proxy( 
    IXboxSections * This,
    /* [in] */ LONG Index,
    /* [retval][out] */ IXboxSection **Section);


void __RPC_STUB IXboxSections_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxSections_get_Count_Proxy( 
    IXboxSections * This,
    /* [retval][out] */ LONG *Count);


void __RPC_STUB IXboxSections_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxSections_get__NewEnum_Proxy( 
    IXboxSections * This,
    /* [retval][out] */ IEnumVARIANT **Enumerator);


void __RPC_STUB IXboxSections_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxSections_INTERFACE_DEFINED__ */


#ifndef __IXboxThread_INTERFACE_DEFINED__
#define __IXboxThread_INTERFACE_DEFINED__

/* interface IXboxThread */
/* [helpstring][unique][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxThread;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8f1e63f5-85ba-4b2d-ad9c-1fa6b750d57f")
    IXboxThread : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ThreadId( 
            /* [retval][out] */ DWORD *ThreadId) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ThreadInfo( 
            /* [retval][out] */ XBOX_THREAD_INFO *ThreadInfo) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_StopEventInfo( 
            /* [retval][out] */ PXBOX_EVENT_INFO StopEventInfo) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TopOfStack( 
            /* [retval][out] */ IXboxStackFrame **StackFrame) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Halt( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Continue( 
            /* [in] */ VARIANT_BOOL Exception) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Suspend( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Resume( void) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentProcessor( 
            /* [retval][out] */ DWORD *Processor) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LastError( 
            /* [retval][out] */ DWORD *LastError) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxThreadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxThread * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxThread * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxThread * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxThread * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxThread * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxThread * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxThread * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ThreadId )( 
            IXboxThread * This,
            /* [retval][out] */ DWORD *ThreadId);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ThreadInfo )( 
            IXboxThread * This,
            /* [retval][out] */ XBOX_THREAD_INFO *ThreadInfo);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopEventInfo )( 
            IXboxThread * This,
            /* [retval][out] */ PXBOX_EVENT_INFO StopEventInfo);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopOfStack )( 
            IXboxThread * This,
            /* [retval][out] */ IXboxStackFrame **StackFrame);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Halt )( 
            IXboxThread * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Continue )( 
            IXboxThread * This,
            /* [in] */ VARIANT_BOOL Exception);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Suspend )( 
            IXboxThread * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Resume )( 
            IXboxThread * This);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentProcessor )( 
            IXboxThread * This,
            /* [retval][out] */ DWORD *Processor);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastError )( 
            IXboxThread * This,
            /* [retval][out] */ DWORD *LastError);
        
        END_INTERFACE
    } IXboxThreadVtbl;

    interface IXboxThread
    {
        CONST_VTBL struct IXboxThreadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxThread_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxThread_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxThread_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxThread_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxThread_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxThread_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxThread_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxThread_get_ThreadId(This,ThreadId)	\
    (This)->lpVtbl -> get_ThreadId(This,ThreadId)

#define IXboxThread_get_ThreadInfo(This,ThreadInfo)	\
    (This)->lpVtbl -> get_ThreadInfo(This,ThreadInfo)

#define IXboxThread_get_StopEventInfo(This,StopEventInfo)	\
    (This)->lpVtbl -> get_StopEventInfo(This,StopEventInfo)

#define IXboxThread_get_TopOfStack(This,StackFrame)	\
    (This)->lpVtbl -> get_TopOfStack(This,StackFrame)

#define IXboxThread_Halt(This)	\
    (This)->lpVtbl -> Halt(This)

#define IXboxThread_Continue(This,Exception)	\
    (This)->lpVtbl -> Continue(This,Exception)

#define IXboxThread_Suspend(This)	\
    (This)->lpVtbl -> Suspend(This)

#define IXboxThread_Resume(This)	\
    (This)->lpVtbl -> Resume(This)

#define IXboxThread_get_CurrentProcessor(This,Processor)	\
    (This)->lpVtbl -> get_CurrentProcessor(This,Processor)

#define IXboxThread_get_LastError(This,LastError)	\
    (This)->lpVtbl -> get_LastError(This,LastError)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxThread_get_ThreadId_Proxy( 
    IXboxThread * This,
    /* [retval][out] */ DWORD *ThreadId);


void __RPC_STUB IXboxThread_get_ThreadId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxThread_get_ThreadInfo_Proxy( 
    IXboxThread * This,
    /* [retval][out] */ XBOX_THREAD_INFO *ThreadInfo);


void __RPC_STUB IXboxThread_get_ThreadInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxThread_get_StopEventInfo_Proxy( 
    IXboxThread * This,
    /* [retval][out] */ PXBOX_EVENT_INFO StopEventInfo);


void __RPC_STUB IXboxThread_get_StopEventInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxThread_get_TopOfStack_Proxy( 
    IXboxThread * This,
    /* [retval][out] */ IXboxStackFrame **StackFrame);


void __RPC_STUB IXboxThread_get_TopOfStack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxThread_Halt_Proxy( 
    IXboxThread * This);


void __RPC_STUB IXboxThread_Halt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxThread_Continue_Proxy( 
    IXboxThread * This,
    /* [in] */ VARIANT_BOOL Exception);


void __RPC_STUB IXboxThread_Continue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxThread_Suspend_Proxy( 
    IXboxThread * This);


void __RPC_STUB IXboxThread_Suspend_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxThread_Resume_Proxy( 
    IXboxThread * This);


void __RPC_STUB IXboxThread_Resume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxThread_get_CurrentProcessor_Proxy( 
    IXboxThread * This,
    /* [retval][out] */ DWORD *Processor);


void __RPC_STUB IXboxThread_get_CurrentProcessor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxThread_get_LastError_Proxy( 
    IXboxThread * This,
    /* [retval][out] */ DWORD *LastError);


void __RPC_STUB IXboxThread_get_LastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxThread_INTERFACE_DEFINED__ */


#ifndef __IXboxThreads_INTERFACE_DEFINED__
#define __IXboxThreads_INTERFACE_DEFINED__

/* interface IXboxThreads */
/* [helpstring][unique][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxThreads;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("da7c0784-9a34-4a9e-a040-59ebcea92c1e")
    IXboxThreads : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG Index,
            /* [retval][out] */ IXboxThread **Thread) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *Count) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IEnumVARIANT **Enumerator) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxThreadsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxThreads * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxThreads * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxThreads * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxThreads * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxThreads * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxThreads * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxThreads * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IXboxThreads * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ IXboxThread **Thread);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IXboxThreads * This,
            /* [retval][out] */ LONG *Count);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IXboxThreads * This,
            /* [retval][out] */ IEnumVARIANT **Enumerator);
        
        END_INTERFACE
    } IXboxThreadsVtbl;

    interface IXboxThreads
    {
        CONST_VTBL struct IXboxThreadsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxThreads_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxThreads_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxThreads_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxThreads_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxThreads_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxThreads_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxThreads_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxThreads_get_Item(This,Index,Thread)	\
    (This)->lpVtbl -> get_Item(This,Index,Thread)

#define IXboxThreads_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IXboxThreads_get__NewEnum(This,Enumerator)	\
    (This)->lpVtbl -> get__NewEnum(This,Enumerator)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxThreads_get_Item_Proxy( 
    IXboxThreads * This,
    /* [in] */ LONG Index,
    /* [retval][out] */ IXboxThread **Thread);


void __RPC_STUB IXboxThreads_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxThreads_get_Count_Proxy( 
    IXboxThreads * This,
    /* [retval][out] */ LONG *Count);


void __RPC_STUB IXboxThreads_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxThreads_get__NewEnum_Proxy( 
    IXboxThreads * This,
    /* [retval][out] */ IEnumVARIANT **Enumerator);


void __RPC_STUB IXboxThreads_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxThreads_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_xdevkit_0279 */
/* [local] */ 

namespace eXboxRegisters32{
/* [v1_enum] */ 
enum XboxRegisters32
    {	msr	= 0,
	iar	= msr + 1,
	lr	= iar + 1,
	cr	= lr + 1,
	xer	= cr + 1
    } ;
}
/*
typedef enum XboxRegisters32 _XboxRegisters32;

*/ typedef eXboxRegisters32::XboxRegisters32 _XboxRegisters32;
namespace eXboxRegisters64{
/* [v1_enum] */ 
enum XboxRegisters64
    {	ctr	= 0,
	r0	= ctr + 1,
	r1	= r0 + 1,
	r2	= r1 + 1,
	r3	= r2 + 1,
	r4	= r3 + 1,
	r5	= r4 + 1,
	r6	= r5 + 1,
	r7	= r6 + 1,
	r8	= r7 + 1,
	r9	= r8 + 1,
	r10	= r9 + 1,
	r11	= r10 + 1,
	r12	= r11 + 1,
	r13	= r12 + 1,
	r14	= r13 + 1,
	r15	= r14 + 1,
	r16	= r15 + 1,
	r17	= r16 + 1,
	r18	= r17 + 1,
	r19	= r18 + 1,
	r20	= r19 + 1,
	r21	= r20 + 1,
	r22	= r21 + 1,
	r23	= r22 + 1,
	r24	= r23 + 1,
	r25	= r24 + 1,
	r26	= r25 + 1,
	r27	= r26 + 1,
	r28	= r27 + 1,
	r29	= r28 + 1,
	r30	= r29 + 1,
	r31	= r30 + 1
    } ;
}
/*
typedef enum XboxRegisters64 _XboxRegisters64;

*/ typedef eXboxRegisters64::XboxRegisters64 _XboxRegisters64;
namespace eXboxRegistersDouble{
/* [v1_enum] */ 
enum XboxRegistersDouble
    {	fp0	= 0,
	fp1	= fp0 + 1,
	fp2	= fp1 + 1,
	fp3	= fp2 + 1,
	fp4	= fp3 + 1,
	fp5	= fp4 + 1,
	fp6	= fp5 + 1,
	fp7	= fp6 + 1,
	fp8	= fp7 + 1,
	fp9	= fp8 + 1,
	fp10	= fp9 + 1,
	fp11	= fp10 + 1,
	fp12	= fp11 + 1,
	fp13	= fp12 + 1,
	fp14	= fp13 + 1,
	fp15	= fp14 + 1,
	fp16	= fp15 + 1,
	fp17	= fp16 + 1,
	fp18	= fp17 + 1,
	fp19	= fp18 + 1,
	fp20	= fp19 + 1,
	fp21	= fp20 + 1,
	fp22	= fp21 + 1,
	fp23	= fp22 + 1,
	fp24	= fp23 + 1,
	fp25	= fp24 + 1,
	fp26	= fp25 + 1,
	fp27	= fp26 + 1,
	fp28	= fp27 + 1,
	fp29	= fp28 + 1,
	fp30	= fp29 + 1,
	fp31	= fp30 + 1,
	fpscr	= fp31 + 1
    } ;
}
/*
typedef enum XboxRegistersDouble _XboxRegistersDouble;

*/ typedef eXboxRegistersDouble::XboxRegistersDouble _XboxRegistersDouble;
namespace eXboxRegistersVector{
/* [v1_enum] */ 
enum XboxRegistersVector
    {	v0	= 0,
	v1	= v0 + 1,
	v2	= v1 + 1,
	v3	= v2 + 1,
	v4	= v3 + 1,
	v5	= v4 + 1,
	v6	= v5 + 1,
	v7	= v6 + 1,
	v8	= v7 + 1,
	v9	= v8 + 1,
	v10	= v9 + 1,
	v11	= v10 + 1,
	v12	= v11 + 1,
	v13	= v12 + 1,
	v14	= v13 + 1,
	v15	= v14 + 1,
	v16	= v15 + 1,
	v17	= v16 + 1,
	v18	= v17 + 1,
	v19	= v18 + 1,
	v20	= v19 + 1,
	v21	= v20 + 1,
	v22	= v21 + 1,
	v23	= v22 + 1,
	v24	= v23 + 1,
	v25	= v24 + 1,
	v26	= v25 + 1,
	v27	= v26 + 1,
	v28	= v27 + 1,
	v29	= v28 + 1,
	v30	= v29 + 1,
	v31	= v30 + 1,
	v32	= v31 + 1,
	v33	= v32 + 1,
	v34	= v33 + 1,
	v35	= v34 + 1,
	v36	= v35 + 1,
	v37	= v36 + 1,
	v38	= v37 + 1,
	v39	= v38 + 1,
	v40	= v39 + 1,
	v41	= v40 + 1,
	v42	= v41 + 1,
	v43	= v42 + 1,
	v44	= v43 + 1,
	v45	= v44 + 1,
	v46	= v45 + 1,
	v47	= v46 + 1,
	v48	= v47 + 1,
	v49	= v48 + 1,
	v50	= v49 + 1,
	v51	= v50 + 1,
	v52	= v51 + 1,
	v53	= v52 + 1,
	v54	= v53 + 1,
	v55	= v54 + 1,
	v56	= v55 + 1,
	v57	= v56 + 1,
	v58	= v57 + 1,
	v59	= v58 + 1,
	v60	= v59 + 1,
	v61	= v60 + 1,
	v62	= v61 + 1,
	v63	= v62 + 1,
	v64	= v63 + 1,
	v65	= v64 + 1,
	v66	= v65 + 1,
	v67	= v66 + 1,
	v68	= v67 + 1,
	v69	= v68 + 1,
	v70	= v69 + 1,
	v71	= v70 + 1,
	v72	= v71 + 1,
	v73	= v72 + 1,
	v74	= v73 + 1,
	v75	= v74 + 1,
	v76	= v75 + 1,
	v77	= v76 + 1,
	v78	= v77 + 1,
	v79	= v78 + 1,
	v80	= v79 + 1,
	v81	= v80 + 1,
	v82	= v81 + 1,
	v83	= v82 + 1,
	v84	= v83 + 1,
	v85	= v84 + 1,
	v86	= v85 + 1,
	v87	= v86 + 1,
	v88	= v87 + 1,
	v89	= v88 + 1,
	v90	= v89 + 1,
	v91	= v90 + 1,
	v92	= v91 + 1,
	v93	= v92 + 1,
	v94	= v93 + 1,
	v95	= v94 + 1,
	v96	= v95 + 1,
	v97	= v96 + 1,
	v98	= v97 + 1,
	v99	= v98 + 1,
	v100	= v99 + 1,
	v101	= v100 + 1,
	v102	= v101 + 1,
	v103	= v102 + 1,
	v104	= v103 + 1,
	v105	= v104 + 1,
	v106	= v105 + 1,
	v107	= v106 + 1,
	v108	= v107 + 1,
	v109	= v108 + 1,
	v110	= v109 + 1,
	v111	= v110 + 1,
	v112	= v111 + 1,
	v113	= v112 + 1,
	v114	= v113 + 1,
	v115	= v114 + 1,
	v116	= v115 + 1,
	v117	= v116 + 1,
	v118	= v117 + 1,
	v119	= v118 + 1,
	v120	= v119 + 1,
	v121	= v120 + 1,
	v122	= v121 + 1,
	v123	= v122 + 1,
	v124	= v123 + 1,
	v125	= v124 + 1,
	v126	= v125 + 1,
	v127	= v126 + 1,
	vscr	= v127 + 1
    } ;
}
/*
typedef enum XboxRegistersVector _XboxRegistersVector;

*/ typedef eXboxRegistersVector::XboxRegistersVector _XboxRegistersVector;


extern RPC_IF_HANDLE __MIDL_itf_xdevkit_0279_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_xdevkit_0279_v0_0_s_ifspec;

#ifndef __IXboxStackFrame_INTERFACE_DEFINED__
#define __IXboxStackFrame_INTERFACE_DEFINED__

/* interface IXboxStackFrame */
/* [helpstring][unique][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxStackFrame;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("eabf8976-1a2f-4aaa-bbbb-3ecab03b2ee9")
    IXboxStackFrame : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_TopOfStack( 
            /* [retval][out] */ VARIANT_BOOL *TopOfStack) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Dirty( 
            /* [retval][out] */ VARIANT_BOOL *Dirty) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_NextStackFrame( 
            /* [retval][out] */ IXboxStackFrame **StackFrame) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetRegister32( 
            /* [in] */ _XboxRegisters32 Register,
            /* [out] */ LONG *Value,
            /* [retval][out] */ VARIANT_BOOL *IsValid) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetRegister32( 
            /* [in] */ _XboxRegisters32 Register,
            /* [in] */ LONG Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetRegister64( 
            /* [in] */ _XboxRegisters64 Register,
            /* [out] */ LONGLONG *Value,
            /* [retval][out] */ VARIANT_BOOL *IsValid) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetRegister64( 
            /* [in] */ _XboxRegisters64 Register,
            /* [in] */ LONGLONG Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetRegisterDouble( 
            /* [in] */ _XboxRegistersDouble Register,
            /* [out] */ double *Value,
            /* [retval][out] */ VARIANT_BOOL *IsValid) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetRegisterDouble( 
            /* [in] */ _XboxRegistersDouble Register,
            /* [in] */ double Value) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE GetRegisterVector_cpp( 
            /* [in] */ _XboxRegistersVector Register,
            /* [length_is][size_is][out] */ float *Value,
            /* [retval][out] */ VARIANT_BOOL *IsValid) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE SetRegisterVector_cpp( 
            /* [in] */ _XboxRegistersVector Register,
            /* [length_is][size_is][in] */ float *Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetRegisterVector( 
            /* [in] */ _XboxRegistersVector Register,
            SAFEARRAY * Value,
            /* [retval][out] */ VARIANT_BOOL *IsValid) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetRegisterVector( 
            /* [in] */ _XboxRegistersVector Register,
            SAFEARRAY * Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FlushRegisterChanges( void) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_FunctionInfo( 
            /* [retval][out] */ XBOX_FUNCTION_INFO *FunctionInfo) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_StackPointer( 
            /* [retval][out] */ DWORD *StackPointer) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ReturnAddress( 
            /* [retval][out] */ DWORD *ReturnAddress) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxStackFrameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxStackFrame * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxStackFrame * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxStackFrame * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxStackFrame * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxStackFrame * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxStackFrame * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxStackFrame * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopOfStack )( 
            IXboxStackFrame * This,
            /* [retval][out] */ VARIANT_BOOL *TopOfStack);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dirty )( 
            IXboxStackFrame * This,
            /* [retval][out] */ VARIANT_BOOL *Dirty);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextStackFrame )( 
            IXboxStackFrame * This,
            /* [retval][out] */ IXboxStackFrame **StackFrame);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetRegister32 )( 
            IXboxStackFrame * This,
            /* [in] */ _XboxRegisters32 Register,
            /* [out] */ LONG *Value,
            /* [retval][out] */ VARIANT_BOOL *IsValid);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetRegister32 )( 
            IXboxStackFrame * This,
            /* [in] */ _XboxRegisters32 Register,
            /* [in] */ LONG Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetRegister64 )( 
            IXboxStackFrame * This,
            /* [in] */ _XboxRegisters64 Register,
            /* [out] */ LONGLONG *Value,
            /* [retval][out] */ VARIANT_BOOL *IsValid);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetRegister64 )( 
            IXboxStackFrame * This,
            /* [in] */ _XboxRegisters64 Register,
            /* [in] */ LONGLONG Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetRegisterDouble )( 
            IXboxStackFrame * This,
            /* [in] */ _XboxRegistersDouble Register,
            /* [out] */ double *Value,
            /* [retval][out] */ VARIANT_BOOL *IsValid);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetRegisterDouble )( 
            IXboxStackFrame * This,
            /* [in] */ _XboxRegistersDouble Register,
            /* [in] */ double Value);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *GetRegisterVector_cpp )( 
            IXboxStackFrame * This,
            /* [in] */ _XboxRegistersVector Register,
            /* [length_is][size_is][out] */ float *Value,
            /* [retval][out] */ VARIANT_BOOL *IsValid);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *SetRegisterVector_cpp )( 
            IXboxStackFrame * This,
            /* [in] */ _XboxRegistersVector Register,
            /* [length_is][size_is][in] */ float *Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetRegisterVector )( 
            IXboxStackFrame * This,
            /* [in] */ _XboxRegistersVector Register,
            SAFEARRAY * Value,
            /* [retval][out] */ VARIANT_BOOL *IsValid);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetRegisterVector )( 
            IXboxStackFrame * This,
            /* [in] */ _XboxRegistersVector Register,
            SAFEARRAY * Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *FlushRegisterChanges )( 
            IXboxStackFrame * This);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FunctionInfo )( 
            IXboxStackFrame * This,
            /* [retval][out] */ XBOX_FUNCTION_INFO *FunctionInfo);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StackPointer )( 
            IXboxStackFrame * This,
            /* [retval][out] */ DWORD *StackPointer);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ReturnAddress )( 
            IXboxStackFrame * This,
            /* [retval][out] */ DWORD *ReturnAddress);
        
        END_INTERFACE
    } IXboxStackFrameVtbl;

    interface IXboxStackFrame
    {
        CONST_VTBL struct IXboxStackFrameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxStackFrame_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxStackFrame_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxStackFrame_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxStackFrame_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxStackFrame_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxStackFrame_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxStackFrame_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxStackFrame_get_TopOfStack(This,TopOfStack)	\
    (This)->lpVtbl -> get_TopOfStack(This,TopOfStack)

#define IXboxStackFrame_get_Dirty(This,Dirty)	\
    (This)->lpVtbl -> get_Dirty(This,Dirty)

#define IXboxStackFrame_get_NextStackFrame(This,StackFrame)	\
    (This)->lpVtbl -> get_NextStackFrame(This,StackFrame)

#define IXboxStackFrame_GetRegister32(This,Register,Value,IsValid)	\
    (This)->lpVtbl -> GetRegister32(This,Register,Value,IsValid)

#define IXboxStackFrame_SetRegister32(This,Register,Value)	\
    (This)->lpVtbl -> SetRegister32(This,Register,Value)

#define IXboxStackFrame_GetRegister64(This,Register,Value,IsValid)	\
    (This)->lpVtbl -> GetRegister64(This,Register,Value,IsValid)

#define IXboxStackFrame_SetRegister64(This,Register,Value)	\
    (This)->lpVtbl -> SetRegister64(This,Register,Value)

#define IXboxStackFrame_GetRegisterDouble(This,Register,Value,IsValid)	\
    (This)->lpVtbl -> GetRegisterDouble(This,Register,Value,IsValid)

#define IXboxStackFrame_SetRegisterDouble(This,Register,Value)	\
    (This)->lpVtbl -> SetRegisterDouble(This,Register,Value)

#define IXboxStackFrame_GetRegisterVector_cpp(This,Register,Value,IsValid)	\
    (This)->lpVtbl -> GetRegisterVector_cpp(This,Register,Value,IsValid)

#define IXboxStackFrame_SetRegisterVector_cpp(This,Register,Value)	\
    (This)->lpVtbl -> SetRegisterVector_cpp(This,Register,Value)

#define IXboxStackFrame_GetRegisterVector(This,Register,Value,IsValid)	\
    (This)->lpVtbl -> GetRegisterVector(This,Register,Value,IsValid)

#define IXboxStackFrame_SetRegisterVector(This,Register,Value)	\
    (This)->lpVtbl -> SetRegisterVector(This,Register,Value)

#define IXboxStackFrame_FlushRegisterChanges(This)	\
    (This)->lpVtbl -> FlushRegisterChanges(This)

#define IXboxStackFrame_get_FunctionInfo(This,FunctionInfo)	\
    (This)->lpVtbl -> get_FunctionInfo(This,FunctionInfo)

#define IXboxStackFrame_get_StackPointer(This,StackPointer)	\
    (This)->lpVtbl -> get_StackPointer(This,StackPointer)

#define IXboxStackFrame_get_ReturnAddress(This,ReturnAddress)	\
    (This)->lpVtbl -> get_ReturnAddress(This,ReturnAddress)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_get_TopOfStack_Proxy( 
    IXboxStackFrame * This,
    /* [retval][out] */ VARIANT_BOOL *TopOfStack);


void __RPC_STUB IXboxStackFrame_get_TopOfStack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_get_Dirty_Proxy( 
    IXboxStackFrame * This,
    /* [retval][out] */ VARIANT_BOOL *Dirty);


void __RPC_STUB IXboxStackFrame_get_Dirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_get_NextStackFrame_Proxy( 
    IXboxStackFrame * This,
    /* [retval][out] */ IXboxStackFrame **StackFrame);


void __RPC_STUB IXboxStackFrame_get_NextStackFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_GetRegister32_Proxy( 
    IXboxStackFrame * This,
    /* [in] */ _XboxRegisters32 Register,
    /* [out] */ LONG *Value,
    /* [retval][out] */ VARIANT_BOOL *IsValid);


void __RPC_STUB IXboxStackFrame_GetRegister32_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_SetRegister32_Proxy( 
    IXboxStackFrame * This,
    /* [in] */ _XboxRegisters32 Register,
    /* [in] */ LONG Value);


void __RPC_STUB IXboxStackFrame_SetRegister32_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_GetRegister64_Proxy( 
    IXboxStackFrame * This,
    /* [in] */ _XboxRegisters64 Register,
    /* [out] */ LONGLONG *Value,
    /* [retval][out] */ VARIANT_BOOL *IsValid);


void __RPC_STUB IXboxStackFrame_GetRegister64_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_SetRegister64_Proxy( 
    IXboxStackFrame * This,
    /* [in] */ _XboxRegisters64 Register,
    /* [in] */ LONGLONG Value);


void __RPC_STUB IXboxStackFrame_SetRegister64_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_GetRegisterDouble_Proxy( 
    IXboxStackFrame * This,
    /* [in] */ _XboxRegistersDouble Register,
    /* [out] */ double *Value,
    /* [retval][out] */ VARIANT_BOOL *IsValid);


void __RPC_STUB IXboxStackFrame_GetRegisterDouble_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_SetRegisterDouble_Proxy( 
    IXboxStackFrame * This,
    /* [in] */ _XboxRegistersDouble Register,
    /* [in] */ double Value);


void __RPC_STUB IXboxStackFrame_SetRegisterDouble_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_GetRegisterVector_cpp_Proxy( 
    IXboxStackFrame * This,
    /* [in] */ _XboxRegistersVector Register,
    /* [length_is][size_is][out] */ float *Value,
    /* [retval][out] */ VARIANT_BOOL *IsValid);


void __RPC_STUB IXboxStackFrame_GetRegisterVector_cpp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_SetRegisterVector_cpp_Proxy( 
    IXboxStackFrame * This,
    /* [in] */ _XboxRegistersVector Register,
    /* [length_is][size_is][in] */ float *Value);


void __RPC_STUB IXboxStackFrame_SetRegisterVector_cpp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_GetRegisterVector_Proxy( 
    IXboxStackFrame * This,
    /* [in] */ _XboxRegistersVector Register,
    SAFEARRAY * Value,
    /* [retval][out] */ VARIANT_BOOL *IsValid);


void __RPC_STUB IXboxStackFrame_GetRegisterVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_SetRegisterVector_Proxy( 
    IXboxStackFrame * This,
    /* [in] */ _XboxRegistersVector Register,
    SAFEARRAY * Value);


void __RPC_STUB IXboxStackFrame_SetRegisterVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_FlushRegisterChanges_Proxy( 
    IXboxStackFrame * This);


void __RPC_STUB IXboxStackFrame_FlushRegisterChanges_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_get_FunctionInfo_Proxy( 
    IXboxStackFrame * This,
    /* [retval][out] */ XBOX_FUNCTION_INFO *FunctionInfo);


void __RPC_STUB IXboxStackFrame_get_FunctionInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_get_StackPointer_Proxy( 
    IXboxStackFrame * This,
    /* [retval][out] */ DWORD *StackPointer);


void __RPC_STUB IXboxStackFrame_get_StackPointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxStackFrame_get_ReturnAddress_Proxy( 
    IXboxStackFrame * This,
    /* [retval][out] */ DWORD *ReturnAddress);


void __RPC_STUB IXboxStackFrame_get_ReturnAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxStackFrame_INTERFACE_DEFINED__ */


#ifndef __IXboxMemoryRegions_INTERFACE_DEFINED__
#define __IXboxMemoryRegions_INTERFACE_DEFINED__

/* interface IXboxMemoryRegions */
/* [helpstring][unique][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxMemoryRegions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7f8e857b-fd59-4b67-8156-faa3fd06d1e5")
    IXboxMemoryRegions : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG Index,
            /* [retval][out] */ IXboxMemoryRegion **MemoryRegion) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *Count) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IEnumVARIANT **Enumerator) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxMemoryRegionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxMemoryRegions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxMemoryRegions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxMemoryRegions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxMemoryRegions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxMemoryRegions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxMemoryRegions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxMemoryRegions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IXboxMemoryRegions * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ IXboxMemoryRegion **MemoryRegion);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IXboxMemoryRegions * This,
            /* [retval][out] */ LONG *Count);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IXboxMemoryRegions * This,
            /* [retval][out] */ IEnumVARIANT **Enumerator);
        
        END_INTERFACE
    } IXboxMemoryRegionsVtbl;

    interface IXboxMemoryRegions
    {
        CONST_VTBL struct IXboxMemoryRegionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxMemoryRegions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxMemoryRegions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxMemoryRegions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxMemoryRegions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxMemoryRegions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxMemoryRegions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxMemoryRegions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxMemoryRegions_get_Item(This,Index,MemoryRegion)	\
    (This)->lpVtbl -> get_Item(This,Index,MemoryRegion)

#define IXboxMemoryRegions_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IXboxMemoryRegions_get__NewEnum(This,Enumerator)	\
    (This)->lpVtbl -> get__NewEnum(This,Enumerator)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxMemoryRegions_get_Item_Proxy( 
    IXboxMemoryRegions * This,
    /* [in] */ LONG Index,
    /* [retval][out] */ IXboxMemoryRegion **MemoryRegion);


void __RPC_STUB IXboxMemoryRegions_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxMemoryRegions_get_Count_Proxy( 
    IXboxMemoryRegions * This,
    /* [retval][out] */ LONG *Count);


void __RPC_STUB IXboxMemoryRegions_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxMemoryRegions_get__NewEnum_Proxy( 
    IXboxMemoryRegions * This,
    /* [retval][out] */ IEnumVARIANT **Enumerator);


void __RPC_STUB IXboxMemoryRegions_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxMemoryRegions_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_xdevkit_0281 */
/* [local] */ 

namespace eXboxMemoryRegionFlags{
/* [v1_enum] */ 
enum XboxMemoryRegionFlags
    {	NoAccess	= 0x1,
	ReadOnly	= 0x2,
	ReadWrite	= 0x4,
	WriteCopy	= 0x8,
	Execute	= 0x10,
	ExecuteRead	= 0x20,
	ExecuteReadWrite	= 0x40,
	ExecuteWriteCopy	= 0x80,
	Guard	= 0x100,
	NoCache	= 0x200,
	WriteCombine	= 0x400,
	UserReadOnly	= 0x1000,
	UserReadWrite	= 0x2000
    } ;
}
/*
typedef enum XboxMemoryRegionFlags _XboxMemoryRegionFlags;

*/ typedef int _XboxMemoryRegionFlags;


extern RPC_IF_HANDLE __MIDL_itf_xdevkit_0281_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_xdevkit_0281_v0_0_s_ifspec;

#ifndef __IXboxMemoryRegion_INTERFACE_DEFINED__
#define __IXboxMemoryRegion_INTERFACE_DEFINED__

/* interface IXboxMemoryRegion */
/* [helpstring][unique][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IXboxMemoryRegion;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4f882a21-7f2a-4bea-a0a3-a3710a93deea")
    IXboxMemoryRegion : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BaseAddress( 
            /* [retval][out] */ LONG *BaseAddress) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_RegionSize( 
            /* [retval][out] */ LONG *RegionSize) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Flags( 
            /* [retval][out] */ _XboxMemoryRegionFlags *Flags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxMemoryRegionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxMemoryRegion * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxMemoryRegion * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxMemoryRegion * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxMemoryRegion * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxMemoryRegion * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxMemoryRegion * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxMemoryRegion * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BaseAddress )( 
            IXboxMemoryRegion * This,
            /* [retval][out] */ LONG *BaseAddress);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RegionSize )( 
            IXboxMemoryRegion * This,
            /* [retval][out] */ LONG *RegionSize);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Flags )( 
            IXboxMemoryRegion * This,
            /* [retval][out] */ _XboxMemoryRegionFlags *Flags);
        
        END_INTERFACE
    } IXboxMemoryRegionVtbl;

    interface IXboxMemoryRegion
    {
        CONST_VTBL struct IXboxMemoryRegionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxMemoryRegion_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxMemoryRegion_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxMemoryRegion_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxMemoryRegion_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxMemoryRegion_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxMemoryRegion_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxMemoryRegion_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxMemoryRegion_get_BaseAddress(This,BaseAddress)	\
    (This)->lpVtbl -> get_BaseAddress(This,BaseAddress)

#define IXboxMemoryRegion_get_RegionSize(This,RegionSize)	\
    (This)->lpVtbl -> get_RegionSize(This,RegionSize)

#define IXboxMemoryRegion_get_Flags(This,Flags)	\
    (This)->lpVtbl -> get_Flags(This,Flags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxMemoryRegion_get_BaseAddress_Proxy( 
    IXboxMemoryRegion * This,
    /* [retval][out] */ LONG *BaseAddress);


void __RPC_STUB IXboxMemoryRegion_get_BaseAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxMemoryRegion_get_RegionSize_Proxy( 
    IXboxMemoryRegion * This,
    /* [retval][out] */ LONG *RegionSize);


void __RPC_STUB IXboxMemoryRegion_get_RegionSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXboxMemoryRegion_get_Flags_Proxy( 
    IXboxMemoryRegion * This,
    /* [retval][out] */ _XboxMemoryRegionFlags *Flags);


void __RPC_STUB IXboxMemoryRegion_get_Flags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxMemoryRegion_INTERFACE_DEFINED__ */


#ifndef __IXboxEventInfo_INTERFACE_DEFINED__
#define __IXboxEventInfo_INTERFACE_DEFINED__

/* interface IXboxEventInfo */
/* [object][oleautomation][dual][uuid] */ 


EXTERN_C const IID IID_IXboxEventInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("85c9127a-11ed-47f2-9e87-a83058fc264a")
    IXboxEventInfo : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Info( 
            /* [retval][out] */ PXBOX_EVENT_INFO EventInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxEventInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxEventInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxEventInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxEventInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXboxEventInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXboxEventInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXboxEventInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXboxEventInfo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Info )( 
            IXboxEventInfo * This,
            /* [retval][out] */ PXBOX_EVENT_INFO EventInfo);
        
        END_INTERFACE
    } IXboxEventInfoVtbl;

    interface IXboxEventInfo
    {
        CONST_VTBL struct IXboxEventInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxEventInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxEventInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxEventInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxEventInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXboxEventInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXboxEventInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXboxEventInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXboxEventInfo_get_Info(This,EventInfo)	\
    (This)->lpVtbl -> get_Info(This,EventInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IXboxEventInfo_get_Info_Proxy( 
    IXboxEventInfo * This,
    /* [retval][out] */ PXBOX_EVENT_INFO EventInfo);


void __RPC_STUB IXboxEventInfo_get_Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxEventInfo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_xdevkit_0283 */
/* [local] */ 

#define	DISPID_XBOX_EVENT	( 1 )

#define	DISPID_XBOX_TEXT_EVENT	( 2 )



extern RPC_IF_HANDLE __MIDL_itf_xdevkit_0283_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_xdevkit_0283_v0_0_s_ifspec;

#ifndef __IXboxEvents_INTERFACE_DEFINED__
#define __IXboxEvents_INTERFACE_DEFINED__

/* interface IXboxEvents */
/* [object][oleautomation][uuid] */ 


EXTERN_C const IID IID_IXboxEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e3c9d73f-9df0-4b57-8cee-05f9ca6823be")
    IXboxEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnStdNotify( 
            /* [in] */ _XboxDebugEventType EventCode,
            /* [in] */ IXboxEventInfo *eventInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnTextNotify( 
            /* [in] */ BSTR Source,
            /* [in] */ BSTR Notification) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXboxEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXboxEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXboxEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXboxEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnStdNotify )( 
            IXboxEvents * This,
            /* [in] */ _XboxDebugEventType EventCode,
            /* [in] */ IXboxEventInfo *eventInfo);
        
        HRESULT ( STDMETHODCALLTYPE *OnTextNotify )( 
            IXboxEvents * This,
            /* [in] */ BSTR Source,
            /* [in] */ BSTR Notification);
        
        END_INTERFACE
    } IXboxEventsVtbl;

    interface IXboxEvents
    {
        CONST_VTBL struct IXboxEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXboxEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXboxEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXboxEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXboxEvents_OnStdNotify(This,EventCode,eventInfo)	\
    (This)->lpVtbl -> OnStdNotify(This,EventCode,eventInfo)

#define IXboxEvents_OnTextNotify(This,Source,Notification)	\
    (This)->lpVtbl -> OnTextNotify(This,Source,Notification)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IXboxEvents_OnStdNotify_Proxy( 
    IXboxEvents * This,
    /* [in] */ _XboxDebugEventType EventCode,
    /* [in] */ IXboxEventInfo *eventInfo);


void __RPC_STUB IXboxEvents_OnStdNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXboxEvents_OnTextNotify_Proxy( 
    IXboxEvents * This,
    /* [in] */ BSTR Source,
    /* [in] */ BSTR Notification);


void __RPC_STUB IXboxEvents_OnTextNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXboxEvents_INTERFACE_DEFINED__ */



#ifndef __XDevkit_LIBRARY_DEFINED__
#define __XDevkit_LIBRARY_DEFINED__

/* library XDevkit */
/* [helpstring][version][uuid] */ 




















































EXTERN_C const IID LIBID_XDevkit;

#ifndef __XboxEvents_DISPINTERFACE_DEFINED__
#define __XboxEvents_DISPINTERFACE_DEFINED__

/* dispinterface XboxEvents */
/* [uuid] */ 


EXTERN_C const IID DIID_XboxEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("420208df-c38c-4efb-9fc3-acd50350941e")
    XboxEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct XboxEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            XboxEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            XboxEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            XboxEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            XboxEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            XboxEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            XboxEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            XboxEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } XboxEventsVtbl;

    interface XboxEvents
    {
        CONST_VTBL struct XboxEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define XboxEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define XboxEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define XboxEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define XboxEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define XboxEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define XboxEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define XboxEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __XboxEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_XboxConsole;

#ifdef __cplusplus

class DECLSPEC_UUID("3ed2b073-99a1-42db-80cc-295e9ffba18f")
XboxConsole;
#endif

EXTERN_C const CLSID CLSID_XboxManager;

#ifdef __cplusplus

class DECLSPEC_UUID("a5eb45d8-f3b6-49b9-984a-0d313ab60342")
XboxManager;
#endif

EXTERN_C const CLSID CLSID_XboxExecutableDatabase;

#ifdef __cplusplus

class DECLSPEC_UUID("3151B328-4A0D-4b83-950F-6861AB6B3ECD")
XboxExecutableDatabase;
#endif
#endif /* __XDevkit_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


