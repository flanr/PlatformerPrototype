// GameObject.h

#pragma once

#include "Vector2.h"

class Sprite;
class Collider;

class GameObject {
public:
	GameObject(Sprite *sprite = nullptr, Collider *collider = nullptr);

	const Vector2 &GetPosition() const;
	void SetPosition(const Vector2 &position);

	bool HasSprite() const;
	Sprite* GetSprite();

	bool HasCollider() const;
	Collider* GetCollider();

protected:
	Sprite *m_sprite;
	Collider *m_collider;
	Vector2 m_position;
};
