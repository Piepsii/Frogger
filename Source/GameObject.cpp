#include "GameObject.h"
#include "config.h"

GameObject::GameObject()
{
	m_texture = new sf::Texture();
	m_direction = Direction::NORTH;
	m_directionVector = sf::Vector2f(0.0f, 0.0f);
}

GameObject::~GameObject()
{
	delete m_texture;
}

void GameObject::Update()
{
	switch (m_direction)
	{
	case Direction::EAST:
		m_directionVector.x = -0.5f;
		break;
	case Direction::WEST:
		m_directionVector.x = 0.5f;
		break;
	}

	m_sprite.move(m_directionVector);

	if (m_sprite.getPosition().x < 0)
		m_sprite.setPosition(static_cast<float>(config::WIDTH), m_sprite.getPosition().y);
	if (m_sprite.getPosition().x > config::WIDTH)
		m_sprite.setPosition(0, m_sprite.getPosition().y);
}

void GameObject::Draw(sf::RenderWindow& _window)
{
	_window.draw(m_sprite);
}

sf::Vector2f GameObject::getDirectionVector()
{
	return m_directionVector;
}
