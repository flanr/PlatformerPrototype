// Level.cpp

#include <sstream>
#include <fstream>
#include "Sprite.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "GameObject.h"
#include "Collider.h"
#include "Level.h"

Level::Level() {
	m_width = 0;
	m_height = 0;

	m_start_position = Vector2(0.0f, 0.0f);
};

Level::~Level() {
	auto it = m_objects.begin();
	while(it != m_objects.end()) {
		delete (*it)->GetSprite();
		delete (*it)->GetCollider();
		delete (*it);
		++it;
	};
	m_objects.clear();
};

bool Level::Load(const std::string &filename, SpriteManager *sprite_manager) {
	std::ifstream stream(filename);
	if(!stream.is_open()) {
		return false;
	};

	std::string row;
	unsigned int coord_count = 0;
	stream >> m_spritemap_filename;
	stream >> coord_count >> m_width >> m_height;
	std::getline(stream, row);

	for(unsigned int i = 0; i < coord_count; i++) {
		std::getline(stream, row);
		std::stringstream ss(row);
		std::string ch;
		Coords coord;

		ss >> ch;
		ss >> coord.x;
		ss >> coord.y;
		ss >> coord.w;
		ss >> coord.h;

		m_tile_coords.insert( std::pair<char,Coords>(ch[0], coord) );
	};

	unsigned int x = 0;
	unsigned int y = 0;
	while(!stream.eof()) {
		std::getline(stream, row, '\n');
		if(row.length() == 0) { 
			continue;
		};
		x = 0;
		for(unsigned int i = 0; i < row.length(); i++) {
			if(row[i] == '0') {
				x += m_width;
				continue;
			}
			else if(row[i] == 'S') {
				m_start_position.m_x = x;
				m_start_position.m_y = y;
				x += m_width;
				continue;
			};

			std::map<char,Coords>::iterator it = m_tile_coords.find(row[i]);
			if(it == m_tile_coords.end()) {
				continue;
			};

			Coords &c = it->second;
			Sprite *sprite = sprite_manager->Load(m_spritemap_filename, c.x, c.y, c.w, c.h); 

			Collider *collider = new Collider;
			collider->m_position = Vector2(x, y);
			collider->m_extension = Vector2(c.w, c.h);

			GameObject *go = new GameObject(sprite, collider);
			go->SetPosition(Vector2(x, y));
			m_objects.push_back(go);

			x += m_width;
		};
		y += m_height;
	};

	stream.close();

	return true;
};

void Level::Draw(DrawManager *draw_manager) {
	for(auto i = 0UL; i < m_objects.size(); i++) {
		draw_manager->Draw(m_objects[i]->GetSprite(),
			m_objects[i]->GetPosition().m_x,
			m_objects[i]->GetPosition().m_y);
	};
};

bool Level::CheckCollision(GameObject *object, Vector2 &offset) {
	if(!object->HasCollider()) { return false; };

	int count = 0;
	for(auto i = 0UL; i < m_objects.size(); i++) {
		if(m_objects[i]->HasCollider()) {
			Vector2 off;
			if(m_objects[i]->GetCollider()->Overlap(*object->GetCollider(), off)) {
				offset += off;
				count++;
			};
		};
	};
	if(count > 0) {
		offset /= (float)count;
		//printf("%2d %f %f\n", count, offset.m_x, offset.m_y);
		offset.m_x=floorf(offset.m_x);
		offset.m_y=floorf(offset.m_y);
		return true;
	};
	return false;
};


Vector2 Level::GetPlayerStartPosition() {
	return m_start_position;
};
