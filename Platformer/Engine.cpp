// Engine.cpp

#include <SDL.h>
#pragma comment(lib,"sdl2.lib")
#pragma comment(lib,"sdl2main.lib")
#include <cstdio>

#include "DrawManager.h"
#include "SpriteManager.h"
#include "Level.h"
#include "PlayerObject.h"
#include "Collider.h"
#include "Engine.h"
#include "Fish.h"
Engine::Engine() : m_log("log.txt") {
	m_window = nullptr;

	m_draw_manager = nullptr;
	m_sprite_manager = nullptr;

	m_running = false;
	m_width = 0;
	m_height = 0;
	m_deltatime = 0.01f;
	m_ticks = SDL_GetTicks();

	m_level = nullptr;
	m_player = nullptr;
};

Engine::~Engine() {
};

bool Engine::Initialize() {
	m_width = 1024;
	m_height = 640;

	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Platformer",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height,
		SDL_WINDOW_OPENGL);
	if(m_window == nullptr) { return false; };

	m_draw_manager = new DrawManager;
	if(!m_draw_manager->Initialize(m_window, m_width, m_height)) {
		return false;
	};

	m_sprite_manager = new SpriteManager(m_draw_manager);
	if(!m_sprite_manager->Initialize("../data/sprites/")) {
		return false;
	};

	m_level = new Level;
	m_level->Load("../data/levels/01.txt", m_sprite_manager);

	Sprite* sprite = m_sprite_manager->Load("p1_spritesheet.png", 0, 0, 70, 95);
	Collider* collider = new Collider(
		m_level->GetPlayerStartPosition(), 
		Vector2(70.0f, 95.0f));
	m_player = new PlayerObject(&m_keyboard, sprite, collider);
	m_player->SetPosition(m_level->GetPlayerStartPosition());
	{
		Sprite* sprite = m_sprite_manager->Load("p1_spritesheet.png",0,70,70,95);
		m_lightball = new GameObject(sprite,nullptr);
		Vector2 tmp = m_player->GetPosition();
		tmp.m_x += 100;
		m_lightball->SetPosition(tmp);
	}

	{
		Sprite *fish = m_sprite_manager->Load("p1_spritesheet.png",0,40,70,95);

		Collider * collider = new Collider(Vector2(0,0),Vector2(0,0));
		m_fish = new Fish(&m_keyboard,fish,collider);
		m_fish->SetPosition(Vector2(0,0));
	}



	m_running = true;

	return true;
};

void Engine::Run() {
	while(m_running) {
		UpdateDeltatime();
		UpdateEvents();

		if(m_keyboard.IsDownOnce(SDLK_ESCAPE)) {
			break;
		};

		/*if(m_keyboard.IsDownOnce(SDLK_z)) {
		__debugbreak();
		};*/

		m_player->Update(m_deltatime,m_lightball);
		m_fish->Update(m_deltatime,m_lightball,m_player);		
		Vector2 offset;
		if(m_level->CheckCollision(m_player, offset)) {
			m_player->SetPosition(m_player->GetCollider()->m_position);
			if(offset.m_y < 0.0f) {
				//printf("--- Y \n");
				m_player->SetVelocityY(0.0f);
				m_player->AllowJump(true);
			}
			else if(offset.m_y > 0.0f) {
				//printf("+++ Y\n");
				m_player->SetVelocityY(0.0f);
			};
			if(offset.m_x > 0.0f) {
				//printf("+++ X\n");
			}
			else if(offset.m_x < 0.0f) {
				//printf("--- X\n");
			};
		};

		m_draw_manager->Clear();
		m_level->Draw(m_draw_manager);

		m_draw_manager->Draw(
			m_player->GetSprite(),
			m_player->GetPosition().m_x,
			m_player->GetPosition().m_y);
		m_draw_manager->Draw(m_lightball->GetSprite(),m_lightball->GetPosition().m_x, m_lightball->GetPosition().m_y);
		m_draw_manager->Draw(m_fish->GetSprite(), m_fish->GetPosition().m_x, m_fish->GetPosition().m_y);
		m_draw_manager->Present();

		m_keyboard.PostUpdate();
		m_mouse.PostUpdate();

		SDL_Delay(10);
	};
};

void Engine::Cleanup() {
	if(m_player != nullptr) {
		delete m_player->GetSprite();
		delete m_player->GetCollider();
		delete m_player;
		m_player = nullptr;
	};

	if(m_level != nullptr) {
		delete m_level;
		m_level = nullptr;
	};

	if(m_sprite_manager != nullptr) {
		m_sprite_manager->Cleanup();
		delete m_sprite_manager;
		m_sprite_manager = nullptr;
	};

	if(m_draw_manager != nullptr) {
		m_draw_manager->Cleanup();
		delete m_draw_manager;
		m_draw_manager = nullptr;
	};

	if(m_window != nullptr) {
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	};
};


// private
void Engine::UpdateDeltatime() {
	unsigned int ticks = SDL_GetTicks();
	unsigned int delta = ticks - m_ticks;
	m_ticks = ticks;
	m_deltatime = (float)delta * 0.001f;
	if(m_deltatime > 0.1f) {
		m_deltatime = 0.1f;
	};
};

void Engine::UpdateEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			m_running = false;
		}
		else if(event.type == SDL_KEYDOWN) {
			int index = event.key.keysym.sym & 0xFF;
			m_keyboard.m_current[index] = true;
		}
		else if(event.type == SDL_KEYUP) {
			int index = event.key.keysym.sym & 0xFF;
			m_keyboard.m_current[index] = false;
		}
		else if(event.type == SDL_MOUSEMOTION) {
			m_mouse.m_x = event.motion.x;
			m_mouse.m_y = event.motion.y;
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN) {
			if(event.button.button == SDL_BUTTON_LEFT) {
				m_mouse.m_current[0] = true;
			}
			else if(event.button.button == SDL_BUTTON_RIGHT) {
				m_mouse.m_current[1] = true;
			};
		}
		else if(event.type == SDL_MOUSEBUTTONUP) {
			if(event.button.button == SDL_BUTTON_LEFT) {
				m_mouse.m_current[0] = false;
			}
			else if(event.button.button == SDL_BUTTON_RIGHT) {
				m_mouse.m_current[1] = false;
			};
		};
	};
};
