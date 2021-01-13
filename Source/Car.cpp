#include "Car.h"
#include <sstream>


Car::Car(int _line, float _x, Direction _direction, int _size)
{
	std::stringstream ss;
	ss << "../Assets/car" << _size << ".png";
	m_texture->loadFromFile(ss.str());
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(_x, _line * 32.0f + 16.0f);
	m_direction = _direction;
}

Car::~Car()
{
}