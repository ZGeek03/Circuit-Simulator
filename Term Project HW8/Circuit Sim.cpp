#include "Event.h"
#include "Wire.h"
#include "Gate.h"
#include <queue>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int ReadCircuit(priority_queue<Event*> *EQ, string fileName);
int ReadInitConditions(fstream *IF);
int SimulateCircuit(priority_queue<Event*> *EQ);
int PrintResults();

int main() {
	string fileName;
	priority_queue<Event*> EventQueue;
	fstream InitFile;
	InitFile.open("circuit0_v.txt");

	cout << "Please enter the name of your Circuit File." << endl << ">> ";
	cin >> fileName;
	cout << endl;

	int read = ReadCircuit(&EventQueue, fileName);

	if (read == 1) {
		cout << "Problem opening file with the requested name." << endl
			<< "Verify you spelled it correctly and try again." << endl;
		return read;
	}
	

	int init = ReadInitConditions(&InitFile);

	int simulated = SimulateCircuit(&EventQueue);

	int printed = PrintResults();

	return 0;
}

// Each function returns an int regarding the error status.
// Return of 1 means error opening file.
int ReadCircuit(priority_queue<Event*> *EQ, string fileName) {
	fstream CircuitFile;
	string FileLine1, FileLine2, FileLine3;
	CircuitFile.open(fileName);

	if (!CircuitFile.is_open()) {
		return 1;
	}
	// 1. Get Circuit Header
	CircuitFile >> FileLine1 >> FileLine2;

	

	return 0;
}

int ReadInitConditions(fstream *IF) {
	return 0;
}

int SimulateCircuit(priority_queue<Event*> *EQ) {
	return 0;
}

int PrintResults() {
	return 0;
}