#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

int main(int argc, char *argv[])
{
	sem_t *semph = sem_open("/test.sem", O_CREAT, 0666, 66);
	
	int sval;
	int r0 = sem_getvalue(semph, &sval);
	printf("Val=%d\n", sval);


	int cnt = 0;
	while (cnt++ < 20) {
		sleep(1);
	}

	int r1 = sem_close(semph);
	int r2 = sem_unlink("/test.sem");
	return 0;
}

