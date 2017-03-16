#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MEGABYTE	1024*1024

int main(int argc, char *argv[])
{
	key_t key = ftok("/tmp/mem.temp", 1);
	int shmid = shmget(key, MEGABYTE, IPC_CREAT | 0666);
	if (shmid == -1) perror("shmget");
	
	char *addr = (char *)shmat(shmid, (void *)0, 0);
	printf("Addr:%p\n", addr);

	int i;
	for (i = 0; i < MEGABYTE; i++) {
		*addr++ = 42;	
	}

	return 0;
}

