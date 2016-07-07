#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define FNAME "main.pid"

pthread_t thread1;
pthread_t thread2;

pthread_mutex_t	mutex;
pthread_cond_t cond;

pthread_barrier_t barrier;

void *thread_t1(void *ptr)
{

	printf("thread_t1 start wait\n");
	pthread_cond_wait(&cond, &mutex);
	printf("thread_t1 stop wait\n");
	pthread_exit(NULL);
}

void *thread_t2(void *ptr)
{
	printf("thread_r1 start wait\n");
	pthread_barrier_wait(&barrier);
	printf("thread_r1 stop wait\n");

	pthread_exit(NULL);
}
void save_pid(pid_t pid)
{
	FILE *f = fopen(FNAME, "w");
	fprintf(f, "%d", (int) pid);
        fclose(f);
}


int main(int argc, char *argv[])
{
	pid_t pid = getpid();
	printf("pid=%d\n", (int)pid);
	save_pid(pid);

	pthread_mutex_init(&mutex, NULL);
	// initialize condition variable
	pthread_cond_init(&cond, NULL);

	// Init barrier
	pthread_barrier_init(&barrier, NULL, 2);

	pthread_mutex_lock(&mutex);


	pthread_create(&thread1, NULL, thread_t1, NULL);
	pthread_create(&thread2, NULL, thread_t2, NULL);



	int cnt = 0;
	while (cnt++ < 3) {
		printf("main %d\n", cnt);
		sleep(1);
	}
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	pthread_barrier_wait(&barrier);



	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
	pthread_barrier_destroy(&barrier);

	printf("Done\n");
	return 0;
}
