/************************************************************************
*                                                                       *
*   XMCore.h -- This module defines the Xbox multicore APIs             *
*                                                                       *
*   Copyright (c) Microsoft Corp. All rights reserved.                  *
*                                                                       *
************************************************************************/
#pragma once 

#include <sal.h>

#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////
// LOCK FREE DECLARATIONS    //
///////////////////////////////

typedef DWORD_PTR XLOCKFREE_HANDLE;
typedef DWORD_PTR XLOCKFREE_LOG;

/////////////////////////////////////////////////////////////////////////////
// Wait function prototype called when a lock-free data structure needs    //
// to block before it can add an element or must wait to remove an         //
// element. Routine must return WAIT_OBJECT_0 if event is signaled.        //
/////////////////////////////////////////////////////////////////////////////
typedef DWORD (CALLBACK *XLockFreeWait)(__in_opt PVOID context,            // Developer supplied context for the wait.
                                        __in HANDLE event,             // Event the xmcore library wants to wait on. 
                                        __in DWORD dwMilliSeconds,     // Expected wait time.
                                        __in BOOL fAlertable);         // Should the wait allow APC's

///////////////////////////////////////////////////////////////////////////////
// Function prototypes if allocators are to be replace. Memory call backs    //
// are specific to one data structure. If all allocations need to be         //
// replaced then XMemAlloc can be overridden.                                //
///////////////////////////////////////////////////////////////////////////////
typedef PVOID (CALLBACK *XLockFreeMemoryAllocate)(__in_opt PVOID context, __in DWORD dwSize);
typedef void (CALLBACK *XLockFreeMemoryFree)(__in_opt PVOID context, __in PVOID pAddress);


////////////////////////////////////////////////////////////////////////////////////////////////
// Function prototype for dump callbacks. Context is user specified in the                    //
// dump call, entry is the data stored in the structure and node is the system data.          //
// Dump functions are NOT thread safe and should only be used when threads are NOT            //
// accessing the data structures.                                                             //
////////////////////////////////////////////////////////////////////////////////////////////////
typedef HRESULT (CALLBACK *XLockFreeUnsafeDump)(__in_opt PVOID context, __in PVOID entry, __in PVOID node);

//////////////////////////////////////////////////////////////////////////////
// Default Allocation routines used by the lock free library. Allocation    //
// is done through XMemAlloc using allocator ID                             //
// eXALLOCAllocatorID_XMCORE.                                               //
//////////////////////////////////////////////////////////////////////////////
PVOID  APIENTRY XLFAllocate(__in DWORD_PTR dwSize);
void   APIENTRY XLFFree(__in_opt PVOID pAddress);

/////////////////////////////
// Lock free attributes    //
/////////////////////////////
#define XLOCKFREE_NO_ATTRIBUTES                   0x000
#define XLOCKFREE_ATTRIBUTE_FLAG                  0x001    // Reservered for internal use
#define XLOCKFREE_RESERVED_FLAG                   0x002
#define XLOCKFREE_ADD_WAIT                        0x004    // Wait until there is room in the queue/stack to add an element.
#define XLOCKFREE_REMOVE_WAIT                     0x008    // Wait until there is an entry to remove from the queue/stack.
#define XLOCKFREE_SPIN_ON_ADD                     0x010    // If we need to wait do we spin first before adding an entry
#define XLOCKFREE_SPIN_ON_REMOVE                  0x020    // If we need to wait do we spin first before removing an entry
#define XLOCKFREE_ALERTABLE_ADD                   0x040    // If we wait while adding an entry, is the wait altertable
#define XLOCKFREE_ALERTABLE_REMOVE                0x080    // If we wait while removing an entry, is the wait  altertable
#define XLOCKFREE_SINGLE_KEY_ENTRY                0x100    // Allow a single key value (PRIORITY QUEUE and HASH TABLE only)

/////////////////////////////////////////////////////////////////////////////
// The XLOCKFREE_CREATE structure is used to initialize the data           //
// structures. All entries in the structure are optional. The structure    //
// can be used to create data structures that have customized wait         //
// characteristics and memory allocations.                                 //
/////////////////////////////////////////////////////////////////////////////
typedef struct _XLOCKFREE_CREATE
{
    DWORD attributes;              // See attributes defined above (OPTIONAL)
    PVOID addWaitContext;          // User data passed when in when an add would wait (OPTIONAL)
    PVOID removeWaitContext;       // User data passed when in when a remove would wait (OPTIONAL)
    DWORD addWaitTime;             // Amount of time to wait before a timeout happens when adding an element (OPTIONAL)
    DWORD removeWaitTime;          // Amount of time to wait before a timeout happens when deleting an element (OPTIONAL)
    XLockFreeWait addWait;         // Custom wait function used if an element cannot be added to the data structure (OPTIONAL)
    XLockFreeWait removeWait;      // Custom wait function used if there is no element to removed from the data structure (OPTIONAL)
   
    // All information after here is used only during creation
    DWORD structureSize;                 // Must be set to sizeof(XLOCKFREE_CREATE)!.
    DWORD allocationLength;              // Number of elements to allocate when the data structure needs to allocate more nodes (OPTIONAL)
    DWORD maximumLength;                 // Total number of entries allowed in the data structure. -1 or 0 means unlimited (OPTIONAL)
    XLockFreeMemoryAllocate allocate;    // Custom Allocator (OPTIONAL)
    XLockFreeMemoryFree     free;        // Matching release for custom Allocator (OPTIONAL)
    PVOID memoryContext;                 // Memory context if required.
} XLOCKFREE_CREATE, *PXLOCKFREE_CREATE;

