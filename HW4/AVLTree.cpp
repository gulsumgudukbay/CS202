/*
 * AVLTree.cpp
 *
 * Created on: Dec 3, 2015
 * Author: Gulsum Gudukbay
 * Student ID: 21401148
 */

#include "AVLTree.h"

AVLTree::AVLTree(){
	treeRoot = NULL;
	totalWordCount = 0;
}

AVLTree::~AVLTree() {

	clr(treeRoot);
}

void AVLTree::generateTree(string inputFileName){

	string line;
	string word;

	ifstream inputF(inputFileName.c_str());

	if(inputF.is_open()){
		//initialize element count
		totalWordCount = 0;

		//getting lines from the text file
		while(getline(inputF,line)){
			//erasing punctuations in every line
			for (int i = 0; i < line.length(); i++){
				if (ispunct(line[ i]))
					line.erase(i--, 1);
		}
			//declaring a string stream for getting the words with the input operator
			istringstream iss(line);

			//adding words to the tree
			while(iss >> word){
				addWord(word.c_str());
			}
		}

		inputF.close();
	}
}

void AVLTree::addWord(string s){
	treeRoot = addWord2(treeRoot, s);
}



void AVLTree::printHeight(){

	cout<<"Height of the tree is: " <<height(treeRoot)<<endl;
}

void AVLTree::printTotalWordCount(){
	cout<<totalWordCount<<endl;
}

void AVLTree::printWordFrequencies(){
	if(treeRoot){
		cout<<" print "<<endl;
		cout<<wordFrequencies(treeRoot);
	}
}


void AVLTree::printLeastFrequent(){

	int minFreq;
	string data;
	if(!treeRoot)
		minFreq = -1;
	else
		minFreq = leastFreq(treeRoot, treeRoot->frequency,data);
	cout<<"Least Frequent: "<<data<<" " << minFreq<<endl;

}

void AVLTree::printMostFrequent(){

	int maxFreq;
	string data;
	if(!treeRoot)
		maxFreq = -1;
	else
		maxFreq = mostFreq(treeRoot, treeRoot->frequency,data);
	cout<<"Most Frequent: "<<data<<" " << maxFreq<<endl;
}


void AVLTree::printStandardDeviation(){

	if(treeRoot){
		string most = treeRoot->data;
		string least = treeRoot->data;

		int maxFreq = mostFreq(treeRoot,treeRoot->frequency,most);
		int minFreq = leastFreq(treeRoot,treeRoot->frequency,least);

		double mean = (maxFreq - minFreq)/2;
		double variance = (((maxFreq - mean)*(maxFreq - mean))+((minFreq - mean)*(minFreq - mean)))/2;
		stdev = sqrt(variance);
		cout<<"Standard Deviation: "<< stdev;
	}
	else
		cout<<"Tree Empty"<<endl;
}

void AVLTree::generateStatistics(string outputFStatistics){

	ofstream outputF;
	outputF.open(outputFStatistics.c_str());

	if(treeRoot){
		string most = treeRoot->data;
		string least = treeRoot->data;


		int maxFreq = mostFreq(treeRoot,treeRoot->frequency, most);
		int minFreq = leastFreq(treeRoot,treeRoot->frequency,least);


		outputF << "Total Word Count: "<<totalWordCount << endl;
		outputF << "Tree Height: "<<height(treeRoot) << endl;
		outputF << "Most Frequent: "<<most<<" "<<maxFreq<< endl;
		outputF << "Least Frequent: "<<least<<" "<<minFreq << endl;
		outputF << "Standard Deviation: "<<stdev<<endl;
	}
	else
		outputF <<"Tree Empty"<<endl;
	outputF.close();
}

void AVLTree::generateWordFreqs(string outputFWordFreqs){

	ofstream outputF;
	outputF.open(outputFWordFreqs.c_str());
	outputF<<wordFrequencies(treeRoot);
	outputF.close();

}


//Private Functions


string AVLTree::wordFrequencies(AVLWord *root){

	if(treeRoot){
		string left = "";
		if(root->left)
			left = wordFrequencies(root->left);
		string right = "";
		if(root->right)
			right = wordFrequencies(root->right);
		stringstream result;
		result<< "" << left << "\n" <<root->data<< ": " << root->frequency << "\n" <<right <<"";
		string res = result.str();
		return res;
	}
	else
		return "-1";

}

void AVLTree::fixHeight(AVLWord* root)
{
    int hl = height(root->left);
    int hr = height(root->right);
    root->height = max(hl, hr) +1;
}


