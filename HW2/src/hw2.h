/*
 * hw2.h
 *
 * Created on: Oct 23, 2015
 * Author: Gulsum Gudukbay
 * Student ID: 21401148
 *  * Section: 1
 *
 */

#ifndef NGRAMTREE_H_
#define NGRAMTREE_H_
using namespace std;
#include <iostream>
#include <string>

class NgramTree {

public:

	struct Ngram{

		string data;
		int count;
		Ngram *leftChild;
		Ngram *rightChild;
	};

	NgramTree();
	~NgramTree();

	void destroyTree(Ngram *& tree);
	void addNgram(string ngram);
	int getTotalNgramCount();
	void printNgramFrequencies();
	bool isComplete();
	bool isFull();
	void generateTree(string fileName, int n);

	//practice
	//void deleteN(string ngram);

private:
	Ngram *rootN;
	void addNgram2(string ngram, Ngram* cur);
	int nGramCount(Ngram *cur);
	void print(Ngram *cur);
	bool isFullTree(Ngram *cur);
	bool isCompleteTree(Ngram *cur, int index, int treeNodeCount);

	//practice
	//Ngram* deleteNgram(string ngram, Ngram*cur);
	//Ngram* findMin(Ngram* cur);


};

#endif /* NGRAMTREE_H_ */
