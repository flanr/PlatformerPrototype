// Collider.cpp

#include <cstdio>
#include <cmath>
#include "Collider.h"

Collider::Collider() 
: m_position(0.0f, 0.0f)
, m_extension(0.0f, 0.0f)
{
};

Collider::Collider(const Vector2 &position, const Vector2 &extension)
: m_position(position)
, m_extension(extension)
{
};

bool Collider::Overlap(Collider &other, Vector2 &offset) {
	float A = m_extension.m_x * 0.5f;
	float B = other.m_extension.m_x * 0.5f;
	float C = (m_position.m_x + A) - (other.m_position.m_x + B);
	if(fabs(C) <= A + B) {
		float Q = m_extension.m_y * 0.5f;
		float P = other.m_extension.m_y * 0.5f;
		float Z = (m_position.m_y + Q) - (other.m_position.m_y + P);
		if(fabs(Z) <= Q + P) {
			float dx = ceilf(fabs(C) - (A + B));
			float dy = ceilf(fabs(Z) - (Q + P));
			if(dx >= dy) {
				if(m_position.m_x < other.m_position.m_x) {
					dx = -dx;
				};
				offset.m_x = dx;
				other.m_position.m_x += dx;
			}
			else {
				if(m_position.m_y < other.m_position.m_y) {
					dy = -dy;
				};
				offset.m_y = dy;
				other.m_position.m_y += dy;
			};
			return true;
		};
	};
	return false;
};
