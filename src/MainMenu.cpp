#include "MainMenu.h"

void mainMenu::cleanup()
{
	CloseWindow();
	textureFiles::freeTextures();

	auto size = uiElements.size();
	for (int i = 0; i < size; i++) {
		delete uiElements[i];
	}
}

void mainMenu::swapToNextState()
{
	switch (choice) {
		case PLAY:
			gameLoop::openLevelSelect();
			break;
		case EDIT:
			l.startEditMode();
			break;
		case NONE:
			break;
		default:
			cout << "ERROR: Unknown menu option selected";
	}
}

void mainMenu::setupUI() {

	textureFiles::initialize();

	vector<Rectangle> texts = {
			Rectangle{64,144,32,16},
			Rectangle{96,144,32,16},
			Rectangle{0,160,32,16}
	};

	for (int i = 0; i < texts.size(); i++) {
		auto func = [i, this]() {selectOption(menuOption(i)); };
		auto newButton = new customButton(texts[i], textureFiles::GUI, func, buttonPosX, buttonPosY + (float)i * spacingY, 2 * buttonHeight, buttonHeight);
		uiElements.push_back(newButton);
	}
}
void mainMenu::drawUI()
{
	DrawTexturePro(textureFiles::background_blue, Rectangle{ 0,0,width,height }, Rectangle{ 0,0,width,height }, Vector2{ 0,0 }, 0.0f, WHITE);

	static const Rectangle buttonBackground{ 112.0f,80.0f,32.0f,16.0f };

	static const Rectangle backgroundBackground{ 0.0f,32.0f,48.0f,48.0f };
	DrawTexturePro(textureFiles::GUI, backgroundBackground, Rectangle{ buttonPosX - mariginX,buttonPosY - startingMariginY,buttonHeight * 2.0f + mariginX * 2,buttonHeight * 3 + mariginY * 2 + startingMariginY*2 }, Vector2{ 0.0 }, 0.0f, WHITE);

	for (float i = 0; i < static_cast<float>(menuOption::COUNT); i++) {
		DrawTexturePro(textureFiles::GUI, buttonBackground, Rectangle{ buttonPosX,buttonPosY+i*spacingY,buttonHeight * 2.0f,buttonHeight }, Vector2{ 0.0 }, 0.0f, WHITE);
	}
	

	for (auto& component : uiElements) {
		component->draw();
	}
}

void mainMenu::selectOption(menuOption opt) {
	choice = opt;
	prematureExit = true;
}

void mainMenu::runMenu() {
	//window parameters defined in Globals
	InitWindow(width, height, "Menu");
	SetTargetFPS(60);

	setupUI();

	while (!WindowShouldClose() && !prematureExit) {
		//Update
		//----------------------------------------

		Vector2 mousePos = GetMousePosition();
		for (auto& component : uiElements) {
			component->update(mousePos.x, mousePos.y);
		}

		if (IsKeyPressed(KEY_L)) choice = EDIT, prematureExit = true;
		if (IsKeyPressed(KEY_S)) choice = PLAY, prematureExit = true;

		//Draw
		//----------------------------------------
		BeginDrawing();

		ClearBackground(BLUE);

		drawUI();

		EndDrawing();
	}

	cleanup();

	swapToNextState();
}