/**************************************************************************
 *
 * Copyright (C) Microsoft Corporation.  All rights reserved.
 *
 * Module Name:
 *
 *      XMAEncoder.h
 *
 * Abstract:
 *
 *      XMA encoder public interfaces, functions and data types
 *
 **************************************************************************/

#ifndef _XMAENCODER_H_
#define _XMAENCODER_H_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
    #pragma once
#endif // #if defined (_MSC_VER) && (_MSC_VER >= 1020)

//------------------------------------------------------------------------------
// The XMA1 and old-style XMA2 formats are no longer supported
//------------------------------------------------------------------------------

#ifndef XMA_ENABLE_OLD_FORMATS

    #pragma deprecated(XMAInMemoryEncoder, XMA2InMemoryEncoder)

#endif // XMA_ENABLE_OLD_FORMATS

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------

#include <basetyps.h>   // For COM interface macros
#include <unknwn.h>     // For IUnknown
#include <audiodefs.h>  // For WAVEFORMATEXTENSIBLE
#include <winerror.h>   // For standard error codes
#include "XMA2Defs.h"   // For the new XMA2WAVEFORMATEX structure

//------------------------------------------------------------------------------
// Flags
//------------------------------------------------------------------------------

#define XMAENCODER_LOOP          0x00000001
#define XMAENCODER_NOFILTER      0x00000002
#define XMAENCODER_DECODEFROMXMA 0x00000004 // Not supported for in-memory encoder
#define XMAENCODER_VERBOSE       0x00000008 // Enable debug output
#define XMAENCODER_PACKSTREAMS   0x00000010 // Pack channels into fewest streams possible

#define XMAENCODER_MASK          0x0000001F

//------------------------------------------------------------------------------
// Speaker assignments
//------------------------------------------------------------------------------

#define XMA_SPEAKER_LEFT            0x01
#define XMA_SPEAKER_RIGHT           0x02
#define XMA_SPEAKER_CENTER          0x04
#define XMA_SPEAKER_LFE             0x08
#define XMA_SPEAKER_LEFT_SURROUND   0x10
#define XMA_SPEAKER_RIGHT_SURROUND  0x20
#define XMA_SPEAKER_LEFT_BACK       0x40
#define XMA_SPEAKER_RIGHT_BACK      0x80

//------------------------------------------------------------------------------
// Other defines
//------------------------------------------------------------------------------

#define XMA_MAXINPUTCHANNELCOUNT    2

#define XMA_MAXLOOPCOUNT            255
#define XMA_INFINITELOOPCOUNT       XMA_MAXLOOPCOUNT

#define XMA_LOOP_ALIGN_SAMPLES      0x00000080


#ifndef WAVE_FORMAT_XMA
#define  WAVE_FORMAT_XMA 0x0165

typedef struct XMASTREAMFORMAT
{
    DWORD   PsuedoBytesPerSec;  // Used by encoder
    DWORD   SampleRate;         // Sample rate for the stream.
    DWORD   LoopStart;          // Loop start offset (in bits).
    DWORD   LoopEnd;            // Loop end offset (in bits).

    // Format for SubframeData: eeee ssss.
    // e: Subframe number of loop end point [0,3].
    // s: Number of subframes to skip before decoding and outputting at the loop start point [1,4].

    BYTE    SubframeData;       // Data for decoding subframes.  See above.
    BYTE    Channels;           // Number of channels in the stream (1 or 2).
    WORD    ChannelMask;        // Channel assignments for the channels in the stream (same as
                                // lower 16 bits of dwChannelMask in WAVEFORMATEXTENSIBLE).
} XMASTREAMFORMAT, *PXMASTREAMFORMAT, *NPXMASTREAMFORMAT, *LPXMASTREAMFORMAT;
typedef const XMASTREAMFORMAT *LPCXMASTREAMFORMAT;

