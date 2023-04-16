#include "Circuit.h"
#include <vector>
#include <string>

Circuit::Circuit() {

}

void Circuit::AddGate(Gate *gateToAdd) {
	AllGates.push_back(gateToAdd);
}

void Circuit::AddWire(Wire* wireToAdd) {
	AllWires.push_back(wireToAdd);
}

void Circuit::SetCircuitName(string const name) { CircuitName = name; }

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

string Circuit::GetCircuitName() const { return CircuitName; }