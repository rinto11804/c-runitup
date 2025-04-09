#include <stdio.h>
#include <stdlib.h>

#include<netinet/in.h>
#include<sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


int main() {
    struct sockaddr_in serveraddr,clientaddr;
    int serversocket = socket(AF_INET,SOCK_DGRAM,0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    int addrlen = sizeof(serveraddr);
    bind(serversocket,(struct sockaddr*)&serveraddr,addrlen);

    // listen(serversocket,5);

    // int clength = sizeof(clientaddr);
    // int clientsocket = accept(serversocket,(struct sockaddr*)&clientaddr,&clength);

    socklen_t  serveraddrlen = sizeof(serveraddr);
    while (1) {
        char msg[100];
        recvfrom(serversocket,&msg,sizeof(msg),0,(struct sockaddr*)&serveraddr,&serveraddrlen);
        printf("%s",msg);
    }

    // close(clientsocket);
    close(serversocket);

}