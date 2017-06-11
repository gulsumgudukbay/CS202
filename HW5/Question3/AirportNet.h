/*
 * AirportNet.h
 *
 * Created on: Dec 24, 2015
 * Author: Gulsum Gudukbay
 * Student ID: 21401148
 */

#ifndef AIRPORTNET_H_
#define AIRPORTNET_H_
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

class AirportNet{

public:
AirportNet(const string aname);
AirportNet(const AirportNet& aNet); // copy contructor
~AirportNet(); // destructor
void listDirectFlights(const string aname);
void listRoutesOnHubAirport(const string aname);
void findConnectedComponents();
void displayMostCentralAirport();

private:
int connectionNo;
int airportNo;
string *airports;
int **connections;
int *visited;


bool searchAirports(string ap);
int indexOf(string ap);
void depthFirstSearch(int airport, int id);
int cc(int id);


};
#endif /* AIRPORTNET_H_ */
