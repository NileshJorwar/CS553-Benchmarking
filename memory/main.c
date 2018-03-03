#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<pthread.h>
#include<sys/time.h>
#include<time.h>
#define BUFFERSIZE 1000000000
#define ITR 100
struct thread_arg_struct {
	char blockSize[12];
	char numberOfThreads[1];
	char accessReadWrite[3];
} struct_thread;
struct mem_segment_thread {
	long long start;
	long long end;
} struct_mem_thread[4];
char *workload;
char *workloadCopy;
void* readWriteRWR(void* arg);
void readWrite(char **accessPattern, char **block_size, char **threadCount);
int readWriteByteSequential(char **block_size, char **threadCount);

void readWrite(char **accessPattern, char **block_size, char **threadCount) {
	char *accessPt;

	printf("Read/Write Access %s\n", accessPattern);
	accessPt = accessPattern;
	if (strstr(accessPt, "RWR")) {
		printf("Read/Write:RWR\n");
		readWriteByteSequential(block_size, threadCount);
	}
	if (strstr(accessPt, "RWS")) {
		printf("Read/Write:RWS\n");
		readWriteByteSequential(block_size, threadCount);
	}
}
int readWriteByteSequential(char **block_size, char **threadCount) {
	int threadsNumber = atoi(threadCount);

	printf("Block size and threads%s \t%d\t\n", struct_thread.blockSize,
			threadsNumber);
	pthread_t pid[threadsNumber];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	if (threadsNumber == 1) {
		printf("Thread 1");
		struct_mem_thread[0].start = 0;
		struct_mem_thread[0].end = BUFFERSIZE;
	}

	if (threadsNumber == 2) {
		printf("Thread 2");
		struct_mem_thread[0].start = 0;
		struct_mem_thread[0].end = BUFFERSIZE / 2;
		struct_mem_thread[1].start = (BUFFERSIZE / 2);
		struct_mem_thread[1].end = BUFFERSIZE;

	}
	if (threadsNumber == 4) {
		printf("\nThread 4\n");
		struct_mem_thread[0].start = 0;
		struct_mem_thread[0].end = BUFFERSIZE / 4;
		struct_mem_thread[1].start = (BUFFERSIZE / 4);
		struct_mem_thread[1].end = BUFFERSIZE / 2;
		struct_mem_thread[2].start = BUFFERSIZE / 2;
		struct_mem_thread[2].end = BUFFERSIZE / (4 / 3.0);
		struct_mem_thread[3].start = BUFFERSIZE / (4 / 3.0);
		struct_mem_thread[3].end = BUFFERSIZE;
	}
	struct timeval timeNow, timeAfter;
	gettimeofday(&timeNow, NULL);
	for (int i = 0; i < threadsNumber; i++) {
		pthread_create(&pid[i], &attr, readWriteRWR, &struct_mem_thread[i]);
	}

	for (int i = 0; i < threadsNumber; i++) {
		pthread_join(pid[i], NULL);
	}

	gettimeofday(&timeAfter, NULL);
	double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
			- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
	double itr = ITR;
	double bffr = BUFFERSIZE;
	//printf("Itrc& Buffer %f \t% f", itr, bffr);
	double throughput = (((1.0 * itr * bffr) / time) / (1.0*bffr));
	printf("\nThrouhput:%f\n", throughput);
	printf("Computation Time:%f\n", time);
	return 0;
}

void* readWriteRWR(void *arg) {

	struct mem_segment_thread *x = (struct mem_segment_thread*) arg;
	long long t_start = (*x).start;
	long long t_end = (*x).end;
	printf("Start and end: %lld\t%lld\n\n", t_start, t_end);
	char *accessRW = struct_thread.accessReadWrite;
	//printf("Accessrw%s",accessRW);
	//printf("Block size%s",struct_thread.blockSize);
	int blockSize = atoi(struct_thread.blockSize);
	//printf("Block size%d",blockSize);
	long long int random_var;
	//int noOfthreads = atoi(struct_thread.numberOfThreads);

	printf("Hiiiiiiii\n");
	for (int i = 0; i < ITR; i++) {
		//              printf("i:%d ", i);
		int j = t_start;

		if (strstr(accessRW, "RWS")) {
			while (j < t_end) {
				memcpy(&workloadCopy[j], &workload[j], blockSize);
				j += blockSize;
			}
		}
		if (strstr(accessRW, "RWR")) {
			srand(time(0));
			while (j < t_end) {
				random_var = rand() % ((t_end - blockSize) - t_start);
				//printf("Random %lld",random_var);
				memcpy(&workloadCopy[random_var], &workload[random_var],
						blockSize);
				j += blockSize;
			}
		}

	} // For Loop
//		printf("\nHi at the end--\n");
	printf("Element at : %c %c", workload[0], workloadCopy[0]);
	pthread_exit(0);
}

int main(int argc, char **argv) {
	printf("Hello\n");
	workload = (char*) malloc(BUFFERSIZE + 1);
	workloadCopy = (char*) malloc(BUFFERSIZE + 1);
	//argv[1] = "RWS", argv[2] = "1000000", argv[3] = "4";
	printf("%s", argv[1]);
	char *blockArr = argv[2];
	//memset(workload,"ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26],BUFFERSIZE);
	/*Another way to write workload using for loop*/

	for (int i = 0; i < BUFFERSIZE; i++) {
		workload[i] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26];
	}

	strcpy(struct_thread.blockSize, blockArr);
	strcpy(struct_thread.numberOfThreads, argv[3]);
	strcpy(struct_thread.accessReadWrite, argv[1]);
	readWrite(argv[1], argv[2], argv[3]);
	free(workloadCopy);
	free(workload);

}

