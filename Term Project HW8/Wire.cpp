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

void   Wire::SetHistory(char const histRecord) { history.push_back(histRecord); }

void   Wire::SetDrives(Gate* const gateToDrive) { drives.push_back(gateToDrive); }

void   Wire::SetName(string const na) { name = na; }

void   Wire::SetIsInput(bool const isIn) { isInput = isIn; }

string Wire::GetName() const { return name; }

int    Wire::GetNum() const { return num; }

char   Wire::GetState() const { return state; }

bool   Wire::GetIsInput() const { return isInput; }

vector<Gate*> Wire::GetDrives() const { return drives; }

vector<char>  Wire::GetHistory() const { return history; }

void Wire::PrintHistory() const {
	for (int histSel = 0; histSel < history.size(); histSel++) {
		cout << history.at(histSel);
	}
	cout << endl;
}
