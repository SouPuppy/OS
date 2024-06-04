#include "./H/common.h"
#include "./H/palette.h"

void init_palette(void) {
    static unsigned char table_rgb[16 * 3] = {
        0x84, 0x02, 0x28,   //  0: True Red     (真红)
        0xED, 0x19, 0x41,   //  1: Scarlet      (赤)
        0xF0, 0x5B, 0x72,   //  2: Rose         (蔷薇色)
        0xF5, 0x82, 0x20,   //  3: Tangerine    (蜜柑色)
        0xFC, 0xAF, 0x17,   //  4: Amber        (山吹色)
        0x7F, 0xB8, 0x0E,   //  5: Willow       (若緑)
        0x45, 0xB9, 0x7C,   //  6: Green        (緑)
        0x00, 0xAE, 0x9D,   //  7: Aquamarine   (青緑)
        0x00, 0x87, 0x92,   //  8: Dark Teal    (御纳戸色)
        0x10, 0x2B, 0x6A,   //  9: Azure        (青蓝)
        0x29, 0x30, 0x47,   // 10: Dark Blue    (铁御纳戸)
        0x69, 0x4D, 0x9F,   // 11: Iris         (菖蒲色)
        0xF2, 0xF2, 0xFB,   // 12: White        (白)
        0xFF, 0xED, 0xDC,   // 13: Skin         (肌色)
        0x5F, 0x3C, 0x23,   // 14: Withered Tea (枯茶)
        0x13, 0x0C, 0x0E    // 15: Black        (黑)
    };
    set_palette(0, 15, table_rgb);
    return ;
}

void set_palette(int start, int end, unsigned char *rgb) {
    int i, eflags;
    eflags = io_load_eflags();  // Save interrupt flag
    io_cli();                   // Disable interrupts
    
    // 0x03c8: VGA head
    // 0x03c9: VGA component
	io_out8(0x03c8, start);
	for (i = start; i <= end; i++) {
		io_out8(0x03c9, rgb[0] / 4);
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3;
	}
    io_store_eflags(eflags);  // Restore interrupt flag
    return ;
}
