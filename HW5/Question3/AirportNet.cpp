/*
 * AirportNet.cpp
 *
 * Created on: Dec 24, 2015
 * Author: Gulsum Gudukbay
 * Student ID: 21401148
 */

#include "AirportNet.h"

AirportNet::AirportNet(const string aname){

	ifstream inputFile(aname.c_str());
	if(inputFile.is_open()){
		string *lines;
		lines= new string[1000];

		for(int i = 0; i < 1000; i++)
			lines[i] = "";

		string line = "";
		int index = 0;

		while(getline(inputFile, line,'\n')){
			lines[index] = line;
			++index;
		}
		connectionNo = index;
		airports = new string[connectionNo];
		airportNo = 1;

		//filling up the vertex (airport array)
		for(int i = 1; i < connectionNo; i++){
			int originLength = 0;
			int destinationLength = 0;

			//adding origin to the airports array
			while(lines[i].at(originLength) != ' ')
				originLength++;
			if(!searchAirports(lines[i].substr(0, originLength))){
				airports[airportNo] = lines[i].substr(0, originLength);
				++airportNo;
			}

			++originLength;
			//adding destination to the airports array
			while(lines[i].at(originLength + destinationLength) != ' ')
				destinationLength++;
			//destinationLength++;
			if(!searchAirports(lines[i].substr(originLength, destinationLength))){
				airports[airportNo] = lines[i].substr(originLength, destinationLength);
				++airportNo;
			}

		}

		//deleting unnecessary memory allocation
		string *temp = new string[airportNo];
		for(int i = 0; i < airportNo; i++)
			temp[i] = airports[i];
		delete[] airports;
		airports = new string[airportNo];
		for(int i = 0; i < airportNo; i++)
			airports[i] = temp[i];
		delete[] temp;
		temp = NULL;


		for(int i = 1; i < airportNo; i++)
			cout<<airports[i]<<" ";
		cout<<endl;
		//declaring adjacency matrix
		connections = new int*[airportNo];
		for(int i = 0; i < airportNo; i++){
			connections[i] = new int[airportNo];
			for(int j = 1; j < airportNo;j++)
				connections[i][j] = 0;

		}

		//initializind visited matrix for dfs
		visited = new int[airportNo];
		for(int j = 0; j < airportNo; j++)
			visited[j] = 0;


		//initializing the airports in the adjacency matrix
		for(int i = 0; i < airportNo; i++){
			connections[0][i] = i;
			connections[i][0] = i;
			connections[i][i] = 0; //same destination & origin
		}

		int row = 0;
		int col = 0;
		//filling up the adjacency matrix (connections)
		for(int i = 1; i < connectionNo; i++){
			int originLength = 0;
			int destinationLength = 0;

			while(lines[i].at(originLength) != ' '){
				originLength++;
			}
			row = indexOf(lines[i].substr(0, originLength));

			++originLength;
			while(lines[i].at(originLength + destinationLength) != ' ')
				destinationLength++;
			//destinationLength++;
			col = indexOf(lines[i].substr(originLength, destinationLength));

			string weightStr = lines[i].substr(originLength + destinationLength);
			int weight = atoi(weightStr.c_str());
			if(row != -1 && col != -1){
				connections[row][col] = weight;
				connections[col][row] = weight;
			}

		}

		for(int i = 0; i < airportNo; i++){
			for(int j = 0; j < airportNo; j++)
				cout<<connections[i][j]<<"\t";
			cout<<endl;
		}
		cout<<endl;
		delete []lines;
		lines =  NULL;
	}
	else{
		airports = new string[1];
		airports[0] = "";
		connections = new int*[1];
		connections[0] = new int[1];
		connections[0][0] = -1;
		connectionNo = 0;
		airportNo = 0;
	}
}

AirportNet::AirportNet(const AirportNet& aNet){

	for(int i = 0; i < airportNo; i++){
		aNet.airports[i] = airports[i];
		aNet.visited[i] = visited[i];
		for(int j = 0; j < airportNo; j++)
			aNet.connections[i][j] = connections[i][j];
	}
}


