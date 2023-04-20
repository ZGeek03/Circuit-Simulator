#include "Circuit.h"
#include <vector>
#include <string>
#include <sstream>
#include "Gate.h"

// Function to split the line up for further parsing.
vector<string> SplitLine(string const line) {
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

Circuit::Circuit() { }

void Circuit::AddGate(Gate *gateToAdd) {
	AllGates.push_back(gateToAdd);
}

void Circuit::AddWire(Wire* wireToAdd) {
	AllWires.push_back(wireToAdd);
}

void Circuit::SetCircuitName(string const name) { CircuitName = name; }

void Circuit::ParseCircuitFile(string const line) {
	string type, linePart;
	stringstream li(line);
	vector<string> FileLineParts;
	int stri = 0;
	int typeIdentifier = 0;

	// Split the line into the individual elements
	FileLineParts = SplitLine(line);

	type = FileLineParts.at(0);

	if (type == "INPUT") { typeIdentifier = INPUT; }
	else if (type == "OUTPUT") { typeIdentifier = OUTPUT; }
	else if (type == "AND" || type == "OR" || type == "XOR"
		 || type == "NAND" || type == "NOR" || type == "XNOR")
	{ typeIdentifier = GATE; }

	linePart.clear();

	Wire* newWire = new Wire();
	switch (typeIdentifier) {
		// FileLineParts is in the following Order: {Name, Wire#}
		case INPUT:
			newWire->SetName(FileLineParts.at(1));
			newWire->SetNum(stoi(FileLineParts.at(2)));
			newWire->SetIsInput(true);

			AllWires.push_back(newWire);

			FileLineParts.clear();
			break;

		// FileLineParts is in the following Order: {Name, Wire#}
		case OUTPUT:
			newWire->SetName(FileLineParts.at(1));
			newWire->SetNum(stoi(FileLineParts.at(2)));
			newWire->SetIsInput(false);

			AllWires.push_back(newWire);

			FileLineParts.clear();
			break;

		// FileLineParts is in the following Order: { Delay, wireOut, wireIn1, wireIn2 }
		case GATE:
			int delay;
			Wire *out, *in1, *in2;

			delay = stoi(FileLineParts.at(1));
			in1 = GetWire(stoi(FileLineParts.at(2)));
			in2 = GetWire(stoi(FileLineParts.at(3)));
			out = GetWire(stoi(FileLineParts.at(4)));

// TODO: Fix the enum setting so that it can handle all types of gates.

			Gate* newGate = new Gate(Gate::GateType::AND, delay, out, in1, in2);

			AllGates.push_back(newGate);

			break;
	}
}

// Returns a gate in our circuit, based on the order it was placed
// into the simulator. Returns the oldest gate by default.
Gate* Circuit::GetGate(int idx = 0) const {
	return AllGates.at(idx);
}

// Cycles through all the wires and finds the one that matches the name
// requested. If no wire found to match, returns the oldest wire.
Wire* Circuit::GetWire(string name) const {
	for (int i = 0; i < AllWires.size(); i++) {
		if (AllWires.at(i)->GetName() == name) {
			return AllWires.at(i);
		}
	}

	return AllWires.at(0);
}
// Overload for above function that allows to search for wireNum instead.
Wire* Circuit::GetWire(int num) const {
	for (int i = 0; i < AllWires.size(); i++) {
		if (AllWires.at(i)->GetNum() == num) {
			return AllWires.at(i);
		}
	}

	return AllWires.at(0);
}

string Circuit::GetCircuitName() const { return CircuitName; }