#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include<pthread.h>
#define PORT 8080
#define BUFFERSIZE 100//1073741824
#define ITR 1

struct mem_segment_thread {
	long long start;
	long long end;
	int threads;
} struct_mem_thread[4];
char *workload; //1 GB of data
char *workloadCopy;
char rwaccess[5]; // Seqeuential or Random Access Type
char rwblocksize[12]; //Block Size
char rwthreads[5]; // Thread Count
char stringBlockSize[12]; //Block Size in characters
int noOfRuns; // Iterations
long long int latency;
int blockSz;
char *fileRead;
char *fileWrite;
char tmp1[100];
int threads_count;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
char buffer[BUFFERSIZE+1] = {0};
void* serverHandler(void *arg);
void* serverThread(void *arg);
void* clientThread(void *arg);
void* clientHandler(void *arg);
void* clientHandler(void *arg) {

    struct mem_segment_thread *x = (struct mem_segment_thread*) arg;
	long long t_start = (*x).start;
	long long t_end = (*x).end;
    int thread_no=(*x).threads;
    printf("Start %lld\n",t_start);
    printf("End %lld\n",t_end);
    //printf("Threads %d\n",thread_no);
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
        return (void*)-1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return (void*)-1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return (void*)-1;
    }
    int block;
    //pthread_mutex_lock(&lock);
    while(t_start<=t_end)
    {
            block=10;
            send(sock , &workload[t_start] , block , 0 );
            t_start=t_start+block;
    }
    printf("In Client Domain\n");
    printf("Client says: Workload sent\n");
    //printf("In Client Domain\n");
    while((valread = read( sock , buffer, BUFFERSIZE+1)>0)){
          printf("In Client Domain\n");
          printf("Server says: %s\n",buffer );
    }
    //pthread_mutex_unlock(&lock);
    exit(0);
    pthread_exit(0);

    return 0;
}

void* serverHandler(void *arg)
{
    int sock = *(int*)arg;
    char *hello = "Successfully Received Workload...";
    int valread;
    while(valread = read( sock , buffer, BUFFERSIZE+1)>0)
    {
        printf("In Server Domain\n");
        printf("Client Says:%s\n",buffer);
        send(sock,hello,strlen(hello),0);

    }
    close(sock);
    exit(0);
    pthread_exit(0);


}
void readFileData() {
	printf("Input File: %s\n", fileRead);
	printf("Output File: %s\n", fileWrite);
	FILE* inputFile;
	inputFile = fopen(fileRead, "r");

	if (inputFile == NULL) {
		perror("Error Storing Data");
	}

	int i = 0;
	while (!feof(inputFile) && i < 5) {
		if (i == 0) {
			fgets(rwaccess, 4, inputFile);
			printf("Protocol: %s\n", rwaccess);

		} else if (i == 1) {
			fgets(tmp1, 2, inputFile);
			//printf("Tmp:%s\n", tmp1);

		} else if (i == 2) {
			fgets(rwblocksize, 10, inputFile);
			printf("Block Size: %s\n", rwblocksize);

		} else if (i == 3) {
			fgets(tmp1, 1, inputFile);
			//printf("Tmp2:%s\n", tmp1);

		} else if (i == 4) {
			fgets(rwthreads, 2, inputFile);
			printf("Threads: %s\n", rwthreads);

		}
		i++;

	}
	//printf("\nMode:%s\n",rwaccess);
	fclose(inputFile);


}
int main(int argc, char const *argv[])
{
    printf("Hello....\nWelcome to the world of Network Benchmarking!!!!!!!\n");

	//Reading File
	//Reading File

	fileRead = argv[1];
	fileWrite = argv[2];
	readFileData();
	// Reading file completed
	blockSz = atoi(rwblocksize);
	threads_count = atoi(rwthreads);
    int threadsC;
	threadsC=atoi(rwthreads);
	//printf("Block Size :%d\n", blockSz);
	//printf("Threads :%d\n", threads_count);
	noOfRuns = ITR;

	if (blockSz == 1) {
		strcpy(stringBlockSize, "1B");
		workloadCopy = (char*) malloc(blockSz);

	} else if (blockSz == 1000) {
		strcpy(stringBlockSize, "1KB");
		workloadCopy = (char*) malloc(blockSz);
	} else if (blockSz == 32000) {
		strcpy(stringBlockSize, "32KB");
		workloadCopy = (char*) malloc(blockSz);
	}
    printf("Block Size in B,KB,MB: %s\n", stringBlockSize);
    workloadCopy = (char*) malloc(BUFFERSIZE + 1);
    workload = (char*) malloc(BUFFERSIZE + 1);
    for (int i = 0; i < BUFFERSIZE; i++) {
		workload[i] = 'A' + (rand() % 26);
	}

    pthread_t pthread_id[2];


    for(int i=0;i<2;i++)
    {
        if(i==0)
        pthread_create(&pthread_id[i],NULL,serverThread,(void*)threadsC);
            sleep(5);
        if(i==1)
        pthread_create(&pthread_id[i],NULL,clientThread,(void*)threadsC);
    }
    for(int i=0;i<2;i++)
    {
        if(i==0)
        pthread_join(pthread_id[i],NULL);
        if(i==1)
        pthread_join(pthread_id[i],NULL);
    }


    pthread_exit(NULL);
    free(workloadCopy);
	free(workload);
    exit(0);
    return 0;
}
void* clientThread(void *arg)
{
    int *t=(int*)arg;
    int threadsC=t;
    //printf("ThreadCount111--%d\n",threadsC);


	//printf("Threads in main() %d\n",threadsC);
    struct_mem_thread[0].start = 0;
	struct_mem_thread[0].end = BUFFERSIZE / threadsC  ;
	struct_mem_thread[0].threads=1;
    for(int i=1;i<threadsC;i++){
            struct_mem_thread[i].start=BUFFERSIZE / (double)((double)threadsC/(double)i) ;
            //printf("Atoi %lld\n",(double)((double)threadsC/(double)(i+1)));
            struct_mem_thread[i].end=BUFFERSIZE /(double)((double)threadsC/(double)(i+1));
            struct_mem_thread[i].threads=i+1;
            //printf("Start %lld\n",struct_mem_thread[i].start);
            //printf("End %lld\n",struct_mem_thread[i].end);
    }

    pthread_t pid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for (int i=0; i<threadsC; i++) {
        if( pthread_create( &pid, NULL ,  clientHandler , &struct_mem_thread[i]) < 0)
        {
            perror("Thread Creation Failed!!!!!!!");
            return (void*)-1;
        }
        sleep(3);
    }
    //pthread_mutex_destroy(&lock);
    pthread_join(pid,NULL);
    pthread_exit(0);
    exit(0);
}
void* serverThread(void *arg)
{
    int *t=(int*)arg;
    int threadsC=t;
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

    if (listen(server_fd, threadsC) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
        while (new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))
        {

            new_sock=malloc(1);
            *new_sock=new_socket;
            pthread_create(&pid,NULL,serverHandler,(void*)new_sock);

        }

    pthread_join(pid,NULL);

    pthread_exit(0);
    exit(0);

}

