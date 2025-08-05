#pragma once
#include "raylib.h"
class uiElement {
protected:

	float posX, posY;

public:

	uiElement(float x, float y) :posX(x), posY(y) {}

	virtual void draw() = 0;
	virtual void update(float& mX, float& mY) = 0;

	virtual ~uiElement() = default;

};