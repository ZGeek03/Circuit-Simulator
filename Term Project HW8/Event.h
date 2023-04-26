#pragma once
#include <string>

using namespace std;

class Event {
	public:
		Event(string wireName, int time, char state, int evtCount);
		string GetWireName() const;
		int    GetTime()     const;
		char   GetState()    const;
		int    GetEvtCount() const;
		bool   IsDuplicate(char const state, int const time);
		

	private:
		string wireName;
		int    time;
		char   state;
		int    evtCount;
};
