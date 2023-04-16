#pragma once

#include "Gate.h"
#include "Wire.h"
#include <vector>

using namespace std;

class Circuit {
	public:
		Circuit();
	private:
		vector<Gate*> AllGates;
		vector<Wire*> AllWires;

};