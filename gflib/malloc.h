#ifndef GUARD_ALLOC_H
#define GUARD_ALLOC_H

#define HEAP_SIZE 0x20000

#define FREE_AND_SET_NULL(ptr)          \
{                                       \
    Free(ptr);                          \
    ptr = NULL;                         \
}

#define TRY_FREE_AND_SET_NULL(ptr) if (ptr != NULL) FREE_AND_SET_NULL(ptr)

extern u8 gHeap[];

void *Alloc(u32 size);
#define Alloc(size) (                                                                               \
{                                                                                                   \
    void *pointer = (Alloc)(size);                                                                  \
    if (pointer == NULL)                                                                            \
        MgbaPrintf(MGBA_LOG_INFO, "FailedToAlloc:0x%x in file \"%s\", line %d", size, __FILE__, __LINE__); \
    pointer;                                                                                        \
})
void *AllocZeroed(u32 size);
#define AllocZeroed(size) (                                                                                 \
{                                                                                                           \
    void *pointer = (AllocZeroed)(size);                                                                    \
    if (pointer == NULL)                                                                                    \
        MgbaPrintf(MGBA_LOG_INFO, "FailedToAllocZeroed:0x%x in file \"%s\", line %d", size, __FILE__, __LINE__); \
    pointer;                                                                                                \
})
void Free(void *pointer);
void InitHeap(void *pointer, u32 size);

#endif // GUARD_ALLOC_H
