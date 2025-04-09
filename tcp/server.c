#include <stdio.h>
#include <stdlib.h>

#include<netinet/in.h>
#include<sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


int reverse_num(int num) {
    int d;int rev = 0;
    while(num > 0) {
        d = num % 10;
        rev = (rev * 10) + d;
        num = num / 10;
    }

    return rev;
}

int is_prime(int num) {
    for(int i =2; i <= (int)(num /2)+1;i++) {
        if(num % i == 0){
            return 0;
        }
    }
    return 1;
}

int main() {
    struct sockaddr_in serveraddr,clientaddr;
    int serversocket = socket(AF_INET,SOCK_STREAM,0);
    int num;

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    int addrlen = sizeof(serveraddr);
    bind(serversocket,(struct sockaddr*)&serveraddr,addrlen);

    listen(serversocket,5);

    int clength = sizeof(clientaddr);
    int clientsocket = accept(serversocket,(struct sockaddr*)&clientaddr,&clength);

    // while (1) {
        char prime_no[] = "is prime no";
        char not_prime[] = "not prime no";
        recv(clientsocket,&num,sizeof(num),0);
        printf("%d",num);


        if (is_prime(num)) {
            send(clientsocket,&prime_no,sizeof(prime_no),0);
        }else {
            send(clientsocket,&not_prime,sizeof(not_prime),0);
        }

    // }

    close(clientsocket);
    close(serversocket);

}