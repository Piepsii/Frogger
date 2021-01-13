#include "GUI.h"

GUI::GUI()
{
	texture = new sf::Texture();
	texture->loadFromFile("../Assets/frog.png");
	sprite.setTexture(*texture);
	sprite.setPosition(16.0f, 480.0f);
	m_guiLives.push_back(sprite);
	sprite.setPosition(32.0f, 480.0f);
	m_guiLives.push_back(sprite);
	sprite.setPosition(48.0f, 480.0f);
	m_guiLives.push_back(sprite);
	m_font.loadFromFile("../Assets/GamePixies.ttf");
	m_score.setFont(m_font);
	m_score.setString("0");
	m_score.setPosition(320.0f, 480.0f);
	m_time.setFont(m_font);
	m_time.setString("TIME");
	m_time.setPosition(600.0f, 480.0f);
	m_time.setOrigin(m_time.getGlobalBounds().width, 0);
	m_highScore.setFont(m_font);
	m_highScore.setString("HI-SCORE 0");
	m_highScore.setPosition(120.0f, 480.0f);
}

GUI::~GUI()
{
	delete texture;
}

void GUI::Update()
{
}

void GUI::Draw(sf::RenderWindow& _window)
{
	for (sf::Sprite& sprite : m_guiLives)
		_window.draw(sprite);
	_window.draw(m_score);
	_window.draw(m_time);
	_window.draw(m_highScore);
}

void GUI::reduceLives()
{
	m_guiLives.pop_back();
}

void GUI::setTime(int _tick)
{
	m_time.setString("TIME " + std::to_string(_tick / 120));
	m_time.setOrigin(m_time.getGlobalBounds().width, 0);
}
