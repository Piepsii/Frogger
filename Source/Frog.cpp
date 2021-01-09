#include "Frog.h"

Frog::Frog()
{
	m_texture = new sf::Texture();
	m_texture->loadFromFile("../Assets/frog.png");
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(16.0f, 16.0f);
	m_sprite.setPosition(7 * 32.0f + 16.0f, 14 * 32.0f + 16.0f);
	m_isJumping = false;
	m_currentPosition = sf::Vector2f(0.0f, 0.0f);
	m_destinationPosition = sf::Vector2f(7 * 32.0f + 16.0f, 14 * 32.0f + 16.0f);
	m_direction = sf::Vector2f(0.0f, 0.0f);
	m_velocity = 0.0f;
}

Frog::~Frog()
{
}

void Frog::Update()
{
	m_currentPosition = m_sprite.getPosition();
	m_direction = m_destinationPosition - m_currentPosition;
	m_velocity = sqrt(powf(m_direction.x, 2.0f) + powf(m_direction.y, 2.0f));
	if (m_velocity < 0.5f)
	{
		m_isJumping = false;
		m_sprite.setPosition(m_destinationPosition);
		m_sprite.setScale(0.0f, 0.0f);
		m_direction.x = 0.0f;
		m_direction.y = 0.0f;
	}
	printf("%f\n", m_velocity);
	m_sprite.setScale(sin((m_velocity - (M_PI * 5.0f) / 2.0f) * 0.2f) * 0.3f + 2.0f, sin((m_velocity - (M_PI * 5.0f) / 2.0f) * 0.2f) * 0.3f + 2.0f);
	m_sprite.move(m_direction / 32.0f);
}

void Frog::Draw(sf::RenderWindow& _window)
{
	_window.draw(m_sprite);
}

void Frog::jump(Direction _direction)
{
	switch (_direction)
	{
	case Direction::NORTH:
		m_isJumping = true;
		m_sprite.setRotation(0.0f);
		m_destinationPosition += sf::Vector2f(0.0f, -32.0f);
		break;
	case Direction::EAST:
		m_isJumping = true;
		m_sprite.setRotation(90.0f);
		m_destinationPosition += sf::Vector2f(32.0f, 0.0f);
		break;
	case Direction::SOUTH:
		m_isJumping = true;
		m_sprite.setRotation(180.0f);
		m_destinationPosition += sf::Vector2f(0.0f, 32.0f);
		break;
	case Direction::WEST:
		m_isJumping = true;
		m_sprite.setRotation(270.0f);
		m_destinationPosition += sf::Vector2f(-32.0f, 0.0f);
		break;
	}
}

bool Frog::isJumping()
{
	return m_isJumping;
}
