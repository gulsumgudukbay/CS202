/*
 * sorting.cpp
 *
 * Created on: Oct 10, 2015
 * Author: Gulsum Gudukbay
 * Student ID: 21401148
 */

#include "sorting.h"

	//swaps two elements
	void swap( int &num1, int &num2 ){

		int temp = num1;
		num1 = num2;
		num2 = temp;

	}

	////////SELECTION SORT/////////
	//sorts elements by finding the minimum and putting it to the beginning of the unsorted subarray
	void selectionSort( int *arr, int size, int &compCount, int &moveCount){

		int min;
		int indexMin = 0;

		for(int j = 0; j < size; j++){
			min = arr[j];
			//Finding the minimum
			for(int i = j; i < size; i++){
				if(min >= arr[i]){
					compCount++;
					min = arr[i];
					indexMin = i;
				}
			}
			if(min != arr[j]){
				swap(arr[j], arr[indexMin]);
				compCount++;
				moveCount = moveCount+3;
			}
		}

	}

	////////MERGE SORT//////

	//calls actualMergeSort, since the parameters weren't enough
	void mergeSort( int *arr, int size, int &compCount, int &moveCount){

		actualMergeSort(arr, 0, size-1, compCount, moveCount);

	}

	//merges two subarrays
	void merge(int *arr, int first, int mid, int last, int &compCount, int &moveCount){

		int *result = new int[last - first +1];

		int f1 = first;
		int l1 = mid;
		int f2 = mid + 1;
		int l2 = last;

		int i = 0;

		while((f1 <=l1) && (f2 <= l2)){
			compCount++;
			moveCount++;
			if(arr[f1] <= arr[f2]){
				result[i] = arr[f1];
				f1++;
			}
			else{
				result[i] = arr[f2];
				f2++;
			}
			i++;
		}

		//finishing the left outs from the first sub array
		while(f1 <= l1){
			moveCount++;
			result[i] = arr[f1];
			f1++;
			i++;
		}

		//finishing the left outs from the second sub array
		while(f2 <= l2){
			moveCount++;
			result[i] = arr[f2];
			f2++;
			i++;
		}

		//copying the resultant array to the original array
		for(int j = 0, k = first; (k <= last) && (j < (last - first +1)); j++, k++)
			arr[k] = result[j];

		delete []result;

	}

	//calls the merge method recursively to sort elements via divide and conquer
	void actualMergeSort(int *arr, int first, int last, int &compCount, int &moveCount){

		if(first < last){

			//finding the middle
			int mid = first + ((last - first)/2);

			//sort left part
			actualMergeSort(arr, first, mid, compCount, moveCount);

			//sort right part
			actualMergeSort(arr, mid+1, last, compCount, moveCount);

			//merge two parts
			merge(arr, first, mid, last, compCount, moveCount);
		}
	}


	/////////QUICK SORT/////////////

	//calls actualQuickSort, because the parameters of quickSort weren't enough
	void quickSort( int *arr, int size, int &compCount, double &moveCount){
		actualQuickSort(arr, 0, size-1, compCount, moveCount);

	}

	//calls partiiton method recursively to sort the array's elements
	void actualQuickSort(int *arr, int first, int last, int &compCount, double &moveCount){

		if(first < last){
			int pivotIndex = partition(arr, first, last, compCount, moveCount);
			actualQuickSort(arr, first, pivotIndex-1, compCount, moveCount);
			actualQuickSort(arr, pivotIndex+1, last, compCount, moveCount);
		}
	}

	//Partitions the elements in the given arrays indices and returns the pivot index.
	//Partitions the array by choosing the pivot as the last element of the array.
	int partition(int *arr, int first, int last, int &compCount, double &moveCount){
		if(first < last){
			int pivot = arr[last];
			int i = first-1;
			for(int j = first; j < last; j++){
				if(arr[j] <= pivot){
					swap(arr[j], arr[++i]);
					moveCount = moveCount+3;
					compCount++;
				}
			}
			swap(arr[++i], arr[last]);
			moveCount = moveCount+3;
			return i;
		}

	}


