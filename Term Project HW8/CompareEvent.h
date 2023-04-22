#pragma once

#include "Event.h"

using namespace std;

// This struct allows for proper ordering in the Event Priority Queue.
// Particularly, the objects will be ordered by their time variable.

struct CompareEvent {
	bool operator()(Event const *e1, Event const *e2) {
		if (e1->GetTime() == e2->GetTime()) { return e1->GetEvtCount() > e2->GetEvtCount(); }
		return e1->GetTime() > e2->GetTime();
	}
};