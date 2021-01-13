#include "Game.h"

Game::Game(unsigned int &screenWidth, unsigned int &screenHeight, const char* &title, InputManager& _inputManager)
	: m_gameState(GameState::STARTMENU), m_score(0), m_gameTimer(0), m_levelTimer(3600), m_playerLives(3), m_completedGoals(0), m_won(false), m_lost(false)
{
	screenWidth = 640;
	screenHeight = 512;
	title = "Frogger";
	m_gui = new GUI();
	m_font.loadFromFile("../Assets/GamePixies.ttf");
	m_menuText.setFont(m_font);
	m_menuText.setString("PRESS SPACE TO START");
	m_menuText.setPosition(150, 400);
	m_inputManager = &_inputManager;
	m_safetyStripe1 = sf::RectangleShape(sf::Vector2f(static_cast<float>(config::WIDTH), 32.0f));
	m_safetyStripe1.setPosition(0.0f, 14 * 32.0f);
	m_safetyStripe1.setFillColor(sf::Color(170, 15, 250));
	m_safetyStripe2 = sf::RectangleShape(m_safetyStripe1);
	m_safetyStripe2.setPosition(0.0f, 8 * 32.0f);
	m_safetyStripe2.setFillColor(sf::Color(170, 15, 250));
	m_water = sf::RectangleShape(sf::Vector2f(static_cast<float>(config::WIDTH), 8 * 32.0f));
	m_water.setFillColor(sf::Color::Blue);
	m_hedge = sf::RectangleShape(sf::Vector2f(static_cast<float>(config::WIDTH), 64.0f));
	m_hedge.setFillColor(sf::Color::Green);
	resetLevel(0);
};

Game::~Game()
{
	deleteArrays();
	delete m_inputManager;
	delete m_gui;
}

bool Game::Update(float deltaTime)
{
	handleInput();
	switch (m_gameState)
	{
	case GameState::STARTMENU:
		break;
	case GameState::GAME:
		if (m_won)
		{
			resetLevel(1);
			m_won = false;
		}
		if (m_lost)
			m_gameState = GameState::ENDMENU;
		m_frog.Update();
		for (auto a = 0; a < m_cars.size(); a++)
			m_cars.at(a)->Update();
		for (auto a = 0; a < m_logs.size(); a++)
			m_logs.at(a)->Update();
		checkWinCondition();
		checkCollision();
		for (auto a = 0; a < m_goals.size(); a++)
		{
			if (m_goals.at(a)->wasCompleted())
				m_completedGoals++;
			m_goals.at(a)->Update();
		}
		updateTimer();
		m_gui->Update();
		break;
	case GameState::ENDMENU:

		break;
	}
	return true;
}

void Game::Draw(sf::RenderWindow& _window)
{
	switch (m_gameState)
	{
	case GameState::STARTMENU:
		_window.draw(m_menuText);
		break;
	case GameState::GAME:
		_window.draw(m_safetyStripe1);
		_window.draw(m_safetyStripe2);
		_window.draw(m_water);
		_window.draw(m_frog.getCollisionRect());
		_window.draw(m_hedge);
		for (auto& rect : m_goalWaterShapes)
			_window.draw(*rect);
		for (auto& car : m_cars)
			car->Draw(_window);
		for (auto& log : m_logs)
			log->Draw(_window);
		for (auto& goal : m_goals)
			goal->Draw(_window);
		m_frog.Draw(_window);
		m_gui->Draw(_window);
		break;
	case GameState::ENDMENU:

		break;
	}
}

