#include <stdio.h>
#include <stdlib.h>
#define MEMSIZE 1000000000

int main(){
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
