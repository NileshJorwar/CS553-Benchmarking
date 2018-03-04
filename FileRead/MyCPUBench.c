#include <dirent.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/time.h>
#define KAXLINE 12
#define ITR 2000000000
struct Operations {
	char precisionOp[10];
	char numberOfThreads[5];
} op;
char *fileRead;
char *fileWrite;
//Following methods declaration for the computation of GOPS and computation time
void* computeSP(void* arg);
void* computeDP(void* arg);
void* computeHP(void* arg);
void* computeQP(void* arg);
int performSP(char* precOp, char* threadsCount);
int performDP(char* precOp, char* threadsCount);
int performHP(char* precOp, char* threadsCount);
int performQP(char* precOp, char* threadsCount);
void computeGops(double ops, double time, int countThread, char* precValue);

/*
 computeGops() method is used to compute the Gops of each precision HP,QP,DP.SP
 */
void computeGops(double ops, double time, int countThread, char* precValue) { //Output file writing
	FILE* outputFile;
	outputFile = fopen(fileWrite, "a");
	if (outputFile == NULL) {
		perror("Error Opening File");
		//return -1;
	}
	double gigaflops = (double) (((ITR * ops) / time) / 1000000000.0);
	fprintf(outputFile, "%s\t%d\t%f\t%f\t%d\n", precValue, countThread,
			gigaflops, 0.0, 100);
	printf("Computation Time %f\n", time);
	printf("Gigaflops %f\n", gigaflops);
	printf("...........................................\n");
	fclose(outputFile);
}

