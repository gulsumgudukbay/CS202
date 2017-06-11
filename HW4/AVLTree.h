/*
 * AVLTree.h
 *
 * Created on: Dec 3, 2015
 * Author: Gulsum Gudukbay
 * Student ID: 21401148
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_
#include <fstream>
#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
using namespace std;
class AVLTree {
public:

	struct AVLWord{
		AVLWord *left;
		AVLWord *right;
		int height;
		string data;
		int frequency;
	};

	AVLTree();
	virtual ~AVLTree();

	void addWord(string s);
	void generateTree(string inputFileName);
	void printHeight();
	void printTotalWordCount();
	void printWordFrequencies();
	void printMostFrequent();
	void printLeastFrequent();
	void printStandardDeviation();
	void generateStatistics(string outputFStatistics);
	void generateWordFreqs(string outputFWordFreqs);

	AVLWord *treeRoot;
	int totalWordCount;
	double stdev;
private:

	AVLTree::AVLWord* addWord2(AVLWord *root, string s);
	AVLWord* balanceTree(AVLWord *root);
	AVLWord* rotateLeft(AVLWord *root);
	AVLWord* rotateRight(AVLWord *root);
	AVLWord* rotateLR(AVLWord *root);
	AVLWord* rotateRL(AVLWord *root);
	void clr(AVLWord *root);
	int max(int i1, int i2);
	int min(int i1, int i2);
	void inorderPrintTest(AVLWord *root);
	int balanceFactor(AVLWord *root);
	int height(AVLWord *root);
	int mostFreq(AVLWord *root, int curMax, string &data);
	int leastFreq(AVLWord *root, int curMin, string &data);
	string wordFrequencies(AVLWord *root);
	void fixHeight(AVLWord *root);

};



#endif /* AVLTREE_H_ */
