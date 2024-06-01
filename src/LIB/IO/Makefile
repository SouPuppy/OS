TOOLPATH = ..\..\..\tolset\z_tools
INCPATH = $(TOOLPATH)\haribote\

MAKE     = $(TOOLPATH)\make.exe -r
NASK     = $(TOOLPATH)\nask.exe
CC1      = $(TOOLPATH)\cc1.exe -I$(INCPATH) -Os -Wall -quiet
GAS2NASK = $(TOOLPATH)\gas2nask.exe -a

DEL      = del

TARGET = $(notdir $(CURDIR))

default:
	$(MAKE) ..\$(TARGET).obj
	$(MAKE) clean

$(TARGET).gas : $(TARGET).c Makefile
	$(CC1) -o $(TARGET).gas $(TARGET).c

$(TARGET).nas : $(TARGET).gas Makefile
	$(GAS2NASK) $(TARGET).gas $(TARGET).nas

..\$(TARGET).obj : $(TARGET).nas Makefile
	$(NASK) $(TARGET).nas ..\$(TARGET).obj

clean:
	-$(DEL) *.gas
	-$(DEL) *.nas
