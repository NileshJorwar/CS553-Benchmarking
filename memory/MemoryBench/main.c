#include <dirent.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/time.h>
#define ITR 100
#define KAXLINE 12
#define MEMSIZE 1000000000
struct Operations {
	char blockSize[2];
	char numberOfThreads[1];
} op;

//Following methods declaration for the computation of GOPS and computation time
void* readWriteByte(void* arg);
int readWriteByteSequential(char* precOp, char* threadsCount, FILE* fout);

int perform(char* precOp, char* threadsCount, FILE* fout) {
	char *p;
	p = precOp;
	if (strstr(p, "1")) {
		readWriteByteSequential(precOp, threadsCount, fout);
	}
	return 0;
}
int readWriteByteSequential(char* precOp, char* threadsCount, FILE* fout) {
	int threadsNumber = atoi(threadsCount);

	if (threadsNumber == 1) {
		pthread_t pid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		//pthread_create(&pid, &attr, readWriteByte, &iterations);
		//pthread_join(pid, NULL);
		gettimeofday(&timeAfter, NULL);
		printf("Hiiii");
		fprintf(fout,"%s","Hi");
//		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
//				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
//		computeGops(5,time,threadsNumber,"QP", fout);

	}
	if (threadsNumber == 2) {
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 2;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, readWriteByte, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
		gettimeofday(&timeAfter, NULL);
		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
		//Performing 5 operations; 5 ops are multiplied by iterations
	//	computeGops(5,time,threadsNumber,"QP", fout);

	}
	if (threadsNumber == 4) {
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 4;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, readWriteByte, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
		gettimeofday(&timeAfter, NULL);
		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
		//computeGops(5,time,threadsNumber,"QP", fout);
	}
	return 0;
}
void* readWriteByte(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	int computeValue1 = 10000;
	int computeValue2 = 20000;
	int result=0;
		/*
	No of operations =5
	1 z increments
	3 addition
	1 division
    */
	for (long long z = 0; z < v; z++) {
		result = (computeValue1+computeValue2) / (computeValue1-computeValue2) + (2000) ;
	}
	printf("Computation in SP %d\n", computeValue1);
	pthread_exit(0);
}
int main(){
	DIR *directoryReadPtr;
	struct dirent *dir;
	directoryReadPtr = opendir(".");
	if (directoryReadPtr == NULL) {
		printf("No Files Available");
		exit(1);
	} //main if close
	int i;
	char *workload;
    workload = (char *) malloc(MEMSIZE);
    printf("Size of char%d",_workload);

	FILE *fout; // Output file
	fout = fopen(".\output\memory-RWR-1-1thread.out.dat", "a");
	if (fout == NULL) {
		perror("Error Storing Data");
		return -1;
	}
	while ((dir = readdir(directoryReadPtr)) != NULL) {
		if (strstr(dir->d_name, ".dat") != NULL) {
			i = 0;
			FILE *fp;
			fp = fopen(dir->d_name, "r");
			//Printing the name of input .dat file
			printf("Input File:%s\n", dir->d_name);
            perform("1", "1", fout);
			while (!feof(fp) && i < 2) {
				if (i == 0) {
					fgets(op.blockSize, sizeof(KAXLINE), fp);

				} else if (i == 1) {
					fgets(op.numberOfThreads, sizeof(KAXLINE), fp);
					//iterate over the data of each .dat file
					//call perform to perform computations using the pthreads
					perform(op.blockSize, op.numberOfThreads, fout);
				}
				i++;
			}
			fclose(fp);

		} //if strstr closed
	} // while closed

	closedir(directoryReadPtr);
	//closing the output file after write
	fclose(fout);

	return 0;
} // int main closed
