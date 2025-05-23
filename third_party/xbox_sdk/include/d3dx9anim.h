//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) Microsoft Corporation.  All Rights Reserved.
//
//  File:       d3dx9anim.h
//  Content:    D3DX mesh types and functions
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __D3DX9ANIM_H__
#define __D3DX9ANIM_H__

// {A632D591-B584-4d03-BCCD-CBB5331F21AA}
DEFINE_GUID(IID_ID3DXAnimationSet, 
0xa632d591, 0xb584, 0x4d03, 0xbc, 0xcd, 0xcb, 0xb5, 0x33, 0x1f, 0x21, 0xaa);

// {73B6DDE3-7E45-4cc8-834F-B7DCBC04D10A}
DEFINE_GUID(IID_ID3DXKeyframedAnimationSet, 
0x73b6dde3, 0x7e45, 0x4cc8, 0x83, 0x4f, 0xb7, 0xdc, 0xbc, 0x4, 0xd1, 0xa);

// {7B7228FD-EA36-4c06-9DA6-E053D688E164}
DEFINE_GUID(IID_ID3DXCompressedAnimationSet, 
0x7b7228fd, 0xea36, 0x4c06, 0x9d, 0xa6, 0xe0, 0x53, 0xd6, 0x88, 0xe1, 0x64);

// {39F628C0-CD5B-41d6-8E9C-3BBBB66FDA57}
DEFINE_GUID(IID_ID3DXAnimationController, 
0x39f628c0, 0xcd5b, 0x41d6, 0x8e, 0x9c, 0x3b, 0xbb, 0xb6, 0x6f, 0xda, 0x57);


//----------------------------------------------------------------------------
// D3DXMESHDATATYPE:
// -----------------
// This enum defines the type of mesh data present in a MeshData structure.
//----------------------------------------------------------------------------
typedef enum _D3DXMESHDATATYPE {
    D3DXMESHTYPE_MESH      = 0x001,             // Normal ID3DXMesh data
    D3DXMESHTYPE_PMESH     = 0x002,             // Progressive Mesh - ID3DXPMesh
    D3DXMESHTYPE_PATCHMESH = 0x003,             // Patch Mesh - ID3DXPatchMesh

    D3DXMESHTYPE_FORCE_DWORD    = 0x7fffffff,   /* force 32-bit size enum */
} D3DXMESHDATATYPE;

//----------------------------------------------------------------------------
// D3DXMESHDATA:
// -------------
// This struct encapsulates a the mesh data that can be present in a mesh 
// container.  The supported mesh types are pMesh, pPMesh, pPatchMesh.
// The valid way to access this is determined by the Type enum.
//----------------------------------------------------------------------------
typedef struct _D3DXMESHDATA
{
    D3DXMESHDATATYPE Type;

    // current mesh data interface
    union
    {
        LPD3DXMESH              pMesh;
        LPD3DXPMESH             pPMesh;
        LPD3DXPATCHMESH         pPatchMesh;
    };
} D3DXMESHDATA, *LPD3DXMESHDATA;

//----------------------------------------------------------------------------
// D3DXMESHCONTAINER:
// ------------------
// This struct encapsulates a mesh object in a transformation frame
// hierarchy. The app can derive from this structure to add other app specific
// data to this.
//----------------------------------------------------------------------------
typedef struct _D3DXMESHCONTAINER
{
    LPSTR                   Name;

    D3DXMESHDATA            MeshData;

    LPD3DXMATERIAL          pMaterials;
    LPD3DXEFFECTINSTANCE    pEffects;
    DWORD                   NumMaterials;
    DWORD                  *pAdjacency;

    LPD3DXSKININFO          pSkinInfo;

    struct _D3DXMESHCONTAINER *pNextMeshContainer;
} D3DXMESHCONTAINER, *LPD3DXMESHCONTAINER;

//----------------------------------------------------------------------------
// D3DXFRAME:
// ----------
// This struct is the encapsulates a transform frame in a transformation frame
// hierarchy. The app can derive from this structure to add other app specific
// data to this
//----------------------------------------------------------------------------
typedef struct _D3DXFRAME
{
    LPSTR                   Name;
    D3DXMATRIX              TransformationMatrix;

    LPD3DXMESHCONTAINER     pMeshContainer;

    struct _D3DXFRAME       *pFrameSibling;
    struct _D3DXFRAME       *pFrameFirstChild;
} D3DXFRAME, *LPD3DXFRAME;


//----------------------------------------------------------------------------
// ID3DXAllocateHierarchy:
// -----------------------
// This interface is implemented by the application to allocate/free frame and
// mesh container objects. Methods on this are called during loading and
// destroying frame hierarchies
//----------------------------------------------------------------------------
typedef interface ID3DXAllocateHierarchy ID3DXAllocateHierarchy;
typedef interface ID3DXAllocateHierarchy *LPD3DXALLOCATEHIERARCHY;

#undef INTERFACE
#define INTERFACE ID3DXAllocateHierarchy