////////////////////////////////////////////////////////////////////////////
// The 'C' API for the queue data structure provides the ability to       //
// create, destroy, add elements and remove elements from a FIFO          //
// queue. The queue is an opaque handle that must be passed into every    //
// function.                                                              //
////////////////////////////////////////////////////////////////////////////
HRESULT WINAPI XLFQueueAdd(__in XLOCKFREE_HANDLE queue, __in void* data);
HRESULT WINAPI XLFQueueAllocated(__in XLOCKFREE_HANDLE queue, __out DWORD* size);
HRESULT WINAPI XLFQueueCreate(__in_opt PXLOCKFREE_CREATE info, __out XLOCKFREE_HANDLE* queue);
void    WINAPI XLFQueueDestroy(__in XLOCKFREE_HANDLE queue);
HRESULT WINAPI XLFQueueGetEntryCount(__in XLOCKFREE_HANDLE queue, __out LONG* entries);
BOOL    WINAPI XLFQueueIsEmpty(__in XLOCKFREE_HANDLE queue);
HRESULT WINAPI XLFQueueRemove(__in XLOCKFREE_HANDLE queue, __deref_out void** data);
HRESULT WINAPI XLFQueueUnsafeDump(__in XLOCKFREE_HANDLE queue, __in_opt PVOID context, __in XLockFreeUnsafeDump callback);

//////////////////////////////////////////////////
// The 'C' API for the stack data structure.    //
//////////////////////////////////////////////////
HRESULT WINAPI XLFStackAllocated(__in XLOCKFREE_HANDLE stack, __out DWORD* size);
HRESULT WINAPI XLFStackCreate(__in_opt PXLOCKFREE_CREATE info, __out XLOCKFREE_HANDLE* stack);
void    WINAPI XLFStackDestroy(__in XLOCKFREE_HANDLE stack);
HRESULT WINAPI XLFStackGetEntryCount(__in XLOCKFREE_HANDLE stack, __out LONG* entries);
BOOL    WINAPI XLFStackIsEmpty(__in XLOCKFREE_HANDLE stack);
HRESULT WINAPI XLFStackPop(__in XLOCKFREE_HANDLE stack, __deref_out void** data);
HRESULT WINAPI XLFStackPush(__in XLOCKFREE_HANDLE stack, __in void* data);
HRESULT WINAPI XLFStackUnsafeDump(__in XLOCKFREE_HANDLE stack, __in_opt PVOID context, __in XLockFreeUnsafeDump callback);


///////////////////////////////////////////////////////////////////////////////
// Compare functions to compare and hash keys used in Priority Queues and    //
// Hash Tables. Call back functions can be used in the Priority Queue and    //
// Hash Table to customize how entries are added and removed from the        //
// data structures.                                                          //
///////////////////////////////////////////////////////////////////////////////
typedef int (CALLBACK *XLockFreeCompareKeys)(int key1, int key2);
typedef unsigned int (CALLBACK *XLockFreeHashKey)(DWORD key, DWORD size);

typedef struct _XLOCKFREE_FUNCTIONS
{
    XLockFreeCompareKeys compare;                     // Function to compare to keys (OPTIONAL)
    XLockFreeHashKey     hash;                        // Function that calculates the bucket [hashtable only] (OPTIONAL)
    DWORD                structureSize;               // Must be set to the sizeof(XLOCKFREE_FUNCTIONS).
} XLOCKFREE_FUNCTIONS, *PXLOCKFREE_FUNCTIONS;

///////////////////////////////////////////////////////////
// The 'C' API for the priority queue data structure.    //
///////////////////////////////////////////////////////////
HRESULT WINAPI XLFPriorityQueueAdd(__in XLOCKFREE_HANDLE queue, __in DWORD key, __in PVOID data);
HRESULT WINAPI XLFPriorityQueueAllocated(__in XLOCKFREE_HANDLE queue, __out DWORD* size);
HRESULT WINAPI XLFPriorityQueueCreate(__in_opt PXLOCKFREE_CREATE info, __in PXLOCKFREE_FUNCTIONS functions, __out XLOCKFREE_HANDLE* queue);
void    WINAPI XLFPriorityQueueDestroy(__in XLOCKFREE_HANDLE queue);
HRESULT WINAPI XLFPriorityQueueGetEntryCount(__in XLOCKFREE_HANDLE queue, __out LONG* entries);
BOOL    WINAPI XLFPriorityQueueIsEmpty(__in XLOCKFREE_HANDLE queue);
HRESULT WINAPI XLFPriorityQueueRemoveFirst(__in XLOCKFREE_HANDLE queue, __out PVOID* data);
HRESULT WINAPI XLFPriorityQueueRemove(__in XLOCKFREE_HANDLE queue, __in DWORD key, __out PVOID* data);
HRESULT WINAPI XLFPriorityQueueUnsafeDump(__in XLOCKFREE_HANDLE queue, __in_opt PVOID context, __in XLockFreeUnsafeDump callback);

///////////////////////////////////////////////////////
// The 'C' API for the hash table data structure.    //
///////////////////////////////////////////////////////
HRESULT WINAPI XLFHashTableAdd(__in XLOCKFREE_HANDLE hashTable, __in DWORD key, __in PVOID data);
HRESULT WINAPI XLFHashTableAllocated(__in XLOCKFREE_HANDLE hashTable, __out DWORD* size);
HRESULT WINAPI XLFHashTableCreate(__in_opt PXLOCKFREE_CREATE info, __in PXLOCKFREE_FUNCTIONS functions, __in DWORD buckets, __out XLOCKFREE_HANDLE* hashTable);
void    WINAPI XLFHashTableDestroy(__in XLOCKFREE_HANDLE hashTable);
HRESULT WINAPI XLFHashTableGetEntryCount(__in XLOCKFREE_HANDLE hashTable, __out LONG* entries);
BOOL    WINAPI XLFHashTableIsEmpty(__in XLOCKFREE_HANDLE hashTable);
HRESULT WINAPI XLFHashTableRemoveFirst(__in XLOCKFREE_HANDLE hashTable, __out PVOID* data);
HRESULT WINAPI XLFHashTableRemove(__in XLOCKFREE_HANDLE hashTable, __in DWORD key, __out PVOID* data);
HRESULT WINAPI XLFHashTableUnsafeDump(__in XLOCKFREE_HANDLE hashTable, __in_opt PVOID context, __in XLockFreeUnsafeDump callback);


