#include "./H/terminal.h"
#include "./H/display.h"
#include "./H/bootinfo.h"

void init_terminal() {
	box(black, 0, 0, boot_info->scrnx, boot_info->scrny);
}