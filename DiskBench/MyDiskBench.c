#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<pthread.h>
#include<sys/time.h>
#include<time.h>
#include <asm/unistd.h>
#include <asm/unistd.h>
#define BUFFERSIZE 10737418240
#define KBBUFFERSIZE 1073741824
#define ITR 1
struct mem_segment_thread {
	long long start;
	long long end;
} struct_mem_thread[130];
char *workload; //1 GB of data
char rwaccess[5]; // Seqeuential or Random Access Type
char rwblocksize[12]; //Block Size
char rwthreads[5]; // Thread Count
char stringBlockSize[12]; //Block Size in characters
int noOfRuns; // Iterations
double latency;
int blockSz;
double totalBlocks;
char *workloadCopy;
char *fileRead;
char *fileWrite;
char tmp1[100];
char fileWorkload[25] = "A20405042_test.txt";
int threads_count;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void* readWriteRWR(void* arg);
void* readFromFile(void* arg);
void createFile() ;
int readWriteByteSequentialAndRandom();
int cacheflush(char *addr, int nbytes, int cache);
void readWrite() {
    // system("sync; echo 3 > /proc/sys/vm/drop_caches" );
	printf("Thread Count in Integer: %d\n", threads_count);

	if (strcmp(rwaccess, "RS") == 0) {
		printf("Read/Write:RS\n");
		readWriteByteSequentialAndRandom();
	} else if (strcmp(rwaccess, "WS") == 0) {
		printf("Read/Write:WS\n");
		readWriteByteSequentialAndRandom();
	} else if (strcmp(rwaccess, "RR") == 0) {
		printf("Read/Write:RR\n");
		readWriteByteSequentialAndRandom();
	} else if (strcmp(rwaccess, "WR") == 0) {
		printf("Read/Write:WR\n");
		readWriteByteSequentialAndRandom();
	}

}
int readWriteByteSequentialAndRandom() {
	//Output file writing
	FILE* outputFile;
	outputFile = fopen(fileWrite, "a+");
	if (outputFile == NULL) {
		perror("Error Opening File");
		return -1;
	}
	pthread_t pid[threads_count];
	pthread_attr_t attr;
	pthread_attr_init(&attr);


    if(blockSz==1000){
        printf("Threads in Disk readWriteByteSequentialAndRandom() %d\n",threads_count);
        struct_mem_thread[0].start = 0;
		struct_mem_thread[0].end = KBBUFFERSIZE/ threads_count  ;
        for(int i=1;i<threads_count;i++){
            struct_mem_thread[i].start=KBBUFFERSIZE / (double)((double)threads_count/(double)i) ;
            struct_mem_thread[i].end=KBBUFFERSIZE /(double)((double)threads_count/(double)(i+1));
            }
    }
    else{
        printf("Threads in Disk readWriteByteSequentialAndRandom() %d\n",threads_count);
        struct_mem_thread[0].start = 0;
		struct_mem_thread[0].end = BUFFERSIZE / threads_count  ;
        for(int i=1;i<threads_count;i++){
            struct_mem_thread[i].start=BUFFERSIZE / (double)((double)threads_count/(double)i) ;
            struct_mem_thread[i].end=BUFFERSIZE /(double)((double)threads_count/(double)(i+1));
            //printf("Start and end in (): %lld\t%lld\n",struct_mem_thread[i].start,struct_mem_thread[i].end);
        }
    }
	struct timeval timeNow, timeAfter;
	gettimeofday(&timeNow, NULL);
	for (int i = 0; i < threads_count; i++) {
		pthread_create(&pid[i], &attr, readFromFile, &struct_mem_thread[i]);
	}

	for (int i = 0; i < threads_count; i++) {
		pthread_join(pid[i], NULL);
	}
	//pthread_mutex_destroy(&lock); // Destroying Mutex

	gettimeofday(&timeAfter, NULL);
	double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
			- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
	double itr = ITR;
	double bffr = BUFFERSIZE;
	if (atoi(rwblocksize) == 1) {
		double theoLatency=4.16*1000;
		latency = (time * 1000)/totalBlocks;
		double diskiops=totalBlocks/time;
		double theoIOPS=75.98;
		printf("\nLatency: %f milliseconds \n", latency);
        printf("Theo Latency: %f milliseconds \n", theoLatency);
        printf("Disk Latency IOPS: %f\n", diskiops);
        printf("Disk Latency Theo IOPS: %f\n", theoIOPS);
        fprintf(outputFile, "%s\t%s\t%s\t%f\t%f\t%f\t%f\t%f\t%f\n", rwaccess, rwthreads,
				stringBlockSize, latency, theoLatency, (latency/theoLatency),diskiops,theoIOPS,(diskiops/theoIOPS));

	} else {
		double throughput = (((1.0 * itr * bffr) / time) / (1e6));
        double theoThroughput=((double)blockSz*75.98)/1e6;
        double efficiency=(throughput/theoThroughput)*100;
        printf("Throughput: %f\n", throughput);
        printf("Theo Throughput: %f\n", theoThroughput);
		printf("Computation Time:%f\n", time);
		printf("Efficiency :%f\n", efficiency);
		printf("Writing to the output file!!!!!!\n");
		fprintf(outputFile, "%s\t%s\t%s\t%f\t%f\t%f\n", rwaccess, rwthreads,
				stringBlockSize, throughput, theoThroughput, efficiency);
	}

	fclose(outputFile);
	//pthread_mutex_destroy(&lock); // Destroying Mutex
	return 0;
}
void* readFromFile(void *arg) {
	//pthread_mutex_lock(&lock);
	FILE* inputFile;

	if (strcmp(rwaccess, "RS") == 0 || strcmp(rwaccess, "RR") == 0) {
		inputFile = fopen(fileWorkload, "r");
		if (inputFile == NULL) {
			perror("Error Reading File");

		}
	}
	if (strcmp(rwaccess, "WS") == 0 || strcmp(rwaccess, "WR") == 0) {

		inputFile = fopen(fileWorkload, "a+");
		if (inputFile == NULL) {
			perror("Error Storing Data");

		}
	}

    struct mem_segment_thread *x = (struct mem_segment_thread*) arg;
	long long t_start = (*x).start;
	long long t_end = (*x).end;
	long long int random_var;

	long long int j = t_start;
	if (strcmp(rwaccess, "RS") == 0) {
        printf("Sequential Read Block Size: %d\n",blockSz);
		printf("Sequential Reading from the file...\n");
		fseek(inputFile, j, SEEK_SET);
		while (j < t_end) {
			memset(workloadCopy, '\0', blockSz);
			fread(workloadCopy, sizeof(char), blockSz, inputFile);
			j += blockSz;
			//printf("J:%lld\n",j);
		}
	}

	if (strcmp(rwaccess, "RR") == 0) {

          //  printf("Randomly Read Block Size: %d\n",blockSz);
            //printf("Randomly Reading from the file...\n");

            fseek(inputFile,j,SEEK_SET);
            srand (time(0));

            while(j < t_end) {
                    memset(workloadCopy,'\0',blockSz);
                    random_var = t_start+rand() / (RAND_MAX / (t_end-t_start+1)+1);
                    fseek(inputFile,random_var,SEEK_SET);
                    fread(workloadCopy,sizeof(char), blockSz, inputFile);
                    j += blockSz;
                    //printf("%s\n",workloadCopy);
                }

	}

	if (strcmp(rwaccess, "WS") == 0) {

		//memset(workloadCopy, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26],atoi(rwblocksize));
		printf("Sequential Write Block Size: %d\n",blockSz);
		printf("Sequential Writing to the file...\n");
		fseek(inputFile, j, SEEK_SET);
		while (j < t_end) {
			fwrite(workloadCopy, sizeof(char), blockSz, inputFile);
			j += blockSz;
			//printf("%d\n", j);
		}
	}
    if (strcmp(rwaccess, "WR") == 0) {

		//memset(workloadCopy, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26],atoi(rwblocksize));
        //printf("Ramdom Write Block Size: %d\n",blockSz);
		//printf("Ramdomly Writing to the 10 GB of file...\n");

		fseek(inputFile, j, SEEK_SET);

		while(j< t_end) {
            random_var = t_start+rand() / (RAND_MAX / (t_end-t_start+1)+1);
            fseek(inputFile,random_var,SEEK_SET);
			fwrite(workloadCopy, sizeof(char), blockSz, inputFile);
			//fsync(inputFile);
			//fflush(inputFile);
			j =j+ blockSz;

		}

	}

	fclose(inputFile);

}