//////////////////
// LOCK POOL    //
//////////////////
#define XLOCKFREE_POOL_ALLOW_RECURSION            0x1    // Allow recursive calls to locks (see warnings below)
#define XLOCKFREE_POOL_WATCH_THREAD               0x2    // Fail if another thread tries to destroy a lock
#define XLOCKFREE_POOL_ACQUIRE_WAIT               0x4    // Wait until the lock can be acquired 
#define XLOCKFREE_POOL_SPIN_ON_WAIT               0x10   // If we need to wait do we spin first
#define XLOCKFREE_POOL_ALERTABLE_WAIT             0x20   // If we wait, the wait is altertable
    

// Recursion warnings:
// 1) A thread that has shared access to a lock will become blocked if it recursively tries to acquire shared 
//    access to the same lock when another thread is requesting exclusive access. When a thread requests exclusive 
//    access to a lock it will block all threads trying to acquire shared access. This includes threads that have 
//    already been granted shared access.
//
// 2) Threads that hold exclusive access will block if they ask for shared access.
//


typedef enum _TWO_WAY_LOCK_ACTIONS
{
    XLF_LOCK_SHARED,              // acquire shared lock (may require waiting); 
    XLF_LOCK_EXCLUSIVE,           // acquire exclusive lock (may require waiting); 
    XLF_LOCK_DOWNGRADE,           // downgrade exclusive lock to shared (non-blocking request); 
    XLF_LOCK_UPGRADE_SAFELY,      // upgrade shared lock to exclusive in order (may require waiting); 
    XLF_LOCK_UPGRADE_IGNORE       // upgrade shared 
} TWO_WAY_LOCK_ACTIONS;

typedef struct _TWO_WAY_LOCK
{
    __int64 data[2];
} TWO_WAY_LOCK, *PTWO_WAY_LOCK;

typedef struct _XLOCKFREE_POOL
{
    DWORD attributes;              // See attributes defined above (OPTIONAL)
    DWORD allocationLength;        // Number of elements to allocate when the data
                                   //   structure needs to allocate more nodes (OPTIONAL)
    PVOID waitContext;             // User data passed into the wait function associated
                                   //   with the data structure (OPTIONAL)
    DWORD acquireWaitTime;         // Amount of time to wait before a timeout happens when acquiring a lock
    XLockFreeWait acquireWait;     // Custom wait function used if an element cannot be
                                   //    added to the data structure (OPTIONAL)
    DWORD structureSize;           // Must be set to sizeof(XLOCKFREE_POOL).
} XLOCKFREE_POOL, *PXLOCKFREE_POOL;


HRESULT WINAPI XLFPoolAcquireLock(__in XLOCKFREE_HANDLE pool, __in TWO_WAY_LOCK_ACTIONS action, __in TWO_WAY_LOCK* lock);
HRESULT WINAPI XLFPoolAllocated(__in XLOCKFREE_HANDLE pool, __out DWORD* size);
HRESULT WINAPI XLFPoolCreate(__in_opt XLOCKFREE_POOL* info, __out XLOCKFREE_HANDLE* pool);
HRESULT WINAPI XLFPoolCreateLock(__in XLOCKFREE_HANDLE pool, __out PTWO_WAY_LOCK* lock);
void    WINAPI XLFPoolDestroy(__in XLOCKFREE_HANDLE pool);
HRESULT WINAPI XLFPoolDestroyLock(__in XLOCKFREE_HANDLE pool, __in TWO_WAY_LOCK* lock);
HRESULT WINAPI XLFPoolIncreaseEvents(__in XLOCKFREE_HANDLE pool, __in DWORD number);
HRESULT WINAPI XLFPoolIncreaseLocks(__in XLOCKFREE_HANDLE pool, __in DWORD number);
HRESULT WINAPI XLFPoolInitializeLock(__in XLOCKFREE_HANDLE pool, __in TWO_WAY_LOCK* lock);
HRESULT WINAPI XLFPoolNumberOfEvents(__in XLOCKFREE_HANDLE pool, __out DWORD* number);
HRESULT WINAPI XLFPoolNumberOfLocks(__in XLOCKFREE_HANDLE pool, __out DWORD* number);
HRESULT WINAPI XLFPoolReleaseLock(__in XLOCKFREE_HANDLE pool, __in TWO_WAY_LOCK_ACTIONS action, __in TWO_WAY_LOCK* lock);

////////////////////
// Error codes    //
////////////////////
#define FACILITY_XLOCKFREE 0x31
#define XLOCKFREE_STRUCTURE_FULL                ((HRESULT)0x80310001L)
#define XLOCKFREE_STRUCTURE_EMPTY               ((HRESULT)0x80310002L)
#define XLOCKFREE_INVALID_ACTION                ((HRESULT)0x80310003L) // When releasing a lock the action must be XLF_LOCK_SHARED or XLF_LOCK_EXCLUSIVE
#define XLOCKFREE_INVALID_UNLOCK                ((HRESULT)0x80310004L) 
#define XLOCKFREE_PENDING_UPGRADE               ((HRESULT)0x80310005L)
#define XLOCKFREE_PENDING_EXCLUSIVE_LOCK        ((HRESULT)0x80310006L)
#define XLOCKFREE_PENDING_RECURSIVE_LOCK        ((HRESULT)0x80310007L)


////////////////////////////////
// The 'C' API for the log    //
////////////////////////////////
typedef HRESULT (CALLBACK *XLFLogMessage)(__in_opt PVOID messageContext, __in_bcount(length) PBYTE buffer, __in DWORD length);
HRESULT WINAPI XLFStartLog(__in int requestedCore,     // Run the logging facility on this core
                           __in_z LPCSTR logFile,        // Log messages to this file
                           __in int messageLength,     // Maximum message length
                           __in int numberOfMessages,  // Maximum number of messages allowed to be queued up 
                           __in BOOL blockOnWrite,     // Block if queue is at is maximum
                           __out XLOCKFREE_LOG* log);   // Handle to the log is returned

