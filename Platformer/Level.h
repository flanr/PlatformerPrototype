// Level.h

#pragma once

#include "Vector2.h"
#include <vector>
#include <string>
#include <map>

class GameObject;
class SpriteManager;
class DrawManager;

class Level {
	struct Coords {
		int x, y, w, h;
	};
public:
	Level();
	~Level();

	bool Load(const std::string &filename, SpriteManager *sprite_manager);

	void Draw(DrawManager *draw_manager);

	bool CheckCollision(GameObject *object, Vector2 &offset);

	Vector2 GetPlayerStartPosition();

private:
	std::string m_spritemap_filename;
	unsigned int m_width;
	unsigned int m_height;
	std::map<char,Coords> m_tile_coords;

	std::vector<GameObject*> m_objects;
	Vector2 m_start_position;
};