void createFile() {

    FILE* inputFile;
	inputFile = fopen(fileWorkload, "w+");

	char arr[] = { "abcdefghijklmnopqrstuvwxyz" };
	//memset(workloadCopy,"ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26],atoi(rwblocksize));

	struct timeval timeNow, timeAfter;
	gettimeofday(&timeNow, NULL);
	if(blockSz==1000)
    {
        long long int noOfRuns = BUFFERSIZE/10;
        printf("1 GB File in Bytes:%lld\n",noOfRuns);
        printf("Writing 1 GB of data,,,, wait for a while!!!!\n");
        for (long long int i = 0; i < (noOfRuns / 26); i++) {
            fprintf(inputFile, "%s", arr);
            //fwrite(arr,sizeof(char),strlen(arr),inputFile);

        }
    }
    else
    {
        long long int noOfRuns = BUFFERSIZE;
        printf("10 GB File in Bytes:%lld\n",noOfRuns);
        printf("Writing 10 GB of data,,,, wait for a while!!!!\n");
        for (long long int i = 0; i < (noOfRuns / 26); i++) {
            fprintf(inputFile, "%s", arr);
            //fwrite(arr,sizeof(char),strlen(arr),inputFile);

        }
    }
    gettimeofday(&timeAfter, NULL);
	double time = (timeAfter.tv_sec + (timeAfter.tv_usec / 1000000.0))
			- (timeNow.tv_sec + (timeNow.tv_usec / 1000000.0));
    printf("Writing done in time: %f\n",time);
	fclose(inputFile);

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
			fgets(rwaccess, 3, inputFile);

		} else if (i == 1) {
			fgets(tmp1, 2, inputFile);

		} else if (i == 2) {
			fgets(rwblocksize, 10, inputFile);

		} else if (i == 3) {
			fgets(tmp1, 1, inputFile);

		} else if (i == 4) {
			fgets(rwthreads, 4, inputFile);

		}
		i++;

	}
	fclose(inputFile);

}

