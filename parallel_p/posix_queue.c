#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>

int main(int argc, char *argv[])
{
	struct mq_attr attr;

	attr.mq_flags = 0;
	attr.mq_maxmsg=10;
	attr.mq_maxmsg = 80;
	attr.mq_curmsgs = 0;
	unlink("/test1.mq");
	mq_unlink("/test1.mq");

	mqd_t mqid = mq_open("/test1.mq", O_CREAT|O_EXCL, 0666, NULL); //&attr);
	if (mqid == -1) {
		perror("mq_open");
		return 1;
	}
	printf("mqid=%d\n", mqid);

	char msg[8192];
	memset(msg, 0, sizeof(msg));
	size_t size = 0;

	int quit = 0;
	int prio = 4;
	do {
		ssize_t bytes_read;

		bytes_read = mq_receive(mqid, msg, 8192, &prio);
		msg[bytes_read] = '\0';
		//if (!strncmp(msg, MSG_STOP, strlen(MSG_STOP)))
		//	quit = 1;
		if (bytes_read > 0) {
			printf("Received: %s\n", msg);
			quit = 1;
		}

	} while (!quit);

	msg[13] = '\0';
	FILE *f = fopen("/tmp/message.txt", "w");
	fprintf(f, "%s", msg);
	fclose(f);

	mq_close(mqid);
	mq_unlink("/test1.mq");
	return 0;
}
