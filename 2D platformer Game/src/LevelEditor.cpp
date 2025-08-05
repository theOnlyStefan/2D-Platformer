#include "LevelEditor.h"

void levelEditor::setupUI()
{
	textureFiles::initialize();
	float currHeight = 0;

	Rectangle saveText{ 128.0f,160.0f,32.0f,16.0f };
	Rectangle loadText{ 160.0f,160.0f,32.0f,16.0f };
	
	uiElements.push_back(new customButton(saveText, textureFiles::GUI, [this] {openSaveMenu(); }, uiStartPos + mariginX / 2.0f, mariginY / 2.0f - buttonHeight / 2.0f, 2.0f * buttonHeight, buttonHeight));
	uiElements.push_back(new customButton(loadText, textureFiles::GUI, [this] {openLoadMenu(); }, uiEndPos - 2.0f * buttonHeight, mariginY / 2.0f - buttonHeight / 2.0f, 2.0f * buttonHeight, buttonHeight));

	auto g = new infiniteGridbox(uiStartPos + mariginX, currHeight + mariginY, uiWidth * 0.8f, (float)height * 0.8f, 30.0f * scale, 40.0f * scale, elementSize);
	uiElements.push_back(g);

	for (int i = 0; i <= 15; i++) {
		object* o = maker.make(i);
		g->addButton(new objectButton(o, currentObject));
	}


}

void levelEditor::update()
{
	float mXglobal = (GetMouseX() - cam.offset.x) / zoom;
	float mYglobal = (GetMouseY() - cam.offset.y) / zoom;

	float mXscreen = (float)GetMouseX();
	float mYscreen = (float)GetMouseY();

	//Mouse pos debugging
	//DrawText((std::to_string(mXglobal) + ' ' + std::to_string(mYglobal)).c_str(), width * 1 / 4, 0, 26, BLUE);

	for (auto& elem : uiElements) {
		elem->update(mXscreen, mYscreen);
	}
	
	if (IsKeyPressed(KEY_Q)) snapMode = !snapMode;
	if (IsKeyPressed(KEY_R)) currentObject = nullptr;
	//if (IsKeyPressed(KEY_S)) openSaveMenu();
	//if (IsKeyPressed(KEY_L)) openLoadMenu();

	if (currentObject != nullptr && !mouseInUI()) {
		//HideCursor();
		
		
		//Grid treba prilagoditi globalnim kooridnatama
		Vector2 snapCoordinates = snapGrid(Vector2{ mXglobal,mYglobal }, int(currentObject->getHitboxSize().x * 2.0f));
		if (!snapMode) snapCoordinates = Vector2{ mXglobal,mYglobal };
		//Crta se pre begin camera 2d tako da su potrebne relativne koordinate
		currentObject->drawImaginary(snapCoordinates.x * zoom + cam.offset.x, snapCoordinates.y * zoom + cam.offset.y, zoom, Color{ 5, 127, 247,255 });
		//currentObject->drawImaginary(mXglobal * zoom + cam.offset.x, mYglobal * zoom + cam.offset.y, zoom, BLUE);

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			entities.push_back(currentObject->clone((snapCoordinates.x), (snapCoordinates.y)));
			//entities.push_back(currentObject->clone((mXglobal), (mYglobal)));
		}
	}
	else {
		//Mouse pan and zoom functionality
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 mouseShift = GetMouseDelta();
			cam.offset.x += mouseShift.x;
			cam.offset.y += mouseShift.y;
		}
		else if (GetMouseWheelMove() != 0) {
			zoom += 0.1f * (float)GetMouseWheelMove();
			cam.zoom = zoom;
		}

	}

	
	
}

void levelEditor::drawUI()
{
	DrawRectangle((int)uiStartPos, 0, (int)uiEndPos, height, DARKGRAY);

	Rectangle buttonBackground{ 112.0f,80.0f,32.0f,16.0f };

	
	Rectangle saveBackground{ uiStartPos + mariginX/2.0f, mariginY / 2.0f - buttonHeight / 2.0f, 2.0f * buttonHeight, buttonHeight };
	Rectangle loadBackground{ uiEndPos - 2.0f * buttonHeight, mariginY / 2.0f - buttonHeight / 2.0f, 2.0f * buttonHeight, buttonHeight };

	DrawTexturePro(textureFiles::GUI, buttonBackground, saveBackground, Vector2{ 0,0 }, 0.0f, WHITE);
	DrawTexturePro(textureFiles::GUI, buttonBackground, loadBackground, Vector2{ 0,0 }, 0.0f, WHITE);

	for (auto& element : uiElements) {
		element->draw();
	}

	//Debugging
	//DrawText(std::to_string(entities.size()).c_str(), width / 2, 0, 26, RED);
	//DrawText((std::to_string(GetMouseX()) + ' ' + std::to_string(GetMouseY())).c_str(), width * 3/ 4, 0, 26, BLUE);

	DrawText("Q - Turn Grid snap on/off\n\nR - Unselect object/Panning mode", int(0.02*width), int(0.9 * height), 22, DARKGREEN);
	
	//Testing sprite cropping
	// IMPORTANT: Rectangle args 3 and 4 are width and height, not bottom right coordinates!!
	//const Rectangle prevLocation{ 128,32,16,16 };
	//const Rectangle destination{ 200,200,400,400 };
	//DrawTexturePro(textureFiles::GUI, prevLocation, destination, Vector2{ 0,0 }, 0.0f, WHITE);

	//const Rectangle rec{ mariginX, mariginY / 2.0f - elementSize / 2.0f, 2.0f * elementSize, elementSize };
	//const Rectangle destination{ 200,200,400,400 };
	//DrawTexturePro(textureFiles::GUI, saveText, destination, Vector2{ 0,0 }, 0.0f, WHITE);
}

void levelEditor::drawStuff()
{
	DrawCircle(0, 0, 50, RED);
	for (auto& entity : entities) {
		entity->draw();
	}

	
}

bool levelEditor::mouseInUI()
{
	int x = GetMouseX();
	return x >= uiStartPos && x <= uiEndPos;
}

Vector2 levelEditor::snapGrid(Vector2 mousePos, int blockSize)
{

	Vector2 mousePosNew{ 0,0 }, realMouse = GetMousePosition();

	//blockSize /= zoom;
	mousePosNew.x = roundf(mousePos.x / (float)blockSize) * blockSize;
	mousePosNew.y = roundf(mousePos.y / (float)blockSize) * blockSize;

	return mousePosNew;

}

void levelEditor::save(std::string saveLocation) {

	std::fstream saveFile(saveLocation, std::ios::out);
	for (int i = 0; i < entities.size(); i++) {
		auto ob = entities[i]->save();
		saveFile << ob[0] << ' ' << ob[1] << ' ' << ob[2];
		if (i < entities.size() - 1)
			saveFile << '\n';
	}
	saveFile.close();
}

void levelEditor::openSaveMenu()
{
	const char* const pattern = "*.txt";
	char* path = tinyfd_saveFileDialog("Save Map", ".\\Levels\\", 1, &pattern, NULL);

	if (path) {
		save(path);
	}
}

void levelEditor::openLoadMenu()
{
	const char* const pattern = "*.txt";
	char* path = tinyfd_openFileDialog("Select Level", ".\\Levels\\", 1, &pattern, NULL, 0);

	if (path) {
		entities = maker.load(path);
	}
}
