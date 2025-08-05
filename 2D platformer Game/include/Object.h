#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "Collision.h"

class object {
protected:
	int id;
	float posX, posY;

	collision hitbox;
	
	Texture& sprite;
	Rectangle spritePart;

	void setPos(float a, float b) { posX = a, posY = b; }

	
	friend class objectButton;
	friend class physicsEngine;
public:
	virtual bool isMoving() { return false; }

	void setHitbox(float sizeX, float sizeY) { hitbox.setSize(sizeX, sizeY); }
	Vector2 getHitboxSize() { return hitbox.getSize(); }

	void drawHitbox() { hitbox.draw(); }

	object(int id, float a, float b, Texture& s) :id(id),posX(a), posY(b), sprite(s), hitbox(posX, posY), spritePart{a,b,(float)s.width,(float)s.height} {}

	object(int id, float a, float b, Texture& s, Rectangle r) :id(id),posX(a), posY(b), sprite(s), hitbox(posX, posY), spritePart(r) {}

	object(const object& o) = default;
	object(object& o, float x, float y) :object(o) { posX = x, posY = y; }

	virtual void update() {}
	virtual void draw() {
		DrawTextureRec(sprite, spritePart, Vector2{ posX,posY }, WHITE);
	}

	virtual object* clone(float xpos, float ypos) { auto a = new object(*this); a->setPos(xpos, ypos); return a; }

	virtual void drawImaginary(float x, float y, float zoom, Color tint = WHITE) {
		Rectangle rec{ x,y, spritePart.width * zoom, spritePart.height * zoom };
		drawUI(rec, tint);
	}

	virtual void drawUI(Rectangle where, Color tint = WHITE) {
		DrawTexturePro(sprite, spritePart, where, Vector2{ 0,0 }, 0.0, tint);
	}

	std::vector<float> save() { return std::vector<float>{(float)id, posX, posY}; }
};