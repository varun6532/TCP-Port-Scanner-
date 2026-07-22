#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() 
{
   
    struct sockaddr_in server;
   
    server.sin_family=AF_INET;
    server.sin_addr.s_addr = inet_addr("192.178.177.138");
    for(int port = 1 ; port <= 100 ; port++)
    {
        int socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if(socket_desc == -1)
        {
            printf("Couldnt create a socket....\n");
            return 1;
        }
        server.sin_port = htons(port);
        int connect_desc = connect(socket_desc , (struct sockaddr*)&server , sizeof(server));
        if(connect_desc < 0)
        {
            printf("IP:192.178.177.138 , Port: %d is closed...\n" ,port);

        }
        else 
        {
            printf("IP:IP:192.178.177.138 , Port: %d is open...\n" ,port);
        }
        close(socket_desc);
    }

   
}