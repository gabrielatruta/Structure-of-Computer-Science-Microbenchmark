#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

double threadCreationElapsedTime, dynamicAllocationElapsedTime, dynamicAccessElapsedTime, staticAllocationElapsedTime, staticAccessElapsedTime;

void dynamicAllocation(FILE* file) {
	dynamicAllocationElapsedTime = 0;
	for (int i = 0; i < 10000; i++) {
		clock_t start = clock();
		int* array;
		array = (int*)malloc(333 * sizeof(int));
		clock_t end = clock();
		dynamicAllocationElapsedTime += (double)(end - start); // / CLOCKS_PER_SEC;
		free(array);
	}
	printf("%s %f %s", "elapsed time for dynamic memory allocation: ", dynamicAllocationElapsedTime / 10000, " ms \n");
	fprintf(file, "%.10f \n", dynamicAllocationElapsedTime / 10000);
}

void staticAllocation(FILE* file){
	staticAllocationElapsedTime = 0;
	for (int i = 0; i < 10000; i++) {
		clock_t start1 = clock();
		int array[333];
		clock_t end1 = clock();
		staticAllocationElapsedTime += (double)(end1 - start1);// / CLOCKS_PER_SEC;
	}
	printf("%s %f %s", "elapsed time for static memory allocation: ", staticAllocationElapsedTime / 10000, " ms \n");
	fprintf(file, "%.10f \n", staticAllocationElapsedTime / 10000);

}

void dynamicAccess(FILE* file) {
	dynamicAccessElapsedTime = 0;
	int* array1;
	array1 = (int*)malloc(333 * sizeof(int));
	for (int i = 0; i < 333; i++)
		array1[i] = i++;
	for (int i = 0; i < 100000; i++) {
		int* array2;
		array2 = (int*)malloc(333 * sizeof(int));
		clock_t start2 = clock();
		memmove(array2, array1, 333 * sizeof(int));
		clock_t end2 = clock();
		dynamicAccessElapsedTime += (double)(end2 - start2); // / CLOCKS_PER_SEC;
		free(array2);
	}
	free(array1);
	printf("%s %f %s", "elapsed time for dynamic memory access: ", dynamicAccessElapsedTime / 10000, " ms \n");
	fprintf(file, "%.10f \n", dynamicAccessElapsedTime / 10000);
}


void staticAccess(FILE* file)
{
	staticAccessElapsedTime = 0;
	int array3[333];
	for (int i = 0; i < 333; i++)
		array3[i] = i * i;
	for (int i = 0; i < 10000; i++) {
		int array4[333];
		clock_t start3 = clock();
		memmove(&array4, &array3, 333 * sizeof(int));
		clock_t end3 = clock();
		staticAccessElapsedTime += (double)(end3 - start3); // / CLOCKS_PER_SEC;
	}
	printf("%s %f %s", "elapsed time for static memory access: ", staticAccessElapsedTime / 10000, " ms \n");
	fprintf(file, "%.10f \n", staticAccessElapsedTime / 10000);

}

void foo(int n) {
	n*n;
}

DWORD WINAPI functionThread(LPVOID data) {
	foo((int)data);
	return 0;
}

void threadCreation(FILE* file) {
	threadCreationElapsedTime = 0;
	HANDLE thread[1];
	DWORD threadID;
	float sum = 0;

	for (int i = 0; i < 1000; i++) {
		clock_t start4 = clock();
		thread[0] = CreateThread(NULL, 0, functionThread, (void*)i, 0, &threadID);
		WaitForMultipleObjects(1, thread, TRUE, INFINITE);
		CloseHandle(thread[0]);
		clock_t end4 = clock();
		threadCreationElapsedTime += (double)(end4 - start4); // / CLOCKS_PER_SEC;
	}
	printf("%s %f %s", "elapsed time for thread creation: ", threadCreationElapsedTime / 1000, " ms \n");
	fprintf(file, "%.10f \n", threadCreationElapsedTime / 1000);

}

int main() {
	FILE* staticAlloc;
	staticAlloc = fopen("static_memory_allocation_c.csv", "w");
	FILE* dynamicAlloc;
	dynamicAlloc = fopen("dynamic_memory_allocation_c.csv", "w");
	FILE* staticAcc;
	staticAcc = fopen("static_memory_access_c.csv", "w");
	FILE* dynamicAcc;
	dynamicAcc = fopen("dynamic_memory_access_c.csv", "w");
	FILE* threadCr;
	threadCr = fopen("thread_creation_c.csv", "w");

	for (int i = 0; i < 1000; i++) {
		printf ("------------------- %d ------------------- \n", i);
		staticAllocation(staticAlloc);
		dynamicAllocation(dynamicAlloc);
		staticAccess(staticAcc);
		dynamicAccess(dynamicAcc);
	}

	for (int i = 0; i < 100; i++)
		threadCreation(threadCr, i);

	return 0;
}