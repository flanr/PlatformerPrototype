// Fish.cpp
#include <cmath>
#include "Fish.h"
#include "PlayerObject.h"


Fish::Fish(Keyboard *keyboard,Sprite* sprite, Collider* collider) 
	: GameObject(sprite, collider)
	, m_keyboard(keyboard)
	, m_velocity(0.0f, 0.0f)
{

}

void Fish::Update(float deltatime, GameObject* lightball, PlayerObject* player)
{
	float speed = 50.0f;
	m_velocity.m_x= 0.0f;
	m_velocity.m_y= 0.0f;
	m_deltatime = deltatime;
	m_lightball = lightball;
	m_player = player;


	Chase();

	Flee();


}

void Fish::Chase()
{
	float speed = 50.0f;
	float delta_x = m_position.m_x - m_lightball->GetPosition().m_x;
	float delta_y = m_position.m_y - m_lightball->GetPosition().m_y;
	Vector2 distance_to_light;
	distance_to_light.m_x = delta_x;
	distance_to_light.m_y = delta_y;
	distance_to_light.Normalize();
	if (m_player->GetPosition().m_x > m_position.m_x && m_player->GetDirection() == 1) // Left
	{


		m_velocity += distance_to_light * speed;

		m_position -= m_velocity *m_deltatime;
	}
	if (m_player->GetPosition().m_x < m_position.m_x && m_player->GetDirection() == 2) // Right
	{


		m_velocity += distance_to_light * speed;

		m_position -= m_velocity *m_deltatime;
	}

}

void Fish::Flee()
{
	float speed = 450.0f;
	float delta_x = m_position.m_x - m_player->GetPosition().m_x;
	float delta_y = m_position.m_y - m_player->GetPosition().m_y;
	Vector2 distance_to_light;
	distance_to_light.m_x = delta_x;
	distance_to_light.m_y = delta_y;
	distance_to_light.Normalize();

	if (fabs(delta_x) <= 200 && fabs(delta_y) <= 200 && m_player->GetPosition().m_x > m_position.m_x && m_player->GetDirection() == 2)
	{
		//distace to player
		m_velocity += distance_to_light * speed;

		m_position += m_velocity * m_deltatime;
	}

	if (fabs(delta_x) <= 200 && fabs(delta_y) <= 200 && m_player->GetPosition().m_x < m_position.m_x && m_player->GetDirection() == 1)
	{
		//distace to player
		m_velocity += distance_to_light * speed;

		m_position += m_velocity * m_deltatime;
	}

}

