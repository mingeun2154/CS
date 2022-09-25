#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024
// hard codig
// #define PORT 1234
// #define IPADDR "127.0.0.1"

void exit_with_errmsg(char* host, char* err, char* msg);

int main(int argc, char* argv[])
{
    char* SERVER_IP;
    char* SERVER_PORT;
    int client_fd, len;
    struct sockaddr_in server_addr, client_addr;
    char recv_data[BUF_SIZE];

    if (argc != 3)
    {
        printf("Usage : ./%s [server ip] [server port] \n", argv[0]);
        exit(0);
    }

    SERVER_IP = argv[1];
    SERVER_PORT = argv[2];

    client_fd = socket(PF_INET, SOCK_STREAM, 0);

    client_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(atoi(SERVER_PORT));


    if (connect(client_fd, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0)
    {
        close(client_fd);
        exit_with_errmsg("client", "connect", "cannot connect");
    }

    int i=1;
    while(i++) 
    {
        recv(client_fd, recv_data, sizeof(recv_data), 0);
        printf("[%d] recv data : %s\n", i, recv_data);

        memset(recv_data, 0, sizeof(recv_data));
    }

    close(client_fd);


    return 0;

}

void exit_with_errmsg(char* host, char* err, char* msg)
{
    // [host]   err내용     err 메세지
    printf("[%-5s]\t%-15s\t%-25s\n", host, err, msg);
    exit(0);
}