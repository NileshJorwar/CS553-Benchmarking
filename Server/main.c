#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include<pthread.h>
#define PORT 8080
#define BUFFERSIZE 1000

struct socket_thread {
	int thread_count;
	int *socket_value;
} struct_mem_thread[4];
char buffer[BUFFERSIZE+1] = {0};
void* socketHandler(void *arg);
void* socketHandler(void *arg) {
    //struct socket_thread *x = (struct socket_thread*) arg;
    //int threads = (*x).thread_count;
    int sock = *(int*)arg;

    char *hello = "Successfully Received Workload...";
    int valread;

    while(valread = read( sock , buffer, 1024)>0)
    {
        printf("Client Says:%s\n",buffer);
        send(sock,hello,strlen(hello),0);
        printf("Received Workload...\n");
    }
    close(sock);
    pthread_exit(0);
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, *new_sock;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    pthread_t pid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, atoi(argv[1])) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

        while (new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))
        {

            new_sock=malloc(1);
            *new_sock=new_socket;
            //socket_thread[i].socket_value=malloc(1);
            //*socket_thread[i].socket_value=new_sock;
            //socket_thread[i].thread_count=atoi(argv[1]);
            pthread_create(&pid,NULL,socketHandler,(void*)new_sock);

        }

        pthread_join(pid,NULL);
        return 0;
}
