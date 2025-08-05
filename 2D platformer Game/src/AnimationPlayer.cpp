#include "AnimationPlayer.h"

void animation::play(float px, float py, bool flipped)
{
	timer += GetFrameTime();
	
	currentFrame += (timer >= frameDuration);
	currentFrame %= totalFrames;
	if (currentFrame == totalFrames - 1) {
		ended = true;
	}

	timer -= frameDuration * (timer >= frameDuration);

	Vector2 offset = Vector2{ frameWidth * (currentFrame % hframes),frameHeight * (currentFrame / hframes) };
	frameWindow.x = offset.x + flipped * frameWidth;
	frameWindow.y = offset.y;
	frameWindow.width = !flipped * frameWidth - flipped * frameWidth;

	if (flipped) px -= 2 * spaceOffsetX;
	Rectangle destination{ px + spaceOffsetX,py + spaceOffsetY,frameWidth,frameHeight };
	DrawTexturePro(*spriteFile, frameWindow, destination, Vector2{ 0,0 }, 0.0, WHITE);
}

//just gibberish, ignore
animation::animation()
{
	frameDuration = 0, frameHeight = 0, frameWidth = 0;
	hframes = 0, vframes = 0;
	frameWindow = Rectangle{ 0,0,0,0 };
}