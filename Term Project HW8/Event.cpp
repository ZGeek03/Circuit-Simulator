#include "Event.h"
#include <string>

using namespace std;

Event::Event(string wn, int t, char s, int ec) {
	wireName = wn;
	time = t;
	state = s;
	evtCount = ec;
}

string Event::GetWireName() const { return wireName; }

int Event::GetTime() const { return time; }

char Event::GetState() const { return state; }

int Event::GetEvtCount() const { return evtCount; }

// Used in the Circut Sim file to check for duplicate Events when simulating feedback loops.
bool Event::IsDuplicate(char const st, int const ti) {
	if (st == state && ti == time) { return true; }
	else { return false; }
}