HRESULT WINAPI XLFStartUserLog(__in int requestedCore,      // Run the logging facility on this core
                               __in_opt PVOID messageContext,   // Context passed to the callback
                               __in XLFLogMessage callback, // Callback processes message 
                               __in int messageLength,      // Maximum message length
                               __in int numberOfMessages,   // Maximum number of messages allowed to be queued up 
                               __in BOOL blockOnWrite,      // Block if queue is at is maximum
                               __out XLOCKFREE_LOG* log);    // Handle to the log is returned

void    WINAPI XLFEndLog(__in XLOCKFREE_LOG log);
void    WINAPI XLFLogPrint(__in XLOCKFREE_LOG log, __in_z const char* format, ...);
void    WINAPI XLFLogPrintV(__in XLOCKFREE_LOG log, __in_z const char* format, va_list argptr);
void    WINAPI XLFLogBuffer(__in XLOCKFREE_LOG log, __in_bcount(length) PBYTE buffer, __in DWORD length);
void    WINAPI XLFLogMessageStats(__in XLOCKFREE_LOG log, __in DWORD* droppedMessages, DWORD* missedMessages);


///////////////////////////////////////////////////////////////////////////
// XLockFree library will RIP in debug mode unless a error handler is    //
// supplied and it returns S_OK after being passed an error message.     //
///////////////////////////////////////////////////////////////////////////
typedef HRESULT (CALLBACK *XLockFreeErrorHandler)(__in_z const char* msg);
XLockFreeErrorHandler APIENTRY XLockFreeGetErrorHandler(void);
XLockFreeErrorHandler APIENTRY XLockFreeSetErrorHandler(__in_opt XLockFreeErrorHandler func);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

///////////////////////////////////////////////////////////////////////////////////////////
// Elements added to the lock free data structures do not need to                        //
// inherit a link structure. These algorithm allocate external link                      //
// structures because it is very difficult to know when the link structures              //
// can be released or changed. The link structure can be referenced on                   //
// multiple threads at the same and failure can occur if the link structure is updated   //
// outside the data structure.                                                           //
//                                                                                       //
// User data cannot be delete when it is added to a list. After the data                 //
// is removed from a list it can be safely deleted at any time.                          //
// Only one thread will have a reference to the user data after it is                    //
// removed from a list.                                                                  //
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
// XLockFreeStack                                                                        //
// --------------                                                                        //
// Creates a stack structure that can accept T objects. The stack stores pointers        //
// to T, it does not copy the contents of T. If the object T is deleted while the        //
// stack holds a reference results can be unpredictable.                                 //
//                                                                                       //
// Care needs to be taken when creating a stack structure that will be visible to        //
// multiple threads. The stack should either be constructed before threads are           //
// started, passed as a parameter to the thread procedure, or have global references     //
// updated using an interlocked function.                                                //
///////////////////////////////////////////////////////////////////////////////////////////

template <class _T> class XLockFreeStack 
{
  public:
    XLockFreeStack();   // Creates a stack structure. 
    ~XLockFreeStack();  // Releases all the stack resources.

    ///////////////////////////////////////////////////////////////////////////
    // Manually release all the stack resources.                             //
    ///////////////////////////////////////////////////////////////////////////
    void     Destroy(); 

    ///////////////////////////////////////////////////////////////////////////
    // Returns the amount of memory allocated for the stack.                 //
    ///////////////////////////////////////////////////////////////////////////
    DWORD GetAllocated() const;

    ///////////////////////////////////////////////////////////////////////////
    // Returns the number of entries in the stack (is a snapshot in time).   //
    ///////////////////////////////////////////////////////////////////////////
    DWORD GetEntryCount() const;

    ///////////////////////////////////////////////////////////////////////////
    // Creates a Stack structure that will allocate nodes as required and    //
    // will not block on Pushes and Pops.                                    //
    ///////////////////////////////////////////////////////////////////////////
    HRESULT Initialize();       

    ////////////////////////////////////////////////////////////////////////////
    // Creates a queue structure where the maximum number of elements, the    //
    // number of allocations and whether calls will block can be              //
    // specified. If waiting is specified in the attributes then an           //
    // optional custom Wait functions can be also added.                      //
    ////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize(__in_opt PXLOCKFREE_CREATE info);

    // Returns TRUE if there are no items in the stack.
    BOOL IsEmpty() const;

    //////////////////////////////////////////////////////////////////////////////
    // Returns the top data type in the stack. Returns NULL if no entry is      //
    // available. Because the stack can be used in a multithreaded              //
    // environment it is very possible that a call to IsEmpty() will return     //
    // FALSE and the Pop() will return NULL.  By the time the Pop() has         //
    // executed another thread may have taken all the available entries. The    //
    // program must always test for a NULL.                                     //
    //////////////////////////////////////////////////////////////////////////////
    _T* Pop(); 

    ///////////////////////////////////////////////////////////////////////////
    // Returns the top data type in the stack.  Returns                      //
    // XLOCKFREE_STRUCTURE_EMPTY if no entry is available.  If there is a    //
    // wait function added to the stack the error code from that function    //
    // would be returned in the case of a failure.                           //
    ///////////////////////////////////////////////////////////////////////////
    HRESULT Pop(__deref_out _T** ref); 

    /////////////////////////////////////////////////////////////////////////////
    // Adds a data type to the stack.  Returns XLOCKFREE_STRUCTURE_FULL if     //
    // the stack was full.  If there is a wait function added to the stack     //
    // the error code from that function would be returned in the case of a    //
    // failure.                                                                //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Push(__in _T* entry);

    PVOID operator new( __in size_t size);
    void  operator delete(__in_opt PVOID p);
    PVOID operator new[]( __in size_t size);
    void  operator delete[](__in_opt PVOID p);

    /////////////////////////////////////////////////////////////////////////////////
    // Dump the stack. Context is user defined and passed into the dump function   //
    // along with every entry in the stack. This routine is NOT thread safe.       // 
    /////////////////////////////////////////////////////////////////////////////////
    HRESULT UnsafeDump(__in_opt PVOID context, __in XLockFreeUnsafeDump function);

  private:
    XLOCKFREE_HANDLE stack;
    XLockFreeStack(__in const XLockFreeStack& s) {} // Copy constructor not allowed
};


