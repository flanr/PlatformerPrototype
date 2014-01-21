// PlayerObject.h

#pragma once

#include "GameObject.h"

class Keyboard;
class Sprite;
class Collider;

class PlayerObject : public GameObject {
public:
	PlayerObject(Keyboard *keyboard, Sprite* sprite = nullptr, Collider* collider = nullptr);

	void Update(float deltatime, GameObject *lightball);
	void SetVelocityY(float vel);
	void AllowJump(bool state);
	int GetDirection();
	void Attack();
	
protected:
	Keyboard* m_keyboard;
	Vector2 m_velocity;
	bool m_allow_jump;
	bool goingright;
	bool goingleft;
	
};
