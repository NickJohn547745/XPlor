//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) Microsoft Corporation.  All Rights Reserved.
//
//  File:       d3dx9tex.h
//  Content:    D3DX texturing APIs
//
//////////////////////////////////////////////////////////////////////////////

#include "d3dx9.h"

#ifndef __D3DX9TEX_H__
#define __D3DX9TEX_H__

//-------------------------------------------------------------------------
// D3DXSetDXT3DXT5
// ---------------
//
// Set premultiplied alpha format for DXT surface and texture processing.
// When set to TRUE, DXT surfaces will be processed with nonpremultiplied
// alpha i.e. DXT3 / DXT5 format. When set to FALSE, surfaces will be
// processed with premultiplied alpha, i.e. DXT2 / DXT4 format. The default
// is nonpremultiplied alpha - DXT3 / DXT5.
//
//-------------------------------------------------------------------------

VOID WINAPI D3DXSetDXT3DXT5(BOOL Set);

//-------------------------------------------------------------------------
// D3DXGetDXT3DXT5
// ---------------
//
// Get whether D3DX is currently using nonpremultiplied alpha format -
// DXT3 / DXT5 or premultiplied alpha format - DXT2 / DXT4 for DXT surface
// and texture processing.
//
//-------------------------------------------------------------------------

BOOL WINAPI D3DXGetDXT3DXT5(VOID);

//----------------------------------------------------------------------------
// D3DX_FILTER flags:
// ------------------
//
// A valid filter must contain one of these values:
//
//  D3DX_FILTER_NONE
//      No scaling or filtering will take place.  Pixels outside the bounds
//      of the source image are assumed to be transparent black.
//  D3DX_FILTER_POINT
//      Each destination pixel is computed by sampling the nearest pixel
//      from the source image.
//  D3DX_FILTER_LINEAR
//      Each destination pixel is computed by linearly interpolating between
//      the nearest pixels in the source image.  This filter works best 
//      when the scale on each axis is less than 2.
//  D3DX_FILTER_TRIANGLE
//      Every pixel in the source image contributes equally to the
//      destination image.  This is the slowest of all the filters.
//  D3DX_FILTER_BOX
//      Each pixel is computed by averaging a 2x2(x2) box pixels from 
//      the source image. Only works when the dimensions of the 
//      destination are half those of the source. (as with mip maps)
//
// And can be OR'd with any of these optional flags:
//
//  D3DX_FILTER_MIRROR_U
//      Indicates that pixels off the edge of the texture on the U-axis
//      should be mirrored, not wraped.
//  D3DX_FILTER_MIRROR_V
//      Indicates that pixels off the edge of the texture on the V-axis
//      should be mirrored, not wraped.
//  D3DX_FILTER_MIRROR_W
//      Indicates that pixels off the edge of the texture on the W-axis
//      should be mirrored, not wraped.
//  D3DX_FILTER_MIRROR
//      Same as specifying D3DX_FILTER_MIRROR_U | D3DX_FILTER_MIRROR_V |
//      D3DX_FILTER_MIRROR_V
//  D3DX_FILTER_DITHER
//      Dithers the resulting image using a 4x4 order dither pattern.
//  D3DX_FILTER_SRGB_IN
//      Denotes that the input data is in sRGB (gamma 2.2) colorspace.
//  D3DX_FILTER_SRGB_OUT
//      Denotes that the output data is in sRGB (gamma 2.2) colorspace.
//  D3DX_FILTER_SRGB
//      Same as specifying D3DX_FILTER_SRGB_IN | D3DX_FILTER_SRGB_OUT
//
//----------------------------------------------------------------------------

#define D3DX_FILTER_NONE             (1 << 0)
#define D3DX_FILTER_POINT            (2 << 0)
#define D3DX_FILTER_LINEAR           (3 << 0)
#define D3DX_FILTER_TRIANGLE         (4 << 0)
#define D3DX_FILTER_BOX              (5 << 0)

#define D3DX_FILTER_MIRROR_U         (1 << 16)
#define D3DX_FILTER_MIRROR_V         (2 << 16)
#define D3DX_FILTER_MIRROR_W         (4 << 16)
#define D3DX_FILTER_MIRROR           (7 << 16)

#define D3DX_FILTER_DITHER           (1 << 19)
#define D3DX_FILTER_DITHER_DIFFUSION (2 << 19)

#define D3DX_FILTER_SRGB_IN          (1 << 21)
#define D3DX_FILTER_SRGB_OUT         (2 << 21)
#define D3DX_FILTER_SRGB             (3 << 21)


//----------------------------------------------------------------------------
// D3DX_NORMALMAP flags:
// ---------------------
// These flags are used to control how D3DXComputeNormalMap generates normal
// maps.  Any number of these flags may be OR'd together in any combination.
//
//  D3DX_NORMALMAP_MIRROR_U
//      Indicates that pixels off the edge of the texture on the U-axis
//      should be mirrored, not wraped.
//  D3DX_NORMALMAP_MIRROR_V
//      Indicates that pixels off the edge of the texture on the V-axis
//      should be mirrored, not wraped.
//  D3DX_NORMALMAP_MIRROR
//      Same as specifying D3DX_NORMALMAP_MIRROR_U | D3DX_NORMALMAP_MIRROR_V
//  D3DX_NORMALMAP_INVERTSIGN
//      Inverts the direction of each normal 
//  D3DX_NORMALMAP_COMPUTE_OCCLUSION
//      Compute the per pixel Occlusion term and encodes it into the alpha.
//      An Alpha of 1 means that the pixel is not obscured in anyway, and
//      an alpha of 0 would mean that the pixel is completly obscured.
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

#define D3DX_NORMALMAP_MIRROR_U     (1 << 16)
#define D3DX_NORMALMAP_MIRROR_V     (2 << 16)
#define D3DX_NORMALMAP_MIRROR       (3 << 16)
#define D3DX_NORMALMAP_INVERTSIGN   (8 << 16)
#define D3DX_NORMALMAP_COMPUTE_OCCLUSION (16 << 16)




//----------------------------------------------------------------------------
// D3DX_CHANNEL flags:
// -------------------
// These flags are used by functions which operate on or more channels
// in a texture.
//
// D3DX_CHANNEL_RED
//     Indicates the red channel should be used
// D3DX_CHANNEL_BLUE
//     Indicates the blue channel should be used
// D3DX_CHANNEL_GREEN
//     Indicates the green channel should be used
// D3DX_CHANNEL_ALPHA
//     Indicates the alpha channel should be used
// D3DX_CHANNEL_LUMINANCE
//     Indicates the luminaces of the red green and blue channels should be 
//     used.
//
//----------------------------------------------------------------------------

#define D3DX_CHANNEL_RED            (1 << 0)
#define D3DX_CHANNEL_BLUE           (1 << 1)
#define D3DX_CHANNEL_GREEN          (1 << 2)
#define D3DX_CHANNEL_ALPHA          (1 << 3)
#define D3DX_CHANNEL_LUMINANCE      (1 << 4)




//----------------------------------------------------------------------------
// D3DXIMAGE_FILEFORMAT:
// ---------------------
// This enum is used to describe supported image file formats.
//
//----------------------------------------------------------------------------

typedef enum _D3DXIMAGE_FILEFORMAT
{
    D3DXIFF_BMP         = 0,
    D3DXIFF_JPG         = 1,
    D3DXIFF_TGA         = 2,
    D3DXIFF_PNG         = 3,
    D3DXIFF_DDS         = 4,
    D3DXIFF_PPM         = 5,
    D3DXIFF_DIB         = 6,
    D3DXIFF_HDR         = 7,       //high dynamic range formats
    D3DXIFF_PFM         = 8,       //
    D3DXIFF_FORCE_DWORD = 0x7fffffff

} D3DXIMAGE_FILEFORMAT;


