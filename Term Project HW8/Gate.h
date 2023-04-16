#pragma once
#include "Wire.h"

using namespace std;

class Wire;

class Gate {
	public:
		enum  GateType;
		Gate(GateType type, int delay, Wire* out, Wire* in1, Wire* in2 = nullptr);

		int    GetDelay()               const;
		Wire*  GetInput(int wireChoice) const;
		Wire*  GetOutput()              const;
		char   ExerciseLogic()          const;
		
	private:
		int      delay;
		GateType type;
		Wire     *in1, *in2;
		Wire     *out;
};
