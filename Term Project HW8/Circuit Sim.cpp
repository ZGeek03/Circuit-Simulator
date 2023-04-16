#include "Event.h"
#include "Wire.h"
#include "Gate.h"
#include <queue>

using namespace std;

int main() {
	priority_queue<Event*> EventQueue;

	Event event1(1, 3, '0', 1);
	Event event2(2, 4, '1', 0);

	EventQueue.push(&event1);
	EventQueue.push(&event2);

	return 0;
}