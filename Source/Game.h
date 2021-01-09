#pragma once

#include "SFML/Graphics.hpp"
#include "InputManager.h"
#include "GameObject.h"
#include "Frog.h"
#include "Car.h"

class Game
{
public:
	Game(unsigned int &screenWidth, unsigned int &screenHeight, const char* &title, InputManager& _inputManager);
	~Game();
	/// Return Value
	/// true = Continue to run program
	/// false = Quits program
	bool Update(float deltaTime); 
	void Draw(sf::RenderWindow& window);
	void handleInput();
	void onKeyPressed(sf::Keyboard::Key& _key);
	void onKeyReleased(sf::Keyboard::Key& _key);
	void setUpLevel(int _level);

private:
	enum class GameState
	{
		MENU,
		GAME
	};
	GameState m_gameState;
	InputManager* m_inputManager;
	Frog m_frog;
	std::vector<Car> m_cars;

	sf::Font m_font;
	sf::Text m_menuText;
	int m_score, m_gameTimer, m_levelTimer;
	sf::RectangleShape m_safetyStripe1, m_safetyStripe2;

};