#include "Wire.h"
#include "Event.h"
#include <iostream>
#include <string>

Wire::Wire(string na, int nu, char st) {
	name  = na;
	num   = nu;
	state = st;
}


void   Wire::SetNum(int const n) { num = n; }

// This overload just fills in the history up to the current time.
void   Wire::SetHistory(int const circuitTime) {
	// Fill in Wire Histories for the current time

	while (!history.empty() && history.size() < circuitTime+1) {
		history.push_back(history.back());
	}
}

// This overload fills in the history, and then appends the new state we found.
void   Wire::SetHistory(char const histRecord, int const circuitTime) { 
	SetHistory(circuitTime);
	if (!history.empty()) { history.pop_back(); }
	history.push_back(histRecord); 
}


void   Wire::SetDrives(Gate* const gateToDrive) { drives.push_back(gateToDrive); }

void   Wire::SetName(string const na) { name = na; }

void   Wire::SetIsInput(bool const isIn) { isInput = isIn; }

void   Wire::SetState(char const st) { state = st; }

string Wire::GetName() const { return name; }

int    Wire::GetNum() const { return num; }

char   Wire::GetState() const { return state; }

bool   Wire::IsInput() const { return isInput; }

vector<Gate*> Wire::GetDrives() const { return drives; }

vector<char>  Wire::GetHistory() const { return history; }

// Loops through the history vector and converts the states to lines for display.
void Wire::PrintHistory() const {
	cout << name << ": ";
	for (int histSel = 0; histSel < history.size(); histSel++) {
		if (history.at(histSel) == '0') { cout << '_'; }
		else if (history.at(histSel) == '1') { cout << '-'; }
		else { cout << history.at(histSel); }
	}
	cout << endl;
}
