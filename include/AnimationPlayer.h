#pragma once
#include "raylib.h"
class animation {

private:
	Texture2D* spriteFile = nullptr;

	float frameDuration;
	int hframes, vframes;
	
	float frameHeight, frameWidth;
	int totalFrames = 0, currentFrame = 0;

	float timer = 0;
	bool ended = false;

	Rectangle frameWindow;
	float spaceOffsetX = 0, spaceOffsetY = 0;

public:
	animation();
	animation(Texture2D& sprite, int hframes, int vframes = 1, float time = 1 / 20.0, float shiftX = 0, float shiftY = 0)
		:frameDuration(time), hframes(hframes), vframes(vframes), spriteFile(&sprite), spaceOffsetX(shiftX), spaceOffsetY(shiftY) 
	{

		frameHeight = (float)spriteFile->height / vframes;
		frameWidth = (float)spriteFile->width / hframes;

		frameWindow.width = frameWidth;
		frameWindow.height = frameHeight;

		totalFrames = hframes * vframes;

	}

	void play(float px, float py, bool flipped = 0);

	
	bool hasEnded() { return ended; }
	void reset() { timer = 0, currentFrame = 0, ended = false; }
};