//----------------------------------------------------------------------------
// LPD3DXFILL2D and LPD3DXFILL3D:
// ------------------------------
// Function types used by the texture fill functions.
//
// Parameters:
//  pOut
//      Pointer to a vector which the function uses to return its result.
//      X,Y,Z,W will be mapped to R,G,B,A respectivly. 
//  pTexCoord
//      Pointer to a vector containing the coordinates of the texel currently 
//      being evaluated.  Textures and VolumeTexture texcoord components 
//      range from 0 to 1. CubeTexture texcoord component range from -1 to 1.
//  pTexelSize
//      Pointer to a vector containing the dimensions of the current texel.
//  pData
//      Pointer to user data.
//
//----------------------------------------------------------------------------

typedef VOID (WINAPI *LPD3DXFILL2D)(__out D3DXVECTOR4 *pOut, 
    __in CONST D3DXVECTOR2 *pTexCoord, __in CONST D3DXVECTOR2 *pTexelSize, __in_opt LPVOID pData);

typedef VOID (WINAPI *LPD3DXFILL3D)(__out D3DXVECTOR4 *pOut, 
    __in CONST D3DXVECTOR3 *pTexCoord, __in CONST D3DXVECTOR3 *pTexelSize, __in_opt LPVOID pData);
 


//----------------------------------------------------------------------------
// D3DXIMAGE_INFO:
// ---------------
// This structure is used to return a rough description of what the
// the original contents of an image file looked like.
// 
//  Width
//      Width of original image in pixels
//  Height
//      Height of original image in pixels
//  Depth
//      Depth of original image in pixels
//  MipLevels
//      Number of mip levels in original image
//  Format
//      D3D format which most closely describes the data in original image
//  ResourceType
//      D3DRESOURCETYPE representing the type of texture stored in the file.
//      D3DRTYPE_TEXTURE, D3DRTYPE_VOLUMETEXTURE, or D3DRTYPE_CUBETEXTURE.
//  ImageFileFormat
//      D3DXIMAGE_FILEFORMAT representing the format of the image file.
//
//----------------------------------------------------------------------------

typedef struct _D3DXIMAGE_INFO
{
    UINT                    Width;
    UINT                    Height;
    UINT                    Depth;
    UINT                    MipLevels;
    D3DFORMAT               Format;
    D3DRESOURCETYPE         ResourceType;
    D3DXIMAGE_FILEFORMAT    ImageFileFormat;

} D3DXIMAGE_INFO;



#ifndef _PALETTEENTRY_DEFINED
#define _PALETTEENTRY_DEFINED

typedef struct tagPALETTEENTRY {
    BYTE        peRed;
    BYTE        peGreen;
    BYTE        peBlue;
    BYTE        peFlags;
} PALETTEENTRY, *PPALETTEENTRY, FAR *LPPALETTEENTRY;

#endif


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus



//////////////////////////////////////////////////////////////////////////////
// Image File APIs ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
;
//----------------------------------------------------------------------------
// GetImageInfoFromFile/Resource:
// ------------------------------
// Fills in a D3DXIMAGE_INFO struct with information about an image file.
//
// Parameters:
//  pSrcFile
//      File name of the source image.
//  pSrcModule
//      Module where resource is located, or NULL for module associated
//      with image the os used to create the current process.
//  pSrcResource
//      Resource name
//  pSrcData
//      Pointer to file in memory.
//  SrcDataSize
//      Size in bytes of file in memory.
//  pSrcInfo
//      Pointer to a D3DXIMAGE_INFO structure to be filled in with the 
//      description of the data in the source image file.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXGetImageInfoFromFileA(
        __in_z LPCSTR                    pSrcFile,
        __out  D3DXIMAGE_INFO*           pSrcInfo);

HRESULT WINAPI
    D3DXGetImageInfoFromFileW(
        __in_z LPCWSTR                   pSrcFile,
        __out  D3DXIMAGE_INFO*           pSrcInfo);

#ifdef UNICODE
#define D3DXGetImageInfoFromFile D3DXGetImageInfoFromFileW
#else
#define D3DXGetImageInfoFromFile D3DXGetImageInfoFromFileA
#endif

#if 0 // Unsupported on Xbox

HRESULT WINAPI
    D3DXGetImageInfoFromResourceA(
        HMODULE                   hSrcModule,
        LPCSTR                    pSrcResource,
        D3DXIMAGE_INFO*           pSrcInfo);

HRESULT WINAPI
    D3DXGetImageInfoFromResourceW(
        HMODULE                   hSrcModule,
        LPCWSTR                   pSrcResource,
        D3DXIMAGE_INFO*           pSrcInfo);

#ifdef UNICODE
#define D3DXGetImageInfoFromResource D3DXGetImageInfoFromResourceW
#else
#define D3DXGetImageInfoFromResource D3DXGetImageInfoFromResourceA
#endif

#endif

HRESULT WINAPI
    D3DXGetImageInfoFromFileInMemory(
        __in_bcount(SrcDataSize) LPCVOID                   pSrcData,
                                 UINT                      SrcDataSize,
        __out                    D3DXIMAGE_INFO*           pSrcInfo);




//////////////////////////////////////////////////////////////////////////////
// Load/Save Surface APIs ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// D3DXLoadSurfaceFromFile/Resource:
// ---------------------------------
// Load surface from a file or resource
//
// Parameters:
//  pDestSurface
//      Destination surface, which will receive the image.
//  pDestPalette
//      Destination palette of 256 colors, or NULL
//  pDestRect
//      Destination rectangle, or NULL for entire surface
//  pSrcFile
//      File name of the source image.
//  pSrcModule
//      Module where resource is located, or NULL for module associated
//      with image the os used to create the current process.
//  pSrcResource
//      Resource name
//  pSrcData
//      Pointer to file in memory.
//  SrcDataSize
//      Size in bytes of file in memory.
//  pSrcRect
//      Source rectangle, or NULL for entire image
//  Filter
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT for D3DX_FILTER_TRIANGLE.
//  ColorKey
//      Color to replace with transparent black, or 0 to disable colorkey.
//      This is always a 32-bit ARGB color, independent of the source image
//      format.  Alpha is significant, and should usually be set to FF for 
//      opaque colorkeys.  (ex. Opaque black == 0xff000000)
//  pSrcInfo
//      Pointer to a D3DXIMAGE_INFO structure to be filled in with the 
//      description of the data in the source image file, or NULL.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXLoadSurfaceFromFileA(
        __in      LPDIRECT3DSURFACE9        pDestSurface,
        __in_opt  CONST PALETTEENTRY*       pDestPalette,
        __in_opt  CONST RECT*               pDestRect,
        __in_z    LPCSTR                    pSrcFile,
        __in_opt  CONST RECT*               pSrcRect,
                  DWORD                     Filter,
                  D3DCOLOR                  ColorKey,
        __out_opt D3DXIMAGE_INFO*           pSrcInfo);

HRESULT WINAPI
    D3DXLoadSurfaceFromFileW(
        __in      LPDIRECT3DSURFACE9        pDestSurface,
        __in_opt  CONST PALETTEENTRY*       pDestPalette,
        __in_opt  CONST RECT*               pDestRect,
        __in_z    LPCWSTR                   pSrcFile,
        __in_opt  CONST RECT*               pSrcRect,
                  DWORD                     Filter,
                  D3DCOLOR                  ColorKey,
        __out_opt D3DXIMAGE_INFO*           pSrcInfo);

#ifdef UNICODE
#define D3DXLoadSurfaceFromFile D3DXLoadSurfaceFromFileW
#else
#define D3DXLoadSurfaceFromFile D3DXLoadSurfaceFromFileA
#endif


#if 0 // Unsupported on Xbox

HRESULT WINAPI
    D3DXLoadSurfaceFromResourceA(
        LPDIRECT3DSURFACE9        pDestSurface,
        CONST PALETTEENTRY*       pDestPalette,
        CONST RECT*               pDestRect,
        HMODULE                   hSrcModule,
        LPCSTR                    pSrcResource,
        CONST RECT*               pSrcRect,
        DWORD                     Filter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo);