AirportNet::~AirportNet(){
	delete []airports;
	airports = NULL;
	for(int i = 0; i < airportNo; i++)
		delete []connections[i];
	delete []connections;
	connections = NULL;
	delete []visited;
	visited = NULL;
}

void AirportNet::listDirectFlights(const string aname){
	int index = indexOf(aname);
	if(searchAirports(aname)){
		int count = 0;
		for(int i = 1; i < airportNo; i++)
			if(connections[index][i] != 0)
				count++;
		cout<<"From "<<aname<<" "<<count<<" airports are directly reachable: ";

		for(int i = 1; i < airportNo; i++){
			if(connections[index][i] != 0)
				cout<<airports[i]<<"  ";
		}
		cout<<endl;

	}
	else
		cout<<aname<<" does not exist in the airport network."<<endl;
}

void AirportNet::listRoutesOnHubAirport(const string aname){

	int index = indexOf(aname);
	if(index != -1){
		cout<<"If "<<aname<<" is considered as hub, these routes are possible: "<<endl;

		for(int i = 1; i < airportNo; i++){
			string origin = "";
			string destination = "";
			if(connections[i][index] != 0){
				origin = airports[i];

				for(int j = 1; j < airportNo; j++)
					if(connections[index][j] != 0){
						destination = airports[j];
						if(origin.compare(destination) != 0)
							cout<<"<"<<origin<<", "<<destination<<">"<<endl;
					}
			}
		}
	}
}

void AirportNet::findConnectedComponents(){
	int index = 1;
	for(int i = 1; i < airportNo; i++){
		int count = cc(i);
		if(count != 0){
			cout<<"For component "<<index<<": "<<count<<" nodes"<<endl;
			index++;
		}
	}
}

void AirportNet::displayMostCentralAirport(){

	double *centralities = new double[airportNo];
	for(int i = 0; i < airportNo; i++)
		centralities[i] = 0;

	for(int k = 1; k < airportNo; k++){
		double sum = 1;
		int noOfShortestPaths = 1;
			for(int i = 1; i < airportNo; i++){
				string origin = "";
				string destination = "";
				if(connections[i][k] != 0){
					origin = airports[i];

					for(int j = 1; j < airportNo; j++)
						if(connections[k][j] != 0){
							destination = airports[j];
							if(origin.compare(destination) != 0){
								++noOfShortestPaths;
								sum+= connections[indexOf(origin)][indexOf(destination)];
							}
						}

				}
				centralities[i] = noOfShortestPaths/sum;
			}
	}

	//finding max in the array of centralities
	double curMax = -1;
	int i;
	int curMaxIndex;
	for(i = 0; i < airportNo; i++)
		if(curMax < centralities[i]){
			curMax = centralities[i];
			curMaxIndex = i;
		}

	cout<<"The most central airport in the network is: "<<airports[curMaxIndex]<<endl;

	delete[] centralities;
	centralities = NULL;
}


//private

//returns number of nodes in the connected component specified
int AirportNet::cc(int id){
	int firstId = id;
	int count = 0;
	for(int i = 1; i < airportNo; i++){
		if(visited[i] == 0){
			depthFirstSearch(indexOf(airports[i]), id++);
		}
	}
	for(int j = 1; j < airportNo; j++){
		if(visited[j] == firstId)
			count++;
	}
	return count;
}

//airport neighbor search for the graph
void AirportNet::depthFirstSearch(int airport, int id){
	int neighbor;
	visited[indexOf(airports[airport])] = id;
	for(neighbor = 1; neighbor < airportNo; neighbor++){
		if(connections[airport][neighbor] != 0 && visited[neighbor] == 0){
			visited[neighbor] = id;
		}
	}
}

bool AirportNet::searchAirports(string ap){
	bool flag = false;
	for(int i = 0; i < airportNo && !flag; i++)
		if(airports[i].compare(ap) == 0)
			flag = true;
	return flag;
}

int AirportNet::indexOf(string ap){
	int index = -1;
	for(int i = 0; i < airportNo; i++)
		if(airports[i].compare(ap) == 0)
			index = i;
	return index;

}