DECLARE_INTERFACE(ID3DXAllocateHierarchy)
{
    // ID3DXAllocateHierarchy

	//------------------------------------------------------------------------
	// CreateFrame:
	// ------------
	// Requests allocation of a frame object.
	//
	// Parameters:
	//  Name
	//		Name of the frame to be created
	//	ppNewFrame
	//		Returns the created frame object
	//
	//------------------------------------------------------------------------
    STDMETHOD(CreateFrame)(THIS_ __in_z LPCSTR Name, 
                            __deref_out LPD3DXFRAME *ppNewFrame) PURE;

	//------------------------------------------------------------------------
	// CreateMeshContainer:
	// --------------------
	// Requests allocation of a mesh container object.
	//
	// Parameters:
	//  Name
	//		Name of the mesh
	//	pMesh
	//		Pointer to the mesh object if basic polygon data found
	//	pPMesh
	//		Pointer to the progressive mesh object if progressive mesh data found
	//	pPatchMesh
	//		Pointer to the patch mesh object if patch data found
	//	pMaterials
	//		Array of materials used in the mesh
	//	pEffectInstances
	//		Array of effect instances used in the mesh
	//	NumMaterials
	//		Num elements in the pMaterials array
	//	pAdjacency
	//		Adjacency array for the mesh
	//	pSkinInfo
	//		Pointer to the skininfo object if the mesh is skinned
	//	pBoneNames
	//		Array of names, one for each bone in the skinned mesh. 
	//		The numberof bones can be found from the pSkinMesh object
	//	pBoneOffsetMatrices
	//		Array of matrices, one for each bone in the skinned mesh.
	//
	//------------------------------------------------------------------------
    STDMETHOD(CreateMeshContainer)(THIS_ 
        __in_z                        LPCSTR Name, 
        __in                          CONST D3DXMESHDATA *pMeshData, 
        __in_ecount_opt(NumMaterials) CONST D3DXMATERIAL *pMaterials, 
        __in_opt                      CONST D3DXEFFECTINSTANCE *pEffectInstances, 
                                      DWORD NumMaterials, 
        __in_opt                      CONST DWORD *pAdjacency, 
        __in_opt                      LPD3DXSKININFO pSkinInfo, 
        __deref_out                   LPD3DXMESHCONTAINER *ppNewMeshContainer) PURE;

	//------------------------------------------------------------------------
	// DestroyFrame:
	// -------------
	// Requests de-allocation of a frame object.
	//
	// Parameters:
	//  pFrameToFree
	//		Pointer to the frame to be de-allocated
	//
	//------------------------------------------------------------------------
    STDMETHOD(DestroyFrame)(THIS_ __in LPD3DXFRAME pFrameToFree) PURE;

	//------------------------------------------------------------------------
	// DestroyMeshContainer:
	// ---------------------
	// Requests de-allocation of a mesh container object.
	//
	// Parameters:
	//  pMeshContainerToFree
	//		Pointer to the mesh container object to be de-allocated
	//
	//------------------------------------------------------------------------
    STDMETHOD(DestroyMeshContainer)(THIS_ __in LPD3DXMESHCONTAINER pMeshContainerToFree) PURE; 
};

//----------------------------------------------------------------------------
// ID3DXLoadUserData:
// ------------------
// This interface is implemented by the application to load user data in a .X file
// When user data is found, these callbacks will be used to allow the application
// to load the data.
//----------------------------------------------------------------------------
typedef interface ID3DXLoadUserData ID3DXLoadUserData;
typedef interface ID3DXLoadUserData *LPD3DXLOADUSERDATA;

#undef INTERFACE
#define INTERFACE ID3DXLoadUserData

DECLARE_INTERFACE(ID3DXLoadUserData)
{
    STDMETHOD(LoadTopLevelData)(__in LPDIRECTXFILEDATA pXofChildData) PURE;
                            
    STDMETHOD(LoadFrameChildData)(__in LPD3DXFRAME pFrame, 
                            __in LPDIRECTXFILEDATA pXofChildData) PURE;
                            
    STDMETHOD(LoadMeshChildData)(__in LPD3DXMESHCONTAINER pMeshContainer, 
                            __in LPDIRECTXFILEDATA pXofChildData) PURE;                            
};

//----------------------------------------------------------------------------
// ID3DXSaveUserData:
// ------------------
// This interface is implemented by the application to save user data in a .X file
// The callbacks are called for all data saved.  The user can then add any
// child data objects to the object provided to the callback.
//----------------------------------------------------------------------------
typedef interface ID3DXSaveUserData ID3DXSaveUserData;
typedef interface ID3DXSaveUserData *LPD3DXSAVEUSERDATA;

#undef INTERFACE
#define INTERFACE ID3DXSaveUserData

DECLARE_INTERFACE(ID3DXSaveUserData)
{
    STDMETHOD(AddFrameChildData)(__in CONST D3DXFRAME *pFrame, 
                            __in LPDIRECTXFILESAVEOBJECT pXofSave, 
                            __in LPDIRECTXFILEDATA pXofFrameData) PURE;
                            
    STDMETHOD(AddMeshChildData)(__in CONST D3DXMESHCONTAINER *pMeshContainer, 
                            __in LPDIRECTXFILESAVEOBJECT pXofSave, 
                            __in LPDIRECTXFILEDATA pXofMeshData) PURE;
                            
    // NOTE: this is called once per Save.  All top level objects should be added using the 
    //    provided interface.  One call adds objects before the frame hierarchy, the other after
    STDMETHOD(AddTopLevelDataObjectsPre)(__in LPDIRECTXFILESAVEOBJECT pXofSave) PURE; 
    STDMETHOD(AddTopLevelDataObjectsPost)(__in LPDIRECTXFILESAVEOBJECT pXofSave) PURE;                             

    // callbacks for the user to register and then save templates to the XFile
    STDMETHOD(RegisterTemplates)(__in LPDIRECTXFILE pXFileApi) PURE;                             
    STDMETHOD(SaveTemplates)(__in LPDIRECTXFILESAVEOBJECT pXofSave) PURE;                             
};


//----------------------------------------------------------------------------
// D3DXCALLBACK_SEARCH_FLAGS:
// --------------------------
// Flags that can be passed into ID3DXAnimationSet::GetCallback. 
//----------------------------------------------------------------------------
typedef enum _D3DXCALLBACK_SEARCH_FLAGS
{
    D3DXCALLBACK_SEARCH_EXCLUDING_INITIAL_POSITION = 0x01,  // exclude callbacks at the initial position from the search
    D3DXCALLBACK_SEARCH_BEHIND_INITIAL_POSITION    = 0x02,  // reverse the callback search direction

    D3DXCALLBACK_SEARCH_FORCE_DWORD                = 0x7fffffff,
} D3DXCALLBACK_SEARCH_FLAGS;

