#pragma once
#include "raylib.h"
class test {
	float velocity = 150;
	float x = 0, y = 300;
	float size = 32;
	bool stateMove = false;

	void moveDirection() {
		float delta = GetFrameTime();

		float directionX = float(IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
		float directionY = float(IsKeyDown(KEY_S) - IsKeyDown(KEY_W));

		x += directionX * velocity * delta;
		y += directionY * velocity * delta;
	}
	void moveDirectly() {
		float delta = GetFrameTime();

		if (IsKeyDown(KEY_D)) x += velocity * delta;
		if (IsKeyDown(KEY_A)) x -= velocity * delta;

		if (IsKeyDown(KEY_S)) y += velocity * delta;
		if (IsKeyDown(KEY_W)) y -= velocity * delta;
		
	}
public:
	void update() {
		if (IsKeyPressed(KEY_R)) stateMove = !stateMove;

		if (stateMove) moveDirectly(), DrawText("Moving directly", 0, 0, 24, RAYWHITE);
		else moveDirection(), DrawText("Moving with vector", 0, 0, 24, RAYWHITE);
	}
	void draw() {
		DrawRectangle((int)x, (int)y, (int)size, (int)size, GREEN);
	}
};