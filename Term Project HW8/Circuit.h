#pragma once

#include "Gate.h"
#include "Wire.h"
#include <vector>
#include <string>

using namespace std;

class Circuit {
	public:
		Circuit();
		void   AddGate(Gate *gateToAdd);
		void   AddWire(Wire *wireToAdd);
		void   SetCircuitName(string const name);
		void   ParseCircuitFile(string const line);
		Gate*  GetGate(int idx)     const;
		Wire*  GetWire(string name) const;
		Wire*  GetWire(int num) const;
		string GetCircuitName()     const;

	private:
		vector<Gate*> AllGates;
		vector<Wire*> AllWires;
		string        CircuitName;
		enum          LineTypes { INPUT, OUTPUT, GATE, NOTGATE };

};