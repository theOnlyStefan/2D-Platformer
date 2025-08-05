#pragma once
#include <vector>
#include "MobileObject.h"
class physicsEngine{
	std::vector<object*> &entities;

	void runCollisionStep3(float delta);
	//old logic
	void runCollisionStep2();

public:
	physicsEngine(std::vector<object*>& e) :entities(e) {}
	void runCollisions() {
		float delta = GetFrameTime();
		const float stableTime = 0.1f;

		do {
			float stepDelta = std::min(delta, stableTime);
			delta = std::max(delta - 0.1f, 0.0f);

			runCollisionStep3(stepDelta);
		} 
		while (delta > 0);

	}

};