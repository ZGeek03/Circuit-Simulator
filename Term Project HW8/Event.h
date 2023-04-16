#pragma once

using namespace std;

class Event {
	public:
		Event(int wireNum, int time, char state, int evtCount);
		int GetWireNum() const;
		int GetTime() const;
		char GetState() const;
		int GetEvtCount() const;

	private:
		int  wireNum;
		int  time;
		char state;
		int  evtCount;
};
