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
		Wire(string name = "X", int num = -1, char state = 'X');

		void          SetNum(int const num);
		void          SetHistory(char const histRecord, int const circuitTime = 0);
		void          SetHistory(int const circuitTime);
		void          SetDrives(Gate* const gateToDrive);
		void          SetName(string const name);
		void          SetIsInput(bool const isIn);
		void          SetState(char const state);
		string        GetName()      const;
		int           GetNum()       const;
		char          GetState()     const;
		bool          IsInput()      const;
		void          PrintHistory() const;
		vector<Gate*> GetDrives()    const;
		vector<char>  GetHistory()   const;

	private:
		string        name;
		int           num;
		char          state;
		vector<Gate*> drives;
		vector<char>  history;
		bool          isInput;
};