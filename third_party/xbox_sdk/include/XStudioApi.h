/***********************************************************************
*                                                                      *
*   XStudioApi.h -- This module defines the APIs for Xbox 360 Studio   *
*                                                                      *
*   Copyright (c) Microsoft Corp. All rights reserved.                 *
*                                                                      *
***********************************************************************/

#pragma once

#ifndef XSTUDIO
#error "You must include xstudio.h rather than including xstudioapi.h directly"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define XSTINLINE   __inline
#define XSTAPI      WINAPI

#ifndef _XBOX //

// -----------------------------------------------------------------------------
// Connection
// -----------------------------------------------------------------------------

typedef enum _XSTUDIO_CONNECTION_TYPE
{
    XSTUDIO_CONNECTION_TYPE_USB,
    XSTUDIO_CONNECTION_TYPE_TCP,
} XSTUDIO_CONNECTION_TYPE;

HRESULT
XSTAPI
XStudioConnect(
    _In_z_ const char *            sConsoleName,
    _In_   XSTUDIO_CONNECTION_TYPE ConnectionType
);

HRESULT
XSTAPI
XStudioDisconnect();

HRESULT
XSTAPI
XStudioGetConnectionStatus();

#endif //

// -----------------------------------------------------------------------------
// XStudio File
// -----------------------------------------------------------------------------

HRESULT
XSTAPI
XStudioCreateFile(
    _In_z_ const char *          sFilePath,
    _In_   DWORD                 dwDesiredAccess,
    _In_   DWORD                 dwCreationDisposition,
    _In_   XSTUDIO_STREAM_FLAGS  dwStreams,
    _Out_  XSTUDIO_FILE_HANDLE * phFile
);

HRESULT
XSTAPI
XStudioCloseFile(
    _In_ XSTUDIO_FILE_HANDLE hFile
);

HRESULT
XSTAPI
XStudioGetFileStreams(
    _In_  XSTUDIO_FILE_HANDLE    hFile,
    _Out_ XSTUDIO_STREAM_FLAGS * pdwStreams
);

// -----------------------------------------------------------------------------
// Stream Mapping
// -----------------------------------------------------------------------------

HRESULT
XSTAPI
XStudioMapStreams(
    _In_ XSTUDIO_STREAM_FLAGS dwStreams,
    _In_ XSTUDIO_HANDLE       hHandle
);

HRESULT
XSTAPI
XStudioUnmapStreams(
    _In_ XSTUDIO_STREAM_FLAGS dwStreams,
    _In_ XSTUDIO_HANDLE       hHandle
);

// -----------------------------------------------------------------------------
// Switch Producers
// -----------------------------------------------------------------------------

typedef enum XSTUDIO_PRODUCER
{
    XSTUDIO_PRODUCER_FILE,
} XSTUDIO_PRODUCER;

HRESULT
XSTAPI
XStudioSwitchToProducers(
    _In_ XSTUDIO_STREAM_FLAGS dwStreams,
    _In_ XSTUDIO_PRODUCER     producer
);

// -----------------------------------------------------------------------------
// Stream Callback
// -----------------------------------------------------------------------------

#define XSTUDIO_STREAM_CALLBACK_REGISTRATION_FLAG_CONSUMER          0x00000001
#define XSTUDIO_STREAM_CALLBACK_REGISTRATION_FLAG_PRODUCER          0x00000002


#define XSTUDIO_STREAM_CALLBACK_REGISTRATION_FLAG_PRODUCER_FILL_IN  0x00000005

#define XSTUDIO_STREAM_CALLBACK_REGISTRATION_FLAG_REALTIME          0x00000100


typedef struct _XSTUDIO_STREAM_EVENT
{
    UINT                cbSize;

    XSTUDIO_STREAM_ID   StreamID;
    UINT                uEventIndex;

    UINT64              uEventMicroseconds;

    void*               pvIndexBuffer;
    UINT                cbIndexBufferSize;
    UINT                cbIndexBufferUsed;

    void*               pvDataBuffer;
    UINT                cbDataBufferSize;
    UINT                cbDataBufferUsed;
} XSTUDIO_STREAM_EVENT;


