// SpriteManager.h

#pragma once

#include <map>
#include <string>

class DrawManager;
class Sprite;

class SpriteManager {
	struct Pair {
		struct SDL_Surface *surface;
		struct SDL_Texture *texture;
	};

public:
	SpriteManager(DrawManager *draw_manager);
	~SpriteManager();

	bool Initialize(const std::string &directory);
	void Cleanup();

	Sprite* Load(const std::string &filename, int x, int y, int width, int height);

private:
	DrawManager *m_draw_manager;
	std::string m_directory;
	std::map<std::string,Pair> m_sprites;
};
