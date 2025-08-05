#include "Player.h"

//Loading textures and drawing them
void Player::loadAssets(int playerNum)
{
	
	animations[IDLE] = animation(textureFiles::p_idles[playerNum], 11, 1, 1 / 15.0f);
	animations[DOUBLE_JUMP] = animation(textureFiles::p_doubleJumps[playerNum], 6, 1, 1 / 15.0f);
	animations[RUN] = animation(textureFiles::p_runs[playerNum], 12);
	animations[FALL] = animation(textureFiles::p_falls[playerNum], 1);
	animations[JUMP] = animation(textureFiles::p_jumps[playerNum], 1);
	animations[HIT] = animation(textureFiles::p_hits[playerNum], 7);
	animations[WALL_JUMP] = animation(textureFiles::p_wallJumps[playerNum], 5, 1, 0.05f, 5, 0);
	
}

void Player::drawState()
{
	switch (state) {
		case GROUNDED:
			DrawText("GROUNDED", 300, 0, 24, MAGENTA);
			break;
		case IN_AIR:
			DrawText("IN_AIR", 300, 0, 24, MAGENTA);
			break;
		case ON_WALL:
			DrawText("ON_WALL", 300, 0, 24, MAGENTA);
			break;
		case DOUBLE_JUMPING:
			DrawText("DOUBLE_JUMPING", 300, 0, 24, MAGENTA);
			break;
		default:
			DrawText("ERROR_STATE", 300, 0, 24, MAGENTA);
			break;
	}
}

void Player::draw()
{
	currentAnimation->play(posX, posY, rotated);
	//hitbox.draw(); //for debugging only, currently redundant

	//Sped and state for debugging
	//std::string text = "Speed: " + std::to_string(velocityX) + " " + std::to_string(velocityY);
	//drawState();
	//DrawText(text.c_str(), 0, 0, 12, SKYBLUE);
}


//Main state logic
void Player::groundedState()
{
	//float delta = GetFrameTime();

	if (!isGrounded()) state = IN_AIR;

	jumpCharges = maxJumpCharges;

	if (IsKeyPressed(KEY_W)) {
		velocityY = -250;
		state = IN_AIR;
	}

	

	velocityX = maxVelocityX * (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
	//velocityX = 10;

	if (velocityX != 0) {
		currentAnimation = &animations[RUN];
	}
	else {
		currentAnimation = &animations[IDLE];
	}

	//currentAnimation.reset();

	if (velocityX > 0) rotated = 0;
	else if (velocityX < 0) rotated = 1;

	
}

void Player::onWall()
{
	
	if (isGrounded()) {
		toGrounded();
		return;
	}
	else if (!isTouchingWall()) state = IN_AIR, slowDownGravity(1), velocityX = 0;

	

	if (IsKeyPressed(KEY_W)) {

		velocityX = 2 * maxVelocityX * (rotated - !rotated);

		velocityY = -150;

		state = IN_AIR, slowDownGravity(1), rotated = !rotated;
		return;
	}

	else if (IsKeyPressed(KEY_S)) {
		
		velocityX = -10.0f * (!rotated - rotated);
		rotated = !rotated;
		wallDropTimer.setTime(wallDropCD);
		toAir();
		return;
	}
	
	velocityX = 10.0f * (!rotated - rotated);
	velocityY = 10.0f;
}

void Player::inAir()
{
	if (IsKeyDown(KEY_D)) velocityX += accelerationX * (velocityX < maxVelocityX), rotated = false;
	if (IsKeyDown(KEY_A)) velocityX -= accelerationX * (velocityX > -maxVelocityX), rotated = true;

	velocityX += wallJumpDeceleration * (velocityX < maxVelocityX);
	velocityX -= wallJumpDeceleration * (velocityX > -maxVelocityX);

	if (isGrounded()) state = GROUNDED;
	else if (isTouchingWall() && wallDropTimer.isDone()) {
		tON_WALL();
		//std::cout << velocityX << " Attached\n";
		return;
	}

	if (jumpCharges > 0 && IsKeyPressed(KEY_W)) {

		if (velocityY < 0) velocityY -= 150;
		else velocityY = -150;

		currentAnimation = &animations[DOUBLE_JUMP];

		jumpCharges--;

		state = DOUBLE_JUMPING;
	}
	else {

		if (velocityY >= 0) currentAnimation = &animations[FALL];
		else currentAnimation = &animations[JUMP];

	}

}

void Player::doubleJump()
{
	if (isGrounded()) state = GROUNDED;
	else if (isTouchingWall() && wallDropTimer.isDone()) {
		tON_WALL();
		return;
	}

	if (IsKeyDown(KEY_D)) velocityX += accelerationX * (velocityX < maxVelocityX); //rotated = false;
	if (IsKeyDown(KEY_A)) velocityX -= accelerationX * (velocityX > -maxVelocityX); //rotated = true;

	velocityX += wallJumpDeceleration * (velocityX < maxVelocityX);
	velocityX -= wallJumpDeceleration * (velocityX > -maxVelocityX);

	if (currentAnimation->hasEnded()) {
		currentAnimation->reset();
		state = IN_AIR;
	}


}

void Player::tON_WALL()
{
	state = ON_WALL;
	jumpCharges = maxJumpCharges;

	rotated = velocityX < 0 ? true : false;

	velocityX = 0;
	velocityY = 0;

	//slowDownGravity(0.05);

	currentAnimation = &animations[WALL_JUMP];
	onWall();
}

//Transitional states
void Player::toGrounded()
{
	state = GROUNDED;
	slowDownGravity(1);
	rotated = !rotated;
	groundedState();
}

void Player::toAir()
{
	state = IN_AIR;
	slowDownGravity(1);
	
	hitbox.setCeiling(false);
	hitbox.setGrounded(false);
	hitbox.setOnWall(false);
	//currentAnimation = &animations[FALL];
	inAir();
}