HRESULT WINAPI
    D3DXLoadSurfaceFromResourceW(
        LPDIRECT3DSURFACE9        pDestSurface,
        CONST PALETTEENTRY*       pDestPalette,
        CONST RECT*               pDestRect,
        HMODULE                   hSrcModule,
        LPCWSTR                   pSrcResource,
        CONST RECT*               pSrcRect,
        DWORD                     Filter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo);


#ifdef UNICODE
#define D3DXLoadSurfaceFromResource D3DXLoadSurfaceFromResourceW
#else
#define D3DXLoadSurfaceFromResource D3DXLoadSurfaceFromResourceA
#endif

#endif



HRESULT WINAPI
    D3DXLoadSurfaceFromFileInMemory(
        __in                     LPDIRECT3DSURFACE9        pDestSurface,
        __in_opt                 CONST PALETTEENTRY*       pDestPalette,
        __in_opt                 CONST RECT*               pDestRect,
        __in_bcount(SrcDataSize) LPCVOID                   pSrcData,
                                 UINT                      SrcDataSize,
        __in_opt                 CONST RECT*               pSrcRect,
                                 DWORD                     Filter,
                                 D3DCOLOR                  ColorKey,
        __out_opt                D3DXIMAGE_INFO*           pSrcInfo);



//----------------------------------------------------------------------------
// D3DXLoadSurfaceFromSurface:
// ---------------------------
// Load surface from another surface (with color conversion)
//
// Parameters:
//  pDestSurface
//      Destination surface, which will receive the image.
//  pDestPalette
//      Destination palette of 256 colors, or NULL
//  pDestRect
//      Destination rectangle, or NULL for entire surface
//  pSrcSurface
//      Source surface
//  pSrcPalette
//      Source palette of 256 colors, or NULL
//  pSrcRect
//      Source rectangle, or NULL for entire surface
//  Filter
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT for D3DX_FILTER_TRIANGLE.
//  ColorKey
//      Color to replace with transparent black, or 0 to disable colorkey.
//      This is always a 32-bit ARGB color, independent of the source image
//      format.  Alpha is significant, and should usually be set to FF for 
//      opaque colorkeys.  (ex. Opaque black == 0xff000000)
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXLoadSurfaceFromSurface(
        __in     LPDIRECT3DSURFACE9        pDestSurface,
        __in_opt CONST PALETTEENTRY*       pDestPalette,
        __in_opt CONST RECT*               pDestRect,
        __in     LPDIRECT3DSURFACE9        pSrcSurface,
        __in_opt CONST PALETTEENTRY*       pSrcPalette,
        __in_opt CONST RECT*               pSrcRect,
                 DWORD                     Filter,
                 D3DCOLOR                  ColorKey);


//----------------------------------------------------------------------------
// D3DXLoadSurfaceFromMemory:
// --------------------------
// Load surface from memory.
//
// Parameters:
//  pDestSurface
//      Destination surface, which will receive the image.
//  pDestPalette
//      Destination palette of 256 colors, or NULL
//  pDestRect
//      Destination rectangle, or NULL for entire surface
//  pSrcMemory
//      Pointer to the top-left corner of the source image in memory
//  SrcFormat
//      Pixel format of the source image.
//  SrcPitch
//      Pitch of source image, in bytes.  For DXT formats, this number
//      should represent the width of one row of cells, in bytes.
//  pSrcPalette
//      Source palette of 256 colors, or NULL
//  pSrcRect
//      Source rectangle.
//  SrcParentPacked
//      TRUE if the source image is part of a texture containing a packed
//      mip tail, FALSE otherwise.
//  SrcParentWidth
//      Width of the base texture containing the source image.  This
//      is ignored if the source image is not tiled or does not contain
//      a packed mip tail.
//  SrcParentHeight
//      Height of the base texture containing the source image.  This
//      is ignored if the source image is not tiled or does not contain
//      a packed mip tail.
//  Filter
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT for D3DX_FILTER_TRIANGLE.
//  ColorKey
//      Color to replace with transparent black, or 0 to disable colorkey.
//      This is always a 32-bit ARGB color, independent of the source image
//      format.  Alpha is significant, and should usually be set to FF for 
//      opaque colorkeys.  (ex. Opaque black == 0xff000000)
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXLoadSurfaceFromMemory(
        __in     LPDIRECT3DSURFACE9        pDestSurface,
        __in_opt CONST PALETTEENTRY*       pDestPalette,
        __in_opt CONST RECT*               pDestRect,
        __in     LPCVOID                   pSrcMemory,
                 D3DFORMAT                 SrcFormat,
                 UINT                      SrcPitch,
        __in_opt CONST PALETTEENTRY*       pSrcPalette,
        __in_opt CONST RECT*               pSrcRect,
                 BOOL                      SrcPacked,
                 UINT                      SrcParentWidth,
                 UINT                      SrcParentHeight,
                 DWORD                     Filter,
                 D3DCOLOR                  ColorKey);


//----------------------------------------------------------------------------
// D3DXSaveSurfaceToFile:
// ----------------------
// Save a surface to a image file.
//
// Parameters:
//  pDestFile
//      File name of the destination file
//  DestFormat
//      D3DXIMAGE_FILEFORMAT specifying file format to use when saving.
//  pSrcSurface
//      Source surface, containing the image to be saved
//  pSrcPalette
//      Source palette of 256 colors, or NULL
//  pSrcRect
//      Source rectangle, or NULL for the entire image
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXSaveSurfaceToFileA(
        __in_z   LPCSTR                    pDestFile,
                 D3DXIMAGE_FILEFORMAT      DestFormat,
        __in     LPDIRECT3DSURFACE9        pSrcSurface,
        __in_opt CONST PALETTEENTRY*       pSrcPalette,
        __in_opt CONST RECT*               pSrcRect);

HRESULT WINAPI
    D3DXSaveSurfaceToFileW(
        __in_z   LPCWSTR                   pDestFile,
                 D3DXIMAGE_FILEFORMAT      DestFormat,
        __in     LPDIRECT3DSURFACE9        pSrcSurface,
        __in_opt CONST PALETTEENTRY*       pSrcPalette,
        __in_opt CONST RECT*               pSrcRect);

#ifdef UNICODE
#define D3DXSaveSurfaceToFile D3DXSaveSurfaceToFileW
#else
#define D3DXSaveSurfaceToFile D3DXSaveSurfaceToFileA
#endif

//----------------------------------------------------------------------------
// D3DXSaveSurfaceToFileInMemory:
// ----------------------
// Save a surface to a image file.
//
// Parameters:
//  ppDestBuf
//      address of pointer to d3dxbuffer for returning data bits
//  DestFormat
//      D3DXIMAGE_FILEFORMAT specifying file format to use when saving.
//  pSrcSurface
//      Source surface, containing the image to be saved
//  pSrcPalette
//      Source palette of 256 colors, or NULL
//  pSrcRect
//      Source rectangle, or NULL for the entire image
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXSaveSurfaceToFileInMemory(
        __deref_out LPD3DXBUFFER*             ppDestBuf,
                    D3DXIMAGE_FILEFORMAT      DestFormat,
        __in        LPDIRECT3DSURFACE9        pSrcSurface,
        __in_opt    CONST PALETTEENTRY*       pSrcPalette,
        __in_opt    CONST RECT*               pSrcRect);


