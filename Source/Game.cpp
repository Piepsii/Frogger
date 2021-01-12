#include "Game.h"

Game::Game(unsigned int &screenWidth, unsigned int &screenHeight, const char* &title, InputManager& _inputManager)
	: m_gameState(GameState::MENU), m_score(0), m_gameTimer(0), m_levelTimer(0)
{
	screenWidth = 640;
	screenHeight = 480;
	title = "The Game";
	m_font.loadFromFile("../Assets/GamePixies.ttf");
	m_menuText.setFont(m_font);
	m_menuText.setString("PRESS SPACE TO START");
	m_menuText.setPosition(150, 400);
	m_inputManager = &_inputManager;
	m_safetyStripe1 = sf::RectangleShape(sf::Vector2f(static_cast<float>(screenWidth), 32.0f));
	m_safetyStripe1.setPosition(0.0f, 14 * 32.0f);
	m_safetyStripe1.setFillColor(sf::Color(170, 15, 250));
	m_safetyStripe2 = sf::RectangleShape(m_safetyStripe1);
	m_safetyStripe2.setPosition(0.0f, 8 * 32.0f);
	m_safetyStripe2.setFillColor(sf::Color(170, 15, 250));
	m_water = sf::RectangleShape(sf::Vector2f(static_cast<float>(screenWidth), 8 * 32.0f));
	m_water.setFillColor(sf::Color::Blue);
	setUpLevel(0);
	m_playerLives = 3;
};

Game::~Game()
{
	for (auto& car : m_cars)
		delete car;
	delete m_inputManager;
}

bool Game::Update(float deltaTime)
{
	handleInput();
	switch (m_gameState)
	{
	case GameState::MENU:
		break;
	case GameState::GAME:
		m_frog.Update();
		for (auto a = 0; a < m_cars.size(); a++)
			m_cars.at(a)->Update();
		checkCollision();
		break;
	}
	return true;
}

void Game::Draw(sf::RenderWindow& _window)
{
	switch (m_gameState)
	{
	case GameState::MENU:
		_window.draw(m_menuText);
		break;
	case GameState::GAME:
		_window.draw(m_safetyStripe1);
		_window.draw(m_safetyStripe2);
		_window.draw(m_water);
		_window.draw(m_frog.getCollisionBounds());
		m_frog.Draw(_window);
		for (auto& car : m_cars)
			car->Draw(_window);
		break;
	}
}

void Game::handleInput()
{
	switch (m_gameState)
	{
	case GameState::MENU:
		if (m_inputManager->isKeyPressed(sf::Keyboard::Space))
			m_gameState = GameState::GAME;
		break;
	case GameState::GAME:
		m_frog.handleInput(m_inputManager);
		break;
	}
}

void Game::onKeyPressed(sf::Keyboard::Key& _key)
{
	m_inputManager->setKey(_key, true);
}

void Game::onKeyReleased(sf::Keyboard::Key& _key)
{
	m_inputManager->setKey(_key, false);
}

void Game::setUpLevel(int _level)
{
	m_cars.push_back(new Car(13, 0.0f, GameObject::Direction::EAST, 1));
	m_cars.push_back(new Car(13, 160.0f, GameObject::Direction::EAST, 1));
	m_cars.push_back(new Car(13, 320.0f, GameObject::Direction::EAST, 1));
	m_cars.push_back(new Car(13, 480.0f, GameObject::Direction::EAST, 1));
	m_cars.push_back(new Car(12, 0.0f, GameObject::Direction::WEST, 1));
	m_cars.push_back(new Car(12, 160.0f, GameObject::Direction::WEST, 1));
	m_cars.push_back(new Car(12, 320.0f, GameObject::Direction::WEST, 1));
	m_cars.push_back(new Car(12, 480.0f, GameObject::Direction::WEST, 1));
	m_cars.push_back(new Car(11, 0.0f, GameObject::Direction::WEST, 1));
	m_cars.push_back(new Car(11, 160.0f, GameObject::Direction::WEST, 1));
	m_cars.push_back(new Car(11, 320.0f, GameObject::Direction::WEST, 1));
	m_cars.push_back(new Car(11, 480.0f, GameObject::Direction::WEST, 1));
	m_cars.push_back(new Car(10, 0.0f, GameObject::Direction::EAST, 2));
	m_cars.push_back(new Car(10, 160.0f, GameObject::Direction::EAST, 2));
	m_cars.push_back(new Car(10, 320.0f, GameObject::Direction::EAST, 2));
	m_cars.push_back(new Car(10, 480.0f, GameObject::Direction::EAST, 2));
}

void Game::checkCollision()
{
	//cars and frog
	for (auto& car : m_cars)
	{
		if (car->m_sprite.getGlobalBounds().intersects(m_frog.getCollisionBounds().getGlobalBounds()))
		{
			m_playerLives--;
			m_frog.resetPlayer();
		}
	}
}

