///////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) Microsoft Corporation.  All Rights Reserved.
//
//  File:       d3dx9shapes.h
//  Content:    D3DX simple shapes
//
///////////////////////////////////////////////////////////////////////////

#include "d3dx9.h"

#ifndef __D3DX9SHAPES_H__
#define __D3DX9SHAPES_H__

///////////////////////////////////////////////////////////////////////////
// Functions:
///////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


//-------------------------------------------------------------------------
// D3DXCreatePolygon: 
// ------------------
// Creates a mesh containing an n-sided polygon.  The polygon is centered
// at the origin.
//
// Parameters:
//
//  pDevice     The D3D device with which the mesh is going to be used.
//  Length      Length of each side.
//  Sides       Number of sides the polygon has.  (Must be >= 3)
//  ppMesh      The mesh object which will be created
//  ppAdjacency Returns a buffer containing adjacency info.  Can be NULL.
//-------------------------------------------------------------------------
HRESULT WINAPI 
    D3DXCreatePolygon(
        __in            LPDIRECT3DDEVICE9   pDevice,
                        FLOAT               Length, 
                        UINT                Sides, 
        __deref_out     LPD3DXMESH*         ppMesh,
        __deref_opt_out LPD3DXBUFFER*       ppAdjacency);


//-------------------------------------------------------------------------
// D3DXCreateBox: 
// --------------
// Creates a mesh containing an axis-aligned box.  The box is centered at
// the origin.
//
// Parameters:
//
//  pDevice     The D3D device with which the mesh is going to be used.
//  Width       Width of box (along X-axis)
//  Height      Height of box (along Y-axis)
//  Depth       Depth of box (along Z-axis)
//  ppMesh      The mesh object which will be created
//  ppAdjacency Returns a buffer containing adjacency info.  Can be NULL.
//-------------------------------------------------------------------------
HRESULT WINAPI 
    D3DXCreateBox(
        __in            LPDIRECT3DDEVICE9   pDevice, 
                        FLOAT               Width,
                        FLOAT               Height,
                        FLOAT               Depth,
        __deref_out     LPD3DXMESH*         ppMesh,
        __deref_opt_out LPD3DXBUFFER*       ppAdjacency);


//-------------------------------------------------------------------------
// D3DXCreateCylinder:
// -------------------
// Creates a mesh containing a cylinder.  The generated cylinder is
// centered at the origin, and its axis is aligned with the Z-axis.
//
// Parameters:
//
//  pDevice     The D3D device with which the mesh is going to be used.
//  Radius1     Radius at -Z end (should be >= 0.0f)
//  Radius2     Radius at +Z end (should be >= 0.0f)
//  Length      Length of cylinder (along Z-axis)
//  Slices      Number of slices about the main axis
//  Stacks      Number of stacks along the main axis
//  ppMesh      The mesh object which will be created
//  ppAdjacency Returns a buffer containing adjacency info.  Can be NULL.
//-------------------------------------------------------------------------
HRESULT WINAPI 
    D3DXCreateCylinder(
        __in            LPDIRECT3DDEVICE9   pDevice,
                        FLOAT               Radius1, 
                        FLOAT               Radius2, 
                        FLOAT               Length, 
                        UINT                Slices, 
                        UINT                Stacks,   
        __deref_out     LPD3DXMESH*         ppMesh,
        __deref_opt_out LPD3DXBUFFER*       ppAdjacency);


//-------------------------------------------------------------------------
// D3DXCreateSphere:
// -----------------
// Creates a mesh containing a sphere.  The sphere is centered at the
// origin.
//
// Parameters:
//
//  pDevice     The D3D device with which the mesh is going to be used.
//  Radius      Radius of the sphere (should be >= 0.0f)
//  Slices      Number of slices about the main axis
//  Stacks      Number of stacks along the main axis
//  ppMesh      The mesh object which will be created
//  ppAdjacency Returns a buffer containing adjacency info.  Can be NULL.
//-------------------------------------------------------------------------
HRESULT WINAPI
    D3DXCreateSphere(
        __in            LPDIRECT3DDEVICE9  pDevice, 
                        FLOAT              Radius, 
                        UINT               Slices, 
                        UINT               Stacks,
        __deref_out     LPD3DXMESH*        ppMesh,
        __deref_opt_out LPD3DXBUFFER*      ppAdjacency);


//-------------------------------------------------------------------------
// D3DXCreateTorus:
// ----------------
// Creates a mesh containing a torus.  The generated torus is centered at
// the origin, and its axis is aligned with the Z-axis.
//
// Parameters: 
//
//  pDevice     The D3D device with which the mesh is going to be used.
//  InnerRadius Inner radius of the torus (should be >= 0.0f)
//  OuterRadius Outer radius of the torue (should be >= 0.0f)
//  Sides       Number of sides in a cross-section (must be >= 3)
//  Rings       Number of rings making up the torus (must be >= 3)
//  ppMesh      The mesh object which will be created
//  ppAdjacency Returns a buffer containing adjacency info.  Can be NULL.
//-------------------------------------------------------------------------
HRESULT WINAPI
    D3DXCreateTorus(
        __in            LPDIRECT3DDEVICE9   pDevice,
                        FLOAT               InnerRadius,
                        FLOAT               OuterRadius, 
                        UINT                Sides,
                        UINT                Rings, 
        __deref_out     LPD3DXMESH*         ppMesh,
        __deref_opt_out LPD3DXBUFFER*       ppAdjacency);


//-------------------------------------------------------------------------
// D3DXCreateTeapot: 
// -----------------
// Creates a mesh containing a teapot.
//
// Parameters: 
//
//  pDevice     The D3D device with which the mesh is going to be used.
//  ppMesh      The mesh object which will be created
//  ppAdjacency Returns a buffer containing adjacency info.  Can be NULL.
//-------------------------------------------------------------------------
HRESULT WINAPI
    D3DXCreateTeapot(
        __in            LPDIRECT3DDEVICE9   pDevice,
        __deref_out     LPD3DXMESH*         ppMesh,
        __deref_opt_out LPD3DXBUFFER*       ppAdjacency);


#ifdef __cplusplus
}
#endif //__cplusplus    

#endif //__D3DX9SHAPES_H__