//////////////////////////////////////////////////////////////////////////////
// Load/Save Volume APIs /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// D3DXLoadVolumeFromFile/Resource:
// --------------------------------
// Load volume from a file or resource
//
// Parameters:
//  pDestVolume
//      Destination volume, which will receive the image.
//  pDestPalette
//      Destination palette of 256 colors, or NULL
//  pDestBox
//      Destination box, or NULL for entire volume
//  pSrcFile
//      File name of the source image.
//  pSrcModule
//      Module where resource is located, or NULL for module associated
//      with image the os used to create the current process.
//  pSrcResource
//      Resource name
//  pSrcData
//      Pointer to file in memory.
//  SrcDataSize
//      Size in bytes of file in memory.
//  pSrcBox
//      Source box, or NULL for entire image
//  Filter
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT for D3DX_FILTER_TRIANGLE.
//  ColorKey
//      Color to replace with transparent black, or 0 to disable colorkey.
//      This is always a 32-bit ARGB color, independent of the source image
//      format.  Alpha is significant, and should usually be set to FF for 
//      opaque colorkeys.  (ex. Opaque black == 0xff000000)
//  pSrcInfo
//      Pointer to a D3DXIMAGE_INFO structure to be filled in with the 
//      description of the data in the source image file, or NULL.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXLoadVolumeFromFileA(
        __in     LPDIRECT3DVOLUME9         pDestVolume,
        __in_opt CONST PALETTEENTRY*       pDestPalette,
        __in_opt CONST D3DBOX*             pDestBox,
        __in_z   LPCSTR                    pSrcFile,
        __in_opt CONST D3DBOX*             pSrcBox,
                 DWORD                     Filter,
                 D3DCOLOR                  ColorKey,
                 D3DXIMAGE_INFO*           pSrcInfo);

HRESULT WINAPI
    D3DXLoadVolumeFromFileW(
        __in     LPDIRECT3DVOLUME9         pDestVolume,
        __in_opt CONST PALETTEENTRY*       pDestPalette,
        __in_opt CONST D3DBOX*             pDestBox,
        __in_z   LPCWSTR                   pSrcFile,
        __in_opt CONST D3DBOX*             pSrcBox,
                 DWORD                     Filter,
                 D3DCOLOR                  ColorKey,
                 D3DXIMAGE_INFO*           pSrcInfo);

#ifdef UNICODE
#define D3DXLoadVolumeFromFile D3DXLoadVolumeFromFileW
#else
#define D3DXLoadVolumeFromFile D3DXLoadVolumeFromFileA
#endif


#if 0 // Unsupported on Xbox

HRESULT WINAPI
    D3DXLoadVolumeFromResourceA(
        LPDIRECT3DVOLUME9         pDestVolume,
        CONST PALETTEENTRY*       pDestPalette,
        CONST D3DBOX*             pDestBox,
        HMODULE                   hSrcModule,
        LPCSTR                    pSrcResource,
        CONST D3DBOX*             pSrcBox,
        DWORD                     Filter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo);

HRESULT WINAPI
    D3DXLoadVolumeFromResourceW(
        LPDIRECT3DVOLUME9         pDestVolume,
        CONST PALETTEENTRY*       pDestPalette,
        CONST D3DBOX*             pDestBox,
        HMODULE                   hSrcModule,
        LPCWSTR                   pSrcResource,
        CONST D3DBOX*             pSrcBox,
        DWORD                     Filter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo);

#ifdef UNICODE
#define D3DXLoadVolumeFromResource D3DXLoadVolumeFromResourceW
#else
#define D3DXLoadVolumeFromResource D3DXLoadVolumeFromResourceA
#endif

#endif


HRESULT WINAPI
    D3DXLoadVolumeFromFileInMemory(
        __in                     LPDIRECT3DVOLUME9         pDestVolume,
        __in_opt                 CONST PALETTEENTRY*       pDestPalette,
        __in_opt                 CONST D3DBOX*             pDestBox,
        __in_bcount(SrcDataSize) LPCVOID                   pSrcData,
                                 UINT                      SrcDataSize,
        __in_opt                 CONST D3DBOX*             pSrcBox,
                                 DWORD                     Filter,
                                 D3DCOLOR                  ColorKey,
        __out_opt                D3DXIMAGE_INFO*           pSrcInfo);



//----------------------------------------------------------------------------
// D3DXLoadVolumeFromVolume:
// -------------------------
// Load volume from another volume (with color conversion)
//
// Parameters:
//  pDestVolume
//      Destination volume, which will receive the image.
//  pDestPalette
//      Destination palette of 256 colors, or NULL
//  pDestBox
//      Destination box, or NULL for entire volume
//  pSrcVolume
//      Source volume
//  pSrcPalette
//      Source palette of 256 colors, or NULL
//  pSrcBox
//      Source box, or NULL for entire volume
//  Filter
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT for D3DX_FILTER_TRIANGLE.
//  ColorKey
//      Color to replace with transparent black, or 0 to disable colorkey.
//      This is always a 32-bit ARGB color, independent of the source image
//      format.  Alpha is significant, and should usually be set to FF for 
//      opaque colorkeys.  (ex. Opaque black == 0xff000000)
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXLoadVolumeFromVolume(
        __in     LPDIRECT3DVOLUME9         pDestVolume,
        __in_opt CONST PALETTEENTRY*       pDestPalette,
        __in_opt CONST D3DBOX*             pDestBox,
        __in     LPDIRECT3DVOLUME9         pSrcVolume,
        __in_opt CONST PALETTEENTRY*       pSrcPalette,
        __in_opt CONST D3DBOX*             pSrcBox,
                 DWORD                     Filter,
                 D3DCOLOR                  ColorKey);



//----------------------------------------------------------------------------
// D3DXLoadVolumeFromMemory:
// -------------------------
// Load volume from memory.
//
// Parameters:
//  pDestVolume
//      Destination volume, which will receive the image.
//  pDestPalette
//      Destination palette of 256 colors, or NULL
//  pDestBox
//      Destination box, or NULL for entire volume
//  pSrcMemory
//      Pointer to the top-left corner of the source volume in memory
//  SrcFormat
//      Pixel format of the source volume.
//  SrcRowPitch
//      Pitch of source image, in bytes.  For DXT formats, this number
//      should represent the size of one row of cells, in bytes.
//  SrcSlicePitch
//      Pitch of source image, in bytes.  For DXT formats, this number
//      should represent the size of one slice of cells, in bytes.
//  pSrcPalette
//      Source palette of 256 colors, or NULL
//  pSrcBox
//      Source box.
//  SrcParentPacked
//      TRUE if the source volume is part of a texture containing a packed
//      mip tail, FALSE otherwise.
//  SrcParentWidth
//      Width of the base texture containing the source volume.  This
//      is ignored if the source volume is not tiled or does not contain
//      a packed mip tail.
//  SrcParentHeight
//      Height of the base texture containing the source volume.  This
//      is ignored if the source volume is not tiled or does not contain
//      a packed mip tail.
//  SrcParentDepth
//      Depth of the base texture containing the source volume.  This
//      is ignored if the source volume is not tiled or does not contain
//      a packed mip tail.
//  Filter
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT for D3DX_FILTER_TRIANGLE.
//  ColorKey
//      Color to replace with transparent black, or 0 to disable colorkey.
//      This is always a 32-bit ARGB color, independent of the source image
//      format.  Alpha is significant, and should usually be set to FF for 
//      opaque colorkeys.  (ex. Opaque black == 0xff000000)
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXLoadVolumeFromMemory(
        __in     LPDIRECT3DVOLUME9         pDestVolume,
        __in_opt CONST PALETTEENTRY*       pDestPalette,
        __in_opt CONST D3DBOX*             pDestBox,
        __in     LPCVOID                   pSrcMemory,
                 D3DFORMAT                 SrcFormat,
                 UINT                      SrcRowPitch,
                 UINT                      SrcSlicePitch,
        __in_opt CONST PALETTEENTRY*       pSrcPalette,
        __in_opt CONST D3DBOX*             pSrcBox,
                 BOOL                      SrcParentPacked,
                 UINT                      SrcParentWidth,
                 UINT                      SrcParentHeight,
                 UINT                      SrcParentDepth,
                 DWORD                     Filter,
                 D3DCOLOR                  ColorKey);



