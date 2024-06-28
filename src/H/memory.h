#ifndef memory_h
#define memory_h

#define EFLAGS_AC_BIT       0x00040000
#define CR0_CACHE_DISABLE   0x60000000

unsigned int memtest(unsigned int start, unsigned int end);

#define MEMMAN_ADDR     0x003c0000
#define MEMMAN_FREES    4090 // aprox 32KB

typedef struct FREE_INFO {
    unsigned int addr, size;
};

typedef struct MEMMAN {
    int frees, maxfrees, lostsize, losts;
    struct FREE_INFO free[MEMMAN_FREES];
};

extern struct MEMMAN *mem_man;

void            init_memman();
void            memman_init (struct MEMMAN *man);
unsigned        memman_total(struct MEMMAN *man);  // total size of a Memory Manager
unsigned int    memman_alloc(struct MEMMAN *man, unsigned int size);
int             memman_free (struct MEMMAN *man, unsigned int addr, unsigned int size);

void mem_debug();

#endif  // memory_h
