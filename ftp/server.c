#include<stdio.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
// #include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define TCP_PORT 5035
#define MAX 60

int main() {
    int serversocket, clientsocket, clength;
    struct sockaddr_in serveraddr, clientaddr;
    char buff[MAX], t[MAX], str[MAX];
    
    // Create socket
    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Configure server address
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(TCP_PORT);
    
    // Bind and listen
    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(serversocket, 5);
    
    // Accept connection
    clength = sizeof(clientaddr);
    clientsocket = accept(serversocket, (struct sockaddr*) &clientaddr, &clength);
    close(serversocket); // Close listening socket
    
    // Receive filename from client
    read(clientsocket, &str, MAX);
    printf("\nClient requested file: %s\n", str);
    
    // Open and send file
    FILE *f1 = fopen(str, "r");
    while(fgets(buff, 4096, f1) != NULL) {
        write(clientsocket, buff, MAX);
    }
    fclose(f1);
    
    printf("File Transferred\n");
    return 0;
}