//----------------------------------------------------------------------------
// D3DXSaveVolumeToFile:
// ---------------------
// Save a volume to a image file.
//
// Parameters:
//  pDestFile
//      File name of the destination file
//  DestFormat
//      D3DXIMAGE_FILEFORMAT specifying file format to use when saving.
//  pSrcVolume
//      Source volume, containing the image to be saved
//  pSrcPalette
//      Source palette of 256 colors, or NULL
//  pSrcBox
//      Source box, or NULL for the entire volume
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXSaveVolumeToFileA(
        __in_z   LPCSTR                    pDestFile,
                 D3DXIMAGE_FILEFORMAT      DestFormat,
        __in     LPDIRECT3DVOLUME9         pSrcVolume,
        __in_opt CONST PALETTEENTRY*       pSrcPalette,
        __in_opt CONST D3DBOX*             pSrcBox);

HRESULT WINAPI
    D3DXSaveVolumeToFileW(
        __in_z   LPCWSTR                   pDestFile,
                 D3DXIMAGE_FILEFORMAT      DestFormat,
        __in     LPDIRECT3DVOLUME9         pSrcVolume,
        __in_opt CONST PALETTEENTRY*       pSrcPalette,
        __in_opt CONST D3DBOX*             pSrcBox);

#ifdef UNICODE
#define D3DXSaveVolumeToFile D3DXSaveVolumeToFileW
#else
#define D3DXSaveVolumeToFile D3DXSaveVolumeToFileA
#endif


//----------------------------------------------------------------------------
// D3DXSaveVolumeToFileInMemory:
// ---------------------
// Save a volume to a image file.
//
// Parameters:
//  pDestFile
//      File name of the destination file
//  DestFormat
//      D3DXIMAGE_FILEFORMAT specifying file format to use when saving.
//  pSrcVolume
//      Source volume, containing the image to be saved
//  pSrcPalette
//      Source palette of 256 colors, or NULL
//  pSrcBox
//      Source box, or NULL for the entire volume
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXSaveVolumeToFileInMemory(
        __deref_out LPD3DXBUFFER*             ppDestBuf,
                    D3DXIMAGE_FILEFORMAT      DestFormat,
        __in        LPDIRECT3DVOLUME9         pSrcVolume,
        __in_opt    CONST PALETTEENTRY*       pSrcPalette,
        __in_opt    CONST D3DBOX*             pSrcBox);

//////////////////////////////////////////////////////////////////////////////
// Create/Save Texture APIs //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// D3DXCheckTextureRequirements:
// -----------------------------
// Checks texture creation parameters.  If parameters are invalid, this
// function returns corrected parameters.
//
// Parameters:
//
//  pDevice
//      The D3D device to be used
//  pWidth, pHeight, pDepth, pSize
//      Desired size in pixels, or NULL.  Returns corrected size.
//  pNumMipLevels
//      Number of desired mipmap levels, or NULL.  Returns corrected number.
//  Usage
//      Texture usage flags
//  pFormat
//      Desired pixel format, or NULL.  Returns corrected format.
//  Pool
//      Memory pool to be used to create texture
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCheckTextureRequirements(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __inout_opt UINT*                     pWidth,
        __inout_opt UINT*                     pHeight,
        __inout_opt UINT*                     pNumMipLevels,
                    DWORD                     Usage,
        __inout_opt D3DFORMAT*                pFormat,
                    D3DPOOL                   Pool);

HRESULT WINAPI
    D3DXCheckCubeTextureRequirements(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __inout_opt UINT*                     pSize,
        __inout_opt UINT*                     pNumMipLevels,
                    DWORD                     Usage,
        __inout_opt D3DFORMAT*                pFormat,
                    D3DPOOL                   Pool);

HRESULT WINAPI
    D3DXCheckVolumeTextureRequirements(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __inout_opt UINT*                     pWidth,
        __inout_opt UINT*                     pHeight,
        __inout_opt UINT*                     pDepth,
        __inout_opt UINT*                     pNumMipLevels,
                    DWORD                     Usage,
        __inout_opt D3DFORMAT*                pFormat,
                    D3DPOOL                   Pool);


//----------------------------------------------------------------------------
// D3DXCreateTexture:
// ------------------
// Create an empty texture
//
// Parameters:
//
//  pDevice
//      The D3D device with which the texture is going to be used.
//  Width, Height, Depth, Size
//      size in pixels. these must be non-zero
//  MipLevels
//      number of mip levels desired. if zero or D3DX_DEFAULT, a complete
//      mipmap chain will be created.
//  Usage
//      Texture usage flags
//  Format
//      Pixel format.
//  Pool
//      Memory pool to be used to create texture
//  ppTexture, ppCubeTexture, ppVolumeTexture
//      The texture object that will be created
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateTexture(
        __in        LPDIRECT3DDEVICE9         pDevice,
                    UINT                      Width,
                    UINT                      Height,
                    UINT                      MipLevels,
                    DWORD                     Usage,
                    D3DFORMAT                 Format,
                    D3DPOOL                   Pool,
        __deref_out LPDIRECT3DTEXTURE9*       ppTexture);

HRESULT WINAPI
    D3DXCreateCubeTexture(
        __in        LPDIRECT3DDEVICE9         pDevice,
                    UINT                      Size,
                    UINT                      MipLevels,
                    DWORD                     Usage,
                    D3DFORMAT                 Format,
                    D3DPOOL                   Pool,
        __deref_out LPDIRECT3DCUBETEXTURE9*   ppCubeTexture);

HRESULT WINAPI
    D3DXCreateVolumeTexture(
        __in        LPDIRECT3DDEVICE9         pDevice,
                    UINT                      Width,
                    UINT                      Height,
                    UINT                      Depth,
                    UINT                      MipLevels,
                    DWORD                     Usage,
                    D3DFORMAT                 Format,
                    D3DPOOL                   Pool,
        __deref_out LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture);



//----------------------------------------------------------------------------
// D3DXCreateTextureFromFile/Resource:
// -----------------------------------
// Create a texture object from a file or resource.
//
// Parameters:
//
//  pDevice
//      The D3D device with which the texture is going to be used.
//  pSrcFile
//      File name.
//  hSrcModule
//      Module handle. if NULL, current module will be used.
//  pSrcResource
//      Resource name in module
//  pvSrcData
//      Pointer to file in memory.
//  SrcDataSize
//      Size in bytes of file in memory.
//  Width, Height, Depth, Size
//      Size in pixels.  If zero or D3DX_DEFAULT, the size will be taken from 
//      the file and rounded up to a power of two.  If D3DX_DEFAULT_NONPOW2, 
//      the size will be not be rounded, if the device supports NONPOW2 textures.
//  MipLevels
//      Number of mip levels.  If zero or D3DX_DEFAULT, a complete mipmap
//      chain will be created.
//  Usage
//      Texture usage flags
//  Format
//      Desired pixel format.  If D3DFMT_UNKNOWN, the format will be
//      taken from the file.
//  Pool
//      Memory pool to be used to create texture
//  Filter
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT for D3DX_FILTER_TRIANGLE.
//  MipFilter
//      D3DX_FILTER flags controlling how each miplevel is filtered.
//      Or D3DX_DEFAULT for D3DX_FILTER_BOX,
//  ColorKey
//      Color to replace with transparent black, or 0 to disable colorkey.
//      This is always a 32-bit ARGB color, independent of the source image
//      format.  Alpha is significant, and should usually be set to FF for 
//      opaque colorkeys.  (ex. Opaque black == 0xff000000)
//  pSrcInfo
//      Pointer to a D3DXIMAGE_INFO structure to be filled in with the 
//      description of the data in the source image file, or NULL.
//  pPalette
//      256 color palette to be filled in, or NULL
//  ppTexture, ppCubeTexture, ppVolumeTexture
//      The texture object that will be created
//
//----------------------------------------------------------------------------


// FromFile

HRESULT WINAPI
    D3DXCreateTextureFromFileA(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __in_z      LPCSTR                    pSrcFile,
        __deref_out LPDIRECT3DTEXTURE9*       ppTexture);

