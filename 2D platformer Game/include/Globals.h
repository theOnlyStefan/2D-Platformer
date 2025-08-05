#pragma once
#include "raylib.h"

#include <iostream>
#include <string>
#include <vector>

inline constexpr int mul = 8;
inline constexpr int width = 160 * mul, height = 90 * mul;
inline constexpr float textureScale = 2;

class textureFiles {
public:
	static Texture2D terrain;
	static Texture2D GUI;
	static Texture2D background_blue;

	static std::vector<Texture2D> p_idles, p_doubleJumps, p_wallJumps, p_runs, p_hits, p_jumps, p_falls;
	
	static void initialize();
	static void initializePlayers();

	static void freeTextures();
	static void freePlayers();
};