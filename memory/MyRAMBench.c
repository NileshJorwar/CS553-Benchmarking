#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<pthread.h>
#include<sys/time.h>
#include<time.h>
#define BUFFERSIZE 1073741824
#define BUFFERSIZEBYTE 100000000
#define ITR 100
struct mem_segment_thread {
	long long start;
	long long end;
} struct_mem_thread[4];
char *workload; //1 GB of data
char rwaccess[5]; // Seqeuential or Random Access Type
char rwblocksize[12]; //Block Size
char rwthreads[5]; // Thread Count
char stringBlockSize[12]; //Block Size in characters
int noOfRuns; // Iterations
double latency;
int blockSz;
int threads_count;
char *workloadCopy;
char *fileRead;
char *fileWrite;
char tmp1[100];
void* readWriteRWR(void* arg);
void readWrite();
int readWriteByteSequential();

/*
 readWrite() to check if to perform RWR or RWS operation
 */

void readWrite() {

	//printf("Block Size: %s\n", rwblocksize);
	printf("Access Type: %s\n", rwaccess);
	printf("No of Threads: %s\n", rwthreads);
	printf("Block Size in Integer: %d\n", blockSz);
	printf("Thread Count in Integer: %d\n", threads_count);

	if (strcmp(rwaccess, "RWR") == 0) {
		printf("Read/Write:RWR\n");
		readWriteByteSequential();
	}
	if (strcmp(rwaccess, "RWS") == 0) {
		printf("Read/Write:RWS\n");
		readWriteByteSequential();
	}
}
int readWriteByteSequential() {
	//Output file writing
	FILE* outputFile;
	outputFile = fopen(fileWrite, "a");
	if (outputFile == NULL) {
		perror("Error Opening File");
		return -1;
	}

	//printf("Block size and threads%d \t%d\t\n", blockSz,threads_count);
	pthread_t pid[threads_count];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	if(blockSz==1)
		{
		if (threads_count == 1) {

			struct_mem_thread[0].start = 0;
			struct_mem_thread[0].end = BUFFERSIZEBYTE;
		}

		if (threads_count == 2) {

			struct_mem_thread[0].start = 0;
			struct_mem_thread[0].end = BUFFERSIZEBYTE / 2;
			struct_mem_thread[1].start = (BUFFERSIZEBYTE / 2);
			struct_mem_thread[1].end = BUFFERSIZEBYTE;

		}
		if (threads_count == 4) {

			struct_mem_thread[0].start = 0;
			struct_mem_thread[0].end = BUFFERSIZEBYTE / 4;
			struct_mem_thread[1].start = (BUFFERSIZEBYTE / 4);
			struct_mem_thread[1].end = BUFFERSIZEBYTE / 2;
			struct_mem_thread[2].start = BUFFERSIZEBYTE / 2;
			struct_mem_thread[2].end = BUFFERSIZEBYTE / (4 / 3.0);
			struct_mem_thread[3].start = BUFFERSIZEBYTE / (4 / 3.0);
			struct_mem_thread[3].end = BUFFERSIZEBYTE;
		}
	}
	else{
		if (threads_count == 1) {

			struct_mem_thread[0].start = 0;
			struct_mem_thread[0].end = BUFFERSIZE;
		}

		if (threads_count == 2) {

			struct_mem_thread[0].start = 0;
			struct_mem_thread[0].end = BUFFERSIZE / 2;
			struct_mem_thread[1].start = (BUFFERSIZE / 2);
			struct_mem_thread[1].end = BUFFERSIZE;

		}
		if (threads_count == 4) {

			struct_mem_thread[0].start = 0;
			struct_mem_thread[0].end = BUFFERSIZE / 4;
			struct_mem_thread[1].start = (BUFFERSIZE / 4);
			struct_mem_thread[1].end = BUFFERSIZE / 2;
			struct_mem_thread[2].start = BUFFERSIZE / 2;
			struct_mem_thread[2].end = BUFFERSIZE / (4 / 3.0);
			struct_mem_thread[3].start = BUFFERSIZE / (4 / 3.0);
			struct_mem_thread[3].end = BUFFERSIZE;
		}
	
	}
	struct timeval timeNow, timeAfter;
	gettimeofday(&timeNow, NULL);
	for (int i = 0; i < threads_count; i++) {
		pthread_create(&pid[i], &attr, readWriteRWR, &struct_mem_thread[i]);
	}

	for (int i = 0; i < threads_count; i++) {
		pthread_join(pid[i], NULL);
	}

	gettimeofday(&timeAfter, NULL);
	double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
			- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
	double itr = ITR;
	double bffr = BUFFERSIZE;
	if (blockSz == 1) {
		latency = (time * 1000000)/1e8;
		double theoLatency=0.0004;
		printf("\nLatency: %f microseconds \n", latency);
		printf("Theoretical Latency: %f microseconds \n", theoLatency);
		fprintf(outputFile, "%s\t%s\t%s\t%f\t%f\t%f\n", rwaccess, rwthreads,
                                stringBlockSize, latency, theoLatency, (latency/theoLatency)*100);
	} else {
		double throughput = (((1.0 * itr * bffr) / time) / (1.0 * bffr));
		double theo1=(double)((2133*2*64*2)/8);
        double theoratical=(double)(theo1/1e3);
        printf("\nTheo Value: %f\n",theoratical);
        double eff=(double)(throughput/theoratical)*100;
		printf("Throughput:%f\n", throughput);
		printf("Computation Time:%f\n", time);
		printf("Efficiency: %f\n",eff);
		printf("Writing to the output file!!!!!!\n");
		fprintf(outputFile, "%s\t%s\t%s\t%f\t%f\t%f\n", rwaccess, rwthreads,
                                stringBlockSize, throughput, theoratical, eff);
	}
	fclose(outputFile);
	return 0;
}

