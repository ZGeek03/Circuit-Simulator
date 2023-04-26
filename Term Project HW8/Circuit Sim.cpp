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
void PrintResults(Circuit *MC, int circuitTime);
vector<string> VectorSplitLine(string const line);
bool CheckForDuplicateEvent(priority_queue<Event*, vector<Event*>, CompareEvent> const EQ, Event* const EvtToCheck);

int main() {
	string fileName = " ";
	int curEventCount = 0;
	// The parameters allows for custom ordering rules for the object in priority_queue.
	priority_queue<Event*, vector<Event*>, CompareEvent> EventQueue;
	Circuit MainCircuit;

	// Input loop to allow for multiple file tests.
	while (true) {
		// Prepare to run the simulation again.
		MainCircuit.ClearCircuit();
		while (!EventQueue.empty()) { EventQueue.pop(); }

		// Each of the 4 functions below represent a step in the simulation process.
		cout << "Please enter the name of your Circuit File, including file extension. Submit 'q' to quit." << endl << ">> ";
		cin >> fileName;
		cout << endl;
		if (fileName == "q") { break; }

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


		int simulatedTime = SimulateCircuit(&EventQueue, &MainCircuit, &curEventCount);


		PrintResults(&MainCircuit, simulatedTime);
	}
	return 0;
}


// Read the main circuit definition file, saving the details to a Circuit object.
int ReadCircuit(Circuit* MC, string fileName) {
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
int ReadInitConditions(priority_queue<Event*, vector<Event*>, CompareEvent>* EQ, string fileName, int *eventCount) {
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

// Returns the total runtime in ns.
int SimulateCircuit(priority_queue<Event*, vector<Event*>, CompareEvent> *EQ, Circuit* MC, int *eventCount) {
	int circuitTime = 0, newEventTime;
	char newState;
	string newEventWName;
	Event* newEvent;

	while (circuitTime < 60 && !EQ->empty()) {
		Event* nextEvent = EQ->top();

		// Get and set the next state of the wire.
		Wire* modifiedW = MC->GetWire(nextEvent->GetWireName());

		if (nextEvent->GetTime() > circuitTime) {
			modifiedW->SetHistory(nextEvent->GetTime());
		}

		// Set next state of the wire.
		modifiedW->SetState(nextEvent->GetState());

		// Evaluate the gate connected, and see if the output will change.
		vector<Gate*> modifiedWGates = modifiedW->GetDrives();

		// Modify circuitTime according to the event timestamp.
		circuitTime = nextEvent->GetTime();

		for (int i = 0; i < modifiedWGates.size(); i++) {

			if (modifiedW->IsInput() && 
				(modifiedW == modifiedWGates.at(i)->GetInput(1) || 
				 modifiedW == modifiedWGates.at(i)->GetInput(2))  ) {
				// Exercise the logic
				newState = modifiedWGates.at(i)->ExerciseLogic();

				// Do the following only if it is not the very first initial event. 
				// Since nothing else is initialized, it will create a junk output 
				// event if not skipped.

				// Create event for output change
				if (nextEvent->GetEvtCount() != 0) {
					newEventTime = circuitTime + modifiedWGates.at(i)->GetDelay();
					newEventWName = modifiedWGates.at(i)->GetOutput()->GetName();
					newEvent = new Event(newEventWName, newEventTime, newState, *eventCount);
					(*eventCount)++;


					// Append the new event to the Event Queue.
					if (!CheckForDuplicateEvent(*EQ, newEvent)) {
						EQ->push(newEvent);
					}
					
				}
				// This logic catches the case in which we have a feedback loop, in which we
				// actually do determine the output on the first Event.
				else if (MC->IsFeedback()) {
					newEventTime = circuitTime + modifiedWGates.at(i)->GetDelay();
					newEventWName = modifiedWGates.at(i)->GetOutput()->GetName();
					newEvent = new Event(newEventWName, newEventTime, newState, *eventCount);
					(*eventCount)++;


					// Append the new event to the Event Queue.
					EQ->push(newEvent);
				}
			}
		}
		// Delete the top Event in the EQ since we handled it.
		EQ->pop();

		// Append the change to the wire history.
		modifiedW->SetHistory(nextEvent->GetState());

		// Fill in Wire Histories for the current time.
		vector<Wire*> AllWires = MC->GetWire();
		for (int i = 0; i < AllWires.size(); i++) {
			AllWires.at(i)->SetHistory(circuitTime);
		}

	}

	cout << "Successfully simulated circuit, printing results." << endl << endl;
	return circuitTime;
}

// Print the simulation results in a visually useful way.
void PrintResults(Circuit *MC, int circuitTime) {
	vector<Wire*> AllWire = MC->GetWire();

	for (int i = 0; i < AllWire.size(); i++) {
		if ((AllWire.at(i)->GetName().find('X')) == string::npos) {
			AllWire.at(i)->PrintHistory();
			cout << endl;
		}
	}
	cout << endl << "Circuit Name: " << MC->GetCircuitName() << endl;
	cout << "Circuit Runtime: " << circuitTime << "ns" << endl << endl;
}

// Extra function needed to process Vector File.
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

// Function to check for duplicate Event object in Event priority_queue
bool CheckForDuplicateEvent(priority_queue<Event*, vector<Event*>, CompareEvent> EQ, Event* const EvtToCheck) {
	Event* QEvent;
	char EVCstate = EvtToCheck->GetState();
	int EVCtime = EvtToCheck->GetTime();

	// Loops through the copy of the priority_queue, looking for any duplicate Events.
	while (!EQ.empty()) {
		QEvent = EQ.top();
		if (QEvent->IsDuplicate(EVCstate, EVCtime)) { return true; }
		EQ.pop();
	}

	return false;
}