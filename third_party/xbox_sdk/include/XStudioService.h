/***************************************************************************
*                                                                          *
*   XStudioService.h -- This module defines the APIs for Xbox 360 Studio   *
*                       Services                                           *
*                                                                          *
*   Copyright (c) Microsoft Corp. All rights reserved.                     *
*                                                                          *
***************************************************************************/

#pragma once

#ifndef XSTUDIO
#error "You must include xstudio.h rather than including xstudioservice.h directly"
#endif


#ifdef __cplusplus
extern "C" {
#endif

// Set bitfield ordering to lsb->msb on PPC (default is msb->lsb)
#if defined(_M_PPCBE)
#pragma bitfield_order(push)
#pragma bitfield_order(lsb_to_msb)
#endif


// -----------------------------------------------------------------------------
// Handle Types
// -----------------------------------------------------------------------------

typedef unsigned int    XSTUDIO_HANDLE;

typedef XSTUDIO_HANDLE  XSTUDIO_FILE_HANDLE;

// -----------------------------------------------------------------------------
// Stream Types
// -----------------------------------------------------------------------------

typedef enum _XSTUDIO_STREAM_ID
{
    XSTUDIO_STREAM_ID_NUICAM_BASE = 0,
    XSTUDIO_STREAM_ID_NUICAM_DEPTH = XSTUDIO_STREAM_ID_NUICAM_BASE + 0,            //  0
    XSTUDIO_STREAM_ID_NUICAM_COLOR = XSTUDIO_STREAM_ID_NUICAM_BASE + 1,            //  1

    XSTUDIO_STREAM_ID_NUIAPI_BASE = 4,
    XSTUDIO_STREAM_ID_NUIAPI_SKELETON = XSTUDIO_STREAM_ID_NUIAPI_BASE + 0,	       //  4
    XSTUDIO_STREAM_ID_NUIAPI_IDENTITY = XSTUDIO_STREAM_ID_NUIAPI_BASE + 2,         //  6
    XSTUDIO_STREAM_ID_NUIAPI_PLAYER_INDEX = XSTUDIO_STREAM_ID_NUIAPI_BASE + 3,     //  7

    XSTUDIO_STREAM_ID_TITLE_BASE = 16,
    XSTUDIO_STREAM_ID_TITLE_DATA = XSTUDIO_STREAM_ID_TITLE_BASE + 0,	           // 16

    XSTUDIO_STREAM_ID_MISC_PRIVATE = 31,                                           // 31

    XSTUDIO_STREAM_ID_COUNT = 32,

    XSTUDIO_STREAM_ID_INVALID = 0xFFFFFFFF

} XSTUDIO_STREAM_ID;


typedef DWORD XSTUDIO_STREAM_FLAGS, *PXSTUDIO_STREAM_FLAGS;

#define XSTUDIO_STREAM_FLAG_NONE                ( 0 )
#define XSTUDIO_STREAM_FLAG_DEFAULT             ( (XSTUDIO_STREAM_FLAGS)-1 )

#define XSTUDIO_STREAM_FLAG_NUICAM_DEPTH        ( 1 << XSTUDIO_STREAM_ID_NUICAM_DEPTH )
#define XSTUDIO_STREAM_FLAG_NUICAM_COLOR        ( 1 << XSTUDIO_STREAM_ID_NUICAM_COLOR )
#define XSTUDIO_STREAM_FLAG_NUICAM_ALL          ( XSTUDIO_STREAM_FLAG_NUICAM_DEPTH | XSTUDIO_STREAM_FLAG_NUICAM_COLOR )

#define XSTUDIO_STREAM_FLAG_NUIAPI_SKELETON     ( 1 << XSTUDIO_STREAM_ID_NUIAPI_SKELETON )
#define XSTUDIO_STREAM_FLAG_NUIAPI_IDENTITY     ( 1 << XSTUDIO_STREAM_ID_NUIAPI_IDENTITY )
#define XSTUDIO_STREAM_FLAG_NUIAPI_PLAYER_INDEX ( 1 << XSTUDIO_STREAM_ID_NUIAPI_PLAYER_INDEX )

#define XSTUDIO_STREAM_FLAG_NUIAPI_ALL          ( XSTUDIO_STREAM_FLAG_NUIAPI_SKELETON \
                                                | XSTUDIO_STREAM_FLAG_NUIAPI_IDENTITY \
                                                | XSTUDIO_STREAM_FLAG_NUIAPI_PLAYER_INDEX )


#define XSTUDIO_STREAM_FLAG_TITLE_DATA          ( 1 << XSTUDIO_STREAM_ID_TITLE_DATA )
#define XSTUDIO_STREAM_FLAG_TITLE_ALL           ( XSTUDIO_STREAM_FLAG_TITLE_DATA )


#define XSTUDIO_STREAM_FLAG_ALL                 ( XSTUDIO_STREAM_FLAG_NUICAM_ALL \
                                                | XSTUDIO_STREAM_FLAG_NUIAPI_ALL \
                                                | XSTUDIO_STREAM_FLAG_TITLE_ALL )



#if defined(_M_PPCBE)
#pragma bitfield_order(pop)
#endif

#ifdef __cplusplus
}
#endif