typedef enum _NUI_IMAGE_TYPE NUI_IMAGE_TYPE;

typedef struct _XSTUDIO_NUICAM_IMAGE_INDEX_DATA
{
    NUI_IMAGE_TYPE ImageType;
    USHORT Width;
    USHORT Height;
    DWORD FrameNumber;
    DWORD64 NuiTimeStamp;

} XSTUDIO_NUICAM_IMAGE_INDEX_DATA;


typedef struct _XSTUDIO_TITLE_INDEX_DATA
{
    UINT64 Reserved;
    DWORD  IndexData[4];

} XSTUDIO_TITLE_INDEX_DATA;

#ifdef _XBOX //
#endif //

#ifndef _XBOX //

typedef HRESULT (CALLBACK * XSTUDIO_STREAM_CALLBACK)(
    _Inout_ XSTUDIO_STREAM_EVENT* pStreamEvent,
    _In_opt_ void*                pvStreamCallbackContext  );

HRESULT
XSTAPI
XStudioRegisterStreamCallback(
    _In_     XSTUDIO_STREAM_CALLBACK pfnStreamCallback,
    _In_     DWORD                   dwStreamCallbackRegistrationFlags,
    _In_opt_ void*                   pvStreamCallbackContext,
    _Out_    XSTUDIO_HANDLE*         phStreamCallback
);

HRESULT
XSTAPI
XStudioCloseHandle(
    _In_ XSTUDIO_HANDLE Handle
);

#endif //

// -----------------------------------------------------------------------------
// Notifications
// -----------------------------------------------------------------------------

typedef HRESULT (CALLBACK * XSTUDIO_NOTIFICATION_CALLBACK)(
    _In_ XSTUDIO_STREAM_FLAGS dwStreams,
    _In_ DWORD                dwNotification,
    _In_ void*                pvContext,
    _In_ LPARAM               lparam);

#ifndef _XBOX //

HRESULT
XSTAPI
XStudioRegisterNotificationCallback(
    _In_ XSTUDIO_NOTIFICATION_CALLBACK  pfnNotificationCallback,
    _In_ XSTUDIO_STREAM_FLAGS           dwStreams,
    _In_ DWORD                          dwNotificationsFlags,
    _In_ DWORD                          dwFlags,
    _In_ void*                          pvContext,
    _Out_ XSTUDIO_HANDLE*               phandle
);


#endif //

// Called just before playback is started.  No events will have been delivered at this point.
#define XSTUDIO_NOTIF_PLAYBACK_STARTING                 0x00000001
// Called just after playback is stopped.  No more events will be delivered at this point.
#define XSTUDIO_NOTIF_PLAYBACK_STOPPED                  0x00000002

// Called just before recording is started.  No events will have been delivered at this point.
#define XSTUDIO_NOTIF_RECORDING_STARTING                0x00000004
// Called just after recording is stopped.  No more events will be delivered at this point.
#define XSTUDIO_NOTIF_RECORDING_STOPPED                 0x00000008

// Called when playback is suspended / resumed
// Does not use stream flags argument
// For SUSPENDED, lparam is one of XSTUDIO_NOTIF_SUSPEND_...
#define XSTUDIO_NOTIF_SUSPENDED                         0x00000010
#define XSTUDIO_NOTIF_RESUMING                          0x00000020

// Called after the last event in a loop iteration,
// but before the first event in the next loop iteration
#define XSTUDIO_NOTIF_LOOPING                           0x00000040

// Switching to a diff producer.  Sent before any event make it to the new producer.
// lparam is one of the XSTUDIO_PRODUCER_... values
#define XSTUDIO_NOTIF_SWITCHING_TO_PROD                 0x00000080

// Switched to a diff producer.  Sent after the switch to a producer is complete.
// lparam is one of the XSTUDIO_PRODUCER_... values
#define XSTUDIO_NOTIF_SWITCHED_TO_PROD                  0x00000100



//--------------------------------
// Suspend reasons
//--------------------------------
#define XSTUDIO_NOTIF_SUSPEND_API                       1
#define XSTUDIO_NOTIF_SUSPEND_SUSPENDPOINT              2
#define XSTUDIO_NOTIF_SUSPEND_SINGLESTEP                3

