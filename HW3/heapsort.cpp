/*
 * heapsort.cpp sorts a heap array and writes the sorted array into an output file
 *
 * Created on: Nov 20, 2015
 * Author: Gulsum Gudukbay
 * Section: 1
 * Student ID: 21401148
 */

#include "heap.h"

void heap::heapsort(string output) {
	initialElementCount = elementCount;

	while (elementCount > 0) {
		int deleted = popMaximum();
		heapArr[elementCount] = deleted;
	}

	ofstream outputF;
	outputF.open(output.c_str());
	for (int i = 0; i < initialElementCount; i++) {
		outputF << heapArr[i] << endl;
	}
	outputF.close();

}

