/*
 * sorting.h
 *
 * Created on: Oct 10, 2015
 * Author: Gulsum Gudukbay
 * Student ID: 21401148
 */

#ifndef SORTING_H_
#define SORTING_H_
#include <iostream>
using namespace std;
	void swap( int &n1, int &n2 );

	void selectionSort( int *arr, int size, int &compCount, int &moveCount);

	void mergeSort( int *arr, int size, int &compCount, int &moveCount);
	void merge(int *arr, int first, int mid, int last, int &compCount, int &moveCount);
	void actualMergeSort(int *arr, int first, int last, int &compCount, int &moveCount);

	void quickSort( int *arr, int size, int &compCount, double &moveCount);
	void actualQuickSort(int *arr, int first, int last, int &compCount, double &moveCount);
	int partition(int *arr, int first, int last, int &compCount, double &moveCount);


#endif /* SORTING_H_ */
