#pragma once
#include <vector>
#include <queue>
#include <string>
#include "Gate.h"
#include "Event.h"

using namespace std;

class Gate;

class Wire {
	public:
		Wire(char name = 'A', int num = -1, char state = 'X');

		void          SetNum(int const num);
		void          SetHistory(char const histRecord);
		void          SetDrives(Gate* const gateToDrive);
		string        GetName()      const;
		int           GetNum()       const;
		char          GetState()     const;
		void          PrintHistory() const;
		vector<Gate*> GetDrives()    const;
		vector<char>  GetHistory()   const;

	private:
		string        name;
		int           num;
		char          state;
		vector<Gate*> drives;
		vector<char>  history;
};