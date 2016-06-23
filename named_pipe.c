#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int fd_fifo_in, fd_fifo_out;
	char buf[512];

	unlink("/tmp/in.fifo");
	unlink("/tmp/out.fifo");

	if (mkfifo("/tmp/in.fifo", 0666) == -1) {
		perror("in.fifo");
		return -1;
	} else printf("Create in.fifo\n");

	if (mkfifo("/tmp/out.fifo", 0666) == -1) {
		perror("out.fifo");
		return -1;
	} else printf("Create out.fifo\n");	
	

	if ((fd_fifo_in = open("/tmp/in.fifo", O_RDWR | O_NONBLOCK)) == -1) {
		perror("open in fifo");
		fflush(stdout);
		return -1;
	} else printf("Open in.fifo\n");

	if ((fd_fifo_out = open("/tmp/out.fifo", O_RDWR )) == -1) {
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
