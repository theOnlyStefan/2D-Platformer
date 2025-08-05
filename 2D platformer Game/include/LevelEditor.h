#pragma once
#include "Player.h"
#include "Object.h"
#include "UIelement.h"
#include "Button.h"
#include "objectButton.h"
#include "Gridbox.h"
#include "ObjectCreator.h"

#include "tinyfiledialogs.h"

#include <fstream>
#include <string>

class levelEditor {
	float scale = 1;
	int width = int(1400 * scale);
	int height = int(700 * scale);
	float zoom = 2.0; //Starting zoom of objects on the screen, doesn't affect UI elements
	bool cameraControl = false;
	bool snapMode = false;
	
	Camera2D cam;
	std::vector<object*> entities;
	std::vector<uiElement*> uiElements;

	creator maker;
	std::string currentSave;

	float uiWidth = 200 * scale;
	float uiStartPos = width - uiWidth;
	float uiEndPos = (float)width;

	const float elementSize = 64.0f * scale;
	const float buttonHeight = elementSize * 0.75f;

	object* currentObject = nullptr;

	const float mariginY = height / 7.0f;
	const float buttonsMarigin = mariginY * 0.1f;
	const float mariginX = 0.1f * uiWidth;

	void setupUI();
	bool mouseInUI();
	
	void update();
	void drawUI();
	void drawStuff();

	Vector2 snapGrid(Vector2 mousePos, int blockSize = 48);

	void save(std::string saveLocation);
	void openSaveMenu();
	void openLoadMenu();

	void close() {
		CloseWindow();
		for (auto& elem : uiElements) {
			delete elem;
		}
		textureFiles::freeTextures();
	}

public:
	levelEditor() :cam{ Vector2{ 0, 0 }, Vector2{ 0, 0 }, 0, zoom } 
	{
		Vector2 saveloc{ uiStartPos + mariginX, mariginY / 2.0f - elementSize / 2.0f };
		Vector2 loadloc{ uiEndPos - mariginX - 2.0f * elementSize, mariginY / 2.0f - elementSize / 2.0f };
	}

	void startEditMode() {
		InitWindow(width, height, "Map Editor");
		SetTargetFPS(60);

		setupUI();

		while (!WindowShouldClose()) {
			//Updating
			update();

			BeginDrawing();
			ClearBackground(SKYBLUE);

			BeginMode2D(cam);

			//Drawing objects
			drawStuff();

			EndMode2D();

			//Drawing UI elements
			drawUI();

			EndDrawing();
		}

		close();

	}

	
};