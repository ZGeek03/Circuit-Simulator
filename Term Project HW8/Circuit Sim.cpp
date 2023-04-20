#include "Circuit.h"
#include "Event.h"
#include "Wire.h"
#include "Gate.h"
#include <queue>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int ReadCircuit(Circuit* MC, string fileName);
int ReadInitConditions(priority_queue<Event*>* EQ);
int SimulateCircuit(priority_queue<Event*> *EQ);
int PrintResults();

int main() {
	string fileName;
	priority_queue<Event*> EventQueue;
	Circuit MainCircuit;
	fstream InitFile;
	InitFile.open("circuit0_v.txt");

	cout << "Please enter the name of your Circuit File." << endl << ">> ";
	cin >> fileName;
	cout << endl;

	int read = ReadCircuit(&MainCircuit, fileName);

	if (read == 1) {
		cout << "Problem opening file with the requested name." << endl
			<< "Verify you spelled it correctly and try again." << endl;
		return read;
	}
	

	int init = ReadInitConditions(&EventQueue);

	int simulated = SimulateCircuit(&EventQueue);

	int printed = PrintResults();

	return 0;
}

// Each function returns an int regarding the error status.
// Return of 1 means error opening file.
int ReadCircuit(Circuit* MC, string fileName) { // DONE-----------------------
	fstream CircuitFile;
	vector<string> FileLinePart;
	string FileLine;
	CircuitFile.open(fileName);

	if (!CircuitFile.is_open()) {
		return 1;
	}
	// 1. Get Circuit Header
	for (int i = 2; i > 0; i--) {
		CircuitFile >> FileLine;
		FileLinePart.push_back(FileLine);
	}

	// Set the Circuit's name appropriately.
	MC->SetCircuitName(FileLinePart.at(1));

	// Clear some things to prepare for future data processing.
	getline(CircuitFile, FileLine);
	FileLinePart.clear();

	while (!CircuitFile.eof()) {
		getline(CircuitFile, FileLine);

		MC->ParseCircuitFile(FileLine);
	}
	

	cout << "Read circuit definition successfully." << endl;
	return 0;
}

int ReadInitConditions(priority_queue<Event*>* EQ) { // TODO
	cout << "Read initial conditions successfully." << endl;
	return 0;
}

int SimulateCircuit(priority_queue<Event*> *EQ) { // TODO
	cout << "Successfully simulated circuit." << endl;
	return 0;
}

int PrintResults() { // TODO
	cout << "Printed results." << endl;
	return 0;
}