#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

static char buf[65536];
int main(int argc, char *argv[])
{
	int fd, ret, len;
	char cmd[256];
/*open函数用来打开或创建一个文件，若成功返回文件描述符，否则返回-1。
 *pathname是要打开或创建文件的名字。
 *oflag参数是下列一个或多个常量执行按位或运算的结果杀
    O_RDONLY　　只读打开
    O_WRONLY　 只写打开
    O_RDWR 读写打开
上面三个常量必须指定一个并且只能指定一个，下面一些常量则是可选的：
    O_APPEND　　将写入追加到文件的尾端
    O_CREAT 若文件不存在，则创建它。使用该选项时，需要第三个参数mode，用来指定新文件的访问权限位
    O_EXCL 如果同时指定了O_CREAT，而文件已经存在，则会出错
    O_TRUNC 如果此文件存在，而且为只写或读写模式成功打开，则将其长度截短为0
    O_NOCTTY 如果pathname指的是终端设备，则不将该设备分配作为此进程的控制终端
    O_NONBLOCK 如果pathname指的是一个FIFO文件、块设备文件或字符设备文件，则此选项将文件的本次打开操作和后续的I/O操作设置为非阻塞模式*/
	fd = open("/dev/char_mem_dev", O_RDWR);
	if (fd == -1) {
		printf("open /dev/char_mem_dev failed\n");
		return 1;
	}
	len = 0;
	while (1) {
		printf("Your CMD?\n");
		scanf("%s", cmd);
		if (!strcmp(cmd, "r")) {
			memset(buf, 0, 65536 * sizeof(char));
			lseek(fd, 0, SEEK_SET);
			ret = read(fd, buf, 65536);
			if (ret == -1) {
				printf("read error\n");
				continue;
			} else {
				printf("[Buffer]\n%s\n", buf);
				len += ret;
			}
		} else if (!strcmp(cmd, "w")) {
			memset(buf, 0, 65536 * sizeof(char));
			printf("[write to buffer]\n");
			scanf("%s", buf);
			lseek(fd, len, SEEK_SET);
			ret = write(fd, buf, strlen(buf));
			if (ret == -1) {
				printf("write error\n");
				continue;
			} else {
				printf("[write %d bytes to buffer]\n", ret);
			}
		} else if (!strcmp(cmd, "cmd")) {
		} else if (!strcmp(cmd, "q") || (!strcmp(cmd, "quit"))) {
			break;
		} else {
		}
	}

	close(fd);
	return 0;
}