HRESULT WINAPI
    D3DXCreateTextureFromFileW(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __in_z      LPCWSTR                   pSrcFile,
        __deref_out LPDIRECT3DTEXTURE9*       ppTexture);

#ifdef UNICODE
#define D3DXCreateTextureFromFile D3DXCreateTextureFromFileW
#else
#define D3DXCreateTextureFromFile D3DXCreateTextureFromFileA
#endif


HRESULT WINAPI
    D3DXCreateCubeTextureFromFileA(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __in_z      LPCSTR                    pSrcFile,
        __deref_out LPDIRECT3DCUBETEXTURE9*   ppCubeTexture);

HRESULT WINAPI
    D3DXCreateCubeTextureFromFileW(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __in_z      LPCWSTR                   pSrcFile,
        __deref_out LPDIRECT3DCUBETEXTURE9*   ppCubeTexture);

#ifdef UNICODE
#define D3DXCreateCubeTextureFromFile D3DXCreateCubeTextureFromFileW
#else
#define D3DXCreateCubeTextureFromFile D3DXCreateCubeTextureFromFileA
#endif


HRESULT WINAPI
    D3DXCreateVolumeTextureFromFileA(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __in_z      LPCSTR                    pSrcFile,
        __deref_out LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture);

HRESULT WINAPI
    D3DXCreateVolumeTextureFromFileW(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __in_z      LPCWSTR                   pSrcFile,
        __deref_out LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture);

#ifdef UNICODE
#define D3DXCreateVolumeTextureFromFile D3DXCreateVolumeTextureFromFileW
#else
#define D3DXCreateVolumeTextureFromFile D3DXCreateVolumeTextureFromFileA
#endif


// FromResource

#if 0 // Unsupported on Xbox

HRESULT WINAPI
    D3DXCreateTextureFromResourceA(
        LPDIRECT3DDEVICE9         pDevice,
        HMODULE                   hSrcModule,
        LPCSTR                    pSrcResource,
        LPDIRECT3DTEXTURE9*       ppTexture);

HRESULT WINAPI
    D3DXCreateTextureFromResourceW(
        LPDIRECT3DDEVICE9         pDevice,
        HMODULE                   hSrcModule,
        LPCWSTR                   pSrcResource,
        LPDIRECT3DTEXTURE9*       ppTexture);

#ifdef UNICODE
#define D3DXCreateTextureFromResource D3DXCreateTextureFromResourceW
#else
#define D3DXCreateTextureFromResource D3DXCreateTextureFromResourceA
#endif


HRESULT WINAPI
    D3DXCreateCubeTextureFromResourceA(
        LPDIRECT3DDEVICE9         pDevice,
        HMODULE                   hSrcModule,
        LPCSTR                    pSrcResource,
        LPDIRECT3DCUBETEXTURE9*   ppCubeTexture);

HRESULT WINAPI
    D3DXCreateCubeTextureFromResourceW(
        LPDIRECT3DDEVICE9         pDevice,
        HMODULE                   hSrcModule,
        LPCWSTR                   pSrcResource,
        LPDIRECT3DCUBETEXTURE9*   ppCubeTexture);

#ifdef UNICODE
#define D3DXCreateCubeTextureFromResource D3DXCreateCubeTextureFromResourceW
#else
#define D3DXCreateCubeTextureFromResource D3DXCreateCubeTextureFromResourceA
#endif


HRESULT WINAPI
    D3DXCreateVolumeTextureFromResourceA(
        LPDIRECT3DDEVICE9         pDevice,
        HMODULE                   hSrcModule,
        LPCSTR                    pSrcResource,
        LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture);

HRESULT WINAPI
    D3DXCreateVolumeTextureFromResourceW(
        LPDIRECT3DDEVICE9         pDevice,
        HMODULE                   hSrcModule,
        LPCWSTR                   pSrcResource,
        LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture);

#ifdef UNICODE
#define D3DXCreateVolumeTextureFromResource D3DXCreateVolumeTextureFromResourceW
#else
#define D3DXCreateVolumeTextureFromResource D3DXCreateVolumeTextureFromResourceA
#endif

#endif // 0

// FromFileEx

HRESULT WINAPI
    D3DXCreateTextureFromFileExA(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __in_z      LPCSTR                    pSrcFile,
                    UINT                      Width,
                    UINT                      Height,
                    UINT                      MipLevels,
                    DWORD                     Usage,
                    D3DFORMAT                 Format,
                    D3DPOOL                   Pool,
                    DWORD                     Filter,
                    DWORD                     MipFilter,
                    D3DCOLOR                  ColorKey,
        __out_opt   D3DXIMAGE_INFO*           pSrcInfo,
        __out_opt   PALETTEENTRY*             pPalette,
        __deref_out LPDIRECT3DTEXTURE9*       ppTexture);

HRESULT WINAPI
    D3DXCreateTextureFromFileExW(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __in_z      LPCWSTR                   pSrcFile,
                    UINT                      Width,
                    UINT                      Height,
                    UINT                      MipLevels,
                    DWORD                     Usage,
                    D3DFORMAT                 Format,
                    D3DPOOL                   Pool,
                    DWORD                     Filter,
                    DWORD                     MipFilter,
                    D3DCOLOR                  ColorKey,
        __out_opt   D3DXIMAGE_INFO*           pSrcInfo,
        __out_opt   PALETTEENTRY*             pPalette,
        __deref_out LPDIRECT3DTEXTURE9*       ppTexture);

#ifdef UNICODE
#define D3DXCreateTextureFromFileEx D3DXCreateTextureFromFileExW
#else
#define D3DXCreateTextureFromFileEx D3DXCreateTextureFromFileExA
#endif


HRESULT WINAPI
    D3DXCreateCubeTextureFromFileExA(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __in_z      LPCSTR                    pSrcFile,
                    UINT                      Size,
                    UINT                      MipLevels,
                    DWORD                     Usage,
                    D3DFORMAT                 Format,
                    D3DPOOL                   Pool,
                    DWORD                     Filter,
                    DWORD                     MipFilter,
                    D3DCOLOR                  ColorKey,
        __out_opt   D3DXIMAGE_INFO*           pSrcInfo,
        __out_opt   PALETTEENTRY*             pPalette,
        __deref_out LPDIRECT3DCUBETEXTURE9*   ppCubeTexture);

HRESULT WINAPI
    D3DXCreateCubeTextureFromFileExW(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __in_z      LPCWSTR                   pSrcFile,
                    UINT                      Size,
                    UINT                      MipLevels,
                    DWORD                     Usage,
                    D3DFORMAT                 Format,
                    D3DPOOL                   Pool,
                    DWORD                     Filter,
                    DWORD                     MipFilter,
                    D3DCOLOR                  ColorKey,
        __out_opt   D3DXIMAGE_INFO*           pSrcInfo,
        __out_opt   PALETTEENTRY*             pPalette,
        __deref_out LPDIRECT3DCUBETEXTURE9*   ppCubeTexture);

#ifdef UNICODE
#define D3DXCreateCubeTextureFromFileEx D3DXCreateCubeTextureFromFileExW
#else
#define D3DXCreateCubeTextureFromFileEx D3DXCreateCubeTextureFromFileExA
#endif


HRESULT WINAPI
    D3DXCreateVolumeTextureFromFileExA(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __in_z      LPCSTR                    pSrcFile,
                    UINT                      Width,
                    UINT                      Height,
                    UINT                      Depth,
                    UINT                      MipLevels,
                    DWORD                     Usage,
                    D3DFORMAT                 Format,
                    D3DPOOL                   Pool,
                    DWORD                     Filter,
                    DWORD                     MipFilter,
                    D3DCOLOR                  ColorKey,
        __out_opt   D3DXIMAGE_INFO*           pSrcInfo,
        __out_opt   PALETTEENTRY*             pPalette,
        __deref_out LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture);

