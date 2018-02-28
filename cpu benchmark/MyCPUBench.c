#include <dirent.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/time.h>
#define KAXLINE 12
#define ITR 200000
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
	char *p;
	p = precOp;
	if (strstr(p, "SP")) {
		performSP(precOp, threadsCount, fout);
	} else if (strstr(p, "QP")) {
		performQP(precOp, threadsCount, fout);
	} else if (strstr(p, "DP")) {
		performDP(precOp, threadsCount, fout);
	} else if (strstr(p, "HP")) {
		performHP(precOp, threadsCount, fout);
	}
	return 0;
}
int performQP(char* precOp, char* threadsCount, FILE* fout) {
	int threadsNumber = atoi(threadsCount);

	if (threadsNumber == 1) {
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
		double gigaflops = (double) (((ITR * 5.0) / time) / 1000000000.0);
		fprintf(fout, "%s\t%d\t%f\t%f\t%d\n", "QP", threadsNumber, gigaflops,
				0.0, 100);
		printf("Computation Time %f\n", time);
		printf("Gigaflops %f\n", gigaflops);
		printf("...........................................\n");

	}
	if (threadsNumber == 2) {
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
		//Performing 5 operations; 5 ops are multiplied by iterations
		double gigaflops = (double) (((ITR * 5.0) / time) / 1000000000.0);
		fprintf(fout, "%s\t%d\t%f\t%f\t%d\n", "QP", threadsNumber, gigaflops,
				0.0, 100);
		printf("Computation Time %f\n", time);
		printf("Gigaflops %f\n", gigaflops);
		printf("...........................................\n");

	}
	if (threadsNumber == 4) {
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
		double gigaflops = (double) (((ITR * 5.0) / time) / 1000000000.0);
		fprintf(fout, "%s\t%d\t%f\t%f\t%d\n", "QP", threadsNumber, gigaflops,
				0.0, 100);
		printf("Computation Time %f\n", time);
		printf("Gigaflops %f\n", gigaflops);
		printf("...........................................\n");

	}
	return 0;
}
int performHP(char* precOp, char* threadsCount, FILE* fout) {
	int threadsNumber = atoi(threadsCount);
	if (threadsNumber == 1) {
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
		double gigaflops = (double) (((ITR * 2.0) / time) / 1000000000.0);
		fprintf(fout, "%s\t%d\t%f\t%f\t%d\n", "HP", threadsNumber, gigaflops,
				0.0, 100);
		printf("Computation Time %f\n", time);
		printf("Gigaflops %f\n", gigaflops);
		printf("...........................................\n");

	}
	if (threadsNumber == 2) {
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
		double gigaflops = (double) (((ITR * 2.0) / time) / 1000000000.0);
		fprintf(fout, "%s\t%d\t%f\t%f\t%d\n", "HP", threadsNumber, gigaflops,
				0.0, 100);
		printf("Computation Time %f\n", time);
		printf("Gigaflops %f\n", gigaflops);
		printf("...........................................\n");

	}
	if (threadsNumber == 4) {
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
		double gigaflops = (double) (((ITR * 2.0) / time) / 1000000000.0);
		fprintf(fout, "%s\t%d\t%f\t%f\t%d\n", "HP", threadsNumber, gigaflops,
				0.0, 100);
		printf("Computation Time %f\n", time);
		printf("Gigaflops %f\n", gigaflops);
		printf("...........................................\n");

	}
	return 0;
}
int performDP(char* precOp, char* threadsCount, FILE* fout) {
	int threadsNumber = atoi(threadsCount);
	if (threadsNumber == 1) {
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
		double gigaflops = (double) (((ITR * 2.0) / time) / 1000000000.0);
		fprintf(fout, "%s\t%d\t%f\t%f\t%d\n", "DP", threadsNumber, gigaflops,
				0.0, 100);
		printf("Computation Time %f\n", time);
		printf("Gigaflops %f\n", gigaflops);
		printf("...........................................\n");

	}
	if (threadsNumber == 2) {
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
		double gigaflops = (double) (((ITR * 2.0) / time) / 1000000000.0);
		fprintf(fout, "%s\t%d\t%f\t%f\t%d\n", "DP", threadsNumber, gigaflops,
				0.0, 100);
		printf("Computation Time %f\n", time);
		printf("Gigaflops %f\n", gigaflops);
		printf("...........................................\n");

	}
	if (threadsNumber == 4) {
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

		double gigaflops = (double) (((ITR * 2.0) / time) / 1000000000.0);
		fprintf(fout, "%s\t%d\t%f\t%f\t%d\n", "DP", threadsNumber, gigaflops,
				0.0, 100);
		printf("Computation Time %f\n", time);
		printf("Gigaflops %f\n", gigaflops);
		printf("...........................................\n");

	}
	return 0;
}
int performSP(char* precOp, char* threadsCount, FILE* fout) {
	int threadsNumber = atoi(threadsCount);

	if (threadsNumber == 1) {

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
		double gigaflops = (double) (((ITR * 2.0) / time) / 1000000000.0);
		fprintf(fout, "%s\t%d\t%f\t%f\t%d\n", "SP", threadsNumber, gigaflops,
				0.0, 100);
		printf("Computation Time %f\n", time);
		printf("Gigaflops %f\n", gigaflops);
		printf("...........................................\n");

	}
	if (threadsNumber == 2) {
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

		double gigaflops = (double) (((ITR * 2.0) / time) / 1000000000.0);
		fprintf(fout, "%s\t%d\t%f\t%f\t%d\n", "SP", threadsNumber, gigaflops,
				0.0, 100);
		printf("Computation Time %f\n", time);
		printf("Gigaflops %f\n", gigaflops);
		printf("...........................................\n");
	}
	if (threadsNumber == 4) {
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

		double gigaflops = (double) (((ITR * 2.0) / time) / 1000000000.0);
		fprintf(fout, "%s\t%d\t%f\t%f\t%d\n", "SP", threadsNumber, gigaflops,
				0.0, 100);
		printf("Computation Time %f\n", time);
		printf("Gigaflops %f\n", gigaflops);
		printf("...........................................\n");

	}
	return 0;
}
void* computeSP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	int computeValue1 = 10000;
	int computeValue2 = 20000;
	for (long long z = 0; z < v; z++) {
		computeValue1 = computeValue1 * computeValue2 / computeValue2;
	}
	printf("Computation in SP %d\n", computeValue1);

	pthread_exit(0);
}
void* computeDP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	double computeValue1 = 10000.0;
	double computeValue2 = 20000.0;
	for (long long z = 0; z < v; z++) {
		computeValue1 = computeValue1 * computeValue2 / computeValue2;
	}
	printf("Computation in DP %.2f\n", computeValue1);

	pthread_exit(0);
}
void* computeHP(void* arg) {
	long long *x = (long long*) arg;
	long long v = *x;
	short computeValue1 = 10;
	short computeValue2 = 20;
	for (long long z = 0; z < v; z++) {
		computeValue1 = computeValue1 * computeValue2 / computeValue2;
	}
	printf("Computation in HP %hu\n", computeValue1);
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
	}
	printf("Computation in QP %c\n", computeValue1);
	pthread_exit(0);
}

int main() {
	DIR *directoryReadPtr;
	struct dirent *dir;
	directoryReadPtr = opendir(".");
	if (directoryReadPtr == NULL) {
		printf("No Files Available");
		exit(1);
	} //main if close
	int i;
	FILE *fout; // Output file
	fout = fopen("./output/cpu_SP_1thread.out.dat", "a");
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
			printf("%s\n", dir->d_name);

			while (!feof(fp) && i < 2) {
				if (i == 0) {
					fgets(op.precisionOp, sizeof(KAXLINE), fp);

				} else if (i == 1) {
					fgets(op.numberOfThreads, sizeof(KAXLINE), fp);
					//iterate over the data of each .dat file
					//call perform to perform computations using the pthreads
					perform(op.precisionOp, op.numberOfThreads, fout);
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

