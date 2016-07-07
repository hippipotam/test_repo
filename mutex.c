#include <stdio.h>
#include <pthread.h>

#define FNAME	"main.pid"

pthread_t thread1;
pthread_t thread2;
pthread_t thread3;
pthread_t thread4;

pthread_mutex_t mut1;
pthread_spinlock_t spinl;
pthread_rwlock_t rdlock;
pthread_rwlock_t rwlock;

void *thread_t1(void *ptr)
{
	printf("thread_t1 started\n");

	pthread_mutex_lock(&mut1);
	printf("thread_t1 mutex locked\n");
	sleep(1);
	pthread_mutex_unlock(&mut1);
	printf("thread_t1 mutex unlocked\n");

	pthread_exit(NULL);
}

void *thread_t2(void *ptr)
{
	printf("thread_t2 started\n");

	pthread_spin_lock(&spinl);
	printf("thread_t2 spinlock locked\n");
	sleep(1);
	pthread_spin_unlock(&spinl);
	printf("thread_t2 spinlock unlocked\n");

	pthread_exit(NULL);
}

void *thread_t3(void *ptr)
{
	printf("thread_t3 started\n");

	pthread_rwlock_rdlock(&rwlock);

	printf("thread_t3 rdlock read locked\n");
	sleep(1);
	pthread_rwlock_unlock(&rwlock);

	pthread_exit(NULL);
}

void *thread_t4(void *ptr)
{
	printf("thread_t4 started\n");

	pthread_rwlock_wrlock(&rwlock);
	printf("thread_t3 rwlock read locked\n");
	sleep(1);
	pthread_rwlock_unlock(&rwlock);

	pthread_exit(NULL);
}

void save_pid(pid_t pid)
{
	FILE *f = fopen(FNAME, "w");

	fprintf(f, "%d", (int) pid);

	fclose(f);
}

int main(int argc, char*argv[])
{
	pid_t pid;
	pid = getpid();
	printf("pid=%d\n", (int)pid);
	save_pid(pid);

	pthread_mutex_init(&mut1, NULL);
	pthread_mutex_lock(&mut1);

	pthread_spin_init(&spinl, PTHREAD_PROCESS_PRIVATE);
	pthread_spin_lock(&spinl);

	//pthread_rwlock_init(&rdlock, NULL);
	pthread_rwlock_init(&rwlock, PTHREAD_PROCESS_PRIVATE);
	//pthread_rwlock_rdlock(&rdlock);
	pthread_rwlock_wrlock(&rwlock);


	
	pthread_create(&thread1, NULL, thread_t1, NULL);
	pthread_create(&thread2, NULL, thread_t2, NULL);
	pthread_create(&thread3, NULL, thread_t3, NULL);
	pthread_create(&thread4, NULL, thread_t4, NULL);
	
	


	int cnt = 0;
	while (cnt++ < 3) {
		printf("main %d\n", cnt);
		sleep(1);
	}
	pthread_mutex_unlock(&mut1);
	pthread_spin_unlock(&spinl);
	//pthread_rwlock_unlock(&rdlock);
	pthread_rwlock_unlock(&rwlock);

	

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
	
	
	pthread_mutex_destroy(&mut1);
	pthread_spin_destroy(&spinl);
	//pthread_rwlock_destroy(&rdlock);
	pthread_rwlock_destroy(&rwlock);
	

	printf("Done\n");	
	return 0;
}