int main(int argc, char **argv) {
	printf("Hello....\nWelcome to the world of Disk Benchmarking!!!!!!!\n");

	//Reading File
	//Reading File
	fileRead = argv[1];
	fileWrite = argv[2];
	readFileData();
	// Reading file completed
	blockSz = atoi(rwblocksize);
	threads_count = atoi(rwthreads);
	//printf("Block Size :%d\n", blockSz);
	//printf("Threads :%d\n", threads_count);
	noOfRuns = ITR;

	if (blockSz == 1) {
		blockSz = blockSz * 1024;
		strcpy(stringBlockSize, "1KB");
		workloadCopy = (char*) malloc(blockSz);

	} else if (blockSz == 1000) {
		blockSz = blockSz * 1024;
		strcpy(stringBlockSize, "1MB");
		workloadCopy = (char*) malloc(blockSz);
	} else if (blockSz == 10000) {
		blockSz = blockSz * 1024;
		strcpy(stringBlockSize, "10MB");
		workloadCopy = (char*) malloc(blockSz);
	} else if (blockSz == 100000) {
		blockSz = blockSz * 1024;
		strcpy(stringBlockSize, "100MB");
		workloadCopy = (char*) malloc(blockSz);
	}
	printf("Block Size in B,KB,MB: %s\n", stringBlockSize);
	//memset(workload,"ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26],BUFFERSIZE);
	/*Another way to write workload using for loop*/
	totalBlocks=(double)(BUFFERSIZE/(double)blockSz);
    printf("Total No of Blocks: %f\n",totalBlocks);
    if(strcmp(rwaccess, "WS") == 0 || strcmp(rwaccess, "WR") == 0)
    {
        /*
        for(int i =0;i<blockSz;i++)
        {
        workloadCopy[i]= 'A' + (rand() % 26);
        }
        */
        memset(workloadCopy,"ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26],blockSz);
    }
	if (strcmp(rwaccess, "RS") == 0 || strcmp(rwaccess, "RR") == 0)
	{
	    createFile();
	}
	readWrite();
	free(workloadCopy);
	free(workload);

	//remove(fileWorkload);
	return 0;
}
