#pragma once
#include <string>

using namespace std;

class Event {
	public:
		Event(string wireNum, int time, char state, int evtCount);
		string GetWireName() const;
		int    GetTime()     const;
		char   GetState()    const;
		int    GetEvtCount() const;
		

	private:
		string wireName;
		int    time;
		char   state;
		int    evtCount;
};
