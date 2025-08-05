#include "GameLoop.h"

void gameLoop::openLevelSelect()
{
	const char* const pattern = "*.txt";
	char* path = tinyfd_openFileDialog("Select Level", ".\\Levels\\", 1, &pattern, NULL, 0);

	if (path) {
		runGame(path);
	}
}

void gameLoop::runGame(string levelPath) {

	vector<object*> entityList;
	creator maker;

	//constexpr int mul = 8;
	//constexpr int width = 160 * mul, height = 90 * mul;
	//constexpr float textureScale = 2;

	//window parameters defined in Globals
	InitWindow(width, height, "Game");
	SetTargetFPS(60);


	textureFiles::initialize();
	entityList = maker.load(levelPath);
	Camera2D cam{ Vector2{0, 0}, Vector2{0, 0}, 0, textureScale };

	//float xs = 200;
	//spaceship s(xs, xs);
	//entityList.pop_back();
	//entityList.push_back(&s);
	physicsEngine phy(entityList);

	for (int i = 0; i < entityList.size(); i++) {
		//std::cout << entityList[i]->save()[1] << endl;
	}

	//cam.SetOffset(Vector2{ width / 4,height / 4 });
	while (!WindowShouldClose()) {
		//Update
		//----------------------------------------

		for (auto& entity : entityList) {
			entity->update();
		}

		//Draw
		//----------------------------------------
		BeginDrawing();

		ClearBackground(BLUE);

		//p.drawState();
		phy.runCollisions();

		timer::updateAllTimers();

		BeginMode2D(cam);

		//Drawing hitboxes for debugging
		//for (auto& entity : entityList) entity->drawHitbox();

		//p.setCamera(cam);

		//Drawing lines through center, for debugging
		//DrawLine(int(width / 2.0f / textureScale), 0, int(width / 2.0f / textureScale), height, YELLOW);
		//DrawLine(0, int(height / 2.0f / textureScale), int(width / textureScale), int(height / 2.0f / textureScale), GREEN);


		for (int i = 0; i < entityList.size(); i++) {
			entityList[i]->draw();

			//Drawing entity IDs, for debugging
			//auto a = entityList[i]->save();
			//DrawText(std::to_string(i).c_str(), (int)a[1], (int)a[2], 14, ORANGE);
		}




		EndMode2D();

		EndDrawing();
	}

	CloseWindow();
	textureFiles::freeTextures();

	auto size = entityList.size();
	for (int i = 0; i < size; i++) {
		delete entityList[i];
	}
}