#pragma once

#include "Gate.h"
#include "Wire.h"
#include <vector>
#include <string>

using namespace std;

class Circuit {
	public:
		Circuit();
		void          AddGate(Gate *gateToAdd);
		void          AddWire(Wire *wireToAdd);
		void          SetCircuitName(string const name);
		void          SetIsFeedback(bool const isFeed);
		void          ParseCircuitFile(string const line);
		Gate*         GetGate(int idx)     const;
		vector<Wire*> GetWire()            const;
		string        GetCircuitName()     const;
		bool          IsFeedback()         const;
		Wire*         GetWire(string name) const;
		Wire*         GetWire(int num);
		void          ClearCircuit();

	private:
		vector<Gate*> AllGates;
		vector<Wire*> AllWires;
		string        CircuitName;
		bool          IsFeedbackLoop = false;
		enum          LineTypes { INPUT, OUTPUT, GATE, NOTGATE };

};