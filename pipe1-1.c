#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BLOCK_SIZE 	512
#define BUF_SIZE	20

// who | sort


int main(int atgc, char *argv[])
{ 
	char buf[BLOCK_SIZE];
	char *bufp[BUF_SIZE];
	int i, c;

	ssize_t bytes_read;
	size_t nbytes = sizeof(buf);

	memset(bufp, 0, sizeof(char *) * BUF_SIZE);
	int cnt = 1;
	
	bytes_read = read(0, buf, BLOCK_SIZE);

	bufp[0] = strtok(buf, "|");
	
	while (bufp[cnt++] = strtok(0, "|"));
	cnt--;

	int end = 0;
	for (i = 0; i < BUF_SIZE; i++) {
		if (bufp[cnt-1][i] == '\n') end = 1;
		if (end) bufp[cnt-1][i] = 0;
	}

	int pfd[2];

	for (c = 0; c < cnt-1; c++) {
		pipe(pfd);

		if (!fork()) {
			close(STDOUT_FILENO);
			
			dup2(pfd[1], STDOUT_FILENO);
			close(pfd[0]);
			close(pfd[1]);
			
			char *cmd = strtok(bufp[c], " ");
			char *args = strtok(0, " ");	
			//printf("[%d] STR=%s\n", getpid(), cmd);
			//printf("[%d] ARGS=%s\n", getpid(), args);
			if (args) 
				execlp(cmd, cmd, args, NULL);	
			else 	execlp(cmd, cmd, NULL);	
			return 0;
		}
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[1]);
		
	}

	int fd_out = open("result.out", O_RDWR | O_CREAT | O_TRUNC, 0666);
	close(STDIN_FILENO);
	dup2(pfd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO); //, fd_out);
	close(fd_out);
	close(pfd[0]);
	close(pfd[1]);
		
	int num = cnt-1;
	char *cmd = strtok(bufp[num], " ");
	char *args = strtok(0, "\n");
	if (args) 
		execlp(cmd, cmd, args, NULL);	
	else 	execlp(cmd, cmd, NULL);	
	

	return 0;
}