///////////////////////////////////////////////////////////////////////////////
// XLockFreeQueue                                                            //
// --------------                                                            //
//                                                                           //
// Creates an queue structure that can accept T objects. The queue stores    //
// pointers to T, it does not copy the contents of T. If the object T is     //
// deleted while the queue holds a reference results can be                  //
// unpredictable.                                                            //
//                                                                           //
// Creates a queue structure. Care needs to be taken when creating a         //
// queue structure that will be visible to multiple threads. The queue       //
// should be constructed before threads are started, should be passed as     //
// a parameter to the thread procedure, or should have the global            //
// reference updated using an interlocked function.                          //
///////////////////////////////////////////////////////////////////////////////

template <class _T> class XLockFreeQueue
{
public:
    XLockFreeQueue(); 
    ~XLockFreeQueue(); 

    /////////////////////////////////////////////////////////////////////////////
    // Adds an entry to the queue, returns S_OK if element successfully        //
    // added.  Returns XLOCKFREE_STRUCTURE_FULL if a free node was not         //
    // available to link in the data.  If there is a wait function added to    //
    // the stack the error code from that function would be returned in the    //
    // case of a failure.                                                      //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Add(__in _T* entry); 

    ///////////////////////////////////////////////////////////////////////////
    // Manually releases all the resources associated with the queue. The    //
    // queue should not be used after this method has been called.           //
    ///////////////////////////////////////////////////////////////////////////
    void    Destroy();

    //////////////////////////////////////////////////////////////
    // Returns the amount of memory allocated for the Queue.    //
    //////////////////////////////////////////////////////////////
    DWORD GetAllocated() const;

    ///////////////////////////////////////////////////////////////////////////
    // Returns the number of entries in the Queue (is a snapshot in time).   //
    ///////////////////////////////////////////////////////////////////////////
    DWORD GetEntryCount() const;

    ///////////////////////////////////////////////////////////////////////////////
    // Creates a queue structure that will grow as necessary and will not        //
    // block on when adding or removing elements. An Initialize() method must    //
    // be called before the queue can be used.                                   //
    ///////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize();

    ////////////////////////////////////////////////////////////////////////////
    // Creates a queue structure where the maximum number of elements, the    //
    // number of allocations and whether calls will block can be              //
    // specified. If waiting is specified in the attributes then an           //
    // optional custom Wait functions can be also added.                      //
    ////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize(__in_opt PXLOCKFREE_CREATE info);

    //////////////////////////////////////////////////////////////
    // Returns TRUE if there currently no items in the queue    //
    //////////////////////////////////////////////////////////////
    BOOL IsEmpty() const; 

    //////////////////////////////////////////////////////////////////////////////
    // Returns the last entry in the queue. Returns NULL if no entry is         //
    // available. Because the queue can be used in a multithreaded              //
    // environment it is very possible that a call to IsEmpty() will return     //
    // FALSE and Remove() will return NULL.  By the time the Remove() has       //
    // executed another thread may have taken all the available entries. The    //
    // program must always test for a NULL.                                     //
    //////////////////////////////////////////////////////////////////////////////
    _T* Remove();

    ///////////////////////////////////////////////////////////////////////////////
    // Returns the last entry in the queue.  Return XLOCKFREE_STRUCTURE_EMPTY    //
    // if no entry is available.  If there is a wait function added to the       //
    // queue the error code from that function would be returned in the case     //
    // of a failure.                                                             //
    ///////////////////////////////////////////////////////////////////////////////
    HRESULT Remove(__deref_out _T** ref);                   

    PVOID operator new( __in size_t size );
    void  operator delete(__in_opt PVOID p);
    PVOID operator new[]( __in size_t size );
    void  operator delete[](__in_opt PVOID p);

    /////////////////////////////////////////////////////////////////////////////////
    // Dump the queue. Context is user defined and passed into the dump function   //
    // along with every entry in the queue. This routine is NOT thread safe.       // 
    /////////////////////////////////////////////////////////////////////////////////
    HRESULT UnsafeDump(__in PVOID context, __in XLockFreeUnsafeDump function);


private:
    XLockFreeQueue(__in const XLockFreeQueue& q) {} // Copy constructor not allowed
    XLOCKFREE_HANDLE queue;
};


class XLockFreeCustom
{ 
public:
    static int WINAPI compare(__in int p1, __in int p2); 
    static unsigned int WINAPI hash(__in unsigned int key, __in unsigned int buckets);
    static unsigned int WINAPI bucketSize(__in unsigned int buckets);
};

template <class _T,
    class _Functions = XLockFreeCustom>
class XLockFreeFunctions
{
public:
    XLockFreeFunctions() {}
    XLockFreeFunctions(__in _Functions c) : _func(c) {}
protected:
    _Functions _func;
};

/////////////////////////////////////////////////////////////////////////////
// XLockFreePriorityQueue                                                  //
// ----------------------                                                  //
//                                                                         //
// Creates a queue structure that can accept T objects. The default        //
// implementation supplies functions for comparing keys and for hashing    //
// the key.                                                                //
//                                                                         //
// Creates a priority queue structure. Care needs to be taken when         //
// creating a priority queue structure that will be visible to multiple    //
// threads. The queue should be constructed before threads are started,    //
// should be passed as a parameter to the thread procedure, or should      //
// have the global reference updated using an interlocked function.        //
/////////////////////////////////////////////////////////////////////////////

