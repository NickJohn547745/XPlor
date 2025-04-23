/**************************************************************************
 *
 * Copyright (C) Microsoft Corporation.  All rights reserved.
 *
 * Module Name:
 *
 *      XWMAEncoder.h
 *
 * Abstract:
 *
 *      xWMA encoder public interfaces, functions and data types
 *
 **************************************************************************/

#ifndef _XWMAENCODER_H_
#define _XWMAENCODER_H_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
    #pragma once
#endif // #if defined (_MSC_VER) && (_MSC_VER >= 1020)

// Default XWMA encoding bitrate
#define XWMA_DEFAULT_BITRATE 48000

// XWMA encoder error codes
#define FACILITY_XWMA 0x899
#define XWMA_ERROR(n) MAKE_HRESULT(SEVERITY_ERROR, FACILITY_XWMA, n)

#define XWMA_E_UNSUPPORTED_FORMATTAG     XWMA_ERROR(0x01) // format tag must be WAVE_FORMAT_PCM or WAVE_FORMAT_IEEE_FLOAT
#define XWMA_E_UNSUPPORTED_FRAMERATE     XWMA_ERROR(0x02) // nSamplesPerSec must be between 1kHz and 200kHz
#define XWMA_E_UNSUPPORTED_CHANNELS      XWMA_ERROR(0x03) // nChannels must be 1, 2, or 6
#define XWMA_E_UNSUPPORTED_BITSPERSAMPLE XWMA_ERROR(0x04) // wBitsPerSample must be 8, 16 or 24 for integer input data or 32 for floating-point data
#define XWMA_E_UNSUPPORTED_BITRATE       XWMA_ERROR(0x05) // bitrate must be 20kbps, 32kbps, 48kbps, 64kbps, 96kbps, 16kbps0, or 192kbps

#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_
    #pragma pack(push, 1)
    typedef struct tWAVEFORMATEX
    {
        WORD    wFormatTag;      // format type
        WORD    nChannels;       // number of channels (i.e. mono, stereo...)
        DWORD   nSamplesPerSec;  // sample rate
        DWORD   nAvgBytesPerSec; // for buffer estimation
        WORD    nBlockAlign;     // block size of data
        WORD    wBitsPerSample;  // Number of bits per sample of mono data
        WORD    cbSize;          // The count in bytes of the size of extra information (after cbSize)

    } WAVEFORMATEX, *PWAVEFORMATEX;
    typedef WAVEFORMATEX NEAR *NPWAVEFORMATEX;
    typedef WAVEFORMATEX FAR  *LPWAVEFORMATEX;
    #pragma pack(pop)
#endif

////
// DESCRIPTION:
//  Encodes PCM data to xWMA
//
// REMARKS:
//  Resamples and pads the input data if necessary for it to encode successfully.
//  May have to adjust the bitrate.
//
// PARAMETERS:
//  pInputBuffer                      - [in] input buffer, contains PCM data, must contain at least one frame
//  inputBufferSize                   - [in] size of input buffer (in bytes)
//  pInputFormat                      - [in] input buffer format
//  outputBitrate                     - [in] requested WMA encoder bitrate
//                                           Must be one of 20000, 32000, 48000, 64000, 96000, 160000 or 192000
//                                           Natively supported bitrates per sample rate and channel count:
//                                           22050Hz mono:   20000
//                                           22050Hz stereo: 32000
//                                           32000Hz mono:   20000
//                                           32000Hz stereo: 32000, 48000
//                                           44100Hz mono:   32000, 48000
//                                           44100Hz stereo: 32000, 48000, 96000, 192000
//                                           44100Hz 5.1:    96000, 192000
//                                           48000Hz stereo: 48000, 64000, 96000, 160000, 192000
//                                           48000Hz 5.1:    48000, 192000
//  ppEncodedBuffer                   - [out] output buffer (use free [] to release)
//  pEncodedBufferSize                - [out] size of output buffer (in bytes)
//  ppEncodedBufferFormat             - [out] output buffer format (use free [] to release)
//  pEncodedBufferFormatSize          - [out] size of output buffer format
//  ppDecodedPacketCumulativeBytes    - [out] decoded packet cumulative data size array (use free [] to release)
//  pDecodedPacketCumulativeBytesSize - [out] size of decoded packet cumulative data (in bytes) - number of packets = *pDecodedPacketCumulativeBytesSize / sizeof(DWORD)
//
// RETURN VALUE:
//  S_OK on success, any other value on failure (see error codes above for reference)
////

STDAPI 
XWMAEncoder(
    __in_bcount(inputBufferSize) const BYTE*                       pInputBuffer,
    __in DWORD                                                     inputBufferSize,
    __in const WAVEFORMATEX*                                       pInputFormat,
    __in DWORD                                                     outputBitrate,
    __deref_out_bcount(*pEncodedBufferSize) BYTE**                 ppEncodedBuffer,
    __out DWORD*                                                   pEncodedBufferSize,
    __deref_out_bcount(*pEncodedBufferFormatSize) WAVEFORMATEX**   ppEncodedBufferFormat,
    __out DWORD*                                                   pEncodedBufferFormatSize,
    __deref_out_bcount(*pDecodedPacketCumulativeBytesSize) DWORD** ppDecodedPacketCumulativeBytes,
    __out DWORD*                                                   pDecodedPacketCumulativeBytesSize
    );

#endif // #ifndef _XWMAENCODER_H_
