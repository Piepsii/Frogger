#include "Car.h"
#include "config.h"

Car::Car(int _line, float _x, Direction _direction, int _size)
{
	m_texture = new sf::Texture();
	if (_size == 1)
	{
		m_texture->loadFromFile("../Assets/car1.png");
	}
	else if (_size == 2)
	{
		m_texture->loadFromFile("../Assets/car2.png");
	}
	m_sprite.setTexture(*m_texture);
	m_sprite.setPosition(_x, _line * 32.0f);
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
		m_sprite.move(1.0f, 0.0f);
		break;
	case Direction::WEST:
		m_sprite.move(-1.0f, 0.0f);
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
