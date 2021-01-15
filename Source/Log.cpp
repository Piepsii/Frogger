#include "Log.h"
#include <sstream>

Log::Log(int _line, float _x, Direction _direction, int _size, float _speed)
{
	std::stringstream ss;
	ss << "../Assets/log" << _size << ".png";
	m_texture->loadFromFile(ss.str());
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(_x, _line * 32.0f + 16.0f);
	m_direction = _direction;
	m_speed = _speed;
}

Log::~Log()
{
}