HRESULT WINAPI
    D3DXCreateVolumeTextureFromFileExW(
        __in        LPDIRECT3DDEVICE9         pDevice,
        __in_z      LPCWSTR                   pSrcFile,
                    UINT                      Width,
                    UINT                      Height,
                    UINT                      Depth,
                    UINT                      MipLevels,
                    DWORD                     Usage,
                    D3DFORMAT                 Format,
                    D3DPOOL                   Pool,
                    DWORD                     Filter,
                    DWORD                     MipFilter,
                    D3DCOLOR                  ColorKey,
        __out_opt   D3DXIMAGE_INFO*           pSrcInfo,
        __out_opt   PALETTEENTRY*             pPalette,
        __deref_out LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture);

#ifdef UNICODE
#define D3DXCreateVolumeTextureFromFileEx D3DXCreateVolumeTextureFromFileExW
#else
#define D3DXCreateVolumeTextureFromFileEx D3DXCreateVolumeTextureFromFileExA
#endif


// FromResourceEx

#if 0 // Unsupported on Xbox

HRESULT WINAPI
    D3DXCreateTextureFromResourceExA(
        LPDIRECT3DDEVICE9         pDevice,
        HMODULE                   hSrcModule,
        LPCSTR                    pSrcResource,
        UINT                      Width,
        UINT                      Height,
        UINT                      MipLevels,
        DWORD                     Usage,
        D3DFORMAT                 Format,
        D3DPOOL                   Pool,
        DWORD                     Filter,
        DWORD                     MipFilter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo,
        PALETTEENTRY*             pPalette,
        LPDIRECT3DTEXTURE9*       ppTexture);

HRESULT WINAPI
    D3DXCreateTextureFromResourceExW(
        LPDIRECT3DDEVICE9         pDevice,
        HMODULE                   hSrcModule,
        LPCWSTR                   pSrcResource,
        UINT                      Width,
        UINT                      Height,
        UINT                      MipLevels,
        DWORD                     Usage,
        D3DFORMAT                 Format,
        D3DPOOL                   Pool,
        DWORD                     Filter,
        DWORD                     MipFilter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo,
        PALETTEENTRY*             pPalette,
        LPDIRECT3DTEXTURE9*       ppTexture);

#ifdef UNICODE
#define D3DXCreateTextureFromResourceEx D3DXCreateTextureFromResourceExW
#else
#define D3DXCreateTextureFromResourceEx D3DXCreateTextureFromResourceExA
#endif


HRESULT WINAPI
    D3DXCreateCubeTextureFromResourceExA(
        LPDIRECT3DDEVICE9         pDevice,
        HMODULE                   hSrcModule,
        LPCSTR                    pSrcResource,
        UINT                      Size,
        UINT                      MipLevels,
        DWORD                     Usage,
        D3DFORMAT                 Format,
        D3DPOOL                   Pool,
        DWORD                     Filter,
        DWORD                     MipFilter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo,
        PALETTEENTRY*             pPalette,
        LPDIRECT3DCUBETEXTURE9*   ppCubeTexture);

HRESULT WINAPI
    D3DXCreateCubeTextureFromResourceExW(
        LPDIRECT3DDEVICE9         pDevice,
        HMODULE                   hSrcModule,
        LPCWSTR                   pSrcResource,
        UINT                      Size,
        UINT                      MipLevels,
        DWORD                     Usage,
        D3DFORMAT                 Format,
        D3DPOOL                   Pool,
        DWORD                     Filter,
        DWORD                     MipFilter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo,
        PALETTEENTRY*             pPalette,
        LPDIRECT3DCUBETEXTURE9*   ppCubeTexture);

#ifdef UNICODE
#define D3DXCreateCubeTextureFromResourceEx D3DXCreateCubeTextureFromResourceExW
#else
#define D3DXCreateCubeTextureFromResourceEx D3DXCreateCubeTextureFromResourceExA
#endif


HRESULT WINAPI
    D3DXCreateVolumeTextureFromResourceExA(
        LPDIRECT3DDEVICE9         pDevice,
        HMODULE                   hSrcModule,
        LPCSTR                    pSrcResource,
        UINT                      Width,
        UINT                      Height,
        UINT                      Depth,
        UINT                      MipLevels,
        DWORD                     Usage,
        D3DFORMAT                 Format,
        D3DPOOL                   Pool,
        DWORD                     Filter,
        DWORD                     MipFilter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo,
        PALETTEENTRY*             pPalette,
        LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture);

HRESULT WINAPI
    D3DXCreateVolumeTextureFromResourceExW(
        LPDIRECT3DDEVICE9         pDevice,
        HMODULE                   hSrcModule,
        LPCWSTR                   pSrcResource,
        UINT                      Width,
        UINT                      Height,
        UINT                      Depth,
        UINT                      MipLevels,
        DWORD                     Usage,
        D3DFORMAT                 Format,
        D3DPOOL                   Pool,
        DWORD                     Filter,
        DWORD                     MipFilter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo,
        PALETTEENTRY*             pPalette,
        LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture);

#ifdef UNICODE
#define D3DXCreateVolumeTextureFromResourceEx D3DXCreateVolumeTextureFromResourceExW
#else
#define D3DXCreateVolumeTextureFromResourceEx D3DXCreateVolumeTextureFromResourceExA
#endif

#endif // 0

// FromFileInMemory

HRESULT WINAPI
    D3DXCreateTextureFromFileInMemory(
        __in                     LPDIRECT3DDEVICE9         pDevice,
        __in_bcount(SrcDataSize) LPCVOID                   pSrcData,
                                 UINT                      SrcDataSize,
        __deref_out              LPDIRECT3DTEXTURE9*       ppTexture);

HRESULT WINAPI
    D3DXCreateCubeTextureFromFileInMemory(
        __in                     LPDIRECT3DDEVICE9         pDevice,
        __in_bcount(SrcDataSize) LPCVOID                   pSrcData,
                                 UINT                      SrcDataSize,
        __deref_out              LPDIRECT3DCUBETEXTURE9*   ppCubeTexture);

HRESULT WINAPI
    D3DXCreateVolumeTextureFromFileInMemory(
        __in                     LPDIRECT3DDEVICE9         pDevice,
        __in_bcount(SrcDataSize) LPCVOID                   pSrcData,
                                 UINT                      SrcDataSize,
        __deref_out              LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture);


// FromFileInMemoryEx

HRESULT WINAPI
    D3DXCreateTextureFromFileInMemoryEx(
        __in                     LPDIRECT3DDEVICE9         pDevice,
        __in_bcount(SrcDataSize) LPCVOID                   pSrcData,
                                 UINT                      SrcDataSize,
                                 UINT                      Width,
                                 UINT                      Height,
                                 UINT                      MipLevels,
                                 DWORD                     Usage,
                                 D3DFORMAT                 Format,
                                 D3DPOOL                   Pool,
                                 DWORD                     Filter,
                                 DWORD                     MipFilter,
                                 D3DCOLOR                  ColorKey,
        __out_opt                D3DXIMAGE_INFO*           pSrcInfo,
        __out_opt                PALETTEENTRY*             pPalette,
        __deref_out              LPDIRECT3DTEXTURE9*       ppTexture);

HRESULT WINAPI
    D3DXCreateCubeTextureFromFileInMemoryEx(
        __in                     LPDIRECT3DDEVICE9         pDevice,
        __in_bcount(SrcDataSize) LPCVOID                   pSrcData,
                                 UINT                      SrcDataSize,
                                 UINT                      Size,
                                 UINT                      MipLevels,
                                 DWORD                     Usage,
                                 D3DFORMAT                 Format,
                                 D3DPOOL                   Pool,
                                 DWORD                     Filter,
                                 DWORD                     MipFilter,
                                 D3DCOLOR                  ColorKey,
        __out_opt                D3DXIMAGE_INFO*           pSrcInfo,
        __out_opt                PALETTEENTRY*             pPalette,
        __deref_out              LPDIRECT3DCUBETEXTURE9*   ppCubeTexture);

