#include <stdio.h>      //printf(), fprintf(), perror()
#include <sys/socket.h> //socket(), bind(), accept(), listen()
#include <arpa/inet.h>  // struct sockaddr_in, struct sockaddr, inet_ntoa(), inet_aton()
#include <stdlib.h>     //atoi(), exit(), EXIT_FAILURE, EXIT_SUCCESS
#include <string.h>     //memset(), strcmp()
#include <unistd.h>     //close()

#define MSGSIZE 1024
#define BUFSIZE (MSGSIZE + 1)

int main(int argc, char *argv[])
{

    int sock;                        //local socket descripter
    struct sockaddr_in servSockAddr; //server internet socket address
    unsigned short servPort;         //server port number
    char recvBuffer[BUFSIZE];        //receive temporary buffer
    char sendBuffer[BUFSIZE];        // send temporary buffer

    if (argc != 3)
    {
        fprintf(stderr, "argument count mismatch error.\n");
        exit(EXIT_FAILURE);
    }

    memset(&servSockAddr, 0, sizeof(servSockAddr));

    servSockAddr.sin_family = AF_INET;

    inet_aton(argv[1], &servSockAddr.sin_addr);

    servPort = (unsigned short)atoi(argv[2]);

    servSockAddr.sin_port = htons(servPort);

    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // server 側でいう listen 的な。接続しにいく
    connect(sock, (struct sockaddr *)&servSockAddr, sizeof(servSockAddr));

    printf("connect to %s\n", inet_ntoa(servSockAddr.sin_addr));

    while (1)
    {
        printf("please enter the characters:");
        fgets(sendBuffer, BUFSIZE, stdin);

        send(sock, sendBuffer, strlen(sendBuffer), 0);

        int byteRcvd = 0;
        int byteIndex = 0;

        while (byteIndex < MSGSIZE)
        {
            byteRcvd = recv(sock, &recvBuffer[byteIndex], 1, 0);
            if (recvBuffer[byteIndex] == '\n')
            {
                recvBuffer[byteIndex] = '\0';
            }
            byteIndex += byteRcvd;
        }
        printf("server return: %s\n", recvBuffer);
    }

    close(sock);
    return EXIT_SUCCESS;
}
