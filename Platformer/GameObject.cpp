// GameObject.cpp

#include "Sprite.h"
#include "Collider.h"
#include "GameObject.h"

GameObject::GameObject(Sprite *sprite, Collider *collider)
: m_position(0.0f, 0.0f)
, m_sprite(sprite)
, m_collider(collider)
{
};

const Vector2 &GameObject::GetPosition() const {
	return m_position;
};

void GameObject::SetPosition(const Vector2 &position) {
	m_position = position;
};

bool GameObject::HasSprite() const {
	return m_sprite != nullptr;
};

Sprite* GameObject::GetSprite() {
	return m_sprite;
};

bool GameObject::HasCollider() const {
	return m_collider != nullptr;
};

Collider* GameObject::GetCollider() {
	return m_collider;
};
