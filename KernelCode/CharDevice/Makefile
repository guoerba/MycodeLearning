
ifneq ($(KERNELRELEASE),)

obj-m += char_mem_dev.o

else
	
KDIR ?= /usr/src/linux-master/linux

all: modules install

modules:
	make -C $(KDIR) M=$$PWD modules

install:
	make -C $(KDIR) M=$$PWD modules_install

clean:
	make -C $(KDIR) M=$$PWD clean

help:
	make -C $(KDIR) M=$$PWD help

endif