//----------------------------------------------------------------------------
// ID3DXAnimationSet:
// ------------------
// This interface implements an animation set.
//----------------------------------------------------------------------------
typedef interface ID3DXAnimationSet ID3DXAnimationSet;
typedef interface ID3DXAnimationSet *LPD3DXANIMATIONSET;

#undef INTERFACE
#define INTERFACE ID3DXAnimationSet

DECLARE_INTERFACE_(ID3DXAnimationSet, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, __deref_out LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // Name
    STDMETHOD_(__out_z LPCSTR, GetName)(THIS) PURE;

    // Period
    STDMETHOD_(DOUBLE, GetPeriod)(THIS) PURE;
    STDMETHOD_(DOUBLE, GetPeriodicPosition)(THIS_ DOUBLE Position) PURE;    // Maps position into animation period

    // Animation names
    STDMETHOD_(UINT, GetNumAnimations)(THIS) PURE;
    STDMETHOD(GetAnimationNameByIndex)(THIS_ UINT Index, __deref_out_z LPCSTR *ppName) PURE;
    STDMETHOD(GetAnimationIndexByName)(THIS_ __in_z LPCSTR pName, __out UINT *pIndex) PURE;

    // SRT
    STDMETHOD(GetSRT)(THIS_ 
              DOUBLE PeriodicPosition,            // Position mapped to period (use GetPeriodicPosition)
              UINT Animation,                     // Animation index
        __out D3DXVECTOR3 *pScale,                // Returns the scale
        __out D3DXQUATERNION *pRotation,          // Returns the rotation as a quaternion
        __out D3DXVECTOR3 *pTranslation) PURE;    // Returns the translation

    // Callbacks
    STDMETHOD(GetCallback)(THIS_ 
                        DOUBLE Position,                    // Position from which to find callbacks
                        DWORD Flags,                        // Callback search flags
        __out_opt       DOUBLE *pCallbackPosition,          // Returns the position of the callback
        __deref_opt_out LPVOID *ppCallbackData) PURE;       // Returns the callback data pointer
};


//----------------------------------------------------------------------------
// D3DXPLAYBACK_TYPE:
// ------------------
// This enum defines the type of animation set loop modes.
//----------------------------------------------------------------------------
typedef enum _D3DXPLAYBACK_TYPE
{
    D3DXPLAY_LOOP          = 0,
    D3DXPLAY_ONCE          = 1,
    D3DXPLAY_PINGPONG      = 2,

    D3DXPLAY_FORCE_DWORD   = 0x7fffffff, /* force 32-bit size enum */
} D3DXPLAYBACK_TYPE;


//----------------------------------------------------------------------------
// D3DXKEY_VECTOR3:
// ----------------
// This structure describes a vector key for use in keyframe animation.
// It specifies a vector Value at a given Time. This is used for scale and
// translation keys.
//----------------------------------------------------------------------------
typedef struct _D3DXKEY_VECTOR3
{
    FLOAT Time;
    D3DXVECTOR3 Value;
} D3DXKEY_VECTOR3, *LPD3DXKEY_VECTOR3;


//----------------------------------------------------------------------------
// D3DXKEY_QUATERNION:
// -------------------
// This structure describes a quaternion key for use in keyframe animation.
// It specifies a quaternion Value at a given Time. This is used for rotation
// keys.
//----------------------------------------------------------------------------
typedef struct _D3DXKEY_QUATERNION
{
    FLOAT Time;
    D3DXQUATERNION Value;
} D3DXKEY_QUATERNION, *LPD3DXKEY_QUATERNION;


//----------------------------------------------------------------------------
// D3DXKEY_CALLBACK:
// -----------------
// This structure describes an callback key for use in keyframe animation.
// It specifies a pointer to user data at a given Time. 
//----------------------------------------------------------------------------
typedef struct _D3DXKEY_CALLBACK
{
    FLOAT Time;
    LPVOID pCallbackData;
} D3DXKEY_CALLBACK, *LPD3DXKEY_CALLBACK;


//----------------------------------------------------------------------------
// D3DXCOMPRESSION_FLAGS:
// ----------------------
// Flags that can be passed into ID3DXKeyframedAnimationSet::Compress. 
//----------------------------------------------------------------------------
typedef enum _D3DXCOMPRESSION_FLAGS
{
    D3DXCOMPRESS_DEFAULT     = 0x00,

    D3DXCOMPRESS_FORCE_DWORD = 0x7fffffff,
} D3DXCOMPRESSION_FLAGS;


//----------------------------------------------------------------------------
// ID3DXKeyframedAnimationSet:
// ---------------------------
// This interface implements a compressable keyframed animation set.
//----------------------------------------------------------------------------
typedef interface ID3DXKeyframedAnimationSet ID3DXKeyframedAnimationSet;
typedef interface ID3DXKeyframedAnimationSet *LPD3DXKEYFRAMEDANIMATIONSET;

#undef INTERFACE
#define INTERFACE ID3DXKeyframedAnimationSet

