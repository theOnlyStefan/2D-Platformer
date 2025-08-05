#pragma once
#include "raylib.h"

#include <unordered_set>

class timer {
	float time = 0;
public:
	
	timer(float startingTime = 0) :time(startingTime) {}

	void setTime(float t) { time = t; timers.insert(this); }
	bool isDone() { return time <= 0; }

	static std::unordered_set<timer*> timers;
	static void updateAllTimers();
};