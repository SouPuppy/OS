#ifndef memory_h
#define memory_h

#include "common.h"

#define EFLAGS_AC_BIT       0x00040000
#define CR0_CACHE_DISABLE   0x60000000

unsigned int memtest(unsigned int start, unsigned int end);

#define MEMMAN_ADDR     0x003c0000
#define MEMMAN_FREES    4090 // aprox 32KB

typedef struct FREE_INFO {
    unsigned int addr, size;
} FREE_INFO;

typedef struct MEMMAN {
    int frees, maxfrees, lostsize, losts;
    struct FREE_INFO free[MEMMAN_FREES];
} MEMMAN;

extern struct MEMMAN *mem_man;

void            init_memman();
void            memman_init     (struct MEMMAN *man);
unsigned        memman_total    (struct MEMMAN *man);  // total size of a Memory Manager
unsigned int    memman_alloc    (struct MEMMAN *man, unsigned int size);
unsigned int    memman_alloc_4k (struct MEMMAN *man, unsigned int size);
int             memman_free     (struct MEMMAN *man, unsigned int addr, unsigned int size);
int             memman_free_4k  (struct MEMMAN *man, unsigned int addr, unsigned int size);

void mem_debug();

// APP  FUNC
void *memcpy(void *dest, const void *src, size_t n);
void *malloc(unsigned int size);
void *realloc(void *old_ptr, unsigned int size);
int   free(void *ptr);


//* Dynamic Array

void* reallocate(void* pointer, size_t oldSize, size_t newSize);


typedef struct Array {
    int     capacity;
    int     count;
    void*   values;
} Array;

#define Array_init(type, a) \
    do { \
        reallocate((a)->values, sizeof(type) * (a)->capacity, 0); \
        (a)->capacity = 0; \
        (a)->count    = 0; \
        (a)->values   = NULL; \
    } while (false)

#define Array_free(type, a) \
    do { \
        reallocate(a, sizeof(type) * (a->capacity), 0); \
    } while (false)

#define Array_append(type, a, data) \
    do { \
        if ((a)->capacity < (a)->count + 1) { \
            int old_capacity = (a)->capacity; \
            (a)->capacity = ((a)->capacity < 8 ? 8 : (a)->capacity * 2); \
            (a)->values = (type*)reallocate((a)->values, sizeof(type) * (old_capacity), sizeof(type) * (a)->capacity); \
        } \
        ((type*)((a)->values))[(a)->count] = data; \
        (a)->count++; \
    } while (false)


#define Array_value(type, a, i) (*((type*)((a)->values) + (i)))
// (*(type*)(((char*)a->values) + element_size_with_padding * i))

//TODO add element_size_with_padding


#endif  // memory_h
