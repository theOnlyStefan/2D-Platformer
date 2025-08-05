#pragma once
#include "MobileObject.h"
#include "AnimationPlayer.h"
#include "Timer.h"
#include "Globals.h"

class Player :public mobileObject {

	enum action { IDLE, RUN, JUMP, WALL_JUMP, HIT, DOUBLE_JUMP, FALL };
	
	enum movement { GROUNDED, ON_WALL, IN_AIR, DOUBLE_JUMPING };
	movement state = GROUNDED;

	Texture2D textures[7];
	animation animations[7];
	animation* currentAnimation = &animations[IDLE];
	bool rotated = 0;
	
	int maxJumpCharges = 1;
	int jumpCharges = maxJumpCharges;

	float wallJumpDeceleration = 5;
	float wallDropCD = 0.5f;
	timer wallDropTimer;

	void loadAssets(int playerNum);

	void groundedState();
	void onWall();
	void inAir();
	void doubleJump();
	
	void tON_WALL();

	void toGrounded();
	void toAir();

public:
	
	Player(int id, float& x, float& y, int playerNum, Texture& uiSprite) :mobileObject(id, uiSprite, x, y, 150) { loadAssets(playerNum); hitbox.setSize(10.5, 12); hitbox.setOffset(6, 7); accelerationX = 10; }

	bool isGrounded() { return hitbox.isGrounded(); }
	bool isTouchingWall() { return hitbox.isTouchingWall(); }

	void updateAdditional() override {
		//std::cout << "Additional";
		switch (state) {
		case GROUNDED:
			groundedState();
			break;
		case IN_AIR:
			inAir();
			break;
		case ON_WALL:
			onWall();
			break;
		case DOUBLE_JUMPING:
			doubleJump();
			break;
		}
	}

	void draw() override;
	void drawState();

	object* clone(float xpos, float ypos) override { auto a = new Player(*this); a->setPos(xpos, ypos); return a; }
	void setCamera(Camera2D &cam) {
		cam.target = Vector2{ posX + 16,posY + 16 };
		
	}
};

