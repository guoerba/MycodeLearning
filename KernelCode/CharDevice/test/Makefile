#一般我们可以使用 $(wildcard *.c) 来获取工作目录下的所有的.c文件列表
SRCS := $(wildcard *.c)
#将列表中所有文件名的后缀.c替换为.o
OBJS := $(patsubst %.c,%.o,$(SRCS))
CC=gcc
CFLAGS += -c -Wall -g

test: $(OBJS)
	$(CC) $^ -o $@
%.o : %.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -rfv *.o