DECLARE_INTERFACE_(ID3DXKeyframedAnimationSet, ID3DXAnimationSet)
{
    // ID3DXAnimationSet
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, __deref_out LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // Name
    STDMETHOD_(__out_z LPCSTR, GetName)(THIS) PURE;

    // Period
    STDMETHOD_(DOUBLE, GetPeriod)(THIS) PURE;
    STDMETHOD_(DOUBLE, GetPeriodicPosition)(THIS_ DOUBLE Position) PURE;    // Maps position into animation period

    // Animation names
    STDMETHOD_(UINT, GetNumAnimations)(THIS) PURE;
    STDMETHOD(GetAnimationNameByIndex)(THIS_ UINT Index, __deref_out_z LPCSTR *ppName) PURE;
    STDMETHOD(GetAnimationIndexByName)(THIS_ __in_z LPCSTR pName, __out UINT *pIndex) PURE;

    // SRT
    STDMETHOD(GetSRT)(THIS_ 
              DOUBLE PeriodicPosition,            // Position mapped to period (use GetPeriodicPosition)
              UINT Animation,                     // Animation index
        __out D3DXVECTOR3 *pScale,                // Returns the scale
        __out D3DXQUATERNION *pRotation,          // Returns the rotation as a quaternion
        __out D3DXVECTOR3 *pTranslation) PURE;    // Returns the translation

    // Callbacks
    STDMETHOD(GetCallback)(THIS_ 
                        DOUBLE Position,                    // Position from which to find callbacks
                        DWORD Flags,                        // Callback search flags
        __out_opt       DOUBLE *pCallbackPosition,          // Returns the position of the callback
        __deref_opt_out LPVOID *ppCallbackData) PURE;       // Returns the callback data pointer

    // Playback
    STDMETHOD_(D3DXPLAYBACK_TYPE, GetPlaybackType)(THIS) PURE;
    STDMETHOD_(DOUBLE, GetSourceTicksPerSecond)(THIS) PURE;

    // Scale keys
    STDMETHOD_(UINT, GetNumScaleKeys)(THIS_ UINT Animation) PURE;
    STDMETHOD(GetScaleKeys)(THIS_ UINT Animation, __out LPD3DXKEY_VECTOR3 pScaleKeys) PURE;

    // Rotation keys
    STDMETHOD_(UINT, GetNumRotationKeys)(THIS_ UINT Animation) PURE;
    STDMETHOD(GetRotationKeys)(THIS_ UINT Animation, __out LPD3DXKEY_QUATERNION pRotationKeys) PURE;

    // Translation keys
    STDMETHOD_(UINT, GetNumTranslationKeys)(THIS_ UINT Animation) PURE;
    STDMETHOD(GetTranslationKeys)(THIS_ UINT Animation, __out LPD3DXKEY_VECTOR3 pTranslationKeys) PURE;

    // Callback keys
    STDMETHOD_(UINT, GetNumCallbackKeys)(THIS) PURE;
    STDMETHOD(GetCallbackKeys)(THIS_ __out LPD3DXKEY_CALLBACK pCallbackKeys) PURE;

    // One-time animaton SRT keyframe registration
    STDMETHOD(RegisterAnimationSRTKeys)(THIS_ 
        __in_z                              LPCSTR pName,                                   // Animation name
                                            UINT NumScaleKeys,                              // Number of scale keys
                                            UINT NumRotationKeys,                           // Number of rotation keys
                                            UINT NumTranslationKeys,                        // Number of translation keys
        __in_ecount_opt(NumScaleKeys)       CONST D3DXKEY_VECTOR3 *pScaleKeys,              // Array of scale keys
        __in_ecount_opt(NumRotationKeys)    CONST D3DXKEY_QUATERNION *pRotationKeys,        // Array of rotation keys
        __in_ecount_opt(NumTranslationKeys) CONST D3DXKEY_VECTOR3 *pTranslationKeys) PURE;  // Array of translation keys

    // Compression
    STDMETHOD(Compress)(THIS_ 
                    DWORD Flags,                            // Compression flags (use D3DXCOMPRESS_STRONG for better results)
                    FLOAT Lossiness,                        // Compression loss ratio in the [0, 1] range
        __in_opt    LPD3DXFRAME pHierarchy,                 // Frame hierarchy (optional)
        __deref_out LPD3DXBUFFER *ppCompressedData) PURE;   // Returns the compressed animation set
};


//----------------------------------------------------------------------------
// ID3DXCompressedAnimationSet:
// ----------------------------
// This interface implements a compressed keyframed animation set.
//----------------------------------------------------------------------------
typedef interface ID3DXCompressedAnimationSet ID3DXCompressedAnimationSet;
typedef interface ID3DXCompressedAnimationSet *LPD3DXCOMPRESSEDANIMATIONSET;

#undef INTERFACE
#define INTERFACE ID3DXCompressedAnimationSet

DECLARE_INTERFACE_(ID3DXCompressedAnimationSet, ID3DXAnimationSet)
{
    // ID3DXAnimationSet
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, __deref_out LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // Name
    STDMETHOD_(__out_z LPCSTR, GetName)(THIS) PURE;

    // Period
    STDMETHOD_(DOUBLE, GetPeriod)(THIS) PURE;
    STDMETHOD_(DOUBLE, GetPeriodicPosition)(THIS_ DOUBLE Position) PURE;    // Maps position into animation period

    // Animation names
    STDMETHOD_(UINT, GetNumAnimations)(THIS) PURE;
    STDMETHOD(GetAnimationNameByIndex)(THIS_ UINT Index, __deref_out_z LPCSTR *ppName) PURE;
    STDMETHOD(GetAnimationIndexByName)(THIS_ __in_z LPCSTR pName, __out UINT *pIndex) PURE;

    // SRT
    STDMETHOD(GetSRT)(THIS_ 
              DOUBLE PeriodicPosition,            // Position mapped to period (use GetPeriodicPosition)
              UINT Animation,                     // Animation index
        __out D3DXVECTOR3 *pScale,                // Returns the scale
        __out D3DXQUATERNION *pRotation,          // Returns the rotation as a quaternion
        __out D3DXVECTOR3 *pTranslation) PURE;    // Returns the translation

    // Callbacks
    STDMETHOD(GetCallback)(THIS_ 
                        DOUBLE Position,                    // Position from which to find callbacks
                        DWORD Flags,                        // Callback search flags
        __out_opt       DOUBLE *pCallbackPosition,          // Returns the position of the callback
        __deref_opt_out LPVOID *ppCallbackData) PURE;       // Returns the callback data pointer

    // Playback
    STDMETHOD_(D3DXPLAYBACK_TYPE, GetPlaybackType)(THIS) PURE;
    STDMETHOD_(DOUBLE, GetSourceTicksPerSecond)(THIS) PURE;

    // Scale keys
    STDMETHOD(GetCompressedData)(THIS_ __deref_out LPD3DXBUFFER *ppCompressedData) PURE;

    // Callback keys
    STDMETHOD_(UINT, GetNumCallbackKeys)(THIS) PURE;
    STDMETHOD(GetCallbackKeys)(THIS_ __out LPD3DXKEY_CALLBACK pCallbackKeys) PURE;
};


