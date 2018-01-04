#include <sys/types.h> /* socket */
#include <sys/socket.h> /* socket */
#include <netinet/in.h> /* struct sockaddr_in6  */
#include <stdio.h> /*perror*/
#include <string.h> /* memset */
#include <unistd.h> /* close */
#include <stdlib.h> /* htons */
#include <arpa/inet.h> /* inet_pton */

#define MSG_SIZE 1024

void InitSocketAdrr(int _port, char* _ip, struct sockaddr_in6* _socketAdrr)
{
    memset(_socketAdrr, 0, sizeof(struct sockaddr_in6));
    _socketAdrr->sin6_family = AF_INET6;
    _socketAdrr->sin6_port = htons(_port);
    inet_pton(AF_INET6, _ip, _socketAdrr->sin6_addr.s6_addr);
}

int InitClient(int _port, struct sockaddr_in6* _socketAdrr)
{
    int socketFd = socket(AF_INET6, SOCK_DGRAM, 0);
    if(socketFd < 0)
    {
        perror("socket creation fdailed");
        return -1;
    }
    
    return socketFd;
}


void Client(int _sockfd, struct sockaddr_in6* _socketAdrr)
{
    int isRunning = 1;
    unsigned int adrrLength = sizeof(struct sockaddr_in6);
    char msg[MSG_SIZE];
    int count;
    struct sockaddr_in6 inAddrs;
    while(isRunning)
    {
        scanf("%s", msg);
        
        if(sendto(_sockfd, msg, strlen(msg), 0, (struct sockaddr *)_socketAdrr, adrrLength) < 0)
        {
            perror("msg send failed");
            return;
        }
        if(0 == strcmp("exit", msg))
        {
            break;
        }
        if((count = recvfrom(_sockfd, msg, MSG_SIZE, 0, (struct sockaddr *)&inAddrs, &adrrLength)) < 0)
        {
            perror("msg recive failed");
            return;
        }
        msg[count] = '\0';
        printf("msg recived: %s\n", msg);
    }
}
    

int main(int argc, char* argv[])
{
    int port = atoi(argv[1]);
    struct sockaddr_in6 socketAddr;
    InitSocketAdrr(port, argv[2], &socketAddr);
    
    int sfd = InitClient(port, &socketAddr);
    Client(sfd, &socketAddr);
    close(sfd);
    return 1;
}
