#include "Timer.h"

std::unordered_set<timer*> timer::timers;


void timer::updateAllTimers() {
	float frameTime = GetFrameTime();
	for (auto it = timers.begin(); it != timers.end(); ) {
		timer* t = *it;
		t->time -= frameTime;
		if (t->time <= 0) {
			t->time = 0;
			it = timers.erase(it);  
		}
		else {
			++it;
		}
	}
}