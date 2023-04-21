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