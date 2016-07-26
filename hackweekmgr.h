//----------------------------------------------------------------
// Statically-allocated memory manager
//
// by Eli Bendersky (eliben@gmail.com)
//  
// This code is in the public domain.
//----------------------------------------------------------------
#ifndef MEMMGR_H
#define MEMMGR_H

//
// Memory manager: dynamically allocates memory from 
// a fixed pool that is allocated statically at link-time.
// 
// Usage: after calling hackweekmgr_init() in your 
// initialization routine, just use hackweekmgr_alloc() instead
// of malloc() and hackweekmgr_free() instead of free().
// Naturally, you can use the preprocessor to define 
// malloc() and free() as aliases to hackweekmgr_alloc() and 
// hackweekmgr_free(). This way the manager will be a drop-in 
// replacement for the standard C library allocators, and can
// be useful for debugging memory allocation problems and 
// leaks.
//
// Preprocessor flags you can define to customize the 
// memory manager:
//
// DEBUG_MEMMGR_FATAL
//    Allow printing out a message when allocations fail
//
// DEBUG_MEMMGR_SUPPORT_STATS
//    Allow printing out of stats in function 
//    hackweekmgr_print_stats When this is disabled, 
//    hackweekmgr_print_stats does nothing.
//
// Note that in production code on an embedded system 
// you'll probably want to keep those undefined, because
// they cause printf to be called.
//
// POOL_SIZE
//    Size of the pool for new allocations. This is 
//    effectively the heap size of the application, and can 
//    be changed in accordance with the available memory 
//    resources.
//
// MIN_POOL_ALLOC_QUANTAS
//    Internally, the memory manager allocates memory in
//    quantas roughly the size of two ulong objects. To
//    minimize pool fragmentation in case of multiple allocations
//    and deallocations, it is advisable to not allocate
//    blocks that are too small.
//    This flag sets the minimal ammount of quantas for 
//    an allocation. If the size of a ulong is 4 and you
//    set this flag to 16, the minimal size of an allocation
//    will be 4 * 2 * 16 = 128 bytes
//    If you have a lot of small allocations, keep this value
//    low to conserve memory. If you have mostly large 
//    allocations, it is best to make it higher, to avoid 
//    fragmentation.
//
// Notes:
// 1. This memory manager is *not thread safe*. Use it only
//    for single thread/task applications.
// 

#define DEBUG_MEMMGR_SUPPORT_STATS 1

#define MIN_POOL_ALLOC_QUANTAS 16

//#ifdef __cplusplus
//extern "C" {
//#endif
// 'malloc' clone
//
extern void* hackweekmgr_alloc(size_t);

// 'malloc' clone
//
extern void* hackweekmgr_calloc(size_t, size_t);
// 'malloc' clone
//
extern void* hackweekmgr_realloc(void*, size_t);


// 'free' clone
//
extern void hackweekmgr_free(void*);
  //#ifdef __cplusplus
  //}
  //#endif

#endif // MEMMGR_H
