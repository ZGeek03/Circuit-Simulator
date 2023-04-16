#include "Event.h"

using namespace std;

Event::Event(int wn, int t, char s, int ec) {
	wireNum = wn;
	time = t;
	state = s;
	evtCount = ec;
}

int Event::GetWireNum() const { return wireNum; }

int Event::GetTime() const { return time; }

char Event::GetState() const { return state; }

int Event::GetEvtCount() const { return evtCount; }