void Game::handleInput()
{
	switch (m_gameState)
	{
	case GameState::STARTMENU:
		if (m_inputManager->isKeyPressed(sf::Keyboard::Space))
			m_gameState = GameState::GAME;
		break;
	case GameState::GAME:
		m_frog.handleInput(m_inputManager);
		break;
	case GameState::ENDMENU:

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

void Game::resetLevel(int _seed)
{
	//general
	deleteArrays();
	m_cars.clear();
	m_logs.clear();
	m_goals.clear();
	m_goalWaterShapes.clear();
	m_frog.resetPlayer();

	//cars 1
	m_cars.push_back(new Car(13, 0.0f	, GameObject::Direction::EAST, 1));
	m_cars.push_back(new Car(13, 160.0f	, GameObject::Direction::EAST, 1));
	m_cars.push_back(new Car(13, 320.0f	, GameObject::Direction::EAST, 1));
	m_cars.push_back(new Car(13, 480.0f	, GameObject::Direction::EAST, 1));
	//cars 2
	m_cars.push_back(new Car(12, 0.0f	, GameObject::Direction::WEST, 1));
	m_cars.push_back(new Car(12, 160.0f	, GameObject::Direction::WEST, 1));
	m_cars.push_back(new Car(12, 320.0f	, GameObject::Direction::WEST, 1));
	m_cars.push_back(new Car(12, 480.0f	, GameObject::Direction::WEST, 1));
	//cars 3
	m_cars.push_back(new Car(11, 0.0f	, GameObject::Direction::WEST, 1));
	m_cars.push_back(new Car(11, 160.0f	, GameObject::Direction::WEST, 1));
	m_cars.push_back(new Car(11, 320.0f	, GameObject::Direction::WEST, 1));
	m_cars.push_back(new Car(11, 480.0f	, GameObject::Direction::WEST, 1));
	//cars 4
	m_cars.push_back(new Car(10, 0.0f	, GameObject::Direction::EAST, 2));
	m_cars.push_back(new Car(10, 160.0f	, GameObject::Direction::EAST, 2));
	m_cars.push_back(new Car(10, 320.0f	, GameObject::Direction::EAST, 2));
	m_cars.push_back(new Car(10, 480.0f	, GameObject::Direction::EAST, 2));
	//cars 5
	m_cars.push_back(new Car(9, 0.0f, GameObject::Direction::WEST, 2));
	m_cars.push_back(new Car(9, 160.0f, GameObject::Direction::WEST, 2));
	m_cars.push_back(new Car(9, 320.0f, GameObject::Direction::WEST, 2));
	m_cars.push_back(new Car(9, 480.0f, GameObject::Direction::WEST, 2));
	
	//logs 1
	m_logs.push_back(new Log(7 , 0.0f	, GameObject::Direction::WEST, 1));
	m_logs.push_back(new Log(7 , 160.0f	, GameObject::Direction::WEST, 3));
	m_logs.push_back(new Log(7 , 320.0f	, GameObject::Direction::WEST, 2));
	m_logs.push_back(new Log(7 , 480.0f	, GameObject::Direction::WEST, 3));
	//logs 2
	m_logs.push_back(new Log(6, 0.0f, GameObject::Direction::EAST, 3));
	m_logs.push_back(new Log(6, 170.0f, GameObject::Direction::EAST, 2));
	m_logs.push_back(new Log(6, 330.0f, GameObject::Direction::EAST, 1));
	m_logs.push_back(new Log(6, 470.0f, GameObject::Direction::EAST, 1));
	//logs 3
	m_logs.push_back(new Log(5, 0.0f, GameObject::Direction::EAST, 2));
	m_logs.push_back(new Log(5, 165.0f, GameObject::Direction::EAST, 1));
	m_logs.push_back(new Log(5, 315.0f, GameObject::Direction::EAST, 3));
	m_logs.push_back(new Log(5, 465.0f, GameObject::Direction::EAST, 3));
	//logs 4
	m_logs.push_back(new Log(4, 0.0f, GameObject::Direction::EAST, 2));
	m_logs.push_back(new Log(4, 165.0f, GameObject::Direction::EAST, 1));
	m_logs.push_back(new Log(4, 315.0f, GameObject::Direction::EAST, 3));
	m_logs.push_back(new Log(4, 465.0f, GameObject::Direction::EAST, 3));
	//logs 5
	m_logs.push_back(new Log(3, 0.0f, GameObject::Direction::EAST, 2));
	m_logs.push_back(new Log(3, 165.0f, GameObject::Direction::EAST, 1));
	m_logs.push_back(new Log(3, 315.0f, GameObject::Direction::EAST, 3));
	m_logs.push_back(new Log(3, 465.0f, GameObject::Direction::EAST, 3));
	//logs 6
	m_logs.push_back(new Log(2, 0.0f, GameObject::Direction::WEST, 2));
	m_logs.push_back(new Log(2, 165.0f, GameObject::Direction::WEST, 1));
	m_logs.push_back(new Log(2, 315.0f, GameObject::Direction::WEST, 3));
	m_logs.push_back(new Log(2, 465.0f, GameObject::Direction::WEST, 3));

	//goals
	m_goals.push_back(new Goal(config::WIDTH / 4.0f));
	m_goals.push_back(new Goal(config::WIDTH / 4.0f * 2));
	m_goals.push_back(new Goal(config::WIDTH / 4.0f * 3));

	//goal background shapes
	for (int i = 0; i < m_goals.size(); i++)
	{
		m_goalWaterShapes.push_back(new sf::RectangleShape(sf::Vector2f(32.0f, 32.0f)));
		m_goalWaterShapes.at(i)->setPosition(sf::Vector2f(config::WIDTH / (m_goals.size() + 1.0f) * (static_cast<float>(i) + 1) - 16.0f, 32.0f));
		m_goalWaterShapes.at(i)->setFillColor(sf::Color::Blue);
	}
}

void Game::checkCollision()
{
	//cars and frog
	for (auto& car : m_cars)
	{
		if (car->m_sprite.getGlobalBounds().intersects(m_frog.getCollisionRect().getGlobalBounds()))
		{
			reduceLives();
		}
	}

	//logs and frog
	int counter = 0;
	for (auto& log : m_logs)
	{
		if (m_frog.getCollisionRect().getGlobalBounds().intersects(log->m_sprite.getGlobalBounds()))
		{
			m_frog.setOnLog(true, log->getDirectionVector());
			counter++;
		}
		else if(counter == 0)
		{
			m_frog.setOnLog(false, sf::Vector2f(0.0f, 0.0f));
		}
	}

	//water and frog
	sf::FloatRect intersectionRect;
	sf::FloatRect test = m_frog.getCollisionRect().getGlobalBounds();
	if (m_water.getGlobalBounds().intersects(m_frog.getCollisionRect().getGlobalBounds(), intersectionRect) 
		&& intersectionRect == test
		&& !m_frog.isJumping()
		&& !m_frog.isOnLog())
	{
		reduceLives();
	}

	//goals and frog
	for (auto& goal : m_goals)
	{
		if (goal->m_sprite.getGlobalBounds().intersects(m_frog.getCollisionRect().getGlobalBounds()))
		{
			goal->setCompleted(true);
			m_frog.resetPlayer();
		}
	}
}

void Game::reduceLives()
{
	m_playerLives--;
	m_frog.resetPlayer();
	m_gui->reduceLives();
}

void Game::checkWinCondition()
{
	if (m_completedGoals >= m_goals.size())
		m_won = true;;
	if (m_playerLives <= 0)
		m_lost = true;
}

void Game::deleteArrays()
{
	for (auto& car : m_cars)
		delete car;
	for (auto& log : m_logs)
		delete log;
	for (auto& goal : m_goals)
		delete goal;
	for (auto& rect : m_goalWaterShapes)
		delete rect;
}

void Game::updateTimer()
{
	m_gameTimer++;
	m_levelTimer--;
	m_gui->setTime(m_levelTimer);
	if (m_levelTimer < 0)
		m_lost = true;
}

