#include"Gate.h"


enum Gate::GateType {AND, NAND, OR, NOR, XOR, XNOR, NOT};

Gate::Gate(GateType t, int d, Wire* o, Wire* i1, Wire* i2) {
	type  =  t;
	delay =  d;
	out   =  o;
	in1   = i1;
	in2   = i2;
}

int   Gate::GetDelay() const { return delay; }

Wire* Gate::GetOutput() const { return out; }

// We only expect 2 possible parameter inputs for wireChoice: 1 or 2.
// From this, return the correct input.
Wire* Gate::GetInput(int wireChoice) const {
	if (wireChoice == 1) { return in1; }
	else { return in2; }
}

// Returns the state expected from the logic exercised.
// Each case follows a similar if statement format:
// - Check for case that the logic returns a 1
// - Check for cases in which we get an undefined output
// - Handle the other cases in which circuit returns a 0
char Gate::ExerciseLogic() const {
	switch (type) {
	case NOT:
		if (in1->GetState() == '0') { return '1'; }
		else if (in1->GetState() == 'X') { return 'X'; }
		else { return '0'; }
		break;

	case AND:
		if (in1->GetState() == '1' && in2->GetState() == '1') {
			return '1';
		}
		else if ((in1->GetState() == 'X' && in2->GetState() == '1') ||
				(in2->GetState() == 'X' && in1->GetState() == '1')) {
			return 'X';
		}
		else { return '0'; }
		break;

	case NAND:
		if (in1->GetState() != '1' && in2->GetState() != '1') { return '1'; }
		else if ((in1->GetState() == 'X' && in2->GetState() == '1') ||
			(in2->GetState() == 'X' && in1->GetState() == '1')) {
			return 'X';
		}
		else { return '0'; }
		break;

	case OR:
		if (in1->GetState() != '0' || in2->GetState() != '0') {
			return '1';
		}
		else if ((in1->GetState() == 'X' && in2->GetState() == '0') ||
			(in2->GetState() == 'X' && in1->GetState() == '0')) {
			return 'X';
		}
		else { return '0'; }
		break;

	case NOR:
		if (in1->GetState() == '0' && in2->GetState() == '0') {
			return '1';
		}
		else if ((in1->GetState() == 'X' && in2->GetState() == '0') ||
			(in2->GetState() == 'X' && in1->GetState() == '0')) {
			return 'X';
		}
		else { return '0'; }
		break;

	case XOR:
		if (in1->GetState() != in2->GetState()) { return '1'; }
		else if (in1->GetState() == 'X' || in2->GetState() == 'X') {
			return 'X';
		}
		else { return '0'; }
		break;

	case XNOR:
		if (in1->GetState() == in2->GetState()) { return '1'; }
		else if (in1->GetState() == 'X' || in2->GetState() == 'X') {
			return 'X';
		}
		else { return '0'; }
		break;
	default:
		return 'X';
		break;
	}
}
