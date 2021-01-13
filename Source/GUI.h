#pragma once
#include "SFML/Graphics.hpp"

class GUI
{
public:
	GUI();
	~GUI();
	void Update();
	void Draw(sf::RenderWindow& _window);
	void reduceLives();
	void setTime(int _tick);

private:
	sf::Texture* texture;
	sf::Sprite sprite;
	std::vector<sf::Sprite> m_guiLives;
	sf::Font m_font;
	sf::Text m_score, m_time, m_highScore;
};