AVLTree::AVLWord* AVLTree::addWord2(AVLWord *root, string s){

	if((s).compare("") != 0){
		if(!root){
			AVLWord *added = new AVLWord;
			added->left = NULL;
			added->right = NULL;
			added->height = 1;
			added->data = s;
			added->frequency = 1;
			return added;
		}
		else if((root->data).compare(s) == 0){
			(root->frequency)++;
		}
		else if ((root->data).compare(s) < 0){
			root->right = addWord2(root->right,s);
			root = balanceTree(root);
		}
		else{
			root->left = addWord2(root->left,s);
			root = balanceTree(root);
		}
		totalWordCount++;
		return root;
	}
	//cannot add null string
	else
		return NULL;

}


AVLTree::AVLWord* AVLTree::balanceTree(AVLWord *root){

	fixHeight(root);

	int bFactor = balanceFactor(root);
	//right skewed root
	if(bFactor > 1){

		//root's right child is left skewed like a greater than sign, double rl rotation
		if(balanceFactor(root->right) < 0)
			root = rotateRL(root);
		//root's right child is also right skewed, single rotation
		else
			root = rotateLeft(root);
	}

	//left skewed root
	else if(bFactor < -1){
		//root's left child is right skewed like a less than sign, double lr rotation
		if(balanceFactor(root->left) > 0)
			root = rotateLR(root);
		//root's left child is also left skewed, single rotation
		else
			root = rotateRight(root);
	}
	return root;
}

AVLTree::AVLWord* AVLTree::rotateLeft(AVLWord *root){

	AVLWord *temp = root->right;
	root->right = temp->left;
	temp->left = root;
	fixHeight(root);
	fixHeight(temp);
	return temp;
}

AVLTree::AVLWord* AVLTree::rotateRight(AVLWord *root){


	AVLWord *temp = root->left;
	root->left = temp->right;
	temp->right = root;
	fixHeight(root);
	fixHeight(temp);
	return temp;
}

AVLTree::AVLWord* AVLTree::rotateLR(AVLWord *root){


	AVLWord *temp = root->left;
	root->left = rotateLeft(temp);
	return rotateRight(root);

}

AVLTree::AVLWord* AVLTree::rotateRL(AVLWord *root){

	AVLWord *temp = root->right;
	root->right = rotateRight(temp);
	return rotateLeft(root);
}


void AVLTree::clr(AVLWord *root){

	if(root){
		clr(root->left);
		clr(root->right);
		delete root;
		root = NULL;
	}
}

int AVLTree::max(int i1, int i2){

	if(i1 > i2)
		return i1;
	else
		return i2;
}

int AVLTree::min(int i1, int i2){

	if(i1 < i2)
		return i1;
	else
		return i2;
}

void AVLTree::inorderPrintTest(AVLWord *root){
	if(root){
		inorderPrintTest(root->left);
		cout<<root->data<<", ";
		inorderPrintTest(root->right);
	}
}

int AVLTree::balanceFactor(AVLWord *root){

	int balanceFactor = 0;
	if(root){
		int leftHeight = height(root->left);
		int rightHeight = height(root->right);
		balanceFactor = rightHeight - leftHeight;

		//if the tree is right skewed, balanceFactor>0, if left balanceFactor<0, if equal, balance factor is 0
	}
	return balanceFactor;

}

int AVLTree::height(AVLWord *root){

	if(root)
		return root->height;
	else
		return 0;
}

int AVLTree::mostFreq(AVLWord *root, int curMax, string &data){
	if(!root){
		return curMax;
	}
	if(root->frequency>curMax){
	curMax = max(curMax,root->frequency);
	data = root->data;
	}
	return max(mostFreq(root->left, curMax, data),mostFreq(root->right,curMax,data));

}

int AVLTree::leastFreq(AVLWord *root, int curMin, string &data){

	if(!root)
		return curMin;
	if(root->frequency<curMin){
		curMin = min(curMin,root->frequency);
		data = root->data;
	}

	return min(leastFreq(root->left, curMin, data),leastFreq(root->right,curMin,data));

}

int main(int argc, char **argv){
	string inputFile(argv[1]);
	string outputFStatistics("statistics.txt");
	string outputFWordFreqs("wordFreqs.txt");

	AVLTree tree;
	tree.generateTree(inputFile);
	tree.printHeight();
	tree.printTotalWordCount();
	tree.printWordFrequencies();
	tree.printMostFrequent();
	tree.printLeastFrequent();
	tree.printStandardDeviation();

	tree.generateStatistics(outputFStatistics);
	tree.generateWordFreqs(outputFWordFreqs);

	return 0;
}

