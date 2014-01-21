// Engine.h

#pragma once

#include "Input.h"
#include "Logging.h"

class DrawManager;
class SpriteManager;
class PlayerObject;
class Level;
class GameObject;
class Fish;

class Engine {
public:
	Engine();
	~Engine();

	bool Initialize();
	void Run();
	void Cleanup();

private:
	void UpdateDeltatime();
	void UpdateEvents();

private:
	struct SDL_Window *m_window;

	DrawManager *m_draw_manager;
	SpriteManager *m_sprite_manager;
	GameObject *m_lightball;
	Fish *m_fish;
	Keyboard m_keyboard;
	Mouse m_mouse;
	Log m_log;

	bool m_running;
	int m_width;
	int m_height;
	float m_deltatime;
	unsigned int m_ticks;

	Level* m_level;
	PlayerObject* m_player;
};
