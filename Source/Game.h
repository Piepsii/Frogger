#pragma once

#include "SFML/Graphics.hpp"
#include "InputManager.h"
#include "GameObject.h"
#include "Frog.h"
#include "Car.h"
#include "Log.h"
#include "Goal.h"
#include "GUI.h"

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
	void resetLevel(int _seed);
	void checkCollision();
	void reduceLives();
	void checkWinCondition();
	void deleteArrays();
	void updateTimer();

private:
	enum class GameState
	{
		STARTMENU,
		GAME,
		ENDMENU
	};
	GameState m_gameState;
	InputManager* m_inputManager;
	Frog m_frog;
	std::vector<Goal*> m_goals;
	std::vector<Car*> m_cars;
	std::vector<Log*> m_logs;
	GUI* m_gui;

	sf::Font m_font;
	sf::Text m_menuText;
	int m_score, m_gameTimer, m_levelTimer, m_playerLives, m_completedGoals;
	sf::RectangleShape m_safetyStripe1, m_safetyStripe2, m_water;
	sf::RectangleShape m_hedge;
	std::vector<sf::RectangleShape*> m_goalWaterShapes;
	bool m_won, m_lost;

};