//----------------------------------------------------------------------------
// D3DXPRIORITY_TYPE:
// ------------------
// This enum defines the type of priority group that a track can be assigned to.
//----------------------------------------------------------------------------
typedef enum _D3DXPRIORITY_TYPE {
    D3DXPRIORITY_LOW         = 0,           // This track should be blended with all low priority tracks before mixed with the high priority result
    D3DXPRIORITY_HIGH        = 1,           // This track should be blended with all high priority tracks before mixed with the low priority result

    D3DXPRIORITY_FORCE_DWORD = 0x7fffffff,  /* force 32-bit size enum */
} D3DXPRIORITY_TYPE;

//----------------------------------------------------------------------------
// D3DXTRACK_DESC:
// ---------------
// This structure describes the mixing information of an animation track. 
// The mixing information consists of the current position, speed, and blending 
// weight for the track.  The Flags field also specifies whether the track is 
// low or high priority.  Tracks with the same priority are blended together
// and then the two resulting values are blended using the priority blend factor.
// A track also has an animation set (stored separately) associated with it.  
//----------------------------------------------------------------------------
typedef struct _D3DXTRACK_DESC
{
    D3DXPRIORITY_TYPE   Priority;
    FLOAT               Weight;
    FLOAT               Speed;
    DOUBLE              Position;
    BOOL                Enable;
} D3DXTRACK_DESC, *LPD3DXTRACK_DESC;

//----------------------------------------------------------------------------
// D3DXEVENT_TYPE:
// ---------------
// This enum defines the type of events keyable via the animation controller.
//----------------------------------------------------------------------------
typedef enum _D3DXEVENT_TYPE
{
    D3DXEVENT_TRACKSPEED    = 0,
    D3DXEVENT_TRACKWEIGHT   = 1,
    D3DXEVENT_TRACKPOSITION = 2,
    D3DXEVENT_TRACKENABLE   = 3,
    D3DXEVENT_PRIORITYBLEND = 4,

    D3DXEVENT_FORCE_DWORD   = 0x7fffffff, /* force 32-bit size enum */
} D3DXEVENT_TYPE;

//----------------------------------------------------------------------------
// D3DXTRANSITION_TYPE:
// --------------------
// This enum defines the type of transtion performed on a event that 
// transitions from one value to another.
//----------------------------------------------------------------------------
typedef enum _D3DXTRANSITION_TYPE {
    D3DXTRANSITION_LINEAR        = 0x000,     // Linear transition from one value to the next
    D3DXTRANSITION_EASEINEASEOUT = 0x001,     // Ease-In Ease-Out spline transtion from one value to the next

    D3DXTRANSITION_FORCE_DWORD   = 0x7fffffff, /* force 32-bit size enum */
} D3DXTRANSITION_TYPE;

//----------------------------------------------------------------------------
// D3DXEVENT_DESC:
// ---------------
// This structure describes a animation controller event.
// It gives the event's type, track (if the event is a track event), global 
// start time, duration, transition method, and target value.
//----------------------------------------------------------------------------
typedef struct _D3DXEVENT_DESC
{
    D3DXEVENT_TYPE      Type;
    UINT                Track;
    DOUBLE              StartTime;
    DOUBLE              Duration;
    D3DXTRANSITION_TYPE Transition;
    union
    {
        FLOAT           Weight;
        FLOAT           Speed;
        DOUBLE          Position;
        BOOL            Enable;
    };
} D3DXEVENT_DESC, *LPD3DXEVENT_DESC;

//----------------------------------------------------------------------------
// D3DXEVENTHANDLE:
// ----------------
// Handle values used to efficiently reference animation controller events.
//----------------------------------------------------------------------------
typedef DWORD D3DXEVENTHANDLE;
typedef D3DXEVENTHANDLE *LPD3DXEVENTHANDLE;


//----------------------------------------------------------------------------
// ID3DXAnimationCallbackHandler:
// ------------------------------
// This interface is intended to be implemented by the application, and can
// be used to handle callbacks in animation sets generated when 
// ID3DXAnimationController::AdvanceTime() is called.  
//----------------------------------------------------------------------------
typedef interface ID3DXAnimationCallbackHandler ID3DXAnimationCallbackHandler;
typedef interface ID3DXAnimationCallbackHandler *LPD3DXANIMATIONCALLBACKHANDLER;

#undef INTERFACE
#define INTERFACE ID3DXAnimationCallbackHandler

DECLARE_INTERFACE(ID3DXAnimationCallbackHandler)
{
    //----------------------------------------------------------------------------
    // ID3DXAnimationCallbackHandler::HandleCallback:
    // ----------------------------------------------
    // This method gets called when a callback occurs for an animation set in one
    // of the tracks during the ID3DXAnimationController::AdvanceTime() call.  
    //
    // Parameters:
    //  Track
    //      Index of the track on which the callback occured.
    //  pCallbackData
    //      Pointer to user owned callback data.
    //
    //----------------------------------------------------------------------------
    STDMETHOD(HandleCallback)(THIS_ UINT Track, __in LPVOID pCallbackData) PURE; 
};


