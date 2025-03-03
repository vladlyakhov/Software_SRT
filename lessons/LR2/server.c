#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>

void server(void)
{
    int rcvid;
    int chid;
    char message[512];

    printf("Server start working \n");

    chid = ChannelCreate(0);
    printf("Chanel id: %d \n", chid);
    printf("PID: %d \n", getpid());

    while (1)
    {
        rcvid = MsgReceive(chid, message, sizeof(message), NULL);
        printf("Received message, rcvid  %X \n", rcvid);
        printf("Message:: \"%s\". \n", message);
        strcpy(message, "This is answer");
        MsgReply(rcvid, EOK, message, sizeof(message));
        printf("\"%s\". \n", message);
    }
}

int main(void)
{
    printf("Prog server  \n");
    server();
    sleep(5);
    return(1);
}
