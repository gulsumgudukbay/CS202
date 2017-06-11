/*
 * main.cpp
 *
 * Created on: Nov 21, 2015
 * Author: Gulsum Gudukbay
 * Section: 1
 * Student ID: 21401148
 */

#include "heap.h"

int main(int argc, char **argv){

	string inputFile(argv[1]);
	string outputFile(argv[2]);

	heap *h = new heap(inputFile);

	h->heapPrint();
	h->heapsort(outputFile);
	h->heapPrint();


	return 0;
}