typedef struct XMAWAVEFORMAT
{
    WORD            FormatTag;     // Audio format type (always WAVE_FORMAT_XMA).
    WORD            BitsPerSample; // Bit depth (currently required to be 16).
    WORD            EncodeOptions; // Options for XMA encoder/decoder.
    WORD            LargestSkip;   // Largest skip used in interleaving streams.
    WORD            NumStreams;    // Number of interleaved audio streams.
    BYTE            LoopCount;     // Number of loop repetitions (255 == infinite).
    BYTE            Version;       // Version of the encoder that generated this.
    XMASTREAMFORMAT XmaStreams[1]; // Format info for each stream (can grow based on wNumStreams).
} XMAWAVEFORMAT, *PXMAWAVEFORMAT, *NPXMAWAVEFORMAT, *LPXMAWAVEFORMAT;
typedef XMAWAVEFORMAT *LPCXMAWAVEFORMAT;

// Additional information for file versions 3 and above:

typedef struct XMA2STREAMFORMAT
{
    BYTE        Channels;           // Number of channels in the stream (1 or 2)
    BYTE        RESERVED;
    WORD        ChannelMask;        // Channel assignments for the channels in the stream (same as
                                    // lower 16 bits of dwChannelMask in WAVEFORMATEXTENSIBLE).
                                    // Stored with big-endian byte ordering.
} XMA2STREAMFORMAT, *LPXMA2STREAMFORMAT;
typedef const XMA2STREAMFORMAT * LPCXMA2STREAMFORMAT;

// RIFF chunk ID is "XMA2"
// Data values are stored with big-endian byte ordering
typedef struct XMA2WAVEFORMAT
{
    BYTE        Version;
    BYTE        NumStreams;
    BYTE        RESERVED;

    BYTE        LoopCount;          // Loop count, 255 == infinite
    DWORD       LoopBegin;          // Loop begin point, in samples
    DWORD       LoopEnd;            // Loop end point, in samples

    DWORD       SampleRate;

    DWORD       EncodeOptions;      // Options for XMA encoder/decoder.
    DWORD       PsuedoBytesPerSec;  // Used by encoder

    DWORD       BlockSizeInBytes;   // Size of the blocks that were encoded.
    DWORD       SamplesEncoded;     // Total number of samples in the XMA file.
    DWORD       SamplesInSource;    // The number of samples in the file used to generate the XMA
    DWORD       BlockCount;         // The number of encoded blocks in the file (also the number of elements in the seek table)

    XMA2STREAMFORMAT    Streams[1]; // Format info for each stream (can grow based on NumStreams)

} XMA2WAVEFORMAT, *LPXMA2WAVEFORMAT;
typedef const XMA2WAVEFORMAT *LPCXMA2WAVEFORMAT;

#endif // #ifndef WAVE_FORMAT_XMA


//------------------------------------------------------------------------------
// Encoder parameters
//------------------------------------------------------------------------------

typedef struct XMAENCODERSTREAM
{
    WAVEFORMATEXTENSIBLE Format;
    LPCVOID              pBuffer;
    DWORD                BufferSize;
    DWORD                LoopStart;
    DWORD                LoopLength;
    BYTE                 SpeakerAssignment[XMA_MAXINPUTCHANNELCOUNT];
} XMAENCODERSTREAM, *LPXMAENCODERSTREAM;
typedef const XMAENCODERSTREAM* LPCXMAENCODERSTREAM;

//------------------------------------------------------------------------------
// XMA Encoder Functions
//------------------------------------------------------------------------------


// The XMAInMemoryEncoder() and XMA2InMemoryEncoder() functions are no longer
// supported and should not be used in new code.  Their declarations are only
// available if XMA_ENABLE_OLD_FORMATS is defined prior to including this header.

#ifdef XMA_ENABLE_OLD_FORMATS

