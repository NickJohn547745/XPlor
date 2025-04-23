//--------------------------------------------------------------------------------------
// XSim.h
// 
// C-Style API for XSim
// 
// Microsoft Game Studios Tools and Technology Group
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once

#ifndef _XSIM_H_
#define _XSIM_H_

#include <sal.h>

// Putting these here so that XSim clients only need to include XSim.h

#ifndef XSIM_INTERNAL
#include <xbdm.h>
#endif
#include "XSimError.h"

#ifdef __cplusplus
extern "C" {
#endif

const DWORD DEFAULT_COMPONENT_FRAMERATE = 60;
const DWORD DM_AUTOMATION_INPUTQUEUE_LENGTH = 100;
const DWORD IO_BUFFER_SIZE = 16384; // Buffer size is one Xbox HD sector.

//------------------------------------------------------------------------------
// Handle definition
//------------------------------------------------------------------------------
typedef HANDLE XSIMHANDLE;

//------------------------------------------------------------------------------
// General component status
//------------------------------------------------------------------------------
typedef enum _XSIM_COMPONENTSTATUS {
    XSIM_COMPONENTSTATUS_IDLE,
    XSIM_COMPONENTSTATUS_RUNNING
} XSIM_COMPONENTSTATUS;

//------------------------------------------------------------------------------
// Synchronization mode used by TextSequencePlayer
//------------------------------------------------------------------------------
typedef enum _XSIM_SYNCHMODE {
    XSIM_SYNCHMODE_FRAME  = 0x00000001,
    XSIM_SYNCHMODE_TIME   = 0x00000002
} XSIM_SYNCHMODE;

//------------------------------------------------------------------------------
// Structs used for Random Input Player button press timings
//------------------------------------------------------------------------------
typedef struct _XSIM_BUTTONPRESSATTRIBUTES {
      DWORD dwIntervalMinMs;
      DWORD dwIntervalMaxMs;
      DWORD dwHoldTimeMinMs; 
      DWORD dwHoldTimeMaxMs;
} XSIM_BUTTONPRESSATTRIBUTES;

typedef struct _XSIM_CONTROLLERPRESSATTRIBUTES {
      XSIM_BUTTONPRESSATTRIBUTES DpadUp;
      XSIM_BUTTONPRESSATTRIBUTES DpadDown;
      XSIM_BUTTONPRESSATTRIBUTES DpadLeft;
      XSIM_BUTTONPRESSATTRIBUTES DpadRight;
      XSIM_BUTTONPRESSATTRIBUTES Start;
      XSIM_BUTTONPRESSATTRIBUTES Back;
      XSIM_BUTTONPRESSATTRIBUTES LeftThumb;
      XSIM_BUTTONPRESSATTRIBUTES RightThumb;
      XSIM_BUTTONPRESSATTRIBUTES LeftShoulder;
      XSIM_BUTTONPRESSATTRIBUTES RightShoulder;
      XSIM_BUTTONPRESSATTRIBUTES A;
      XSIM_BUTTONPRESSATTRIBUTES B;
      XSIM_BUTTONPRESSATTRIBUTES X;
      XSIM_BUTTONPRESSATTRIBUTES Y;
      XSIM_BUTTONPRESSATTRIBUTES XBox360Button;
      XSIM_BUTTONPRESSATTRIBUTES RightTrigger;
      XSIM_BUTTONPRESSATTRIBUTES LeftTrigger;
      XSIM_BUTTONPRESSATTRIBUTES ThumbLX;
      XSIM_BUTTONPRESSATTRIBUTES ThumbLY;
      XSIM_BUTTONPRESSATTRIBUTES ThumbRX;
      XSIM_BUTTONPRESSATTRIBUTES ThumbRY;
} XSIM_CONTROLLERPRESSATTRIBUTES;

//------------------------------------------------------------------------------
// User index bits used for building user index masks
//------------------------------------------------------------------------------
typedef enum _XSIM_USERINDEXMASK {
    XSIM_USERINDEXMASK_0   = 0x00000001,
    XSIM_USERINDEXMASK_1   = 0x00000002,
    XSIM_USERINDEXMASK_2   = 0x00000004,
    XSIM_USERINDEXMASK_3   = 0x00000008,
    XSIM_USERINDEXMASK_ALL = 0x0000000F,
} XSIM_USERINDEXMASK;

//------------------------------------------------------------------------------
// XSim Functions
//------------------------------------------------------------------------------
// Initialize/Uninitialize
HRESULT WINAPI XSimInitialize( __in DWORD dwComponentFrameRate );
HRESULT WINAPI XSimUninitialize( );

// Take/Return control from/to the physical controller
HRESULT WINAPI XSimAcquireControl( __in DWORD dwUserIndexMask );
HRESULT WINAPI XSimReturnControl( __in DWORD dwUserIndexMask );

// Player creation
HRESULT WINAPI XSimCreateRandomInputPlayer( __out XSIMHANDLE* phXSimHandle );
HRESULT WINAPI XSimCreateRandomStatePlayer( __in_z LPCSTR lpFileName, __out XSIMHANDLE* phXSimHandle );
HRESULT WINAPI XSimCreateFilePlayer( __in_z LPCSTR lpFileName,
                                     __in XSIM_SYNCHMODE eSynchMode,
                                     __out XSIMHANDLE* phXSimHandle );
HRESULT WINAPI XSimCreateTextSequencePlayer( __in_z LPCSTR lpPlaybackString,
                                             __in XSIM_SYNCHMODE eSynchMode,
                                             __in DWORD dwDefaultPlaybackRate, 
                                             __out XSIMHANDLE* phXSimHandle );
// Recorder creation
HRESULT WINAPI XSimCreateFileRecorder( __in_z LPCSTR lpFileName, __out XSIMHANDLE* phXSimHandle );

// Handle releasing
HRESULT WINAPI XSimCloseHandle( __in XSIMHANDLE hXSimHandle );

// Start/Stop player(s)
HRESULT WINAPI XSimStartPlayer( __in XSIMHANDLE hXSimHandle, __in DWORD dwUserIndex );
HRESULT WINAPI XSimStopPlayer( __in DWORD dwUserIndex);

// Start/Stop recorder(s)
HRESULT WINAPI XSimStartRecorder( __in XSIMHANDLE hXSimHandle, __in DWORD dwUserIndex );
HRESULT WINAPI XSimStopRecorder( __in DWORD dwUserIndex );

// Player/Recorder status
HRESULT WINAPI XSimGetPortPlayerStatus( __in DWORD dwUserIndex, __out XSIM_COMPONENTSTATUS* pStatus );
HRESULT WINAPI XSimGetPortRecorderStatus( __in DWORD dwUserIndex, __out XSIM_COMPONENTSTATUS* pStatus );

// Random Input Player settings
HRESULT WINAPI XSimSetRandomInputPlayerConnectAttributes( __in XSIMHANDLE hXSimHandle,
                                                          __in BOOL bStartConnected,
                                                          __in DWORD dwDisconnectIntervalMin,
                                                          __in DWORD dwDisconnectIntervalMax,
                                                          __in DWORD dwReconnectIntervalMin,
                                                          __in DWORD dwReconnectIntervalMax );
HRESULT WINAPI XSimGetRandomInputPlayerPressAttributes( __in XSIMHANDLE hXSimHandle, __out XSIM_CONTROLLERPRESSATTRIBUTES* pPressAttributes );
HRESULT WINAPI XSimSetRandomInputPlayerPressAttributes( __in XSIMHANDLE hXSimHandle, __in XSIM_CONTROLLERPRESSATTRIBUTES* pPressAttributes );

// Random State Player state control
HRESULT WINAPI XSimGetRandomStatePlayerState( __in XSIMHANDLE hXSimHandle,
                                              __in DWORD dwBufferSize,
                                              __out_ecount(dwBufferSize) LPSTR lpStateName );
HRESULT WINAPI XSimSetRandomStatePlayerState( __in XSIMHANDLE hXSimHandle, __in_z LPCSTR lpStateName );

#ifdef __cplusplus
}
#endif


#endif 
