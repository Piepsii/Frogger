#include "GameObject.h"

GameObject::GameObject()
{
	m_texture = new sf::Texture();
	m_direction = Direction::NORTH;
}

GameObject::~GameObject()
{
	delete m_texture;
}