void* readWriteRWR(void *arg) {

	struct mem_segment_thread *x = (struct mem_segment_thread*) arg;
	long long t_start = (*x).start;
	long long t_end = (*x).end;
	long long int random_var;
	if (blockSz == 1) {
		noOfRuns = 1;
	}
	
	//printf("Start and end: %lld\t%lld\n\n", t_start, t_end);
	for (int i = 0; i < noOfRuns; i++) {
		int j = t_start;
		if (strcmp(rwaccess, "RWS") == 0) {
			while (j < t_end) {
				memcpy(&workloadCopy[j], &workload[j], blockSz);
				j += blockSz;
			}
		}
		if (strcmp(rwaccess, "RWR") == 0) {
			srand(time(0));
			while (j < t_end) {
				random_var = rand() % ((t_end - blockSz) - t_start);
				memcpy(&workloadCopy[random_var], &workload[random_var],
						blockSz);
				j += blockSz;
			}
		}

	} 
	pthread_exit(0);
}
void readFileData() {
	printf("Input File: %s\n", fileRead);
	printf("Output File: %s\n", fileWrite);
	FILE* inputFile;
	inputFile = fopen(fileRead, "r");

	if (inputFile == NULL) {
		perror("Error Storing Data");
		return (void*)-1;
	}

	int i = 0;
	while (!feof(inputFile) && i < 5) {
		if (i == 0) {
			fgets(rwaccess, 4, inputFile);

		} else if (i == 1) {
			fgets(tmp1, 2, inputFile);

		} else if (i == 2) {
			fgets(rwblocksize, 10, inputFile);

		} else if (i == 3) {
			fgets(tmp1, 1, inputFile);

		} else if (i == 4) {
			fgets(rwthreads, 2, inputFile);

		}
		i++;

	}
	//printf("\nMode:%s\n",rwaccess);
	fclose(inputFile);
	return NULL;

}
int main(int argc, char **argv) {
	printf("Hello....\nWelcome to the world of Memory Benchmarking!!!!!!!\n");

	workload = (char*) malloc(BUFFERSIZE + 1);
	workloadCopy = (char*) malloc(BUFFERSIZE + 1);
	//Reading File
	fileRead = argv[1];
	fileWrite = argv[2];
	readFileData();
	// Reading file completed
	blockSz = atoi(rwblocksize);
	threads_count = atoi(rwthreads);
	noOfRuns = ITR;
	if (blockSz == 1)
		strcpy(stringBlockSize, "1B");
	else if (blockSz == 1000)
		strcpy(stringBlockSize, "1KB");
	else if (blockSz == 1000000)
		strcpy(stringBlockSize, "1MB");
	else if (blockSz == 10000000)
		strcpy(stringBlockSize, "10MB");
	printf("Block Size in B,KB,MB: %s\n", stringBlockSize);
	/*Another way to write workload using for loop*/

	memset(workload,"ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26],BUFFERSIZE);
	/*
	for (int i = 0; i < BUFFERSIZE; i++) {
		workload[i] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26];
	}
	*/
	readWrite();
	free(workloadCopy);
	free(workload);

}
