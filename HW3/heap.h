/*
 * heap.h
 *
 * Created on: Nov 16, 2015
 * Author: Gulsum Gudukbay
 * Section: 1
 *
 * Student ID: 21401148
 */

#ifndef HEAP_H_
#define HEAP_H_
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class heap {
public:
	heap(string inputFileName);
	~heap();

	void insert(const int a);
	int maximum();
	int popMaximum();
	void heapRebuild(int index, int toIndex);
	void heapsort( string output);

	void heapPrint();

	int *heapArr;
	int arrSize;
	int elementCount;
	int initialElementCount;
	int comparisons;
};

#endif /* HEAP_H_ */
