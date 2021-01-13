#include "Goal.h"

Goal::Goal(float _x)
	:m_isCompleted(false), m_wasCompleted(false)
{
	m_texture->loadFromFile("../Assets/frog.png");
	m_sprite.setTexture(*m_texture);
	m_sprite.setColor(sf::Color::Transparent);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(_x, 32.0f + 16.0f);
}

void Goal::Update()
{
	if (wasCompleted())
		m_sprite.setColor(sf::Color::White);
	m_wasCompleted = m_isCompleted;
}

void Goal::setCompleted(bool _param)
{
	m_isCompleted = _param;
}

bool Goal::wasCompleted()
{
	bool result = m_isCompleted && !m_wasCompleted;
	return result;
}
