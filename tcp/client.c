#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main() {
    struct sockaddr_in serveraddr;
    
    int clientsocket = socket(AF_INET,SOCK_STREAM,0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientsocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

    
    // char msg[100];
    int num;
    // while(1){

        printf("Enter the number:");
        scanf("%d",&num);
        printf("%d",num);
        send(clientsocket,&num,sizeof(num),0);

        char msg[100];
        recv(clientsocket,&msg,sizeof(msg),0);
        printf("%s",msg);
        
    // }

    close(clientsocket);

}