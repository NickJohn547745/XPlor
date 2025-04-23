/**************************************************************************
*                                                                         *
*   XedFile.h -- This module defines the APIs for Xbox 360 Studio Files   *
*                                                                         *
*   Copyright (c) Microsoft Corp. All rights reserved.                    *
*                                                                         *
**************************************************************************/

#pragma once


#ifdef __cplusplus
extern "C" {
#endif


#define XEDAPI WINAPI

typedef enum _NUI_IMAGE_TYPE  NUI_IMAGE_TYPE;
typedef struct _NUI_SKELETON_FRAME  NUI_SKELETON_FRAME;
typedef struct _NUI_IDENTITY_MESSAGE NUI_IDENTITY_MESSAGE;


#ifndef NUI_INITIALIZE_FLAG_USES_COLOR
    #define NUI_INITIALIZE_FLAG_USES_COLOR                  0x00000002
#endif

#ifndef NUI_INITIALIZE_FLAG_USES_HIGH_QUALITY_COLOR
    #define NUI_INITIALIZE_FLAG_USES_HIGH_QUALITY_COLOR     0x00000040
#endif

typedef struct _XSTUDIO_TITLE_INDEX_DATA  XSTUDIO_TITLE_INDEX_DATA;


typedef struct XED_CONTEXT XED_CONTEXT;


#define XED_EVENTINDEX_INVALID      ((UINT)-1)
#define XED_FRAMENUMBER_INVALID     ((UINT)-1)
#define XED_TIMESTAMP_INVALID       ((UINT64)-1)

#define XED_FLAG_CREATE_NEW         CREATE_NEW
#define XED_FLAG_CREATE_ALWAYS      CREATE_ALWAYS


HRESULT
XEDAPI
XedOpenFile(
    _In_z_ const char * sFilePath,
    DWORD flags,
    _Deref_out_opt_ XED_CONTEXT ** ppContext
    );


HRESULT
XEDAPI
XedCreateFile(
    _In_z_ const char * sFilePath,
    _In_opt_ const XED_CONTEXT * pTemplate,
    DWORD flags,
    _Deref_out_opt_ XED_CONTEXT ** ppContext
    );



HRESULT
XEDAPI
XedCloseFile(
    XED_CONTEXT ** ppContext
    );


HRESULT
XedSetNuiDepthImageType(
    XED_CONTEXT * pContext,
    NUI_IMAGE_TYPE newImageType,
    NUI_IMAGE_TYPE * pPreviousImageType
);


HRESULT
XEDAPI
XedSetNuiColorBufferType(
    _In_ XED_CONTEXT * pContext,
    NUI_IMAGE_TYPE newImageType,
    _Out_opt_ NUI_IMAGE_TYPE * pPreviousImageType
    );


HRESULT
XEDAPI
XedSetFileNuiColorQuality(
    _In_ XED_CONTEXT * pContext,
    DWORD newColorQuality,
    _Out_opt_ DWORD * pPreviousColorQuality
    );


UINT
XEDAPI
XedGetNuiDepthEventCount(
    _In_ XED_CONTEXT * pContext
    );


UINT
XEDAPI
XedGetNuiColorEventCount(
    _In_ XED_CONTEXT * pContext
    );


UINT
XEDAPI
XedGetNuiSkeletonEventCount(
    _In_ XED_CONTEXT * pContext
    );


UINT
XEDAPI
XedGetNuiDepthEventIndexFromFrameNumber(
    _In_ XED_CONTEXT * pContext,
    UINT frameNumber
    );


UINT
XEDAPI
XedGetNuiColorEventIndexFromFrameNumber(
    _In_ XED_CONTEXT * pContext,
    UINT frameNumber
    );


UINT
XEDAPI
XedGetNuiSkeletonEventIndexFromFrameNumber(
    _In_ XED_CONTEXT * pContext,
    UINT frameNumber
    );


UINT
XEDAPI
XedGetNuiDepthEventIndexFromMicroseconds(
    _In_ XED_CONTEXT * pContext,
    UINT64 frameMicroseconds
    );


UINT
XEDAPI
XedGetNuiColorEventIndexFromMicroseconds(
    _In_ XED_CONTEXT * pContext,
    UINT64 frameMicroseconds
    );


UINT
XEDAPI
XedGetNuiSkeletonEventIndexFromMicroseconds(
    _In_ XED_CONTEXT * pContext,
    UINT64 frameMicroseconds
    );


HRESULT
XEDAPI
XedReadNuiDepthFrame(
    _In_ XED_CONTEXT * pContext,
    UINT eventIndex,
    _Out_opt_ UINT * pFrameNumber,
    _Out_opt_ UINT64 * pFrameMicroseconds,
    _Out_opt_bytecap_(bufferSize) WORD * pBuffer,
    UINT bufferSize, // in bytes
    BOOL registerWithColor
    );


HRESULT
XEDAPI
XedReadNuiColorFrame(
    _In_ XED_CONTEXT * pContext,
    UINT eventIndex,
    _Out_opt_ UINT * pFrameNumber,
    _Out_opt_ UINT64 * pFrameMicroseconds,
    _Out_opt_bytecap_(bufferSize) DWORD * pBuffer,
    UINT bufferSize, // in bytes
    BOOL registerWithDepth
    );


HRESULT
XEDAPI
XedReadNuiSkeletonFrame(
    _In_ XED_CONTEXT * pContext,
    UINT eventIndex,
    _Out_opt_ UINT * pFrameNumber,
    _Out_opt_ UINT64 * pFrameMicroseconds,
    _Out_opt_bytecap_(skeletonFrameSize) NUI_SKELETON_FRAME * pSkeletonFrame,
    UINT skeletonFrameSize
    );


HRESULT
XEDAPI
XedWriteNuiDepthFrame(
    _In_ XED_CONTEXT * pContext,
    UINT frameNumber,
    UINT64 frameMicroseconds,
    _In_bytecount_(bufferSize) const WORD * pBuffer,
    UINT bufferSize // in bytes
    );


HRESULT
XEDAPI
XedWriteNuiColorFrame(
    _In_ XED_CONTEXT * pContext,
    UINT frameNumber,
    UINT64 frameMicroseconds,
    _In_bytecount_(bufferSize) const DWORD * pBuffer,
    UINT bufferSize // in bytes
    );


HRESULT
XEDAPI
XedWriteNuiSkeletonFrame(
    _In_ XED_CONTEXT * pContext,
    UINT frameNumber,
    UINT64 frameMicroseconds,
    _In_bytecount_(skeletonFrameSize) const NUI_SKELETON_FRAME * pSkeletonFrame,
    UINT skeletonFrameSize
    );


HRESULT
XEDAPI
XedCopyNuiDepthFrame(
    _In_ XED_CONTEXT * pFromContext,
    UINT eventIndex,
    _In_ XED_CONTEXT * pToContext,
    UINT frameNumber,
    UINT64 frameMicroseconds
    );


HRESULT
XEDAPI
XedCopyNuiColorFrame(
    _In_ XED_CONTEXT * pFromContext,
    UINT eventIndex,
    _In_ XED_CONTEXT * pToContext,
    UINT frameNumber,
    UINT64 frameMicroseconds
    );


HRESULT
XEDAPI
XedCopyNuiSkeletonFrame(
    _In_ XED_CONTEXT * pFromContext,
    UINT eventIndex,
    _In_ XED_CONTEXT * pToContext,
    UINT frameNumber,
    UINT64 frameMicroseconds
    );


UINT
XEDAPI
XedGetTitleDataEventCount(
    _In_ XED_CONTEXT * pContext
    );


UINT
XEDAPI
XedGetTitleDataEventIndexFromMicroseconds(
    _In_ XED_CONTEXT * pContext,
    UINT64 eventMicroseconds
    );


HRESULT
XEDAPI
XedReadTitleData(
    _In_ XED_CONTEXT * pContext,
    UINT eventIndex,
    _Out_opt_ UINT64 * pEventMicroseconds,
    _Out_opt_ XSTUDIO_TITLE_INDEX_DATA * pTitleIndexData,
    _Out_opt_bytecap_(titleDataBufferSize) void * pTitleDataBuffer,
    UINT titleDataBufferSize,
    _Out_ UINT * pRequiredTitleDataBufferSize
    );


HRESULT
XEDAPI
XedWriteTitleData(
    _In_ XED_CONTEXT * pContext,
    UINT64 eventMicroseconds,
    _In_opt_ const XSTUDIO_TITLE_INDEX_DATA * pTitleIndexData,
    _In_bytecount_(titleDataBufferSize) const void * pTitleDataBuffer,
    UINT titleDataBufferSize
    );


HRESULT
XEDAPI
XedCopyTitleData(
    _In_ XED_CONTEXT * pFromContext,
    UINT eventIndex,
    _In_ XED_CONTEXT * pToContext,
    UINT64 eventMicroseconds
    );



UINT
XEDAPI
XedGetEventCount(
    _In_ XED_CONTEXT * pContext,
    XSTUDIO_STREAM_ID streamId
);


UINT
XEDAPI
XedGetEventIndexFromMicroseconds(
    _In_ XED_CONTEXT * pContext,
    XSTUDIO_STREAM_ID streamId,
    UINT64 eventMicroseconds
);


HRESULT
XEDAPI
XedReadNuiIdentityMessage(
    _In_ XED_CONTEXT * pContext,
    UINT eventIndex,
    _Out_opt_ UINT64* pFrameMicroseconds,
    _Out_opt_bytecap_(identityMessageSize) NUI_IDENTITY_MESSAGE * pIdentityMessage,
    UINT identityMessageSize
);


HRESULT
XEDAPI
XedWriteNuiIdentityMessage(
    _In_ XED_CONTEXT * pContext,
    UINT64 frameMicroseconds,
    _In_bytecount_(identityMessageSize) const NUI_IDENTITY_MESSAGE * pIdentityMessage,
    UINT identityMessageSize    
);


HRESULT
XEDAPI
XedCopyNuiIdentityMessage(
    _In_ XED_CONTEXT * pSrcContext,
    UINT srcEventIndex,
    _In_ XED_CONTEXT * pDstContext,
    DWORD dwDstTrackingID,
    UINT64 dstEventMicroseconds );


#ifdef __cplusplus
} // extern "C"
#endif