//----------------------------------------------------------------------------
// ID3DXAnimationController:
// -------------------------
// This interface implements the main animation functionality. It connects
// animation sets with the transform frames that are being animated. Allows
// mixing multiple animations for blended animations or for transistions
// It adds also has methods to modify blending parameters over time to 
// enable smooth transistions and other effects.
//----------------------------------------------------------------------------
typedef interface ID3DXAnimationController ID3DXAnimationController;
typedef interface ID3DXAnimationController *LPD3DXANIMATIONCONTROLLER;

#undef INTERFACE
#define INTERFACE ID3DXAnimationController

DECLARE_INTERFACE_(ID3DXAnimationController, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, __deref_out LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // Max sizes
    STDMETHOD_(UINT, GetMaxNumAnimationOutputs)(THIS) PURE;
    STDMETHOD_(UINT, GetMaxNumAnimationSets)(THIS) PURE;
    STDMETHOD_(UINT, GetMaxNumTracks)(THIS) PURE;
    STDMETHOD_(UINT, GetMaxNumEvents)(THIS) PURE;

    // Animation output registration
    STDMETHOD(RegisterAnimationOutput)(THIS_ 
        __in_z   LPCSTR pName, 
        __in_opt D3DXMATRIX *pMatrix, 
        __in_opt D3DXVECTOR3 *pScale, 
        __in_opt D3DXQUATERNION *pRotation, 
        __in_opt D3DXVECTOR3 *pTranslation) PURE;

    // Animation set registration
    STDMETHOD(RegisterAnimationSet)(THIS_ __in LPD3DXANIMATIONSET pAnimSet) PURE;
    STDMETHOD(UnregisterAnimationSet)(THIS_ __in LPD3DXANIMATIONSET pAnimSet) PURE;

    STDMETHOD_(UINT, GetNumAnimationSets)(THIS) PURE;
    STDMETHOD(GetAnimationSet)(THIS_ UINT Index, __deref_out LPD3DXANIMATIONSET *ppAnimationSet) PURE;

    // Global time
    STDMETHOD(AdvanceTime)(THIS_ DOUBLE TimeDelta, __in LPD3DXANIMATIONCALLBACKHANDLER pCallbackHandler) PURE;
    STDMETHOD(ResetTime)(THIS) PURE;
    STDMETHOD_(DOUBLE, GetTime)(THIS) PURE;

    // Tracks
    STDMETHOD(SetTrackAnimationSet)(THIS_ UINT Track, __in LPD3DXANIMATIONSET pAnimSet) PURE;
    STDMETHOD(GetTrackAnimationSet)(THIS_ UINT Track, __deref_out LPD3DXANIMATIONSET *ppAnimSet) PURE;

    STDMETHOD(SetTrackPriority)(THIS_ UINT Track, D3DXPRIORITY_TYPE Priority) PURE;

    STDMETHOD(SetTrackSpeed)(THIS_ UINT Track, FLOAT Speed) PURE;
    STDMETHOD(SetTrackWeight)(THIS_ UINT Track, FLOAT Weight) PURE;
    STDMETHOD(SetTrackPosition)(THIS_ UINT Track, DOUBLE Position) PURE;
    STDMETHOD(SetTrackEnable)(THIS_ UINT Track, BOOL Enable) PURE;

    STDMETHOD(SetTrackDesc)(THIS_ UINT Track, __in LPD3DXTRACK_DESC pDesc) PURE;
    STDMETHOD(GetTrackDesc)(THIS_ UINT Track, __out LPD3DXTRACK_DESC pDesc) PURE;

    // Priority blending
    STDMETHOD(SetPriorityBlend)(THIS_ FLOAT BlendWeight) PURE;
    STDMETHOD_(FLOAT, GetPriorityBlend)(THIS) PURE;

    // Event keying
    STDMETHOD_(__out D3DXEVENTHANDLE, KeyTrackSpeed)(THIS_ UINT Track, FLOAT NewSpeed, DOUBLE StartTime, DOUBLE Duration, D3DXTRANSITION_TYPE Transition) PURE;
    STDMETHOD_(__out D3DXEVENTHANDLE, KeyTrackWeight)(THIS_ UINT Track, FLOAT NewWeight, DOUBLE StartTime, DOUBLE Duration, D3DXTRANSITION_TYPE Transition) PURE;
    STDMETHOD_(__out D3DXEVENTHANDLE, KeyTrackPosition)(THIS_ UINT Track, DOUBLE NewPosition, DOUBLE StartTime) PURE;
    STDMETHOD_(__out D3DXEVENTHANDLE, KeyTrackEnable)(THIS_ UINT Track, BOOL NewEnable, DOUBLE StartTime) PURE;

    STDMETHOD_(__out D3DXEVENTHANDLE, KeyPriorityBlend)(THIS_ FLOAT NewBlendWeight, DOUBLE StartTime, DOUBLE Duration, D3DXTRANSITION_TYPE Transition) PURE;

    // Event unkeying
    STDMETHOD(UnkeyEvent)(THIS_ __in D3DXEVENTHANDLE hEvent) PURE;

    STDMETHOD(UnkeyAllTrackEvents)(THIS_ UINT Track) PURE;
    STDMETHOD(UnkeyAllPriorityBlends)(THIS) PURE;

    // Event enumeration
    STDMETHOD_(__out D3DXEVENTHANDLE, GetCurrentTrackEvent)(THIS_ UINT Track, D3DXEVENT_TYPE EventType) PURE;
    STDMETHOD_(__out D3DXEVENTHANDLE, GetCurrentPriorityBlend)(THIS) PURE;

    STDMETHOD_(__out D3DXEVENTHANDLE, GetUpcomingTrackEvent)(THIS_ UINT Track, __in D3DXEVENTHANDLE hEvent) PURE;
    STDMETHOD_(__out D3DXEVENTHANDLE, GetUpcomingPriorityBlend)(THIS_ __in D3DXEVENTHANDLE hEvent) PURE;

    STDMETHOD(ValidateEvent)(THIS_ __in D3DXEVENTHANDLE hEvent) PURE;

    STDMETHOD(GetEventDesc)(THIS_ __in D3DXEVENTHANDLE hEvent, __out LPD3DXEVENT_DESC pDesc) PURE;

    // Cloning
    STDMETHOD(CloneAnimationController)(THIS_ 
        UINT MaxNumAnimationOutputs, 
        UINT MaxNumAnimationSets, 
        UINT MaxNumTracks, 
        UINT MaxNumEvents, 
        __deref_out LPD3DXANIMATIONCONTROLLER *ppAnimController) PURE;
};

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


