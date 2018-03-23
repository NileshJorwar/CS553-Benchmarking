#include <dirent.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<immintrin.h>
#include<sys/time.h>
#define KAXLINE 12
#define ITR 1000000000000
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
 computeGops() method is used to compute the Gops of each operation HP,QP,DP.SP
 */
void computeGops(double ops, double time, int countThread, char* precValue) { 
	//Output file writing
	FILE* outputFile;
	outputFile = fopen(fileWrite, "a+");
	if (outputFile == NULL) {
		perror("Error Opening File");
		//return (void*)-1;
	}

	double gigaflops = (double) (((ITR ) / time) / 1000000000.0);
    //double theo1=(double)((2.3*2*ops));
    double theoretical=(double)((2.3*2*ops));
    double eff=(double)(gigaflops/theoretical)*100;	
    printf("Theoretical Value: %f\n",theoretical);
    printf("Computation Time: %f\n", time);
	printf("Gigaflops: %f\n", gigaflops);
	printf("Efficiency: %f\n",eff);
    printf("Writing to the output file!!!!!!\n");
	fprintf(outputFile, "%s\t%d\t%f\t%f\t%f\n", precValue, countThread,
			gigaflops, theoretical, eff);
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
	computeGops(128, time, threadsNumber, "QP");

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
	computeGops(64, time, threadsNumber, "HP");

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
	computeGops(16, time, threadsNumber, "DP");

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
	computeGops(32, time, threadsNumber, "SP");

	return 0;
}
void* computeSP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	__m256 computeValue1=_mm256_set_ps(1.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2);
	__m256 computeValue2=_mm256_set_ps(2.2,2.2,2.2,2.2,2.2,2.2,2.2,2.2);
    __m256 computeValue3=_mm256_set_ps(3.2,3.2,3.2,3.2,3.2,3.2,3.2,3.2);

	for (long long z = 0; z < v/(32); z++) {
        __m256 result = _mm256_fmadd_ps(computeValue1,computeValue2,computeValue3);
        }
	printf("Computation in SP done\n");
	pthread_exit(0);
}
void* computeDP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	//printf("Itr:%lld\n",v);
	__m256d computeValue1=_mm256_set_pd(1.2,1.2,1.2,1.2);
	__m256d computeValue2=_mm256_set_pd(2.2,2.2,2.2,2.2);
    __m256d computeValue3=_mm256_set_pd(3.2,3.2,3.2,3.2);
	for (long long z = 0; z < v/(16); z++) {
		__m256d result = _mm256_fmadd_pd(computeValue1,computeValue2,computeValue3);
		__m256d result1 = _mm256_fmadd_pd(computeValue2,computeValue1,computeValue3);
	}
	printf("Computation in DP done\n");

	pthread_exit(0);
}
void* computeHP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	__m256i computeValue1=_mm256_set_epi16(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
	__m256i computeValue2=_mm256_set_epi16(2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2);


	for (long long z = 0; z < v/(32); z++) {
		__m256i result = _mm256_add_epi16(computeValue1,computeValue2);
	}
	printf("Computation in HP done\n");
	pthread_exit(0);
}
void* computeQP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	__m256i computeValue1=_mm256_set_epi8('a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a');
	__m256i computeValue2=_mm256_set_epi8('b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b');

	for (long long z = 0; z < v/(128); z++) {
		__m256i result = _mm256_add_epi8(computeValue1,computeValue2);
	}
	printf("Computation in QP \n");
	pthread_exit(0);
}

void readFileData() {
	printf("Input File: %s\n", fileRead);
	printf("Output File: %s\n", fileWrite);
	FILE* inputFile;
	inputFile = fopen(fileRead, "r");

	if (inputFile == NULL) {
		perror("Error Storing Data");
		//return (void*)-1;
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

