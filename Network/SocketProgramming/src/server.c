#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUF_LEN 128

void exit_with_errmsg(char* host, char* err, char* msg);

int main(int argc, char* argv[]) 
{
    char buffer[BUF_LEN];
    struct sockaddr_in server_addr, client_addr;
    int server_fd, client_fd;
    int len, msg_size;
    char temp[20];
    char optval[32];

    if (argc != 2)
    {
        printf("Usage : ./%s [PORT] \n", argv[0]);
        exit(0);
    }

    // 1. open socket.
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
        exit_with_errmsg("server", "socket error", "cannot open socket");

    // set socket option
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));

    // 2. bind socket.
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        exit_with_errmsg("server", "bind error", "cannot bind address");
    

    // 3. start to listen.
    if (listen(server_fd, 5) < 0)
        exit_with_errmsg("server", "listen", "cannot listen connection");

    memset(buffer, 0x00, sizeof(buffer));
    strcpy(buffer, "test test test");
    len =  sizeof(client_addr);

    printf("======== [PORT] : %d ========\n", atoi(argv[1]));
    printf("[server] : waiting connection request... \n\n");

    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&len)) < 0)
        exit_with_errmsg("server", "accept", "accept failed");
    inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));

    printf("[server] %s client is connected. \n", temp);

    // send message in infinite loop.
    int i = 1;
    while (i++)
    {
        if (send(client_fd, buffer, BUF_LEN, 0) < 0)
            printf("%s\n", strerror(errno));
        printf("[%d] send data \n" ,i);
    }
    close(client_fd);
    printf("[server] %s client is closed. \n\n", temp);
    close(server_fd);

    return 0;
}

void exit_with_errmsg(char* host, char* err, char* msg)
{
    // [host]   err내용     err 메세지
    printf("[%-5s]\t%-15s\t%-25s\n", host, err, msg);
    exit(0);
}