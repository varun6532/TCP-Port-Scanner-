#include<stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include<netdb.h>
#include <sys/time.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
struct port_range
{
    int start_port;
    int end_port;
    char *ip ;
    struct sockaddr_in server;
};

void * ScannerFxn(void * arg)
{
    struct port_range *range = (struct port_range *)arg;
    for(int port = range->start_port ; port <= range->end_port ;  port++)
    {
        int socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if(socket_desc < 0 )
        {
            printf("Couldnt create a socket!!!\n");
            return NULL;

        }
        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        setsockopt(socket_desc , SOL_SOCKET , SO_RCVTIMEO , &timeout , sizeof(timeout));
        setsockopt(socket_desc , SOL_SOCKET , SO_SNDTIMEO , &timeout , sizeof(timeout));
        range->server.sin_port = htons(port);
        int connet_desc = connect(socket_desc , (struct sockaddr*)&range->server , sizeof(range->server));  
        if(connet_desc < 0)
        {
           // printf("Port:%d is down...\n",port);
            
        }      
        else
        {
            printf("Port:%d is up...\n",port);
        }
        close(socket_desc);   
    }
}
int main(int argc , char * argv[])
{
    if(argc < 4)
    {
        printf("Not Enough Arguments!!!\n");
    }
    struct sockaddr_in server;
    struct port_range ranges[4];
    pthread_t thread[4];
    struct hostent *host = gethostbyname(argv[1]);
    if(host == NULL)
    {
        printf("Couldn't find the host\n");
        return 1;
    }
    server.sin_family = AF_INET ;
    memcpy(&server.sin_addr,host->h_addr_list[0],host->h_length);
    char * ip = inet_ntoa(*(struct in_addr*)host->h_addr_list[0]);
    int start_port = atoi(argv[2]);
    int end_port = atoi(argv[3]);
    int chunk_size =( end_port - start_port + 1 ) / 4;
    for(int i = 0 ; i < 4 ; i++ )
    {
        ranges[i].start_port = start_port + chunk_size * i;
        ranges[i].end_port = ranges[i].start_port + chunk_size - 1;
    }
    printf("Beginning the scan!\n");
    printf("Hostname:%s\n",host->h_name);
    printf("IP:%s\n" ,ip);
    for(int i  = 0  ; i < 4 ; i++)
    {
        ranges[i].server = server;
        pthread_create(&thread[i],NULL,ScannerFxn,&ranges[i]);
    }
    for(int i = 0 ; i <4 ; i++ )
    {
        pthread_join(thread[i],NULL);
    }
    printf("Scan Complete\n");
    return 0;
}