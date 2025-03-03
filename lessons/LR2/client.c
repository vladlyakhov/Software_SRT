#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>

int main(void)
{
	char smsg[20];
	char rmsg[200];
	int coid;
	long serv_pid;
	printf("Prog client,  Enter server PID \n");
	scanf("%ld", &serv_pid);
	printf("Entered %ld  \n", serv_pid);
	coid = ConnectAttach(0, serv_pid, 1, 0, 0);
	printf("Connect res %d  \n, Enter message", coid);
	scanf("%s", &smsg);
	printf("Entered %s  \n", smsg);
	if (MsgSend(coid, smsg, strlen(smsg) + 1, rmsg, sizeof(rmsg)) == -1)
	{
		printf("Error MsgSend  \n");
	}
	return(1);
}
