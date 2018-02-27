#include <dirent.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#define KAXLINE 12
#define ITR 1000000
struct Operations {
	char precisionOp[2];
	char numberOfThreads[1];
} op;
void* computeSP(void* arg);
void* computeDP(void* arg);
void* computeHP(void* arg);
void* computeQP(void* arg);
int performSP(char* precOp, char* threadsCount);
int performDP(char* precOp, char* threadsCount);
int performHP(char* precOp, char* threadsCount);
int performQP(char* precOp, char* threadsCount);
int perform(char* precOp, char* threadsCount) {
	printf("Precision Type-%s", precOp);
	printf("No Threads-%s\n", threadsCount);
	char *p;
	p = precOp;
	//printf("Precision Type11-%s", p);
	if (strstr(p,"SP")) {
		printf("inside perform() SP-%s\n", p);
		performSP(precOp, threadsCount);
	}
	else if (strstr(p,"QP")) {
		printf("inside perform() QP-%s\n", p);
		performQP(precOp, threadsCount);
	}
	else if (strstr(p,"DP")) {
		printf("inside perform() DP-%s\n", p);
		performDP(precOp, threadsCount);
	}
	else if (strstr(p,"HP")) {
		printf("inside perform() HP-%s\n", p);
		performHP(precOp, threadsCount);
	}
	return 0;
}
int performQP(char* precOp, char* threadsCount) {
	int threadsNumber = atoi(threadsCount);
	printf(" Inside performQP()\n");
	if (threadsNumber == 1) {
		printf(" Inside performQP()-ThreadCount 1 %d\n", threadsNumber);
		pthread_t pid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR;
		pthread_create(&pid, &attr, computeQP, &iterations);
		pthread_join(pid, NULL);
	}
	if (threadsNumber == 2) {
		printf(" Inside performQP()-ThreadCount 2 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 2;
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeQP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
	}
	if (threadsNumber == 4) {
		printf(" Inside performQP()-ThreadCount 4 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 4;
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeQP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
	}
	return 0;
}
int performHP(char* precOp, char* threadsCount) {
	int threadsNumber = atoi(threadsCount);
	printf(" Inside performHP()\n");
	if (threadsNumber == 1) {
		printf(" Inside performHP()-ThreadCount 1 %d\n", threadsNumber);
		pthread_t pid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR;
		pthread_create(&pid, &attr, computeHP, &iterations);
		pthread_join(pid, NULL);
	}
	if (threadsNumber == 2) {
		printf(" Inside performHP()-ThreadCount 2 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 2;
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeHP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
	}
	if (threadsNumber == 4) {
		printf(" Inside performHP()-ThreadCount 4 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 4;
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeHP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
	}
	return 0;
}
int performDP(char* precOp, char* threadsCount) {
	int threadsNumber = atoi(threadsCount);
	printf(" Inside performDP()\n");
	if (threadsNumber == 1) {
		printf(" Inside performDP()-ThreadCount 1 %d\n", threadsNumber);
		pthread_t pid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR;
		pthread_create(&pid, &attr, computeDP, &iterations);
		pthread_join(pid, NULL);
	}
	if (threadsNumber == 2) {
		printf(" Inside performDP()-ThreadCount 2 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 2;
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeDP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
	}
	if (threadsNumber == 4) {
		printf(" Inside performDP()-ThreadCount 4 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 4;
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeDP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
	}
	return 0;
}
int performSP(char* precOp, char* threadsCount) {
	int threadsNumber = atoi(threadsCount);
	printf(" Inside performSP()\n");
	if (threadsNumber == 1) {
		printf(" Inside performSP()-ThreadCount 1 %d\n", threadsNumber);
		pthread_t pid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR;
		pthread_create(&pid, &attr, computeSP, &iterations);
		pthread_join(pid, NULL);
	}
	if (threadsNumber == 2) {
		printf(" Inside performSP()-ThreadCount 2 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 2;
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeSP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
	}
	if (threadsNumber == 4) {
		printf(" Inside performSP()-ThreadCount 4 %d\n", threadsNumber);
		pthread_t pid[threadsNumber];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		long long iterations = ITR / 4;
		for (int k = 0; k < threadsNumber; k++) {
			pthread_create(&pid[k], &attr, computeSP, &iterations);
		}
		for (int k = 0; k < threadsNumber; k++) {
			pthread_join(pid[k], NULL);
		}
	}
	return 0;
}
void* computeSP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	int computeValue1 = 1;
	int computeValue2 = 2;
	for (long long z = 0; z < v; z++) {
		computeValue1 = computeValue1 * 0 + computeValue2 * 0 + 1 - 1;
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
		computeValue1 = computeValue1 * 0 + computeValue2 * 0 + 1 - 1;
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
	short computeValue1 = 1;
	short computeValue2 = 2;
	for (long long z = 0; z < v; z++) {
		computeValue1 = computeValue1 * 0 + computeValue2 * 0 + 1 - 1;
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
	char computeValue1 = 'A';
	char computeValue2 ='B';
	for (long long z = 0; z < v; z++) {
		computeValue1 = computeValue1 + 1 - 1;
		if (z == (v - 1)) {
			computeValue1 = computeValue1+2;
		}
	}
	printf("Computation %c\n", computeValue1);
	printf("---------------------------------------------");
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
					perform(op.precisionOp, op.numberOfThreads);
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

	return 0;
} // int main closed

