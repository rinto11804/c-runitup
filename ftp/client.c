#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
// #include<netdb.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define TCP_PORT 5035
#define MAX 60

int main() {
    int clientsocket, n;
    struct sockaddr_in serveraddr;
    char send[MAX], recvline[MAX];
    
    // Create socket
    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Configure server address
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost
    serveraddr.sin_port = htons(TCP_PORT);
    
    // Connect to server
    connect(clientsocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    
    // Send filename
    printf("Enter the source file name: ");
    scanf("%s", send);
    write(clientsocket, send, MAX);
    
    // Receive and display file contents
    while((n = read(clientsocket, recvline, MAX)) != 0) {
        printf("%s", recvline);
    }
    
    close(clientsocket);
    return 0;
}