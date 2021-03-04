#include <iostream>
#include <thread>
#include <stdlib.h>
#include <stdio.h>
#include "Stopwatch.h"
#include <time.h>
using namespace win32;
using namespace std;

Stopwatch stopwatch1, stopwatch2, stopwatch3, stopwatch4, stopwatch5;
double staticAllocationElapsedTime, dynamicAllocationElapsedTime, threadCreationElapsedTime, dynamicAccessTime, staticAccessTime;

void dynamicAllocation(FILE* file, int k) {
	dynamicAllocationElapsedTime = 0;
	for (int i = 0; i < 100000; i++) {
		stopwatch1.Start();
		int* array;
 		array = new int[333];
		stopwatch1.Stop();
		clock_t end = clock();
		delete[] array;
		dynamicAllocationElapsedTime += stopwatch1.ElapsedMilliseconds();
	}
	cout << "elapsed time for dynamic memory allocation: " << dynamicAllocationElapsedTime / 100000 << " ms" <<endl;
	fprintf(file, "%.10f \n", dynamicAllocationElapsedTime / 100000);

}

void staticAllocation(FILE* file, int k) {
	staticAllocationElapsedTime = 0;
	for (int i = 0; i < 100000; i++) {
		stopwatch2.Start();
			int array[333];
		stopwatch2.Stop();
		staticAllocationElapsedTime += stopwatch2.ElapsedMilliseconds();
	}
	cout << "elapsed time for static memory allocation: " << staticAllocationElapsedTime / 100000 << " ms" << endl;
	fprintf(file, "%.10f \n", staticAllocationElapsedTime / 100000);
}

void dynamicAccess(FILE* file, int k) {
	dynamicAccessTime = 0;
	int* array1;
	array1 = new int[333];
	for (int i = 0; i < 333; i++)
		array1[i] = i * i;
	for (int i = 0; i < 100000; i++) {
		int* array2;
		array2 = new int[333];
		stopwatch3.Start();
		memmove(array2, array1, 333 * sizeof(int));
		stopwatch3.Stop();
		dynamicAccessTime += stopwatch3.ElapsedMilliseconds();
		delete[] array2;
	}
	delete[] array1;
	cout << "elapsed time for dynamic memory access: " << dynamicAccessTime / 100000 << " ms" << endl;
	fprintf(file, "%.10f \n", dynamicAccessTime / 100000);
}

void staticAccess(FILE* file, int k) {
	staticAccessTime = 0;
	int array3[333];
	for (int i = 0; i < 333; i++)
		array3[i] = i * i;
	for (int i = 0; i < 100000; i++) {
		int array4[333];
		stopwatch4.Start();
		memmove(&array4, &array3, 333 * sizeof(int));
		stopwatch4.Stop();
		staticAccessTime += stopwatch4.ElapsedMilliseconds();
	}
	cout << "elapsed time for static memory access: " << staticAccessTime / 100000 << " ms" << endl;
	fprintf(file, "%.10f \n", staticAccessTime / 100000);
}

void foo (int n) {
	n++;
}

void threadCreation(FILE* file, int k) {
	threadCreationElapsedTime = 0;
	for (int i = 0; i < 1000; i++) {
		stopwatch5.Start();
		thread t(foo, i);
		t.join();
		stopwatch5.Stop();
		threadCreationElapsedTime += stopwatch5.ElapsedMilliseconds();
	}
	cout << "elapsed time for thread creation: " << threadCreationElapsedTime / 1000 << " ms\n";
	fprintf(file, "%.10f \n", threadCreationElapsedTime / 1000);

}

int main() {
	FILE* staticAlloc;
	staticAlloc = fopen("static_memory_allocation_c_plus.csv", "w");
	FILE* dynamicAlloc;
	dynamicAlloc = fopen("dynamic_memory_allocation_c_plus.csv", "w");
	FILE* staticAcc;
	staticAcc = fopen("static_memory_access_c_plus.csv", "w");
	FILE* dynamicAcc;
	dynamicAcc = fopen("dynamic_memory_access_c_plus.csv", "w");
	FILE* threadCr;
	threadCr = fopen("thread_creation_c_plus.csv", "w");

	for (int i = 0; i < 1000; i++) {
		cout << "------------------- " << i << "------------------- " << endl;
		staticAllocation(staticAlloc, i);
		dynamicAllocation(dynamicAlloc, i);
		staticAccess(staticAcc, i);
		dynamicAccess(dynamicAcc, i);
	}

	for (int i = 0; i < 100; i++) 
		threadCreation(threadCr, i);
	

	fclose(staticAlloc);
	fclose(dynamicAlloc);
	fclose(staticAcc);
	fclose(dynamicAcc);
	fclose(threadCr);
	return 0;
}