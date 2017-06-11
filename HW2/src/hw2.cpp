/*
 * hw2.cpp
 *
 * Created on: Oct 23, 2015
 * Author: Gulsum Gudukbay
 * Student ID: 21401148
 * Section: 1
 */

#include "hw2.h"
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
NgramTree::NgramTree() {
	rootN = NULL;
}

NgramTree::~NgramTree() {
	destroyTree(rootN);
}

//preorder traversal
void NgramTree::destroyTree(Ngram *& tree){
	if(tree != NULL){
		destroyTree(tree->leftChild);
		destroyTree(tree->rightChild);
		delete tree;
		tree = NULL;
	}
}

//actual addNgram method
void NgramTree::addNgram(string ngram){
	addNgram2(ngram,rootN);
}

//recursively adds an ngram to the specified root
void NgramTree::addNgram2(string ngram, Ngram *cur){

	if(!ngram.empty() && ngram[0]!= ' '){

		//if empty tree, root becomes the added ngram
		if(rootN == NULL){
			rootN = new Ngram();
			rootN->data = ngram;
			(rootN->count)++;
			rootN->leftChild = NULL;
			rootN->rightChild = NULL;
		}
		else{
			//if added ngram doesn't exists in the present ngram tree
			if(ngram.compare(cur->data)!=0){
				//if added ngram should be before the current root alphabetically, left child is checked
				if(ngram.compare(cur->data)<0){

					//if left child exists, the left child of it is checked
					if(cur->leftChild)
						addNgram2(ngram,cur->leftChild);

					//if left child doesn't exist, added ngram becomes the left child
					else{
						cur->leftChild = new Ngram();
						(cur->leftChild)->data = ngram;
						((cur->leftChild)->count)++;
						(cur->leftChild)->leftChild = NULL;
						(cur->leftChild)->rightChild = NULL;
					}
				}

				//if added ngram should be after the current root alphabetically, right child is checked
				else{

					//if right child exists, the right child of it is checked
					if(cur->rightChild)
						addNgram2(ngram,cur->rightChild);

					//if right child doesn't exist, added ngram becomes the right child
					else{
						cur->rightChild = new Ngram();
						(cur->rightChild)->data = ngram;
						((cur->rightChild)->count)++;
						(cur->rightChild)->leftChild = NULL;
						(cur->rightChild)->rightChild = NULL;
					}
				}
			}

			//if added ngram exists in the present ngram tree, its frequency is increased by 1
			else
				(cur->count)++;
		}
	}
}

//actual getTotalNgramCount method
int NgramTree::getTotalNgramCount(){
	return nGramCount(rootN);
}

//recursively returns the number of unique ngrams
int NgramTree::nGramCount(Ngram *cur){
	if(cur != NULL){
		//root is counted
		int c = 1;
		//if left child is not null, it is counted as well
		if(cur->leftChild)
			c += nGramCount(cur->leftChild);
		//if right child is not null, it is counted as well
		if(cur->rightChild)
			c += nGramCount(cur->rightChild);
		return c;
	}
	else
		return 0;
}

//actual printNgramFrequencies method
void NgramTree::printNgramFrequencies(){
	print(rootN);
}

//recursively prints all the ngrams and their ocurrence numbers
void NgramTree::print(Ngram *cur){

	if(cur != NULL){
		//inorder traversal: first left, then root, then right child
		if(cur->leftChild != NULL)
			print(cur->leftChild);
		cout<<cur->data<< " appears " << cur->count<< " time(s)."<<endl;
		if(cur->rightChild != NULL)
			print(cur->rightChild);
	}
	else
		cout<<"BST is empty."<<endl;
}

bool NgramTree::isComplete(){
	int size = getTotalNgramCount();
	return isCompleteTree(rootN, 0, size);
}

