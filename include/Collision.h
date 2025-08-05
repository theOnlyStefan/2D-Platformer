#pragma once
#include "raylib.h"
#include <cmath>

class collision {

private:
	float &x, &y; //origin coordinates (top left corner (0,0))
	float offX = 0, offY = 0; //hitbox offset
	float a, b; //half the hitbox length (from center to edge)

	bool grounded = false;
	bool touchingWall = false;
	bool touchingCeiling = false;

	bool work(float x1, float y1, float x2, float y2, float a1, float b1, float a2, float b2) {
		return x1<x2+a2 && x2<x1+a1 && y1<y2+b2 && y2<y1+b1;
	}

	float resolve1d(float x1, float x2, float a1, float a2) {
		if (x1 < x2) return x2 - a1 - a2;
		else return x2 + a1 + a2;
	}

	void resolveCollision1d(collision& h2, bool xAxis);
	
	//Drawing push angle after collision happens
	void drawPush(int x2, int y2, int a2, int b2, bool xAxis, bool firstIsLowerValue);

	friend class physicsEngine;
public:
	collision(float& posX, float& posY, float a1 = 0, float b1 = 0) : x(posX), y(posY), a(a1), b(b1) { }

	void setSize(float a1, float b1) { a = a1, b = b1; }
	Vector2 getSize() { return Vector2{ a,b }; }

	void setOffset(float a1, float b1) { offX = a1, offY = b1; }

	bool checkCollision(collision& c);

	bool isGrounded() { return grounded; }
	bool isTouchingWall() { return touchingWall; }
	bool isTouchingCeiling() { return touchingCeiling; }
	bool inAir() { return !isGrounded() && !isTouchingWall() && isTouchingCeiling(); }

	void setGrounded(bool val) { grounded = val; }
	void setCeiling(bool val) { touchingCeiling = val; }
	void setOnWall(bool val) { touchingWall = val; }

	void draw() { 
		DrawRectangleLines(int(x + offX), int(y + offY), (int)a * 2, (int)b * 2, DARKBLUE);
	}
};