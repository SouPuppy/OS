#include "./H/common.h"
#include "./H/memory.h"

unsigned int memtest(unsigned int start, unsigned int end) {
    char flag486 = 0;
    unsigned int eflags, cr0, i;
    eflags  = io_load_eflags();
    eflags |= EFLAGS_AC_BIT;
    io_store_eflags(eflags);
    eflags  = io_load_eflags();
    if ((eflags & EFLAGS_AC_BIT) != 0) {
        flag486 = 1;
    }
    eflags &= ~EFLAGS_AC_BIT;
    io_store_eflags(eflags);

    if (flag486 != 0) {
        cr0  = load_cr0();
        cr0 |= CR0_CACHE_DISABLE;
        store_cr0(cr0);
    }

    i = memtest_sub(start, end);

    if (flag486 != 0) {
        cr0  = load_cr0();
        cr0 &= ~CR0_CACHE_DISABLE;
        store_cr0(cr0);
    }

    return i;
}

struct MEMMAN *mem_man;

void init_memman() {
    unsigned int mem_total;
    mem_man = (struct MEMMAN *) MEMMAN_ADDR;
    mem_total = memtest(0x00400000, 0xffffffff);
    memman_init(mem_man);
    memman_free(mem_man, 0x00001000, 0x0009e000); 
    memman_free(mem_man, 0x00400000, mem_total - 0x00400000);
}

void memman_init(struct MEMMAN *man) {
	man->frees = 0;
	man->maxfrees = 0;
	man->lostsize = 0;
	man->losts = 0;
    return ;
}

unsigned memman_total(struct MEMMAN *man) {
    unsigned int i, total_size = 0;
    for (i = 0; i < man->frees; i++) {
        total_size += man->free[i].size;
    }
    return total_size;
}

unsigned int memman_alloc(struct MEMMAN *man, unsigned int size) {
    unsigned int i, a;
    for (i = 0; i < man->frees; i++) {
        if (man->free[i].size >= size) {
            a = man->free[i].addr;
            man->free[i].addr += size;
            man->free[i].size -= size;
            if (man->free[i].size == 0) {
                man->frees--;
                for (; i < man->frees; i++) {
                    man->free[i] = man->free[i + 1];
                }
            }
            return a;
        }
    }
    return 0;
}

int memman_free (struct MEMMAN *man, unsigned int addr, unsigned int size) {
    int i, j;
    for (i = 0; i < man->frees; i++) {
        if (man->free[i].addr > addr) {
            break;
        }
    }
    if (i > 0) {
        if (man->free[i - 1].addr + man->free[i - 1].size == addr) {
            man->free[i - 1].size += size;
            if (i < man->frees) {
                if (addr + size == man->free[i].addr) {
                    man->free[i - 1].size += man->free[i].size;
                    man->frees--;
                    for (; i < man->frees; i++) {
                        man->free[i] = man->free[i + 1];
                    }
                }
            }
            return 0;
        }
    }
    if (i < man->frees) {
        if (addr +size == man->free[i].addr) {
            man->free[i].addr = addr;
            man->free[i].size += size;;
            return 0;
        }
    }
    if (man->frees < MEMMAN_FREES) {
        for (j = man->frees; j > i; j--) {
            man->free[j] = man->free[j - 1];
        }
        man->frees ++;
        if (man->maxfrees < man->frees) {
                man->maxfrees = man->frees;
        }
        man->free[i].addr = addr;
        man->free[i].size = size;
        return 0;
        }
    man->losts++;
    man->lostsize += size;
    return -1;
}

unsigned int memman_alloc_4k (struct MEMMAN *man, unsigned int size) {
    unsigned int a;
    size = (size + 0xfff) & 0xfffff000;
    a = memman_alloc(man, size);
    return a;
}

int memman_free_4k  (struct MEMMAN *man, unsigned int addr, unsigned int size) {
    int i ;
    size = (size + 0xfff) & 0xfffff000;
    i = memman_free(man, addr, size);
    return i;
}

#include "./H/io.h"

void mem_debug() {
    const int i = 11;
    _fprintf(stdout, "Total memory %d MB | Free memory  %d KB\n",
     memtest(0x00400000, 0xffffffff) / (1024 * 1024),
     memman_total(mem_man) / (1024));
}

// APP FUNC

void *malloc(unsigned int size) {
    unsigned int mem_addr;
    
    if (size == 0) {
        return NULL;
    }

    mem_addr = memman_alloc(mem_man, sizeof(unsigned int) + (unsigned int)size);
    
    if (mem_addr == 0) {
        return NULL;
    }

    return (void *)(mem_addr + sizeof(unsigned int));
}

int free(void *ptr) {
    if (ptr == NULL) {
        return -1;
    }

    unsigned int mem_addr = (unsigned int)ptr - sizeof(unsigned int);

    if (mem_addr < sizeof(unsigned int)) {
        return -1;
    }

    unsigned int size = *((unsigned int *)mem_addr);

    return memman_free(mem_man, mem_addr, size);
}
