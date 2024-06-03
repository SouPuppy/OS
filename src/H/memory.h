#ifndef MEMORY_H
#define MEMORY_H

typedef struct SEGMENT_DESCRIPTOR {
	short 	limit_low	, base_low;
	char 	base_mid	, access_right;
	char 	limit_high	, base_high;
};

typedef struct GATE_DESCRIPTOR {
	short 	offset_low	, selector;
	char 	dw_count	, access_right;
	short 	offset_high;
};

void init_gdtidt(void);
void set_segmdesc(struct SEGMENT_DESCRIPTOR *segm_d, unsigned int limit, int base, int ar);
void set_gatedesc(struct GATE_DESCRIPTOR *gate_d, int offset, int selector, int ar);

/**
#define ALLOCATE(type, count) \
    (type*)reallocate(NULL, 0, sizeof(type) * (count))

#define FREE(type, pointer) \
    reallocate(pointer, sizeof(type), 0)

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), \
        sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

void* reallocate(void* pointer, size_t oldSize, size_t newSize);
*/

#endif  // MEMORY_H
