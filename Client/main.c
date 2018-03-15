#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
#define BUFFERSIZE 1000
struct mem_segment_thread {
	long long start;
	long long end;
	int threads;
} struct_mem_thread[4];
char *workload; //1 GB of data
char *workloadCopy;
void* socketHandler(void *arg);
void* socketHandler(void *arg) {
    struct mem_segment_thread *x = (struct mem_segment_thread*) arg;
	long long t_start = (*x).start;
	long long t_end = (*x).end;
    int thread_no=(*x).threads;
    printf("Start %lld\n",t_start);
    printf("End %lld\n",t_end);
    printf("Threads %d\n",thread_no);
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[] = "Client Hello";
    char *b = ""+thread_no;
    char arr[2];
    sprintf(arr,"%d",thread_no);
    strcat(hello,arr);
    //printf("Message: %s\n",hello);

    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    int block;
    while(t_start<t_end)
    {
            block=100;

            send(sock , &workload[t_start] , block+1 , 0 );
            t_start=t_start+block;
    }

    printf("Client: Workload sent\n");
    valread = read( sock , buffer, 1024);
    printf("Server: %s\n",buffer );
    pthread_exit(0);
    return 0;
}
int main(int argc, char const *argv[])
{
    workloadCopy = (char*) malloc(BUFFERSIZE + 1);
    workload = (char*) malloc(BUFFERSIZE + 1);
    for (int i = 0; i < BUFFERSIZE; i++) {
		workload[i] = 'A' + (rand() % 26);
	}

	printf("Threads in main() %d\n",atoi(argv[1]));
    struct_mem_thread[0].start = 0;
	struct_mem_thread[0].end = BUFFERSIZE / atoi(argv[1])  ;
	struct_mem_thread[0].threads=1;
    for(int i=1;i<atoi(argv[1]);i++){
            struct_mem_thread[i].start=BUFFERSIZE / (double)((double)atoi(argv[1])/(double)i) ;
            printf("Atoi %lld\n",(double)((double)atoi(argv[1])/(double)(i+1)));
            struct_mem_thread[i].end=BUFFERSIZE /(double)((double)atoi(argv[1])/(double)(i+1));
            struct_mem_thread[i].threads=i+1;
            //printf("Start and end in (): %lld\t%lld\n",struct_mem_thread[i].start,struct_mem_thread[i].end);
    }

    pthread_t pid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for (int i=0; i<atoi(argv[1]); i++) {
        if( pthread_create( &pid, NULL ,  socketHandler , &struct_mem_thread[i]) < 0)
        {
            perror("Thread Creation Failed!!!!!!!");
            return 1;
        }
        sleep(3);
    }
    return 0;
}
