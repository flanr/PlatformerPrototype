// PlayerObject.cpp

#include <cstdio>
#include <SDL.h>
#include "Input.h"
#include "Sprite.h"
#include "Collider.h"
#include "PlayerObject.h"
#include "GameObject.h"

PlayerObject::PlayerObject(Keyboard *keyboard,Sprite* sprite, Collider* collider) 
	: GameObject(sprite, collider)
	, m_keyboard(keyboard)
	, m_velocity(0.0f, 0.0f)
{ 
	m_allow_jump = false;
	goingleft=false;
	goingright=true;
};
int PlayerObject::GetDirection()
{
	if (goingleft)
	{
		return 1;
	}
	if (goingright)
	{
		return 2;
	}
}

void PlayerObject::Attack()
{
	if (m_keyboard->IsDownOnce(SDLK_SPACE))
	{

	}
}

void PlayerObject::Update(float deltatime, GameObject *lightball) {
	const float speed = 200.0f;
	/*const float gravity = 9.8f;
	*/
	m_velocity.m_x = 0.0f;
	m_velocity.m_y = 0.0f;
	if(m_keyboard->IsDown(SDLK_a)) {
		m_velocity.m_x = deltatime * -speed;
		goingleft = true; 
		goingright = false;
	};
	if(m_keyboard->IsDown(SDLK_d)) {
		m_velocity.m_x = deltatime * speed;
		goingright = true;
		goingleft= false;
	};
	if(m_keyboard->IsDown(SDLK_w))
	{
		m_velocity.m_y = deltatime * -speed;
	}
	if(m_keyboard->IsDown(SDLK_s))
	{
		m_velocity.m_y = deltatime * speed;
	}

	if(m_allow_jump && m_keyboard->IsDownOnce(SDLK_SPACE)) {
		//m_velocity.m_y = -gravity;
		m_allow_jump = false;
	};

	//m_velocity.m_y *= 0.985f;
	//m_velocity.m_y += deltatime * gravity;
	m_position += m_velocity;

	if(HasCollider()) {
		m_collider->m_position = m_position;
	};

	Vector2 tmp = m_position;

	if (goingright)
	{
		tmp.m_x += 100;
	}
	if (goingleft)
	{
		tmp.m_x -=100;
	}
	lightball->SetPosition(tmp);



};

void PlayerObject::SetVelocityY(float vel) {
	m_velocity.m_y = vel;
};

void PlayerObject::AllowJump(bool state) {
	m_allow_jump = state;
};
