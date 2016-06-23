#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t ppid, cpid, w;
	int status;
	
	ppid = getpid();

	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {
		printf("Child PID is %ld\n", (long) getpid());
		while (1) {
			sleep(1);
			printf("Hi from child\n");
		}

	} else {
		printf("PPID=%d, CPID=%d\n", ppid, cpid);
		FILE *pf = fopen("/tmp/ppid", "w");
		FILE *cf = fopen("/tmp/cpid", "w");
		fprintf(pf, "%d\n", ppid);
		fprintf(cf, "%d\n", cpid);
		fclose(pf);
		fclose(cf);
	
		while(1) {
			w = waitpid(cpid, &status, WNOHANG);
			//printf("Hi from Parent\n");
			/*if (w == -1) {
				perror("waitpid");
				exit(EXIT_FAILURE);
			}*/
			
			/*if (WIFEXITED(status)) {
				printf("exited, status=%d\n", WEXITSTATUS(status));
			//} else if (WIFSIGNALED(status)) {
			} else if (WTERMSIG(status)) {
				printf("killed by signal %d\n", WTERMSIG(status));
				
			} else if (WIFSTOPPED(status)) {
				printf("stopped by signal %d\n", WSTOPSIG(status));
			} else if (WIFCONTINUED(status)) {
				printf("continued\n");
			}
			if (w == -1) {
				perror("waitpid");
				exit(EXIT_FAILURE);
			}*/
		}
	}

	return 0;
}
