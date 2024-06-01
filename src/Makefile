TOOLPATH = ..\tolset\z_tools
INCPATH = $(TOOLPATH)\haribote\

MAKE     = $(TOOLPATH)\make.exe -r
NASK     = $(TOOLPATH)\nask.exe
CC1      = $(TOOLPATH)\cc1.exe -I$(INCPATH) -Os -Wall -quiet
GAS2NASK = $(TOOLPATH)\gas2nask.exe -a

OBJ2BIM  = $(TOOLPATH)\obj2bim.exe
BIM2HRB  = $(TOOLPATH)\bim2hrb.exe

MAKEFONT = $(TOOLPATH)\makefont.exe
BIN2OBJ  = $(TOOLPATH)\bin2obj.exe

RULEFILE = $(TOOLPATH)\haribote\haribote.rul
EDIMG    = $(TOOLPATH)\edimg.exe
IMGTOL   = $(TOOLPATH)\imgtol.com
COPY     = copy
DEL      = del

default : 
	$(MAKE) run

ipl10.bin : ipl10.nas Makefile
	$(NASK) ipl10.nas ipl10.bin ipl10.lst

asmhead.bin : asmhead.nas Makefile
	$(NASK) asmhead.nas asmhead.bin asmhead.lst

bootpack.gas : bootpack.c Makefile
	$(CC1) -o bootpack.gas bootpack.c

bootpack.nas : bootpack.gas Makefile
	$(GAS2NASK) bootpack.gas bootpack.nas

bootpack.obj : bootpack.nas Makefile
	$(NASK) bootpack.nas bootpack.obj bootpack.lst






# 规则：将 LIB/IO/IO.c 编译为 IO.gas
LIB/IO/IO.gas : LIB/IO/IO.c Makefile
	$(CC1) -o LIB/IO/IO.gas LIB/IO/IO.c

# 规则：将 LIB/IO/IO.gas 转换为 IO.nas
LIB/IO/IO.nas : LIB/IO/IO.gas Makefile
	$(GAS2NASK) LIB/IO/IO.gas LIB/IO/IO.nas

# 规则：将 LIB/IO/IO.nas 汇编为 IO.obj 和 IO.lst
LIB/IO/IO.obj : LIB/IO/IO.nas Makefile
	$(NASK) LIB/IO/IO.nas LIB/IO/IO.obj LIB/IO/IO.lst





LIB_OBJ := $(wildcard LIB/*.obj)

naskfunc.obj : naskfunc.nas Makefile
	$(NASK) naskfunc.nas naskfunc.obj naskfunc.lst

EZ_font.bin : FONT\EZ_font.txt Makefile
	$(MAKEFONT) FONT\EZ_font.txt EZ_font.bin

EZ_font.obj : EZ_font.bin Makefile
	$(BIN2OBJ) EZ_font.bin EZ_font.obj _EZ_font

bootpack.bim : bootpack.obj naskfunc.obj EZ_font.obj $(LIB_OBJ) Makefile
	$(MAKE) -C lib
	$(OBJ2BIM) @$(RULEFILE) out:bootpack.bim stack:3136k map:bootpack.map \
		bootpack.obj naskfunc.obj $(LIB_OBJ) EZ_font.obj





bootpack.hrb : bootpack.bim Makefile
	$(BIM2HRB) bootpack.bim bootpack.hrb 0

haribote.sys : asmhead.bin bootpack.hrb Makefile
	copy /B asmhead.bin+bootpack.hrb haribote.sys
	
haribote.img : ipl10.bin haribote.sys Makefile
	$(EDIMG)   imgin:$(TOOLPATH)\fdimg0at.tek \
		wbinimg src:ipl10.bin len:512 from:0 to:0 \
		copy from:haribote.sys to:@: \
		imgout:haribote.img

img :
	$(MAKE) haribote.img

run :
	$(MAKE) img
	$(COPY) haribote.img 	$(TOOLPATH)\qemu\fdimage0.bin
	$(MAKE)	-C 				$(TOOLPATH)\qemu


install :
	$(MAKE) img
	$(IMGTOL) w a: haribote.img

clean :
	-$(DEL) *.bin
	-$(DEL) *.lst
	-$(DEL) *.gas
	-$(DEL) *.obj
	-$(DEL) bootpack.nas
	-$(DEL) bootpack.map
	-$(DEL) bootpack.bim
	-$(DEL) bootpack.hrb
	-$(DEL) haribote.sys
	$(MAKE) -C LIB clean


src_only :
	$(MAKE) clean
	-$(DEL) haribote.img