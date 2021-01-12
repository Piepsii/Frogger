#include "Log.h"
#include <sstream>

Log::Log(int _line, float _x, Direction _direction, int _size)
{
	std::stringstream ss;
	ss << "../Assets/car" << _size << ".png";
	m_texture->loadFromFile(ss.str());
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(16.0f, 16.0f);
	m_sprite.setPosition(_x, _line * 32.0f + 16.0f);
	m_direction = _direction;

}

Log::~Log()
{
}

void Log::Update()
{
}

void Log::Draw(sf::RenderWindow& _window)
{
}
