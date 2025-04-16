#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <unistd.h>
#include <errno.h> 

void compress_string(char* input, char* output) {
    int count, pos = 0;
    char current;

    while (*input) {
        current = *input++;
        count = 1;

        while (*input == current) {
            count++;
            input++;
        }

        pos += sprintf(output + pos, "%d%c", count, current);
    }
    output[pos] = '\0';
}

void server(void) {
    int rcvid;
    int chid;
    char message[512];
    char compressed[512];

    printf("Server start working\n");

    if ((chid = ChannelCreate(0)) == -1) {
        perror("ChannelCreate");
        exit(EXIT_FAILURE);
    }

    printf("Channel id: %d\n", chid);
    printf("Pid: %d\n", getpid());

    while (1) {
        rcvid = MsgReceive(chid, message, sizeof(message), NULL);
        if (rcvid == -1) {
            perror("MsgReceive");
            continue;
        }

        printf("Received message: \"%s\"\n", message);

        compress_string(message, compressed);
        printf("Compressed message: \"%s\"\n", compressed);

        if (MsgReply(rcvid, 0, compressed, strlen(compressed) + 1) == -1) {
            perror("MsgReply");
        }
    }
}

int main(void) {
    printf("Server program\n");
    server();
    return EXIT_SUCCESS;
}