//horizontal traversal is made to find whether if the tree is complete or not
bool NgramTree::isCompleteTree(Ngram *cur, int index, int treeNodeCount){
	if(cur == NULL)
		return true;
	//if index is larger than or equal to the total number of tree nodes, the tree is not complete, since the last row of nodes have 2 levels of or more parents missing
	else if(index >= treeNodeCount)
		return false;
	else{
		//recursive case, indices are determined like the array based implementation, left child of i is 2i+1, right child of i is 2i+2
		return isCompleteTree(cur->leftChild, (2*index)+1, treeNodeCount) && isCompleteTree(cur->rightChild, (2*index)+2, treeNodeCount);
	}

}

//actual isFull method
bool NgramTree::isFull(){
	return isFullTree(rootN);
}

//checks recursively whether each node has two children or not
bool NgramTree::isFullTree(Ngram *cur){
	//an empty tree is assumed as full tree
	if(cur == NULL)
		return true;
	//a leaf node is assumed to be full
	else if(cur->leftChild == NULL && cur->rightChild == NULL)
		return true;
	//if there are both children present, the children are checked
	else if(cur->leftChild && cur->rightChild)
		return isFullTree(cur->leftChild) && isFullTree(cur->rightChild);
	//if only one child is present, tree is not full
	else
		return false;
}

//generates an ngram tree with the specified ngram length and the string
void NgramTree::generateTree(string fileName, int n){

/*
	//read file
	string input, buf;
	ifstream inputFile(fileName);
	while(!inputFile.eof()) {
	    getline(inputFile, buf);
	    input += buf;
	}

	string substring;
	int index = n-1;
	char c = input[index];

	//while string is not empty
	while( c != '\0'){
		substring = string();
		bool found = false;
		for( int i = 0; i < n; i++)	{
			if( input[index - n + 1 + i] != ' ' && input[index - n + 1 + i] != '\n' && input[index - n + 1 + i] != '\t' ){
				substring[i] = input[index - n + 1 + i];
				found = true;
			}
			else{
				index = index + i;
				found = false;
				break;
			}
		}
		if(found){
			addNgram(substring);
			index++;
			c = input[index];
		}
	}
*/


	for(int i = 0; i < fileName.length()-n+1; i++){
		bool b = false; //assumed that there aren't any space or new line characters in the next n characters
		for(int j = i; j < n+i; j++){
			if(fileName[j] == ' ' || fileName[j] == '\n' || fileName[j] == '\t' )//if the string has any unwanted characters, false assumption becomes true
				b = true;
		}
		if(!b){
			string added = fileName.substr(i, n);
			//adds tha substring starting from i and n characters long
			addNgram(added);
		}
	}
}

/*

void NgramTree::deleteN(string ngram){
	rootN = deleteNgram(ngram, rootN);
}

NgramTree::Ngram* NgramTree::deleteNgram(string ngram, Ngram*cur){
	if(!cur)
		return NULL;
	else if(ngram.compare(cur->data) < 0)
		cur->leftChild = deleteNgram(ngram, cur->leftChild);
	else if(ngram.compare(cur->data) > 0)
		cur->rightChild = deleteNgram(ngram, cur->rightChild);
	else{
		if(!(cur->leftChild) && !(cur->rightChild)){
			delete cur;
			cur = NULL;
		}
		else if(!(cur->leftChild)){

			Ngram* temp = cur;
			cur = cur->rightChild;
			delete temp;
			temp = NULL;
		}
		else if(!(cur->rightChild)){
			Ngram* temp = cur;
			cur = cur->leftChild;
			delete temp;
			temp = NULL;
		}
		else{
			Ngram* inSuccessor = findMin(cur->rightChild);
			cur->data = inSuccessor->data;
			cur->count = inSuccessor->count;
			cur->rightChild = deleteNgram(inSuccessor->data, cur->rightChild);
		}
	}
	return cur;

}
NgramTree::Ngram* NgramTree::findMin(Ngram* cur){
	if(!cur->leftChild)
		return cur;
	else
		return findMin(cur->leftChild);


}
*/