int perform(char* precOp, char* threadsCount) {
	char *p;
	p = precOp;
	if (strstr(p, "SP")) {
		performSP(precOp, threadsCount);
	} else if (strstr(p, "QP")) {
		performQP(precOp, threadsCount);
	} else if (strstr(p, "DP")) {
		performDP(precOp, threadsCount);
	} else if (strstr(p, "HP")) {
		performHP(precOp, threadsCount);
	}
	return 0;
}
int performQP(char* precOp, char* threadsCount) {
	int threadsNumber = atoi(threadsCount);
	pthread_t pid[threadsNumber];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	long long iterations;
	if (threadsNumber == 1) {
		iterations = ITR;
	}
	if (threadsNumber == 2) {
		iterations = ITR / 2;
	}
	if (threadsNumber == 4) {
		iterations = ITR / 4;
	}
	struct timeval timeNow, timeAfter;
	gettimeofday(&timeNow, NULL);
	for (int i = 0; i < threadsNumber; i++) {
		pthread_create(&pid[i], &attr, computeQP, &iterations);
	}

	for (int i = 0; i < threadsNumber; i++) {
		pthread_join(pid[i], NULL);
	}
	gettimeofday(&timeAfter, NULL);
	double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
			- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
	computeGops(5, time, threadsNumber, "QP");

	return 0;
}
int performHP(char* precOp, char* threadsCount) {
	int threadsNumber = atoi(threadsCount);
	pthread_t pid[threadsNumber];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	long long iterations;
	if (threadsNumber == 1) {
		iterations = ITR;
	}
	if (threadsNumber == 2) {
		iterations = ITR / 2;
	}
	if (threadsNumber == 4) {
		iterations = ITR / 4;
	}
	struct timeval timeNow, timeAfter;
	gettimeofday(&timeNow, NULL);
	for (int i = 0; i < threadsNumber; i++) {
		pthread_create(&pid[i], &attr, computeHP, &iterations);
	}

	for (int i = 0; i < threadsNumber; i++) {
		pthread_join(pid[i], NULL);
	}
	gettimeofday(&timeAfter, NULL);
	double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
			- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
	computeGops(5, time, threadsNumber, "HP");

	return 0;
}
int performDP(char* precOp, char* threadsCount) {
	int threadsNumber = atoi(threadsCount);
	pthread_t pid[threadsNumber];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	long long iterations;
	if (threadsNumber == 1) {
		iterations = ITR;
	}
	if (threadsNumber == 2) {
		iterations = ITR / 2;
	}
	if (threadsNumber == 4) {
		iterations = ITR / 4;
	}
	struct timeval timeNow, timeAfter;
	gettimeofday(&timeNow, NULL);
	for (int i = 0; i < threadsNumber; i++) {
		pthread_create(&pid[i], &attr, computeDP, &iterations);
	}

	for (int i = 0; i < threadsNumber; i++) {
		pthread_join(pid[i], NULL);
	}
	gettimeofday(&timeAfter, NULL);
	double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
			- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
	computeGops(5, time, threadsNumber, "DP");

	return 0;
}
int performSP(char* precOp, char* threadsCount) {
	int threadsNumber = atoi(threadsCount);
	pthread_t pid[threadsNumber];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	long long iterations;
	if (threadsNumber == 1) {
		iterations = ITR;
	}
	if (threadsNumber == 2) {
		iterations = ITR / 2;
	}
	if (threadsNumber == 4) {
		iterations = ITR / 4;
	}
	struct timeval timeNow, timeAfter;
	gettimeofday(&timeNow, NULL);
	for (int i = 0; i < threadsNumber; i++) {
		pthread_create(&pid[i], &attr, computeSP, &iterations);
	}

	for (int i = 0; i < threadsNumber; i++) {
		pthread_join(pid[i], NULL);
	}
	gettimeofday(&timeAfter, NULL);
	double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
			- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
	computeGops(5, time, threadsNumber, "SP");

	return 0;
}
void* computeSP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	int computeValue1 = 10000;
	int computeValue2 = 20000;
	int result = 0;
	/*
	 No of operations =5
	 1 z increments
	 3 addition
	 1 division
	 */
	for (long long z = 0; z < v; z++) {
		result = (computeValue1 + computeValue2)
				/ (computeValue1 - computeValue2) + (2000);
	}
	printf("Computation in SP %d\n", computeValue1);
	pthread_exit(0);
}
void* computeDP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	double computeValue1 = 550.450;
	double computeValue2 = 990.05;
	double result = 0;
	/*
	 No of operations =5
	 1 z increments
	 3 addition
	 1 division
	 */
	for (long long z = 0; z < v; z++) {
		result = (computeValue1 + computeValue2)
				/ (computeValue1 - computeValue2) + (450.12);
	}
	printf("Computation in DP %.2f\n", result);

	pthread_exit(0);
}
void* computeHP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	short computeValue1 = 600;
	short computeValue2 = 12;
	short computeValue3;
	/*
	 No of operations =5
	 1 z increments
	 3 addition
	 1 division
	 */
	for (long long z = 0; z < v; z++) {
		computeValue3 = 100 + 500 + 50 + computeValue1 / computeValue2;
	}
	printf("Computation in HP %hu\n", computeValue3);
	pthread_exit(0);
}
void* computeQP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	char computeValue1 = 'z';
	char computeValue2 = 10;
	char computeValue3;
	/*
	 No of operations =5
	 2 cast
	 1 subtraction
	 1 z increments
	 1 final cast
	 */
	for (long long z = 0; z < v; z++) {
		computeValue3 = computeValue1 - computeValue2;
	}
	printf("Computation in QP %c\n", computeValue3);
	pthread_exit(0);
}

void readFileData() {
	printf("Input File: %s\n", fileRead);
	printf("Output File: %s\n", fileWrite);
	FILE* inputFile;
	inputFile = fopen(fileRead, "r");

	if (inputFile == NULL) {
		perror("Error Storing Data");
		//return -1;
	}

	int i = 0;
	while (!feof(inputFile) && i < 2) {
		if (i == 0) {
			fgets(op.precisionOp, sizeof(KAXLINE), inputFile);
		} else if (i == 1) {
			fgets(op.numberOfThreads, sizeof(KAXLINE), inputFile);
		}
		i++;
	}
	//printf("\nMode:%s\n",rwaccess);
	fclose(inputFile);
	//return NULL;
}

int main(int argc, char **argv) {
	printf("Hello....\nWelcome to the world of CPU Benchmarking!!!!!!!\n");

	//Reading File
	fileRead = argv[1];
	fileWrite = argv[2];
	readFileData();
	// Reading file completed
	//printf("Threads :%s Operation: %s\n",op.numberOfThreads,op.precisionOp);
	perform(op.precisionOp, op.numberOfThreads);
}