template <class _T,
          class _XFunctions = XLockFreeFunctions<_T> >
class XLockFreePriorityQueue : _XFunctions
{
public:
    XLockFreePriorityQueue();
    ~XLockFreePriorityQueue(); 
    
    ////////////////////////////////////////////////////////////////////////////////
    // Adds and entry to the priority queue.  Returns                             //
    // XLOCKFREE_STRUCTURE_FULL if there is no space to add the entry             //
    //                                                                            //
    // Returns XLOCKFREE_STRUCTURE_FULL if there is no space to add the           //
    // entry or the key exists in the queue and the queue was initialized         //
    // with XLOCKFREE_SINGLE_KEY_ENTRY                                            //
    //                                                                            //
    // If there is a wait function added to the queue the error code from that    //
    // function would be returned in the case of a failure                        //
    ////////////////////////////////////////////////////////////////////////////////
    HRESULT Add(__in DWORD key, __in _T* entry);

    ///////////////////////////////////////////////////////////////////////////////
    // Manually release all the priority queue resources.  The priority queue    //
    // should not be used after this method has been called.                     //
    ///////////////////////////////////////////////////////////////////////////////
    void    Destroy();

    ///////////////////////////////////////////////////////////////////////
    // Returns the amount of memory allocated for the priority queue.    //
    ///////////////////////////////////////////////////////////////////////
    DWORD GetAllocated() const;

    //////////////////////////////////////////////////////////////////////////////////
    // Returns the number of entries in the priority queue (is a snapshot in time). //
    //////////////////////////////////////////////////////////////////////////////////
    DWORD GetEntryCount() const;

    ///////////////////////////////////////////////////////////////////////////////
    // Creates a priority queue structure that will allocate nodes as            //
    // required to add new entries and will not block when adding or removing    //
    // entries.                                                                  //
    ///////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize();

    /////////////////////////////////////////////////////////////////////////////
    // Creates a priority queue structure where the maximum number of          //
    // elements, the number of allocations and whether calls will block can    //
    // be specified. If waiting is specified in the attributes then an         //
    // optional custom Wait functions can be also added.                       //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize(__in_opt PXLOCKFREE_CREATE info);
    
    ////////////////////////////////////////////////////////////////////////////
    // Returns TRUE if there are currently no items in the priority queue     //
    ////////////////////////////////////////////////////////////////////////////
    BOOL IsEmpty() const; 

    /////////////////////////////////////////////////////////////////////////////
    // Returns the first entry in the priority queue (the entry with the       //
    // lowest key).  Returns NULL if no entry is available.  Because the       //
    // queue can be used in a multithreaded environment it is very possible    //
    // that a call to Search() will return TRUE and Remove() will return       //
    // NULL.  By the time the Remove() has executed another thread may have    //
    // taken entries. The program must always test for a NULL.                 //
    /////////////////////////////////////////////////////////////////////////////
    _T* RemoveFirst();

    //////////////////////////////////////////////////////////////////////////////
    // Returns the first entry in the queue (the entry with the lowest key).    //
    // Returns XLOCKFREE_STRUCTURE_EMPTY if no entry is available.  If there    //
    // is a wait function added to the queue the error code from that           //
    // function would be returned in the case of a failure.                     //
    //////////////////////////////////////////////////////////////////////////////
    HRESULT RemoveFirst(__deref_out _T** ref);

    ///////////////////////////////////////////////////////////////////////////////
    // Returns the entry in the queue identified by 'key'. Returns NULL if no    //
    // entry is available. Because the queue can be used in a multithreaded      //
    // environment it is very possible that a call to Search() will return       //
    // TRUE and Remove() will return NULL.  By the time the Remove() has         //
    // executed another thread may have taken entries. The program must          //
    // always test for a NULL.                                                   //
    ///////////////////////////////////////////////////////////////////////////////
    _T* Remove(__in DWORD key);

    ///////////////////////////////////////////////////////////////////////////
    // Returns the entry in the queue identified by 'key'.  Returns          //
    // XLOCKFREE_STRUCTURE_EMPTY if no entry is available.  If there is a    //
    // wait function added to the queue the error code from that function    //
    // would be returned in the case of a failure.                           //
    ///////////////////////////////////////////////////////////////////////////
    HRESULT Remove(__in DWORD key, __deref_out _T** ref);

    PVOID operator new( __in size_t size );
    void  operator delete(__in_opt PVOID p);
    PVOID operator new[]( __in size_t size );
    void  operator delete[](__in_opt PVOID p);

    /////////////////////////////////////////////////////////////////////////////////
    // Dump the priority queue. Context is user defined and passed into the        //
    // dump function along with every entry in the priority queue. This routine is // 
    // NOT thread safe.                                                            //
    /////////////////////////////////////////////////////////////////////////////////
    HRESULT UnsafeDump(__in PVOID context, __in XLockFreeUnsafeDump function);


private:
    XLockFreePriorityQueue(__in const XLockFreePriorityQueue& q) {} // Copy constructor not allowed.
    XLOCKFREE_HANDLE queue;
};



/////////////////////////////////////////////////////////////////////////////////
// XLockFreeHashTable                                                          //
// ------------------                                                          //
//                                                                             //
// Creates a hash table that can accept T objects. The default                 //
// implementation supplies functions for comparing keys and for hashing        //
// the key                                                                     //
//                                                                             //
// Creates a hash table structure. Care needs to be taken when                 //
// creating a hash table structure that will be visible to multiple            //
// threads. The hash table should be constructed before threads are started    //
// should be passed as a parameter to the thread procedure, or should          //
// have the global reference updated using an interlocked function             //
/////////////////////////////////////////////////////////////////////////////////

template <class _T,
          class _XFunctions = XLockFreeFunctions<_T> >
