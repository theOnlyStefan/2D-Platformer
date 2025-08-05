#pragma once
#include "UIelement.h"
#include "Object.h"
#include <iostream>
#include <functional>

class button :public uiElement {

protected:

	float sizeX, sizeY;

	const float outlineThickness = 3;
	const float innerlineThickness = 2;

	bool selected = false;

	void addPadding();

	virtual void onPress() {}
	virtual void drawAdditional([[maybe_unused]] Rectangle& rect) {}

	friend class gridbox;

public:

	button(float px, float py, float sx = 0, float sy = 0) : uiElement(px, py), sizeX(sx), sizeY(sy) {
		sx += 2 * (innerlineThickness + outlineThickness);
		sy += 2 * (innerlineThickness + outlineThickness);
	}

	virtual void draw() override {
		Rectangle rect{ posX, posY, sizeX, sizeY };
		DrawRectangleLinesEx(rect, outlineThickness, DARKBLUE);
		
		rect.x += outlineThickness;
		rect.y += outlineThickness;
		
		rect.width -= 2 * outlineThickness;
		rect.height -= 2 * outlineThickness;
		
		DrawRectangleRec(rect, Color{ 109, 84, 133 ,255 });

		rect.x += innerlineThickness;
		rect.y += innerlineThickness;

		rect.width -= 2 * innerlineThickness;
		rect.height -= 2 * innerlineThickness;
		
		drawAdditional(rect);
	}

	void update(float& mX, float& mY) override {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (mX >= posX && mX <= posX + sizeX && mY >= posY && mY <= posY + sizeY) {
				selected = true;
				onPress();
			}
			else {
				selected = false;
			}
		}
	}

	virtual void changePos(float x, float y) { posX = x, posY = y; }
	virtual void changeSize(float x, float y) { sizeX = x, sizeY = y; }
};

class customButton :public button {

	std::function<void()> act;
	Texture2D sprite;
	Rectangle spritePart{ 0,0,0,0 };

public:
	customButton(std::function<void()> func,float px, float py, float sx = 0, float sy = 0):
		button(px,py,sx,sy),act(func) {
		sprite = LoadTextureFromImage(GenImageColor((int)sx, (int)sy, GREEN));
		spritePart = Rectangle{ 0, 0, sx, sy };
	}

	customButton(Texture2D s, std::function<void()> func, float px, float py, float sx = 0, float sy = 0) :
		button(px, py, sx, sy),
		act(func), sprite(s) {
		spritePart = Rectangle{ 0, 0, (float)sprite.width, (float)sprite.height };
	}

	customButton(Rectangle part, Texture2D s, std::function<void()> func, float px, float py, float sx = 0, float sy = 0) :
		button(px, py, sx, sy),
		act(func), sprite(s), spritePart(part) {}

	void onPress() override {
		act();
	}

	void draw() override {
		if (posX == 1220) {
			[[maybe_unused]]int k = 1;
		}
		DrawTexturePro(sprite, spritePart, Rectangle{ posX, posY, sizeX, sizeY }, Vector2{ 0,0 }, 0.0, WHITE);
	}
};