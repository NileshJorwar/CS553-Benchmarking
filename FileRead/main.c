#include <dirent.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/time.h>
#define KAXLINE 12
#define ITR 2000000000
struct Operations {
	char precisionOp[2];
	char numberOfThreads[1];
} op;
void* computeSP(void* arg);
void* computeDP(void* arg);
void* computeHP(void* arg);
void* computeQP(void* arg);
int performSP(char* precOp, char* threadsCount, FILE* fout);
int performDP(char* precOp, char* threadsCount, FILE* fout);
int performHP(char* precOp, char* threadsCount, FILE* fout);
int performQP(char* precOp, char* threadsCount, FILE* fout);
int perform(char* precOp, char* threadsCount, FILE* fout) {
	printf("Precision Type-%s", precOp);
	printf("No Threads-%s\n", threadsCount);
	char *p;
	p = precOp;
	//printf("Precision Type11-%s", p);
	if (strstr(p, "SP")) {
		printf("inside perform() SP-%s\n", p);
		performSP(precOp, threadsCount, fout);
	} else if (strstr(p, "QP")) {
		printf("inside perform() QP-%s\n", p);
		performQP(precOp, threadsCount, fout);
	} else if (strstr(p, "DP")) {
		printf("inside perform() DP-%s\n", p);
		performDP(precOp, threadsCount, fout);
	} else if (strstr(p, "HP")) {
		printf("inside perform() HP-%s\n", p);
		performHP(precOp, threadsCount, fout);
	}
	return 0;
}
int performQP(char* precOp, char* threadsCount, FILE* fout) {
	int threadsNumber = atoi(threadsCount);
	printf(" Inside performQP()\n");
	if (threadsNumber == 1) {
		printf(" Inside performQP()-ThreadCount 1 %d\n", threadsNumber);
		pthread_t pid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		pthread_create(&pid, &attr, computeQP, &iterations);
		pthread_join(pid, NULL);
		gettimeofday(&timeAfter, NULL);
		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
		printf("Computation Time %f\n", time);
		fprintf(fout, "%s\t%d\t%f\t%f\t%f\n", "QP", 1, time, time, time);
		printf("---------------------------------------------\n");
	}
	if (threadsNumber == 2) {
		printf(" Inside performQP()-ThreadCount 2 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 2;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeQP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
		gettimeofday(&timeAfter, NULL);
		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
		printf("Computation Time %f\n", time);
		fprintf(fout, "%s\t%d\t%f\t%f\t%f\n", "QP", 2, time, time, time);
		printf("---------------------------------------------\n");
	}
	if (threadsNumber == 4) {
		printf(" Inside performQP()-ThreadCount 4 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 4;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeQP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
		gettimeofday(&timeAfter, NULL);
		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
		printf("Computation Time %f\n", time);
		fprintf(fout, "%s\t%d\t%f\t%f\t%f\n", "QP", 4, time, time, time);
		printf("---------------------------------------------\n");
	}
	return 0;
}
int performHP(char* precOp, char* threadsCount, FILE* fout) {
	int threadsNumber = atoi(threadsCount);
	printf(" Inside performHP()\n");
	if (threadsNumber == 1) {
		printf(" Inside performHP()-ThreadCount 1 %d\n", threadsNumber);
		pthread_t pid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		pthread_create(&pid, &attr, computeHP, &iterations);
		pthread_join(pid, NULL);
		gettimeofday(&timeAfter, NULL);
		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
		printf("Computation Time %f\n", time);
		fprintf(fout, "%s\t%d\t%f\t%f\t%f\n", "HP", 1, time, time, time);
		printf("---------------------------------------------\n");
	}
	if (threadsNumber == 2) {
		printf(" Inside performHP()-ThreadCount 2 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 2;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeHP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
		gettimeofday(&timeAfter, NULL);
		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
		printf("Computation Time %f\n", time);
		fprintf(fout, "%s\t%d\t%f\t%f\t%f\n", "HP", 2, time, time, time);
		printf("---------------------------------------------\n");
	}
	if (threadsNumber == 4) {
		printf(" Inside performHP()-ThreadCount 4 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 4;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeHP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
		gettimeofday(&timeAfter, NULL);
		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
		printf("Computation Time %f\n", time);
		fprintf(fout, "%s\t%d\t%f\t%f\t%f\n", "HP", 4, time, time, time);
		printf("---------------------------------------------\n");
	}
	return 0;
}
int performDP(char* precOp, char* threadsCount, FILE* fout) {
	int threadsNumber = atoi(threadsCount);
	printf(" Inside performDP()\n");
	if (threadsNumber == 1) {
		printf(" Inside performDP()-ThreadCount 1 %d\n", threadsNumber);
		pthread_t pid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		pthread_create(&pid, &attr, computeDP, &iterations);
		pthread_join(pid, NULL);
		gettimeofday(&timeAfter, NULL);
		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
		printf("Computation Time %f\n", time);
		fprintf(fout, "%s\t%d\t%f\t%f\t%f\n", "DP", 1, time, time, time);
		printf("---------------------------------------------\n");
	}
	if (threadsNumber == 2) {
		printf(" Inside performDP()-ThreadCount 2 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 2;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeDP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
		gettimeofday(&timeAfter, NULL);
		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
		printf("Computation Time %f\n", time);
		fprintf(fout, "%s\t%d\t%f\t%f\t%f\n", "DP", 2, time, time, time);
		printf("---------------------------------------------\n");
	}
	if (threadsNumber == 4) {
		printf(" Inside performDP()-ThreadCount 4 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 4;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeDP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
		gettimeofday(&timeAfter, NULL);
		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
		printf("Computation Time %f\n", time);
		fprintf(fout, "%s\t%d\t%f\t%f\t%f\n", "DP", 4, time, time, time);
		printf("---------------------------------------------\n");
	}
	return 0;
}
int performSP(char* precOp, char* threadsCount, FILE* fout) {
	int threadsNumber = atoi(threadsCount);
	printf(" Inside performSP()\n");
	if (threadsNumber == 1) {
		printf(" Inside performSP()-ThreadCount 1 %d\n", threadsNumber);
		pthread_t pid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		pthread_create(&pid, &attr, computeSP, &iterations);
		pthread_join(pid, NULL);
		gettimeofday(&timeAfter, NULL);
		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
		printf("Computation Time %f\n", time);
		fprintf(fout, "%s\t%d\t%f\t%f\t%f\n", "SP", 1, time, time, time);
		printf("---------------------------------------------\n");
	}
	if (threadsNumber == 2) {
		printf(" Inside performSP()-ThreadCount 2 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 2;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeSP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
		gettimeofday(&timeAfter, NULL);
		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
		printf("Computation Time %f\n", time);
		fprintf(fout, "%s\t%d\t%f\t%f\t%f\n", "SP", 2, time, time, time);
		printf("---------------------------------------------\n");
	}
	if (threadsNumber == 4) {
		printf(" Inside performSP()-ThreadCount 4 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 4;
		struct timeval timeNow, timeAfter;
		gettimeofday(&timeNow, NULL);
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeSP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
		gettimeofday(&timeAfter, NULL);
		double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
				- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
		printf("Computation Time %f\n", time);
		fprintf(fout, "%s\t%d\t%f\t%f\t%f\n", "SP", 4, time, time, time);
		printf("---------------------------------------------\n");
	}
	return 0;
}
void* computeSP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	int computeValue1 = 1000;
	int computeValue2 = 2000;
	for (long long z = 0; z < v; z++) {
		computeValue1 = computeValue1 * computeValue2 / computeValue2;
		if (z == (v - 1)) {
			computeValue1 = (int) v / 10000 + computeValue2;
		}

	}
	printf("Computation %d\n", computeValue1);
	printf("---------------------------------------------\n");
	pthread_exit(0);
}
void* computeDP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	double computeValue1 = 1.0;
	double computeValue2 = 2.0;
	for (long long z = 0; z < v; z++) {
		computeValue1 = computeValue1 * computeValue2 / computeValue2;
		if (z == (v - 1)) {
			computeValue1 = (double) v / 10000 + computeValue2;
		}

	}
	printf("Computation %.2f\n", computeValue1);
	printf("---------------------------------------------\n");
	pthread_exit(0);
}
void* computeHP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	short computeValue1 = 1000;
	short computeValue2 = 2000;
	for (long long z = 0; z < v; z++) {
		computeValue1 = computeValue1 * computeValue2 / computeValue2;
		if (z == (v - 1)) {
			computeValue1 = (short) v / 10000 + computeValue2;
		}
	}
	printf("Computation %hu\n", computeValue1);
	printf("---------------------------------------------\n");
	pthread_exit(0);
}
void* computeQP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	char computeValue1 = 'z';
	char computeValue2 = 'a';
	for (long long z = 0; z < v; z++) {
		computeValue1 = computeValue1 - computeValue2 + 20 + (254 / 254) - 20
				+ 1 - 1;
		if (z == (v - 1)) {
			computeValue1 = computeValue1 + 2;
		}
	}
	printf("Computation %c\n", computeValue1);
	printf("---------------------------------------------\n");
	pthread_exit(0);
}

int main() {
	DIR *directoryReadPtr;
	struct dirent *dir;
	char ch[252];
	int line = 0;
	int structCounter;
	directoryReadPtr = opendir(".");
	if (directoryReadPtr == NULL) {
		printf("No Files Available");
		exit(1);
	} //main if close
	structCounter = 0;
	int i;
	FILE *fout;
	fout = fopen("cpu_SP_1thread.out.dat", "a");
	if (fout == NULL) {
		perror("Error Storing Data");
		return -1;
	}
	while ((dir = readdir(directoryReadPtr)) != NULL) {
		if (strstr(dir->d_name, ".dat") != NULL) {
			i = 0;
			FILE *fp;
			fp = fopen(dir->d_name, "r");
			printf("%s\n", dir->d_name);

			while (!feof(fp) && i < 2) {
				if (i == 0) {
					fgets(op.precisionOp, sizeof(KAXLINE), fp);
					printf("Precision Value %s ", op.precisionOp);
				} else if (i == 1) {
					fgets(op.numberOfThreads, sizeof(KAXLINE), fp);
					printf("No of Threads %s\n", op.numberOfThreads);
					perform(op.precisionOp, op.numberOfThreads, fout);
					//printf("After SP1\n");
				}
				i++;
			}
			fclose(fp);
			//printf("After SP2\n");
			structCounter++;

		} //if strstr closed
	} // while closed

	closedir(directoryReadPtr);
	fclose(fout);

	return 0;
} // int main closed