class XLockFreeHashTable : _XFunctions
{
public:
    XLockFreeHashTable(); 
    ~XLockFreeHashTable(); 

    /////////////////////////////////////////////////////////////////////////////
    // Adds an entry to the hash table. The entries are added in the           //
    // numerical order of the keys.                                            //
    //                                                                         //
    // Returns XLOCKFREE_STRUCTURE_FULL if there is no space to add the entry  //
    // or the entry exists in the table and the table was initialized with     //
    // XLOCKFREE_SINGLE_KEY_ENTRY.                                             //
    //                                                                         //
    // If there is a wait function added to the queue the error code from      //
    // that function would be returned in the case of a failure                //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Add(__in DWORD key, __in _T* entry);

    /////////////////////////////////////////////////////////////////////////////
    // Manually release all the hash table resources. The hash table should    //
    // not be used after this method is called.                                //
    /////////////////////////////////////////////////////////////////////////////
    void    Destroy();

    /////////////////////////////////////////////////////////////////////////////
    // Returns the amount of memory currently allocated for the hash table.    //
    /////////////////////////////////////////////////////////////////////////////
    DWORD GetAllocated() const;

    //////////////////////////////////////////////////////////////////////////////
    // Returns the number of entries in the hash table (is a snapshot in time). //
    //////////////////////////////////////////////////////////////////////////////
    DWORD GetEntryCount() const;

    /////////////////////////////////////////////////////////////////////////////
    // Creates a hash table that will allocate nodes as required to add new    //
    // entries and will not block when adding or removing entries.             //
    //                                                                         //
    // There hash table will be created with a fixed number of buckets.        //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize(__in DWORD buckets);

    /////////////////////////////////////////////////////////////////////////////
    // Creates a hash table structure where the maximum number of elements,    //
    // the number of allocations and whether calls will block can be           //
    // specified. If the maximum number of elements is specified then          //
    // optional custom Wait functions can be also added.                       //
    //                                                                         //
    // There hash table will be created with a fixed number of buckets.        //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize(__in_opt PXLOCKFREE_CREATE info, __in DWORD buckets);

    /////////////////////////////////////////////////////////////////////////////
    // Returns TRUE if there are currently no items in the hash table          //
    /////////////////////////////////////////////////////////////////////////////
    BOOL IsEmpty() const; 

    /////////////////////////////////////////////////////////////////////////////
    // Returns the first entry in the hash table (the entry with the lowest    //
    // key).                                                                   //
    //                                                                         //
    // Returns NULL if no entry is available.                                  //
    /////////////////////////////////////////////////////////////////////////////
    _T* RemoveFirst();

    ////////////////////////////////////////////////////////////////////////////
    // Returns the first entry in the hash table queue (the entry with the    //
    // lowest key).                                                           //
    //                                                                        //
    // Returns XLOCKFREE_STRUCTURE_EMPTY if no entry is available.            //
    ////////////////////////////////////////////////////////////////////////////
    HRESULT RemoveFirst(__deref_out _T** ref);

    ///////////////////////////////////////////////////////////////////////////////
    // Returns the entry in the table identified by 'key'. Returns NULL if no    //
    // entry is available. Because the table can be used in a multithreaded      //
    // environment it is very possible that a call to Remove() will return       //
    // NULL. The program must always test for a NULL.                            //
    ///////////////////////////////////////////////////////////////////////////////
    _T* Remove(__in DWORD key);

    ///////////////////////////////////////////////////////////////////////////
    // Returns the entry in the queue identified by 'key'.                   //
    //                                                                       //
    // Returns XLOCKFREE_STRUCTURE_EMPTY if no entry is available.           //
    //                                                                       //
    // If there is a wait function added to the queue the error code from    //
    // that function would be returned in the case of a failure.             //
    ///////////////////////////////////////////////////////////////////////////
    HRESULT Remove(__in DWORD key, __deref_out _T** ref);

    PVOID operator new( __in size_t size );
    void  operator delete(__in_opt PVOID p);
    PVOID operator new[]( __in size_t size );
    void  operator delete[](__in_opt PVOID p);

    /////////////////////////////////////////////////////////////////////////////
    // Dump the hashtable. Context is user defined and passed into the dump    //
    // function along with every entry in the hash table. This routine is not  // 
    // thread safe.                                                            //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT UnsafeDump(__in PVOID context, __in XLockFreeUnsafeDump function);


private:
    XLOCKFREE_HANDLE hashTable;
    XLockFreeHashTable(__in const XLockFreeHashTable& h) {}
};


/////////////////////////////////////////////////////////////////////////////////
// Often the number of lockable objects is huge. For example, an               //
// implementation of a thread-safe hash table requires one lock per hash       //
// chain (using one lock per hash table considerably reduces                   //
// performance). In such situations the number of two-way locks (and thus      //
// event handles and size of memory required) grows proportionally to the      //
// number of lockable objects.                                                 //
//                                                                             //
// This class implements a pool of fast two locks. A fast two lock provides    //
// exclusive or shared access where requests for exclusive lock will be        //
// satisfied ahead of any requests for shared locks (it does not matter        //
// of timing (traditional implementations process lock requests on "first      //
// came first served" basis).                                                  //
//                                                                             //
// In this implementation the number of event/semaphore pairs that are         //
// actually required never exceeds the max number of threads running           //
// simultaneousely (this limit may be reached on complete deadlock), and       //
// since this number of threads that process may simultaneousely create is     //
// very limited and the use of too many threads (more than few dozens)         //
// considerably reduces performance, the total amount of required              //
// synchonization events is limited and does not depend on number of           //
// lockable objects.                                                           //
/////////////////////////////////////////////////////////////////////////////////

class XLockFreeLockPool
{
  public:
    XLockFreeLockPool();
    ~XLockFreeLockPool();

    //
    // Pool functions
    //
    /////////////////////////////////////////////////////////////////////////////
    // Releases all resources associated with the pool The pool cannot be      //
    // used after calling this function.                                       //
    /////////////////////////////////////////////////////////////////////////////
    void    Destroy();

