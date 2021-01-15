#include "Frog.h"

Frog::Frog()
{
	m_texture->loadFromFile("../Assets/frog.png");
	m_sprite.setTexture(*m_texture);
	m_sprite.setOrigin(16.0f, 16.0f);
	m_sprite.setPosition(7 * 32.0f + 16.0f, 14 * 32.0f + 16.0f);
	m_isJumping = false;
	m_isOnLog = false;
	m_destinationPosition = sf::Vector2f(7 * 32.0f + 16.0f, 14 * 32.0f + 16.0f);
	m_direction = sf::Vector2f(0.0f, 0.0f);
	m_velocity = 0.0f;
	m_collisionRect = sf::RectangleShape(sf::Vector2f(16.0f, 16.0f));
	m_collisionRect.setFillColor(sf::Color::Red);
	m_jumpBuffer.loadFromFile("../Assets/jump.wav");
	m_jump.setBuffer(m_jumpBuffer);
	m_jump.setVolume(15);
}

Frog::~Frog()
{
}

void Frog::Update()
{
	//floating
	if(m_isOnLog && !m_isJumping)
		m_sprite.move(m_floatDirection);
	m_floatDirection.x = 0.0f;

	//movement
	m_collisionRect.setPosition(m_sprite.getPosition().x - 8.0f, m_sprite.getPosition().y - 8.0f);
	if (m_destinationPosition.x > 0 && m_destinationPosition.x < config::WIDTH && m_destinationPosition.y > 0 && m_destinationPosition.y < config::HEIGHT && m_isJumping)
	{
		m_direction = m_destinationPosition - m_sprite.getPosition();
		m_velocity = sqrt(powf(m_direction.x, 2.0f) + powf(m_direction.y, 2.0f));
		if (m_velocity < 0.7f)
		{
			m_isJumping = false;
			m_sprite.setPosition(m_destinationPosition);
			m_sprite.setScale(0.0f, 0.0f);
			m_direction.x = 0.0f;
			m_direction.y = 0.0f;
		}
		m_sprite.setScale(sin((m_velocity - (M_PI * 5.0f) / 2.0f) * 0.2f) * 0.3f + 1.7f, sin((m_velocity - (M_PI * 5.0f) / 2.0f) * 0.2f) * 0.3f + 1.7f);
		m_sprite.move(m_direction / 8.0f);
	}
	else 
	{
		m_destinationPosition = m_sprite.getPosition();
	}
}

void Frog::jump(Direction _direction)
{
	switch (_direction)
	{
	case Direction::NORTH:
		m_jump.play();
		m_isJumping = true;
		m_sprite.setRotation(0.0f);
		m_destinationPosition += sf::Vector2f(0.0f, -32.0f);
		break;
	case Direction::EAST:
		m_jump.play();
		m_isJumping = true;
		m_sprite.setRotation(90.0f);
		m_destinationPosition += sf::Vector2f(32.0f, 0.0f);
		break;
	case Direction::SOUTH:
		m_jump.play();
		m_isJumping = true;
		m_sprite.setRotation(180.0f);
		m_destinationPosition += sf::Vector2f(0.0f, 32.0f);
		break;
	case Direction::WEST:
		m_jump.play();
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

void Frog::handleInput(InputManager* _inputManager)
{
	if (_inputManager->isKeyPressed(sf::Keyboard::Up) && !isJumping())
		jump(GameObject::Direction::NORTH);
	if (_inputManager->isKeyPressed(sf::Keyboard::Right) && !isJumping())
		jump(GameObject::Direction::EAST);
	if (_inputManager->isKeyPressed(sf::Keyboard::Down) && !isJumping())
		jump(GameObject::Direction::SOUTH);
	if (_inputManager->isKeyPressed(sf::Keyboard::Left) && !isJumping())
		jump(GameObject::Direction::WEST);

}

void Frog::resetPlayer()
{
	m_sprite.setPosition(7 * 32.0f + 16.0f, 14 * 32.0f + 16.0f);
	m_destinationPosition = m_sprite.getPosition();
}

sf::RectangleShape Frog::getCollisionRect()
{
	return m_collisionRect;
}

void Frog::setOnLog(bool _param, sf::Vector2f _directionVector)
{
	m_isOnLog = _param;
	m_floatDirection = _directionVector;
}

bool Frog::isOnLog()
{
	return m_isOnLog;
}
