#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, SIG_IGN);


	pid_t pid = getpid();
	printf("PID=%d\n", pid);
	FILE *f = fopen("/tmp/pid", "w");
	if (!f) {
		printf("Cannot create file\n");
		return -1;
	}
	fprintf(f, "%d\n", pid);
	

	fclose(f);

	int cnt = 0;
	while(1) {
		printf("%d Hi\n", cnt++);
		sleep(1);
	}
		
	return 0;
}
