#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>

#define MEGABYTE	1024*1024

int main(int argc, char *argv[])
{
	int fd = shm_open("/test.shm", O_CREAT | 0666, 0);
	if (fd == -1) perror("shm open: ");

	off_t length = MEGABYTE;
	int res = ftruncate(fd, length);
	if (res != 0) perror("ftruncate:");

	char *buf = (char *)mmap((void *)0, MEGABYTE, PROT_READ | PROT_WRITE, 
				MAP_SHARED , fd, 0);
	
	int i;
	for (i = 0; i < MEGABYTE; i++) {
		*buf++ = 13;	
	}

	return 0;
}