//----------------------------------------------------------------------------
// D3DXLoadMeshHierarchyFromX:
// ---------------------------
// Loads the first frame hierarchy in a .X file.
//
// Parameters:
//  Filename
//      Name of the .X file
//  MeshOptions
//      Mesh creation options for meshes in the file (see d3dx9mesh.h)
//  pD3DDevice
//      D3D9 device on which meshes in the file are created in
//  pAlloc
//      Allocation interface used to allocate nodes of the frame hierarchy
//  pUserDataLoader
//      Application provided interface to allow loading of user data
//  ppFrameHierarchy
//      Returns root node pointer of the loaded frame hierarchy
//  ppAnimController
//      Returns pointer to an animation controller corresponding to animation
//		in the .X file. This is created with default max tracks and events
//
//----------------------------------------------------------------------------
HRESULT WINAPI 
D3DXLoadMeshHierarchyFromXA
    (
    __in_z          LPCSTR Filename,
                    DWORD MeshOptions,
    __in            LPDIRECT3DDEVICE9 pD3DDevice,
    __in            LPD3DXALLOCATEHIERARCHY pAlloc,
    __in_opt        LPD3DXLOADUSERDATA pUserDataLoader, 
    __deref_out     LPD3DXFRAME *ppFrameHierarchy,
    __deref_opt_out LPD3DXANIMATIONCONTROLLER *ppAnimController
    );

HRESULT WINAPI 
D3DXLoadMeshHierarchyFromXW
    (
    __in_z          LPCWSTR Filename,
                    DWORD MeshOptions,
    __in            LPDIRECT3DDEVICE9 pD3DDevice,
    __in            LPD3DXALLOCATEHIERARCHY pAlloc,
    __in_opt        LPD3DXLOADUSERDATA pUserDataLoader, 
    __deref_out     LPD3DXFRAME *ppFrameHierarchy,
    __deref_opt_out LPD3DXANIMATIONCONTROLLER *ppAnimController
    );

#ifdef UNICODE
#define D3DXLoadMeshHierarchyFromX D3DXLoadMeshHierarchyFromXW
#else
#define D3DXLoadMeshHierarchyFromX D3DXLoadMeshHierarchyFromXA
#endif

HRESULT WINAPI 
D3DXLoadMeshHierarchyFromXInMemory
    (
    __in_bcount(SizeOfMemory) LPCVOID Memory,
                              DWORD SizeOfMemory,
                              DWORD MeshOptions,
    __in                      LPDIRECT3DDEVICE9 pD3DDevice,
    __in                      LPD3DXALLOCATEHIERARCHY pAlloc,
    __in_opt                  LPD3DXLOADUSERDATA pUserDataLoader, 
    __deref_out               LPD3DXFRAME *ppFrameHierarchy,
    __deref_opt_out           LPD3DXANIMATIONCONTROLLER *ppAnimController
    );

//----------------------------------------------------------------------------
// D3DXSaveMeshHierarchyToFile:
// ----------------------------
// Creates a .X file and saves the mesh hierarchy and corresponding animations
// in it
//
// Parameters:
//  Filename
//      Name of the .X file
//  XFormat
//      Format of the .X file (text or binary, compressed or not, etc)
//  pFrameRoot
//      Root node of the hierarchy to be saved
//  pAnimController
//      The animation controller whose animation sets are to be stored
//  pUserDataSaver
//      Application provided interface to allow adding of user data to
//        data objects saved to .X file
//
//----------------------------------------------------------------------------
HRESULT WINAPI 
D3DXSaveMeshHierarchyToFileA
    (
    __in_z   LPCSTR Filename,
             DWORD XFormat,
    __in     CONST D3DXFRAME *pFrameRoot, 
    __in_opt LPD3DXANIMATIONCONTROLLER pAnimcontroller,
    __in_opt LPD3DXSAVEUSERDATA pUserDataSaver
    );

HRESULT WINAPI 
D3DXSaveMeshHierarchyToFileW
    (
    __in_z   LPCWSTR Filename,
             DWORD XFormat,
    __in     CONST D3DXFRAME *pFrameRoot, 
    __in_opt LPD3DXANIMATIONCONTROLLER pAnimController,
    __in_opt LPD3DXSAVEUSERDATA pUserDataSaver
    );

#ifdef UNICODE
#define D3DXSaveMeshHierarchyToFile D3DXSaveMeshHierarchyToFileW
#else
#define D3DXSaveMeshHierarchyToFile D3DXSaveMeshHierarchyToFileA
#endif

//----------------------------------------------------------------------------
// D3DXFrameDestroy:
// -----------------
// Destroys the subtree of frames under the root, including the root
//
// Parameters:
//	pFrameRoot
//		Pointer to the root node
//  pAlloc
//      Allocation interface used to de-allocate nodes of the frame hierarchy
//
//----------------------------------------------------------------------------
HRESULT WINAPI
D3DXFrameDestroy
    (
    __inout LPD3DXFRAME pFrameRoot,
    __in    LPD3DXALLOCATEHIERARCHY pAlloc
    );

