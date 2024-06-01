TOOLPATH = ..\..\tolset\z_tools
INCPATH = $(TOOLPATH)\haribote\

MAKE     = $(TOOLPATH)\make.exe -r
NASK     = $(TOOLPATH)\nask.exe
CC1      = $(TOOLPATH)\cc1.exe -I$(INCPATH) -Os -Wall -quiet
GAS2NASK = $(TOOLPATH)\gas2nask.exe -a

DEL      = del

SUBDIRS = $(wildcard */)
DIR_NAMES = $(notdir $(SUBDIRS))

.PHONY: default clean $(SUBDIRS)

default: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

$(DIR_NAMES): $(DIR_NAMES:=.obj)

%.gas : %.c Makefile
	$(CC1) -o $@ $<

%.nas : %.gas Makefile
	$(GAS2NASK) $< $@

..\%.obj : %.nas Makefile
	$(NASK) $< $@ $(basename $@).lst

clean:
	-$(DEL) *.lst
	-$(DEL) *.obj