// -----------------------------------------------------------------------------
// Monitoring / Live Preview
// -----------------------------------------------------------------------------

#ifndef _XBOX //


#endif //

// -----------------------------------------------------------------------------
// Record and Play Control
// -----------------------------------------------------------------------------

HRESULT
XSTAPI
XStudioStart(
    _In_ XSTUDIO_STREAM_FLAGS dwStreams
);

HRESULT
XSTAPI
XStudioStop(
    _In_ XSTUDIO_STREAM_FLAGS dwStreams
);

HRESULT
XSTAPI
XStudioStopEx(
    _In_ XSTUDIO_STREAM_FLAGS dwStreams,
    _In_ XSTUDIO_HANDLE       handle
);

// -----------------------------------------------------------------------------
// Status Query
// -----------------------------------------------------------------------------


HRESULT
XSTAPI
XStudioGetActiveStreams(
    _Out_ XSTUDIO_STREAM_FLAGS * pdwStreams
);

HRESULT
XSTAPI
XStudioGetErrorStreams(
    _Out_ XSTUDIO_STREAM_FLAGS * pdwStreams
);


// -----------------------------------------------------------------------------
// Title Data
// -----------------------------------------------------------------------------

#define XSTUDIO_TITLE_DATA_MAX_BUFFER_SIZE (32*1024)

#ifdef _XBOX //

HRESULT
XSTAPI
XStudioWriteTitleData(
    _In_opt_                                  const XSTUDIO_TITLE_INDEX_DATA * pTitleIndexData,
    _In_opt_bytecount_(dwTitleDataBufferSize) const void * pTitleDataBuffer,
    _In_                                      DWORD dwTitleDataBufferSize
);

HRESULT
XSTAPI
XStudioReadTitleData(
    _In_                                     DWORD dwMillisecondsToWait,
    _Out_opt_                                XSTUDIO_TITLE_INDEX_DATA * pTitleIndexData,
    _Out_opt_bytecap_(dwTitleDataBufferSize) void * pTitleDataBuffer,
    _In_                                     DWORD dwTitleDataBufferSize,
    _Out_                                    DWORD * pdwRequiredTitleDataBufferSize
);

#endif //

// -----------------------------------------------------------------------------
// Input Mode
// -----------------------------------------------------------------------------

typedef enum _XSTUDIO_INPUT_MODE
{
    XSTUDIO_INPUT_MODE_DEFAULT,
    XSTUDIO_INPUT_MODE_SIMULATED,

    XSTUDIO_INPUT_MODE_INVALID = 0xFFFFFFFF,

} XSTUDIO_INPUT_MODE;


HRESULT XStudioSetInputMode(
    XSTUDIO_STREAM_FLAGS streamFlags,
    XSTUDIO_INPUT_MODE InputMode
);

HRESULT XStudioGetInputMode(
    XSTUDIO_STREAM_FLAGS streamFlags,
    _Out_ XSTUDIO_INPUT_MODE * pInputModeOut
);

// -----------------------------------------------------------------------------
// Loop
// -----------------------------------------------------------------------------

HRESULT XStudioSetLoopCount( XSTUDIO_STREAM_FLAGS streamFlags, UINT loopCount );
HRESULT XStudioGetLoopCount( XSTUDIO_STREAM_FLAGS streamFlags, _Out_ UINT * pLoopCount );


// -----------------------------------------------------------------------------
// Suspend / Resume
// -----------------------------------------------------------------------------

HRESULT XStudioSuspend( XSTUDIO_STREAM_FLAGS streamFlags );
HRESULT XStudioResume( XSTUDIO_STREAM_FLAGS streamFlags );

#ifndef _XBOX //

// -----------------------------------------------------------------------------
// Suspend points / Single step
// -----------------------------------------------------------------------------
HRESULT XStudioAddSuspendPoint(
    _In_ XSTUDIO_STREAM_ID          dwStreamID,
    _In_ DWORD                      dwEventIndex,
    _Out_ XSTUDIO_HANDLE*           phandle
);

HRESULT XStudioSingleStep(
    _In_ XSTUDIO_STREAM_FLAGS       dwStreams
);

#endif //

#ifdef __cplusplus
}
#endif