//----------------------------------------------------------------------------
// D3DXFrameAppendChild:
// ---------------------
// Add a child frame to a frame
//
// Parameters:
//	pFrameParent
//		Pointer to the parent node
//  pFrameChild
//      Pointer to the child node
//
//----------------------------------------------------------------------------
HRESULT WINAPI 
D3DXFrameAppendChild
    (
    __inout LPD3DXFRAME pFrameParent,
    __in    CONST D3DXFRAME *pFrameChild
    );

//----------------------------------------------------------------------------
// D3DXFrameFind:
// --------------
// Finds a frame with the given name.  Returns NULL if no frame found.
//
// Parameters:
//	pFrameRoot
//		Pointer to the root node
//  Name
//      Name of frame to find
//
//----------------------------------------------------------------------------
LPD3DXFRAME WINAPI 
D3DXFrameFind
    (
    __in   CONST D3DXFRAME *pFrameRoot,
    __in_z LPCSTR Name
    );

//----------------------------------------------------------------------------
// D3DXFrameRegisterNamedMatrices:
// -------------------------------
// Finds all frames that have non-null names and registers each of those frame
// matrices to the given animation controller
//
// Parameters:
//	pFrameRoot
//		Pointer to the root node
//	pAnimController
//		Pointer to the animation controller where the matrices are registered
//
//----------------------------------------------------------------------------
HRESULT WINAPI
D3DXFrameRegisterNamedMatrices
    (
    __in    LPD3DXFRAME pFrameRoot,
    __inout LPD3DXANIMATIONCONTROLLER pAnimController
    );

//----------------------------------------------------------------------------
// D3DXFrameNumNamedMatrices:
// --------------------------
// Counts number of frames in a subtree that have non-null names 
//
// Parameters:
//	pFrameRoot
//		Pointer to the root node of the subtree
// Return Value:
//		Count of frames
//
//----------------------------------------------------------------------------
UINT WINAPI
D3DXFrameNumNamedMatrices
    (
    __in CONST D3DXFRAME *pFrameRoot
    );

//----------------------------------------------------------------------------
// D3DXFrameCalculateBoundingSphere:
// ---------------------------------
// Computes the bounding sphere of all the meshes in the frame hierarchy.
//
// Parameters:
//	pFrameRoot
//		Pointer to the root node
//	pObjectCenter
//		Returns the center of the bounding sphere
//	pObjectRadius
//		Returns the radius of the bounding sphere
//
//----------------------------------------------------------------------------
HRESULT WINAPI
D3DXFrameCalculateBoundingSphere
    (
    __in      CONST D3DXFRAME *pFrameRoot,       
    __out_opt LPD3DXVECTOR3 pObjectCenter,  
    __out_opt FLOAT *pObjectRadius          
    );


//----------------------------------------------------------------------------
// D3DXCreateKeyframedAnimationSet:
// --------------------------------
// This function creates a compressable keyframed animations set interface.
// 
// Parameters:
//  pName
//      Name of the animation set
//  TicksPerSecond
//      Number of keyframe ticks that elapse per second
//  Playback
//      Playback mode of keyframe looping
//  NumAnimations
//      Number of SRT animations
//  NumCallbackKeys
//      Number of callback keys
//  pCallbackKeys
//      Array of callback keys
//  ppAnimationSet
//      Returns the animation set interface
// 
//-----------------------------------------------------------------------------		
HRESULT WINAPI
D3DXCreateKeyframedAnimationSet
    (
    __in_z                           LPCSTR pName,                               
                                     DOUBLE TicksPerSecond,
                                     D3DXPLAYBACK_TYPE Playback,
                                     UINT NumAnimations,                         
                                     UINT NumCallbackKeys,                       
    __in_ecount_opt(NumCallbackKeys) CONST D3DXKEY_CALLBACK *pCallbackKeys,           
    __deref_out                      LPD3DXKEYFRAMEDANIMATIONSET *ppAnimationSet 
    );


//----------------------------------------------------------------------------
// D3DXCreateCompressedAnimationSet:
// --------------------------------
// This function creates a compressed animations set interface from 
// compressed data.
// 
// Parameters:
//  pName
//      Name of the animation set
//  TicksPerSecond
//      Number of keyframe ticks that elapse per second
//  Playback
//      Playback mode of keyframe looping
//  pCompressedData
//      Compressed animation SRT data
//  NumCallbackKeys
//      Number of callback keys
//  pCallbackKeys
//      Array of callback keys
//  ppAnimationSet
//      Returns the animation set interface
// 
//-----------------------------------------------------------------------------		
HRESULT WINAPI
D3DXCreateCompressedAnimationSet
    (
    __in_z                           LPCSTR pName,                               
                                     DOUBLE TicksPerSecond,
                                     D3DXPLAYBACK_TYPE Playback,
    __in                             LPD3DXBUFFER pCompressedData,                         
                                     UINT NumCallbackKeys,                       
    __in_ecount_opt(NumCallbackKeys) CONST D3DXKEY_CALLBACK *pCallbackKeys,           
    __deref_out                      LPD3DXCOMPRESSEDANIMATIONSET *ppAnimationSet 
    );


//----------------------------------------------------------------------------
// D3DXCreateAnimationController:
// ------------------------------
// This function creates an animation controller object.
//
// Parameters:
//  MaxNumMatrices
//      Maximum number of matrices that can be animated
//  MaxNumAnimationSets
//      Maximum number of animation sets that can be played
//  MaxNumTracks
//      Maximum number of animation sets that can be blended
//  MaxNumEvents
//      Maximum number of outstanding events that can be scheduled at any given time
//  ppAnimController
//      Returns the animation controller interface
//
//-----------------------------------------------------------------------------		
HRESULT WINAPI
D3DXCreateAnimationController
    (
                UINT MaxNumMatrices,                       
                UINT MaxNumAnimationSets,                  
                UINT MaxNumTracks,                         
                UINT MaxNumEvents,                         
    __deref_out LPD3DXANIMATIONCONTROLLER *ppAnimController
    );


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__D3DX9ANIM_H__