HRESULT WINAPI
    D3DXCreateVolumeTextureFromFileInMemoryEx(
        __in                     LPDIRECT3DDEVICE9         pDevice,
        __in_bcount(SrcDataSize) LPCVOID                   pSrcData,
                                 UINT                      SrcDataSize,
                                 UINT                      Width,
                                 UINT                      Height,
                                 UINT                      Depth,
                                 UINT                      MipLevels,
                                 DWORD                     Usage,
                                 D3DFORMAT                 Format,
                                 D3DPOOL                   Pool,
                                 DWORD                     Filter,
                                 DWORD                     MipFilter,
                                 D3DCOLOR                  ColorKey,
        __out_opt                D3DXIMAGE_INFO*           pSrcInfo,
        __out_opt                PALETTEENTRY*             pPalette,
        __deref_out              LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture);



//----------------------------------------------------------------------------
// D3DXSaveTextureToFile:
// ----------------------
// Save a texture to a file.
//
// Parameters:
//  pDestFile
//      File name of the destination file
//  DestFormat
//      D3DXIMAGE_FILEFORMAT specifying file format to use when saving.
//  pSrcTexture
//      Source texture, containing the image to be saved
//  pSrcPalette
//      Source palette of 256 colors, or NULL
//
//----------------------------------------------------------------------------


HRESULT WINAPI
    D3DXSaveTextureToFileA(
        __in_z   LPCSTR                    pDestFile,
                 D3DXIMAGE_FILEFORMAT      DestFormat,
        __in     LPDIRECT3DBASETEXTURE9    pSrcTexture,
        __in_opt CONST PALETTEENTRY*       pSrcPalette);

HRESULT WINAPI
    D3DXSaveTextureToFileW(
        __in_z   LPCWSTR                   pDestFile,
                 D3DXIMAGE_FILEFORMAT      DestFormat,
        __in     LPDIRECT3DBASETEXTURE9    pSrcTexture,
        __in_opt CONST PALETTEENTRY*       pSrcPalette);

#ifdef UNICODE
#define D3DXSaveTextureToFile D3DXSaveTextureToFileW
#else
#define D3DXSaveTextureToFile D3DXSaveTextureToFileA
#endif


//----------------------------------------------------------------------------
// D3DXSaveTextureToFileInMemory:
// ----------------------
// Save a texture to a file.
//
// Parameters:
//  ppDestBuf
//      address of a d3dxbuffer pointer to return the image data
//  DestFormat
//      D3DXIMAGE_FILEFORMAT specifying file format to use when saving.
//  pSrcTexture
//      Source texture, containing the image to be saved
//  pSrcPalette
//      Source palette of 256 colors, or NULL
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXSaveTextureToFileInMemory(
        __deref_out LPD3DXBUFFER*             ppDestBuf,
                    D3DXIMAGE_FILEFORMAT      DestFormat,
        __in        LPDIRECT3DBASETEXTURE9    pSrcTexture,
        __in_opt    CONST PALETTEENTRY*       pSrcPalette);




//////////////////////////////////////////////////////////////////////////////
// Misc Texture APIs /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// D3DXFilterTexture:
// ------------------
// Filters mipmaps levels of a texture.
//
// Parameters:
//  pBaseTexture
//      The texture object to be filtered
//  pPalette
//      256 color palette to be used, or NULL for non-palettized formats
//  SrcLevel
//      The level whose image is used to generate the subsequent levels. 
//  Filter
//      D3DX_FILTER flags controlling how each miplevel is filtered.
//      Or D3DX_DEFAULT for D3DX_FILTER_BOX,
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXFilterTexture(
        __in     LPDIRECT3DBASETEXTURE9    pBaseTexture,
        __in_opt CONST PALETTEENTRY*       pPalette,
                 UINT                      SrcLevel,
                 DWORD                     Filter);

#define D3DXFilterCubeTexture D3DXFilterTexture
#define D3DXFilterVolumeTexture D3DXFilterTexture



//----------------------------------------------------------------------------
// D3DXFillTexture:
// ----------------
// Uses a user provided function to fill each texel of each mip level of a
// given texture.
//
// Paramters:
//  pTexture, pCubeTexture, pVolumeTexture
//      Pointer to the texture to be filled.
//  pFunction
//      Pointer to user provided evalutor function which will be used to 
//      compute the value of each texel.
//  pData
//      Pointer to an arbitrary block of user defined data.  This pointer 
//      will be passed to the function provided in pFunction
//-----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXFillTexture(
        __in     LPDIRECT3DTEXTURE9        pTexture,
        __in     LPD3DXFILL2D              pFunction,
        __in_opt LPVOID                    pData);

HRESULT WINAPI
    D3DXFillCubeTexture(
        __in     LPDIRECT3DCUBETEXTURE9    pCubeTexture,
        __in     LPD3DXFILL3D              pFunction,
        __in_opt LPVOID                    pData);

HRESULT WINAPI
    D3DXFillVolumeTexture(
        __in     LPDIRECT3DVOLUMETEXTURE9  pVolumeTexture,
        __in     LPD3DXFILL3D              pFunction,
        __in_opt LPVOID                    pData);

//----------------------------------------------------------------------------
// D3DXFillTextureTX:
// ----------------
// Uses a TX Shader target to function to fill each texel of each mip level of a
// given texture. The TX Shader target should be a compiled function taking 2
// 2 paramters and returning a float4 color.
//
// Paramters:
//  pTexture, pCubeTexture, pVolumeTexture
//      Pointer to the texture to be filled.
//  pFunction:
//      Pointer to the compiled function returned by D3DX
//  pConstants
//      Constants used by program. Should be filled by user by parsing constant
//      Table information
//  Constants
//      Number of Constants   
//-----------------------------------------------------------------------------

HRESULT WINAPI 
    D3DXFillTextureTX(
        __in                       LPDIRECT3DTEXTURE9        pTexture,
        __in                       CONST DWORD*              pFunction,
        __in_ecount_opt(Constants) CONST D3DXVECTOR4*        pConstants,
                                   UINT                      Constants);


HRESULT WINAPI
    D3DXFillCubeTextureTX(
        __in                       LPDIRECT3DCUBETEXTURE9    pCubeTexture,
        __in                       CONST DWORD*              pFunction,
        __in_ecount_opt(Constants) CONST D3DXVECTOR4*        pConstants,
                                   UINT                      Constants);
                                                
                                                        
HRESULT WINAPI 
    D3DXFillVolumeTextureTX(
        __in                       LPDIRECT3DVOLUMETEXTURE9  pVolumeTexture,
        __in                       CONST DWORD*              pFunction,
        __in_ecount_opt(Constants) CONST D3DXVECTOR4*        pConstants,
                                   UINT                      Constants);


//----------------------------------------------------------------------------
// D3DXComputeNormalMap:
// ---------------------
// Converts a height map into a normal map.  The (x,y,z) components of each
// normal are mapped to the (r,g,b) channels of the output texture.
//
// Parameters
//  pTexture
//      Pointer to the destination texture
//  pSrcTexture
//      Pointer to the source heightmap texture 
//  pSrcPalette
//      Source palette of 256 colors, or NULL
//  Flags
//      D3DX_NORMALMAP flags
//  Channel
//      D3DX_CHANNEL specifying source of height information
//  Amplitude
//      The constant value which the height information is multiplied by.
//---------------------------------------------------------------------------

HRESULT WINAPI
    D3DXComputeNormalMap(
        __in     LPDIRECT3DTEXTURE9        pTexture,
        __in     LPDIRECT3DTEXTURE9        pSrcTexture,
        __in_opt CONST PALETTEENTRY*       pSrcPalette,
                 DWORD                     Flags,
                 DWORD                     Channel,
                 FLOAT                     Amplitude);




#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__D3DX9TEX_H__

