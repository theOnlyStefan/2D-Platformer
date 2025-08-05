#pragma once
#include "Object.h"
#include "Globals.h"

class mobileObject :public object {
protected:
	float baseGravity = -300;
	float gravity = baseGravity;

protected:
	float velocityX = 0;
	float maxVelocityX = 0;
	float accelerationX = 0;

	float velocityY = 0;

	friend class physicsEngine;

	void slowDownGravity(float multiplier) { gravity = baseGravity * multiplier; }
	virtual void updateAdditional() {}
public:
	mobileObject(int id, Texture& t, float& xx, float& yy, float speed = 0) :object(id, xx, yy, t), maxVelocityX(speed) {}

	bool isMoving() override { return !(velocityX == 0 && velocityY == 0); }
	bool movingHorizontally() { return velocityX != 0; }
	bool movingVertically() { return velocityY != 0; }
	bool falling() { return velocityY < 0; }

	virtual object* clone(float xpos, float ypos) override { auto a = new mobileObject(*this); a->setPos(xpos, ypos); return a;}
	void update() override {
		//std::cout << "Overriden";
		velocityY -= gravity * GetFrameTime();
		updateAdditional();
	}
};

class spaceship : public mobileObject {
public:
	spaceship(float& x, float& y):mobileObject(10,textureFiles::p_jumps[2],x,y) {
		gravity = 0;
		hitbox.setSize(12, 12);
	}
	void updateAdditional() override {
		velocityX = 100.0f * (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
		velocityY = 100.0f * (IsKeyDown(KEY_S) - IsKeyDown(KEY_W));
	}

	void draw() override {
		hitbox.draw();
	}
};
