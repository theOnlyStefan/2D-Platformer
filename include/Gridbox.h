#pragma once
#include "Button.h"
#include "Globals.h"

class gridbox:public uiElement {
	float sizeX, sizeY;
	float mariginX, mariginY;
	float currX = 0, currY = 0;
	float gridElementSize;

	std::vector<button*> buttons;

public:

	bool active = false;

	gridbox(float xpos, float ypos, float szx,float szy,float marx,float mary, float grid):uiElement(xpos,ypos),sizeX(szx),sizeY(szy),mariginX(marx),mariginY(mary),gridElementSize(grid) {}
	bool addButton(button* B) {
		
		B->sizeX = gridElementSize;
		B->sizeY = gridElementSize;
		
		if (currX + B->sizeX > sizeX) {
			currX = 0;
			currY += mariginY + gridElementSize;
		}
		
		if (currY + B->sizeY > sizeY) {
			return false;
		}
		
		buttons.push_back(B);
		
		B->changePos(currX + posX, currY + posY);

		currX += B->sizeX + mariginX;

		return true;
	}

	void clearButtons() { buttons.clear(); }

	void update(float& mx, float& my) {
		if (active) {
			for (auto& b : buttons) {
				b->update(mx,my);
			}
		}
	}

	void draw() {
		if (active) {
			for (auto& b : buttons) {
				b->draw();
			}
		}
	}
};

class infiniteGridbox: public uiElement {
	std::vector<gridbox> gridboxes;
	int activeGrid = 0;

	float sizeX, sizeY;
	float mariginX, mariginY;
	float currX = 0, currY = 0;
	float gridElementSize;

	const Rectangle prevLocation{ 128,32,16,16 };
	const Rectangle nextLocation{ 144,32,16,16 };

	const float prevPx = posX + sizeX / 2.0f - gridElementSize;
	const float nextPx = posX + sizeX / 2.0f;

	const float prevPy = posY + sizeY - gridElementSize;
	const float nextPy = prevPy;

	customButton next, prev;

	const float contentSizeY = prevPy - posY;

	void nextGrid() {
		if (activeGrid < gridboxes.size() - 1) {
			gridboxes[activeGrid].active = false;
			activeGrid++;
			gridboxes[activeGrid].active = true;
		}
	}

	void previousGrid() {
		if (activeGrid > 0) {
			gridboxes[activeGrid].active = false;
			activeGrid--;
			gridboxes[activeGrid].active = true;
		}
	}

public:

	infiniteGridbox(float xpos, float ypos, float szx, float szy, float marx, float mary, float grid) 
		:uiElement(xpos, ypos), sizeX(szx), sizeY(szy), mariginX(marx), mariginY(mary), gridElementSize(grid),
		prev(prevLocation, textureFiles::GUI, [this] {previousGrid(); }, prevPx, prevPy, gridElementSize, gridElementSize),
		next(nextLocation, textureFiles::GUI, [this] {nextGrid(); }, nextPx, nextPy, gridElementSize, gridElementSize) {

		gridboxes.push_back(gridbox(xpos, ypos, szx, contentSizeY, marx, mary, grid));
		gridboxes[0].active = true;
		
	}

	void addButton(button* B) {
		auto& last = gridboxes[gridboxes.size() - 1];
		if (!last.addButton(B)) {
			gridboxes.push_back(gridbox(posX, posY, sizeX, contentSizeY, mariginX, mariginY, gridElementSize));
			auto& lastNew = gridboxes[gridboxes.size() - 1];
			lastNew.addButton(B);
		}
	}

	

	void update(float& mx, float& my) override {
		prev.update(mx, my);
		next.update(mx, my);
		gridboxes[activeGrid].update(mx, my);
	}

	void draw() override {

		//Show elements of UI for debugging
		//
		//DrawRectangle((int)posX, (int)posY, (int)sizeX, (int)sizeY, GREEN);
		//DrawRectangle((int)posX, (int)posY, (int)sizeX, (int)contentSizeY, PURPLE);
		//DrawRectangle((int)prevPx, (int)prevPy, (int)gridElementSize, (int)gridElementSize, RED);

		prev.draw();
		next.draw();
		gridboxes[activeGrid].draw();

	}
};