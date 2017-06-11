/*
 * main.cpp
 *
 * Created on: Oct 10, 2015
 * Author: Gulsum Gudukbay
 * Student ID: 21401148
 */

#include "sorting.h"
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


int main() {

	//Declaration of variables
	const int inputSize = 10000;
	const int maxInputSize = 60000;

	int trial;

	double durationSelection;
	int compCountSelection;
	int moveCountSelection;

	double durationMerge;
	int compCountMerge;
	int moveCountMerge;

	double durationQuick;
	int compCountQuick;
	double moveCountQuick;

	//Program Code

	trial = 1;
	while((inputSize * trial) <= maxInputSize) {

		cout<<"\n INPUT SIZE: "<<inputSize*trial<<endl;

		//Initializing
		int *arrSelection = new int[inputSize*trial];
		int *arrMerge = new int[inputSize*trial];
		int *arrQuick = new int[inputSize*trial];

		compCountSelection = 0;
		moveCountSelection = 0;

		compCountMerge = 0;
		moveCountMerge = 0;

		compCountQuick = 0;
		moveCountQuick = 0;


		//Filling in the arrays (same values for each array)


		//Random
	    for (int i = 0; i < (inputSize * trial); i++){
			arrSelection[i] = rand() % 101;
			arrMerge[i] = arrSelection[i];
			arrQuick[i] = arrSelection[i];
		}


		/*
	  	//Descending
		for (int i = 0, j = (inputSize * trial); j >=1 && i < (inputSize * trial); i++, j--){
			arrSelection[i] = j;
			arrMerge[i] = arrSelection[i];
			arrQuick[i] = arrSelection[i];
		}
		*/

		/*
		//Ascending
		for (int i = 0; i < (inputSize * trial); i++){
			arrSelection[i] = i;
			arrMerge[i] = arrSelection[i];
			arrQuick[i] = arrSelection[i];
		}
		*/

		//SELECTION SORT
		//Store the starting time
		clock_t startTimeSelection = clock();

		selectionSort(arrSelection, (inputSize*trial), compCountSelection, moveCountSelection);

		//Compute the number of seconds that passed since the starting time
		durationSelection = 1000 * double(clock() - startTimeSelection) / CLOCKS_PER_SEC;
		cout << "SelectionSort took " << durationSelection << " milliseconds, " << compCountSelection << " comparisons and " << moveCountSelection << " moves."<< endl;

		//MERGE SORT
		//Store the starting time
		clock_t startTimeMerge = clock();
		mergeSort(arrMerge, (inputSize*trial), compCountMerge, moveCountMerge);

		//Compute the number of seconds that passed since the starting time
		durationMerge = 1000 * double(clock() - startTimeMerge) / CLOCKS_PER_SEC;
		cout << "MergeSort took " << durationMerge << " milliseconds, " << compCountMerge << " comparisons and " << moveCountMerge << " moves."<< endl;



		//QUICK SORT
		//Store the starting time
		clock_t startTimeQuick = clock();

		quickSort(arrQuick, (inputSize*trial), compCountQuick, moveCountQuick);

		//Compute the number of seconds that passed since the starting time
		durationQuick = 1000 * double(clock() - startTimeQuick) / CLOCKS_PER_SEC;
		cout << "QuickSort took " << durationQuick << " milliseconds, " << compCountQuick << " comparisons and " << moveCountQuick << " moves."<< endl;



		trial++;


		//Deleting all the dynamically created arrays
		delete []arrSelection;
		delete []arrMerge;
		delete []arrQuick;
	}

	return 0;
}
