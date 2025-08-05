#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"
#include "Player.h"
#include "PhysicsEngine.h"
#include "Test.h"
#include "ObjectCreator.h"
#include "Timer.h"
#include "Globals.h"
#include "tinyfiledialogs.h"

#define blockSize 48

using namespace std;

namespace gameLoop {
	void openLevelSelect();
	void runGame(string levelPath);
}