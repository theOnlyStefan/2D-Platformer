#pragma once
#include "Button.h"
#include "Gridbox.h"

class objectButton :public button {
private:
	object* thing = nullptr;

	object*& curr;
	
	void onPress() override {
		curr = thing;
	}

	void drawAdditional(Rectangle& rect) override {
		thing->drawUI(rect);
	}

public:
	objectButton(object* obj, object*& ptr, float px = 0, float py = 0, float sx = 0, float sy = 0) :button(px, py, sx, sy), thing(obj), curr(ptr) {
		changePos(px, py);
	}

	~objectButton() { delete thing; }

	void changePos(float x, float y) override {
		posX = x, posY = y;
		if (thing) {
			thing->setPos(x, y);
		}
	}

	
};

class resetButton :public button {
private:
	object*& curr;
	void onPress() override {
		curr = nullptr;
	}

	void drawAdditional(Rectangle& r) override {
		DrawRectangleRec(r, RAYWHITE);
		DrawCircleLines(int(r.x + r.width / 2.0f), int(r.y + r.height / 2.0f), r.width / 3, RED);
		DrawLine(int(r.x + r.width / 2 - r.width / 3), int(r.y + r.height / 2 - r.width / 3), int(r.x + r.width / 2 + r.width / 3), int(r.y + r.height / 2 + r.width / 3), RED);
		
	}
public:
	resetButton(object*& ptr, float px, float py, float sx = 0, float sy = 0) :button(px, py, sx, sy), curr(ptr) {}
	
};

class nextButton :public button {
	int currentPos = 0;
	std::vector<gridbox>* gridboxes;
public:
	nextButton(auto g): gridboxes(g) {}

	void onPress() override {
		if (currentPos < gridboxes->size()) {
			(*gridboxes)[currentPos].active = false;
			currentPos++;
			(*gridboxes)[currentPos].active = true;
		}
	}
};