// This function encodes to the original, unsupported XMA1 format
STDAPI XMAInMemoryEncoder
(
    DWORD InputStreamCount,
    __in_ecount(InputStreamCount) const XMAENCODERSTREAM* pStreams,
    DWORD Compression,
    DWORD Flags,
    __deref_out_bcount(*pEncodedBufferSize) VOID** ppEncodedBuffer,
    __out DWORD* pEncodedBufferSize,
    __deref_out_bcount(*pEncodedBufferFormatSize) XMAWAVEFORMAT** ppEncodedBufferFormat,
    __out DWORD* pEncodedBufferFormatSize,
    __deref_out_bcount(*pSeekTableSize) DWORD** ppSeekTable,
    __out DWORD* pSeekTableSize
);

// This function encodes to the old, unsupported version of the XMA2 format
STDAPI XMA2InMemoryEncoder
(
    DWORD InputStreamCount,
    __in_ecount(InputStreamCount) const XMAENCODERSTREAM* pStreams,
    DWORD Compression,
    DWORD Flags,
    DWORD BlockSizeInKbytes, // Cannot be zero
    __deref_out_bcount(*pEncodedBufferSize) VOID** ppEncodedBuffer,
    __out DWORD* pEncodedBufferSize,
    __deref_out_bcount(*pEncodedBufferFormatSize) XMA2WAVEFORMAT** ppEncodedBufferFormat,
    __out DWORD* pEncodedBufferFormatSize,
    __deref_out_bcount(*pSeekTableSize) DWORD** ppSeekTable,
    __out DWORD* pSeekTableSize
);

#endif // #ifdef XMA_ENABLE_OLD_FORMATS

// This function encodes to the new, approved version of the XMA2 format,
// which is the only format usable in XAudio2.
STDAPI XAudio2XMAEncoder
(
    DWORD InputStreamCount,
    __in_ecount(InputStreamCount) const XMAENCODERSTREAM* pStreams,
    DWORD Compression,
    DWORD Flags,
    DWORD BlockSizeInKbytes, // Cannot be zero
    __deref_out_bcount(*pEncodedBufferSize) VOID** ppEncodedBuffer,
    __out DWORD* pEncodedBufferSize,
    __deref_out_bcount(*pEncodedBufferFormatSize) XMA2WAVEFORMATEX** ppEncodedBufferFormat,
    __out DWORD* pEncodedBufferFormatSize,
    __deref_out_bcount(*pSeekTableSize) DWORD** ppSeekTable,
    __out DWORD* pSeekTableSize
);

//------------------------------------------------------------------------------
// Encoder error codes
//------------------------------------------------------------------------------

#define FACILITY_XMACodec 0x889
#define XMAENCODERERROR(n) MAKE_HRESULT(SEVERITY_ERROR, FACILITY_XMACodec, n)

#define XMAENCODER_E_OUTOFMEMORY         E_OUTOFMEMORY          // Out of memory
#define XMAENCODER_E_INVALIDARG          E_INVALIDARG           // Invalid arg
#define XMAENCODER_E_NOTIMPL             E_NOTIMPL              // Not implemented
#define XMAENCODER_E_FAIL                E_FAIL                 // Unknown error

#define XMAENCODER_E_INVALIDLOOP         XMAENCODERERROR(0x001)  // The loop points are invalid.
#define XMAENCODER_E_UNSUPPORTEDFORMAT   XMAENCODERERROR(0x002)  // Format is invalid.
#define XMAENCODER_E_OUTOFRANGE          XMAENCODERERROR(0x003)  // Parameter is out of valid range.
#define XMAENCODER_E_READFAILED          XMAENCODERERROR(0x004)  // Read operation failed.
#define XMAENCODER_E_INVALIDFRAME        XMAENCODERERROR(0x005)  // Invalid XMA frame.
#define XMAENCODER_E_INCOMPLETEFRAME     XMAENCODERERROR(0x006)  // Incomplete XMA frame.
#define XMAENCODER_E_ZEROSTUFFINGBIT     XMAENCODERERROR(0x007)  // Stuffing bit is zero
#define XMAENCODER_E_GETDATAFAILED       XMAENCODERERROR(0x008)  // Data fetch failed.

#endif // #ifndef _XMAENCODER_H_
