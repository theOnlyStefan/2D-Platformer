#include "Globals.h"

//IMPORTANT: MUST DEFINE EVERYTHING HERE FIRST
//!!!!!!!!!!!
//!!!!!!!!!!!
//!!!!!!!!!!!
Texture2D textureFiles::terrain;
Texture2D textureFiles::GUI;
Texture2D textureFiles::background_blue;
std::vector<Texture2D> textureFiles::p_idles, textureFiles::p_doubleJumps, textureFiles::p_wallJumps, textureFiles::p_runs, textureFiles::p_hits, textureFiles::p_jumps, textureFiles::p_falls;


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


void textureFiles::initialize() {
	terrain = LoadTexture(".\\Assets\\Terrain\\Terrain (16x16).png");
	GUI = LoadTexture(".\\Assets\\GUI.png");
	background_blue = LoadTexture(".\\Assets\\Background\\Blue.png");

	initializePlayers();
}

void textureFiles::initializePlayers() {
	std::vector<std::string> names = { "Mask Dude","Ninja Frog","Pink Man", "Virtual Guy" };


	for (auto& name : names) {
		std::string folderName = "Assets/Main Characters/" + name + '/';
		p_idles.push_back(LoadTexture((folderName + "Idle (32x32).png").c_str()));
		p_doubleJumps.push_back(LoadTexture((folderName + "Double Jump (32x32).png").c_str()));
		p_runs.push_back(LoadTexture((folderName + "Run (32x32).png").c_str()));
		p_falls.push_back(LoadTexture((folderName + "Fall (32x32).png").c_str()));
		p_jumps.push_back(LoadTexture((folderName + "Jump (32x32).png").c_str()));
		p_hits.push_back(LoadTexture((folderName + "Hit (32x32).png").c_str()));
		p_wallJumps.push_back(LoadTexture((folderName + "Wall Jump (32x32).png").c_str()));
	}
}

void textureFiles::freeTextures()
{
	UnloadTexture(terrain);
	UnloadTexture(GUI);
	freePlayers();
}

void textureFiles::freePlayers()
{
	for (int i = 0; i < p_idles.size(); i++) {
		UnloadTexture(p_idles[i]);
		UnloadTexture(p_doubleJumps[i]);
		UnloadTexture(p_runs[i]);
		UnloadTexture(p_falls[i]);
		UnloadTexture(p_jumps[i]);
		UnloadTexture(p_hits[i]);
		UnloadTexture(p_wallJumps[i]);
	}
}
