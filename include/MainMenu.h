#pragma once
#include "LevelEditor.h"
#include "GameLoop.h"
#include "Globals.h"

using namespace std;

class mainMenu {
	//states
	enum menuOption { PLAY, EDIT, NONE, COUNT };
	menuOption choice = NONE;

	bool prematureExit = false;

	vector<uiElement*> uiElements;
	const float startingMariginY = 50;
	const float mariginY = 30;
	
	const float buttonHeight = 64.0f;
	const float mariginX = 1.0f * buttonHeight;

	const float buttonPosX = 0.5f * width - buttonHeight;
	const float buttonPosY = 0.5f * height - mariginY - buttonHeight * 3.0f / 2.0f;
	const float spacingY = buttonHeight + mariginY;

	levelEditor l;

	void setupUI();
	void drawUI();

	void selectOption(menuOption opt);

	void cleanup();
	void swapToNextState();

public:
	void runMenu();
public:

	mainMenu() {
		
	}

};