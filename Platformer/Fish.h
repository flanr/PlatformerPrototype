// Fish.h



#pragma once

#include "GameObject.h"

class Keyboard;
class Sprite;
class Collider;
class PlayerObject;

class Fish : public GameObject {
public:
	Fish(Keyboard *keyboard, Sprite* sprite = nullptr, Collider* collider = nullptr);

	void Update(float deltatime, GameObject *lightball, PlayerObject *player);
	void SetVelocityY(float vel);
	void AllowJump(bool state);
	
	
protected:
	Keyboard* m_keyboard;
	Vector2 m_velocity;
	PlayerObject* m_player;
	GameObject* m_lightball;
	float m_deltatime;
	bool m_allow_jump;
	bool goingright;
	bool goingleft;
	void Chase();	
	void Flee();
};