    /////////////////////////////////////////////////////////////////////////////
    // Returns the amount of memory allocated for the Pool.                    //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT GetAllocated(__out DWORD* allocated);

    /////////////////////////////////////////////////////////////////////////////
    // Sets up the lock pool. This must be done prior to any other methods     //
    // calls on the Pool are attempted. If multiple threads will be accessing  //
    // the Pool it must be finished initializing before any other thread uses  //
    // the object.                                                             //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize();

    /////////////////////////////////////////////////////////////////////////////
    // Initializes the pool with custom information.  The amount of memory     //
    // that is allocated, whether a thread should wait or not when accessing   //
    // the pool, and what the custom wait function should be.                  //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize(__in_opt XLOCKFREE_POOL* info);

    //
    // Lock functions
    //
    /////////////////////////////////////////////////////////////////////////////
    // Acquire a lock. The lock can either be shared (multiple readers) or     //
    // exclusive (one writer). The writers are queued up in order of           //
    // requests. The only exception to this is when a shared lock is           //
    // upgraded.                                                               //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Acquire(__in TWO_WAY_LOCK_ACTIONS action, __in TWO_WAY_LOCK* lock);

    /////////////////////////////////////////////////////////////////////////////
    // Returns the number of locks allocated for the pool (does not include    //
    // locks that were created using external memory - see SetupExternal())    //
    /////////////////////////////////////////////////////////////////////////////
    DWORD GetCount() const;

    /////////////////////////////////////////////////////////////////////////////
    // Increases the number of locks created in the Pool. Useful when the      //
    // total number of locks is known.                                         //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Increase(__in DWORD number);

    /////////////////////////////////////////////////////////////////////////////
    // Creates a lock that can be used to protect data or synchronize          //
    // execution.  The lock is created using the Pool's memory routines.       //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Obtain(__deref_out TWO_WAY_LOCK** lock);

    /////////////////////////////////////////////////////////////////////////////
    // Releases a lock that has been acquired (see Acquire()).  The action     //
    // must be identical to the action used when acquiring the lock.           //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Release(__in TWO_WAY_LOCK_ACTIONS action, __in TWO_WAY_LOCK* lock);

    /////////////////////////////////////////////////////////////////////////////
    // Returns the lock to pool so it can be reused. Only locks that were      //
    // created with Obtain() can be returned to the pool. Locks that are       //
    // created using SetupExternal() are not returned.                         //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Return(__in TWO_WAY_LOCK* lock);

    /////////////////////////////////////////////////////////////////////////////
    // Initializes a lock using memory supplied by the caller. The memory      //
    // must by 4 byte aligned. Memory management of the lock is the            //
    // responsibility of the caller. This lock can not be returned to the      //
    // pool (see Return()).                                                    //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT SetupExternal(__in TWO_WAY_LOCK* lock);

    //
    // System resource functions
    //
    ///////////////////////////////////////////////////////////////////////////////
    // Returns the number of event/semaphore pairs used by the Pool. The         //
    // number will not exceed 32767. An event/semaphore pair is only required    //
    // when there is contention between locks. Pairs are shared between locks    //
    // because the maximum number required at any given point during             //
    // execution is determined by the number of simultaneously executing         //
    // threads.                                                                  //
    ///////////////////////////////////////////////////////////////////////////////
    DWORD GetEventCount() const;

    ///////////////////////////////////////////////////////////////////////////////
    // Increase the number of events/semaphore pairs available to the            //
    // Pool. (Maximum 32767). This function is useful when the maximum number    //
    // concurrently running threads is known in advance.                         //
    /////////////////////////////////////////////////////////////////////////////// 
    HRESULT IncreaseEvents(__in DWORD number);

  private:
    XLOCKFREE_HANDLE pool;
};

////////////////////////////////////////////////////////////////////////////
// LOGGING FACILITY                                                       //
//                                                                        //
// Create a log file that does the physical writes to the file on the     //
// requested core. The log allocates a fixed number of messages of a      //
// specified length. The can log can either be blocking or                //
// non-blocking. If the log is non-blocking it will drop messages. The    //
// number of dropped messages is reported when the log is shut down.      //
//                                                                        //
// N.B. Log created with InitializeUser writes to the debugger only       //
// when _DEBUG is defined. The default behavior can be changed by         //  
// overriding LogMessage(PBYTE buffer, DWORD length).                     //
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
// Logs directly to file or output    //
////////////////////////////////////////
class XLockFreeLog
{
  public:
    XLockFreeLog();
    virtual ~XLockFreeLog();

    HRESULT Initialize( __in int requestedCore,       // Run the logging facility on this core
                        __in_z LPCSTR logFile,         // Log messages to this file
                        __in int messageLength,      // Maximum message length
                        __in int numberOfMessages,   // Maximum number of messages allowed to be queued up 
                        __in BOOL blockOnWrite);     // Block if queue is at is maximum

    HRESULT InitializeUser(__in int requestedCore,      // Run the logging facility on this core
                           __in int messageLength,      // Maximum message length
                           __in int numberOfMessages,   // Maximum number of messages allowed to be queued up 
                           __in BOOL blockOnWrite);     // Block if queue is at is maximum

    void Destroy();
    void LogPrint(__in_z const char* format, ...);
    void LogBuffer(__in_bcount(length) PBYTE buffer, __in DWORD length);

  protected:
    virtual HRESULT CALLBACK LogMessage(__in_bcount(length) PBYTE buffer, __in DWORD length);
  private:
    static HRESULT CALLBACK LogMessageCallback(__in PVOID context, __in_bcount(length) PBYTE buffer, __in DWORD length); // XLFLogMessage callback
    XLockFreeLog(const XLockFreeLog&){}                                                    // Copy constructor not allowed.
    XLOCKFREE_LOG log;
};

#include "xmcore.inl"

#endif /* __cplusplus */
