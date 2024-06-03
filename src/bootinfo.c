#include "./H/common.h"
#include "./H/bootinfo.h"

struct BOOTINFO *boot_info;

void init_bootinfo(void) {
	// see in asmhead.nas
    boot_info = (struct BOOTINFO *) 0x0ff0;
}
