#include "Car.h"
#include "config.h"
#include <sstream>


Car::Car(int _line, float _x, Direction _direction, int _size)
{
	std::stringstream ss;
	ss << "../Assets/car" << _size << ".png";
	m_texture->loadFromFile(ss.str());
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(16.0f, 16.0f);
	m_sprite.setPosition(_x, _line * 32.0f + 16.0f);
	m_direction = _direction;
}

Car::~Car()
{
}

void Car::Update()
{
	switch (m_direction)
	{
	case Direction::EAST:
		m_sprite.move(0.5f, 0.0f);
		break;
	case Direction::WEST:
		m_sprite.move(-0.5f, 0.0f);
		break;
	}

	if (m_sprite.getPosition().x < 0)
		m_sprite.setPosition(static_cast<float>(config::WIDTH), m_sprite.getPosition().y);
	if (m_sprite.getPosition().x > config::WIDTH)
		m_sprite.setPosition(0, m_sprite.getPosition().y);
}

void Car::Draw(sf::RenderWindow& _window)
{
	_window.draw(m_sprite);
}
