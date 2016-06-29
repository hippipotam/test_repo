#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg {
	long mtype;
	char mtext[80];
};

int main(int argc, char *argv[])
{
	struct msg mess;

	key_t key = ftok("/tmp/msg.temp", 1);
	printf("key: %ld\n", (long int)key);

	int msgid = msgget(key, IPC_CREAT|0666);

	printf("msgid: %d]\n", msgid);


	/*struct msgid_ds data;
	msgctl(msgid, IPC_STAT, &data);
	printf("uid=%d, gid=%d\ncuid=%d, cgid=%d\n", data.msg_perm.uid, data.msg_perm.gid,
			data.msg_perm.cuid, data.msg_perm.cgid);
	printf("msg num=%d\n", (int)data.msg_num);
	prinf("LASTPID=%d\n", (int)data.msglspid);
	*/
	int res = msgrcv(msgid, (struct msg *)(&mess), 80, 0, 0);

	printf("Recv %d bytes: %s\n", res, mess.mtext);

	FILE *f = fopen("/tmp/message.txt", "w");
	fprintf(f, "%s", mess.mtext);
	fclose(f);

	if(msgctl(msgid, IPC_RMID, NULL))
		perror("msgctl");
	
	return 0;
}
