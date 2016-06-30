#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(int argc, char *argv[])
{
	key_t key = ftok("/tmp/sem.temp", 1);
	int semid = semget(key, 16, IPC_CREAT | 0666);

	int i;
	struct sembuf mbuf[16];
	for (i = 0; i < 16; i++) {
		mbuf[i].sem_num = i;
		mbuf[i].sem_op = i;
		mbuf[i].sem_flg = 0;
	}
	int res = semop(semid, mbuf, 16);
	printf("sem: %d\n", res);
	if (res != 0) perror("Semop: ");

	return 0;
}

