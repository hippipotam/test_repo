#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_IN_FILE	"/tmp/in.fifo"
#define FIFO_OUT_FILE	"/tmp/out.fifo"

int main(int argc, char* argv[])
{
	int fd_fifo_in, fd_fifo_out;
	char buf[512];

	unlink(FIFO_IN_FILE);
	unlink(FIFO_OUT_FILE);

	if (mkfifo(FIFO_IN_FILE, 0666) == -1) {
		perror("in.fifo");
		return -1;
	} else printf("Create in.fifo\n");

	if (mkfifo(FIFO_OUT_FILE, 0666) == -1) {
		perror("out.fifo");
		return -1;
	} else printf("Create out.fifo\n");	
	

	if ((fd_fifo_in = open(FIFO_IN_FILE, O_RDWR | O_NONBLOCK)) == -1) {
		perror("open in fifo");
		fflush(stdout);
		return -1;
	} else printf("Open in.fifo\n");

	if ((fd_fifo_out = open(FIFO_OUT_FILE, O_RDWR )) == -1) {
		perror("open in fifo");
		return -1;
	} else printf("Open out.fifo\n");

	while (1) {
		int rd_bytes = read(fd_fifo_in, &buf, sizeof(buf));
		
		if (rd_bytes > 0) {
			printf("READ %d bytes ( %s )\n", rd_bytes, buf);
			int wr_bytes = write(fd_fifo_out, &buf, rd_bytes);
			printf("WRITE %d bytes ( %s )\n", wr_bytes, buf);
		}
	}

	close(fd_fifo_in);
	close(fd_fifo_out);


	return 0;
}
