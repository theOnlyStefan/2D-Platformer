#pragma once
#include <fstream>
#include <sstream>
#include "Object.h"
#include "MobileObject.h"
#include "Player.h"
#include "Globals.h"
class creator {
//private:
	//Texture2D terrain;
	//std::vector<Texture2D> p_idles, p_doubleJumps, p_wallJumps, p_runs, p_hits, p_jumps, p_falls;
public:
	enum itemID { STONE_BLOCK, DIRT_BLOCK, WOOD_BLOCK, AUTUMN_BLOCK, GREENSTONE_BLOCK, CANDY_BLOCK, BRICK_BLOCK, PLAYER };

	std::vector<object*> load(std::string saveLocation) {
		std::fstream saveFile(saveLocation, std::ios::in);
		std::vector<object*> result;

		std::string row;
		while (std::getline(saveFile, row)) {
			std::istringstream line(row);
			std::vector<float> values;

			std::string token;
			while (std::getline(line, token, ' ')) {
				values.push_back(std::stof(token));
			}
			
			result.push_back(make(int(values[0]), values[1], values[2]));
		}
		return result;
	}

	object* make(int id, float posX = 0, float posY = 0) {
		return make(static_cast<itemID>(id), posX, posY);
	}

	object* make(itemID id, float posX = 0, float posY = 0) {

		object* a = nullptr;
		switch (int(id)) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			{
				Rectangle part{ float(id % 2) * (48 + 32 + 16),float((id / 2) % 3) * (48 + 16),48.0f,48.0f };
				a = new object(id,posX, posY, textureFiles::terrain, part);
				a->setHitbox(24, 24);
				return a;
				break;
			}
			case 6:
			{
				Rectangle part{ 3 * (48 + 32 + 16) - 16,1 * (48 + 16),48,48 };
				a = new object(id,posX, posY, textureFiles::terrain, part);
				a->setHitbox(24, 24);
				return a;
				break;
			}
			case 7:
			case 8:
			case 9:
			case 10:
			{
				Player* p = new Player(id, posX, posY, id - 7, textureFiles::p_falls[id-7]);
				return p;
				break;
			}
			case 11:
			case 12:
			case 13:
			{
				Rectangle part{ 208.0f,16 + float(id - 11) * 64.0f ,32.0f,32.0f };
				a = new object(id, posX, posY, textureFiles::terrain, part);
				a->setHitbox(16, 16);
				return a;
				break;
			}
			case 14:
			{
				Rectangle part{ 288.0f,144.0f ,32.0f,32.0f };
				a = new object(id, posX, posY, textureFiles::terrain, part);
				a->setHitbox(16, 16);
				return a;
				break;
			}
			case 15:
			{
				Rectangle part{ 320.0f,64.0f ,32.0f,32.0f };
				a = new object(id, posX, posY, textureFiles::terrain, part);
				a->setHitbox(16, 16);
				return a;
				break;
			}
			default:
				return nullptr;

		}

	}

};