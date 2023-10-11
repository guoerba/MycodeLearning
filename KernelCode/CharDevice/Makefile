#用于区分kbuild和外部Makefile的全局变量，仅在kbuild中有定义
ifneq ($(KERNELRELEASE),)
#内核部分kbuild代码
obj-m += char_mem_dev.o

else
#外部模块Makefile代码

#都可以作为源代码目录
#编译内核后出现的目录
#KDIR ?= /lib/modules/$(shell uname -r)/build

#.o .ko文件目录
KDIR ?= /lib/modules/$(shell uname -r)/build

all: modules install
#内核kbuild为外部makefile提供了四个target:
#modules : 编译外部模块（产生ko文件）
#modules_install : 安装外部模块到内核（将ko文件复制到/lib/modules/$(uname -r)/kernel的对应目录下<全是ko文件>，并更新/lib/modules/$(uname -r)下一大堆modules.*文件）
#clean : 清除模块
#help : 打印帮助信息
modules:
	make -C $(KDIR) M=$$PWD modules

install:
	make -C $(KDIR) M=$$PWD modules_install

clean:
	make -C $(KDIR) M=$$PWD clean

help:
	make -C $(KDIR) M=$$PWD help

endif
