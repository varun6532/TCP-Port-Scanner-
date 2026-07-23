#include <stdio.h>
#include <sys/socket.h>
#include<sys/time.h>
#include <netdb.h>
#include<arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>





int main(int argc , char* argv[])
{
    if(argc < 4)
    {
        printf("Not Enough Arguments!!!");
        return 1;
    }
    struct sockaddr_in server;
    struct hostent *host = gethostbyname(argv[1]);
    if(host == NULL)
    {
        printf("No host found!!");
        return 1;

    }
    server.sin_family = AF_INET;
    char * ip = inet_ntoa(*(struct in_addr*)host->h_addr_list[0]);
    memcpy(&server.sin_addr , host->h_addr_list[0] , host->h_length);
    int start_port = atoi(argv[2]);
    int end_port = atoi(argv[3]);
    if(end_port < start_port || start_port <= 0  || end_port > 65535)
    {
        printf("Invalid port range.\n");
        printf("Usage: %s <hostname> <start_port> <end_port>\n", argv[0]);
        return 1;
    }
    else if(start_port == end_port)
    {
        printf("Give me a range of ports!\n");
        return 1;
    }
    printf("Beginning the scan.....\n");
    printf("Hostname:%s\n",host->h_name);
    printf("IP:%s\n",ip);
    for(int port = start_port ; port <= end_port ; port++)
    {
        int socket_desc = socket(AF_INET , SOCK_STREAM  , 0);
        if(socket_desc == -1 )
        {
            printf("Couldnt create a socket!");
            return 1;
        }
        struct timeval timeout;
        server.sin_port = htons(port);
        timeout.tv_sec = 1;
        timeout.tv_usec = 0 ;
        setsockopt(socket_desc , SOL_SOCKET  , SO_RCVTIMEO , &timeout , sizeof(timeout));
        setsockopt(socket_desc , SOL_SOCKET , SO_SNDTIMEO , &timeout , sizeof(timeout));
        int connect_desc = connect(socket_desc , (struct sockaddr*)&server , sizeof(server));

        if(connect_desc  < 0)
        {
            printf("Port: %d is DOWN...\n",port);
        }
        else 
        {
            printf("Port: %d is UP...\n",port);
        }
        close(socket_desc);

    }
    printf("Scan Complete.\n");
}