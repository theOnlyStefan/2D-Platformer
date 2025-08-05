#include "PhysicsEngine.h"

void physicsEngine::runCollisionStep3(float delta) {
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->isMoving()) {

			mobileObject* e = static_cast<mobileObject*>(entities[i]);
			e->hitbox.grounded = false;
			e->hitbox.touchingCeiling = false;
			e->hitbox.touchingWall = false;

			//X axis movement and collisions
			e->posX += e->velocityX * delta;

			for (int j = 0; j < entities.size(); j++) {
				if (i != j && e->hitbox.checkCollision(entities[j]->hitbox)) {
					//DrawCircle(0, 0, 50, RED);
					e->hitbox.resolveCollision1d(entities[j]->hitbox, true);

				}
			}

			//Y axis movement and collisions
			e->posY += e->velocityY * delta;

			for (int j = 0; j < entities.size(); j++) {
				if (i != j && e->hitbox.checkCollision(entities[j]->hitbox)) {
					//DrawCircle(0, 0, 50, RED);
					e->hitbox.resolveCollision1d(entities[j]->hitbox, false);

				}
			}

			//State post-processing
			if (e->hitbox.grounded) e->hitbox.touchingCeiling = false;

			if (e->hitbox.isGrounded() || e->hitbox.isTouchingCeiling()) {
				e->hitbox.touchingWall = false;
				e->velocityY = 0;
			}

		}
	}
}

//old logic
void physicsEngine::runCollisionStep2() {
	//float delta = 1 / 60.0;
	float delta = GetFrameTime();

	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->isMoving()) {

			mobileObject* e = static_cast<mobileObject*>(entities[i]);

			e->posX += e->velocityX * delta;
			e->posY += e->velocityY * delta;

			std::vector<object*> detectedOverlaps;

			for (int j = 0; j < entities.size(); j++) {
				if (i != j && e->hitbox.checkCollision(entities[j]->hitbox)) {
					//DrawCircle(0, 0, 50, RED);
					detectedOverlaps.push_back(entities[j]);
					// deprecated e->hitbox.resolveCollision(entities[j]->hitbox); //deprecated

				}
			}

		}
	}
}