/*
 * heap.cpp, creates an array based heap structure that uses a sentinel value to hold the number of elements.
 *
 * Created on: Nov 16, 2015
 * Author: Gulsum Gudukbay
 * Section: 1
 * Student ID: 21401148
 */

#include "heap.h"

heap::heap(string inputFileName) {
	//Array based max heap implementation with a sentinel value elementCount
	arrSize = 10000;
	comparisons = 0;
	heapArr = new int[arrSize];
	string line;
	ifstream inputF(inputFileName.c_str());

	for(int i = 0; i < arrSize; i++)
		heapArr[i] = -1;


	//inserting elements from the file to the heapArr to construct the max heap structure
	if(inputF.is_open()){
		//initialize element count
		elementCount = 0;

		while(getline(inputF,line,'\n'))
			insert(atoi(line.c_str()));

		//initialElementCount is the elementCount in the file
		initialElementCount = elementCount;
		inputF.close();
	}
}

heap::~heap() {
	delete []heapArr;
}

void heap::insert(const int a){

	//inserts the a value to the end of heap
	heapArr[elementCount] = a;

	//trickle up
	int currentPlace = elementCount;
	int parent = (currentPlace - 1)/2;

	//swap parent with child if child is larger
	while( currentPlace > 0 && heapArr[currentPlace] > heapArr[parent]){
		int temp = heapArr[parent];
		heapArr[parent] = heapArr[currentPlace];
		heapArr[currentPlace] = temp;

		//assign indices again
		currentPlace = parent;
		parent = (currentPlace - 1)/2;
	}
	//increment element count after insertion
	++elementCount;

}

//returns the maximum element in the heap, which is the first element in the array, also known as the root
int heap::maximum(){
	return heapArr[0];
}

//deletes and returns the maximum element (first element in the array)
int heap::popMaximum(){

	//assign the first element to a variable not to lose it
	int max = maximum();

	//delete and assign the last element as the root to start to build a heap from 2 semiheaps
	heapArr[0] = heapArr[--elementCount];

	//assign the deleted value -1 to indicate that its place is empty
	heapArr[elementCount] = -1;

	//trickle down the root to its proper place with heapRebuild
	heapRebuild(0, elementCount);

	//return deleted element for heapSort purpose
	return max;

}

void heap::heapRebuild(int index, int toIndex){

	//left child
	int child = 2*index + 1;

	if(child < toIndex){
		int rightChild = child + 1;

		//if right child is greater, child becomes right child
		if(rightChild < toIndex && heapArr[rightChild] > heapArr[child])
			child = rightChild;
		comparisons++;

		//if root is smaller than larger child, swap them
		if(heapArr[index] < heapArr[child]){
			int temp = heapArr[index];
			heapArr[index] = heapArr[child];
			heapArr[child] = temp;

			//recursive call for the subtree
			heapRebuild(child, toIndex);
		}
		comparisons++;

	}
}


//prints the heap in order to test
void heap::heapPrint(){
	//cout<<"\nCurrent State of Heap Array "<<endl;
	//	for(int i = 0; i < initialElementCount; i++)
	//		cout<<heapArr[i]<<", ";
	cout<<"\nNumber of elements in the file is "<<initialElementCount<<endl;
	cout<<"Number of comparisons done "<<comparisons<<endl;
}



