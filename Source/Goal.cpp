#include "Goal.h"

Goal::Goal(float _x)
	:m_completed(false)
{
	m_texture->loadFromFile("../Assets/frog.png");
	m_sprite.setTexture(*m_texture);
	m_sprite.setColor(sf::Color::Black);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(_x, 32.0f + 16.0f);
}

void Goal::Update()
{
	if (m_completed)
		m_sprite.setColor(sf::Color::White);
}

void Goal::setCompleted(bool _param)
{
	m_completed = _param;
}
