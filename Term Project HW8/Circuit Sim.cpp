#include "Circuit.h"
#include "Event.h"
#include "Wire.h"
#include "Gate.h"
#include "CompareEvent.h"
#include <queue>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int ReadCircuit(Circuit* MC, string fileName);
int ReadInitConditions(priority_queue<Event*, vector<Event*>, CompareEvent>* EQ, string fileName, int *eventCount);
int SimulateCircuit(priority_queue<Event*, vector<Event*>, CompareEvent> *EQ, Circuit* MC, int *eventCount);
int PrintResults();
vector<string> VectorSplitLine(string const line);

int main() {
	string fileName;
	int curEventCount = 0;
	// The parameters allows for custom ordering rules for the object in priority_queue.
	priority_queue<Event*, vector<Event*>, CompareEvent> EventQueue;
	Circuit MainCircuit;

	cout << "Please enter the name of your Circuit File." << endl << ">> ";
	cin >> fileName;
	cout << endl;

	int read = ReadCircuit(&MainCircuit, fileName);

	if (read == 1) {
		cout << "Problem opening file with the requested name." << endl
			<< "Verify you spelled it correctly and try again." << endl;
		return read;
	}
	

	int init = ReadInitConditions(&EventQueue, fileName, &curEventCount);

	if (init == 1) {
		cout << "Problem opening vector file with the requested name." << endl
			<< "Verify the file is in the same folder as definition file." << endl;
		return init;
	}

	int simulated = SimulateCircuit(&EventQueue, &MainCircuit, &curEventCount);

	int printed = PrintResults();

	return 0;
}

// Each function returns an int regarding the error status.
// Return of 1 means error opening file.
// Read the main circuit definition file, saving the details to a Circuit object.
int ReadCircuit(Circuit* MC, string fileName) { // DONE-----------------------
	fstream CircuitFile;
	vector<string> FileLinePart;
	string FileLine;
	CircuitFile.open(fileName);

	if (!CircuitFile.is_open()) { return 1; }
	// Get Circuit Header
	for (int i = 2; i > 0; i--) {
		CircuitFile >> FileLine;
		FileLinePart.push_back(FileLine);
	}

	// Set the Circuit's name appropriately.
	MC->SetCircuitName(FileLinePart.at(1));

	// Clear some things to prepare for future data processing.
	getline(CircuitFile, FileLine);
	FileLinePart.clear();

	// Get first good line.
	getline(CircuitFile, FileLine);
	// Loop through file until either eof or we hit an empty line.
	while (!CircuitFile.eof() && FileLine != "") {
		MC->ParseCircuitFile(FileLine);

		getline(CircuitFile, FileLine);
	}
	

	cout << "Read circuit definition successfully." << endl;
	CircuitFile.close();
	return 0;
}

// Read the initial conditions, and future circuit conditions from Vector File, saving each
// event to a priority_queue storing Event objects.
int ReadInitConditions(priority_queue<Event*, vector<Event*>, CompareEvent>* EQ, string fileName, int *eventCount) { // DONE-------------------
	fstream VectorFile;
	vector<string> FileLinePart;
	string FileLine, vectoredFN;
	int nameEnd = fileName.find('.');

	// Format file name and open vector file.
	vectoredFN = fileName;
	vectoredFN.insert(nameEnd, "_v");
	VectorFile.open(vectoredFN);

	if (!VectorFile.is_open()) { return 1; }

	// Collect the Vector Header line to prepare to parse future lines.
	getline(VectorFile, FileLine);

	// Get first line that matters.
	getline(VectorFile, FileLine);

	// Loop as long as we aren't at the end of file, and the next line isn't empty.
	while (!VectorFile.eof() && FileLine != "") {
		// Split up the File Line retreived, and put into separate variables.
		FileLinePart = VectorSplitLine(FileLine);
		string WireName = FileLinePart.at(1);
		int    time     = stoi(FileLinePart.at(2));
		char   state    = (FileLinePart.at(3))[0]; // Get the first character in string

		// Push an Event object with the characteristics retreived above.
		EQ->push(new Event(WireName, time, state, *eventCount));

		(*eventCount)++;
		getline(VectorFile, FileLine);
	}

	cout << "Read initial conditions successfully." << endl;
	VectorFile.close();
	return 0;
}

// TODO: Fix setting wires and creating Events for Inputs vs. Outputs.
int SimulateCircuit(priority_queue<Event*, vector<Event*>, CompareEvent> *EQ, Circuit* MC, int *eventCount) { // TODO
	int circuitTime = 0, newEventTime;
	char newState;
	string newEventWName;
	Event* newEvent;

	while (circuitTime < 60 && !EQ->empty()) {
		Event* nextEvent = EQ->top();

		// Get and set the next state of the wire.
		Wire* modifiedW = MC->GetWire(nextEvent->GetWireName());
		modifiedW->SetState(nextEvent->GetState());

		// Append the change to the wire history.
		modifiedW->SetHistory(nextEvent->GetState());

		// Evaluate the gate connected, and see if the output will change.
		vector<Gate*> modifiedWGates = modifiedW->GetDrives();

		for (int i = 0; i < modifiedWGates.size(); i++) {
			// Exercise the logic
			newState = modifiedWGates.at(i)->ExerciseLogic();

			// Create event for output change
			newEventTime = circuitTime + modifiedWGates.at(i)->GetDelay();
			newEventWName = modifiedWGates.at(i)->GetOutput()->GetName();
			newEvent = new Event(newEventWName, newEventTime, newState, *eventCount);
			(*eventCount)++;

			// Append the new event to the Event Queue.
			EQ->push(newEvent);
		}
		// Delete the top Event in the EQ since we handled it.
		EQ->pop();

		// Modify circuitTime according to the event timestamp.
		circuitTime = nextEvent->GetTime();
	}

	cout << "Successfully simulated circuit." << endl;
	return 0;
}

int PrintResults() { // TODO
	cout << "Printed results." << endl;
	return 0;
}

// Extra function needed to process Vector File.
// TODO: Decide if this needs moved to Event class.
vector<string> VectorSplitLine(string const line) {
	vector<string> lineParts;
	string linePart;
	int spaceNum = 0;

	// Loop through the line, splitting the string at each whitespace
	for (int i = 0; i < line.length(); i++) {
		if (isalnum(line.at(i))) {
			spaceNum = 0;
			linePart += line.at(i);
		}
		else if (spaceNum == 0 && line.at(i) == ' ') {
			spaceNum++;
			lineParts.push_back(linePart);
			linePart.clear();
		}
	}
	// Push back the last value retreived
	lineParts.push_back(linePart);

	return lineParts;
}