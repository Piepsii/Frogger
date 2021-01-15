// Paul Brandstetter DOD: 15.01.2021
#include "Game.h"

Game::Game(unsigned int &screenWidth, unsigned int &screenHeight, const char* &title, InputManager& _inputManager)
	: m_gameState(GameState::STARTMENU),
	m_score(0),
	m_gameTimer(0),
	m_playerLives(3),
	m_completedGoals(0),
	m_won(false),
	m_lost(false),
	m_highestPosition(INT_MAX),
	m_positionScore(0),
	m_collectiveScore(0),
	m_maxTime(7200),
	m_levelTimer(7200)
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
	
	resetLevel(static_cast<unsigned int>(time(NULL)));

	m_music.openFromFile("../Assets/The_Snake_Strut.wav");
	m_music.play();
	m_music.setVolume(30);
	m_crashBuffer.loadFromFile("../Assets/crash.wav");
	m_crash.setBuffer(m_crashBuffer);
	m_crash.setVolume(30);
	m_goalBuffer.loadFromFile("../Assets/goal.wav");
	m_goal.setBuffer(m_goalBuffer);
	m_goal.setVolume(30);
	m_splashBuffer.loadFromFile("../Assets/splash.wav");
	m_splash.setBuffer(m_splashBuffer);
	m_splash.setVolume(30);

	m_highScoreManager = new HighScoreManager();

};

Game::~Game()
{
	deleteArrays();
	delete m_gui;
	delete m_highScoreManager;
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
		{
			m_gameState = GameState::ENDMENU;
		}
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
		m_collectiveScore = scoreByMoving() + scoreByTime();
		m_gui->Update(m_score + m_collectiveScore);
		break;
	case GameState::ENDMENU:
		if (!m_highScoreManager->Update())
			return false;
	}
	return true;
}

void Game::Draw(sf::RenderWindow& _window)
{
	switch (m_gameState)
	{
	case GameState::STARTMENU:
		_window.draw(m_menuText);
		m_highScoreManager->DrawHighScores(_window);
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
		m_highScoreManager->Draw(_window);
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

void Game::resetLevel(unsigned int _seed)
{
	//general
	m_score += m_collectiveScore;
	m_levelTimer = m_maxTime;
	deleteArrays();
	m_cars.clear();
	m_logs.clear();
	m_goals.clear();
	m_goalWaterShapes.clear();
	m_frog.resetPlayer();
	m_completedGoals = 0;
	m_highestPosition = INT_MAX;
	srand(_seed);

	//cars
	for (int i = 0; i < 5; i++)
	{
		GameObject::Direction direction = static_cast<GameObject::Direction>(rand() % 2 == 0 ? 1 : 3);
		int size = rand() % 2 + 1;
		float speed = (rand() / RAND_MAX) * 2 + 0.6f;
		m_cars.push_back(new Car(13 - i, 0.0f + rand() % 40 - 20.0f, direction, size, speed));
		m_cars.push_back(new Car(13 - i, 160.0f + rand() % 40 - 20.0f, direction, size, speed));
		m_cars.push_back(new Car(13 - i, 320.0f + rand() % 40 - 20.0f, direction, size, speed));
		m_cars.push_back(new Car(13 - i, 480.0f + rand() % 40 - 20.0f, direction, size, speed));
	}

	//logs
	for (int i = 0; i < 6; i++)
	{
		GameObject::Direction direction = static_cast<GameObject::Direction>(rand() % 2 == 0 ? 1 : 3);
		int size = rand() % 3 + 1;
		float speed = (rand() / RAND_MAX) * 2 + 0.6f;
		m_logs.push_back(new Log(7 - i, 0.0f + rand() % 40 - 20.0f, direction, size, speed));
		m_logs.push_back(new Log(7 - i, 160.0f + rand() % 40 - 20.0f, direction, size, speed));
		m_logs.push_back(new Log(7 - i, 320.0f + rand() % 40 - 20.0f, direction, size, speed));
		m_logs.push_back(new Log(7 - i, 480.0f + rand() % 40 - 20.0f, direction, size, speed));
	}

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
			m_crash.play();
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
		m_splash.play();
		reduceLives();
	}

	//goals and frog
	for (auto& goal : m_goals)
	{
		if (goal->m_sprite.getGlobalBounds().intersects(m_frog.getCollisionRect().getGlobalBounds()))
		{
			m_goal.play();
			m_score += m_positionScore;
			m_highestPosition = INT_MAX;
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
		m_won = true;
	if (m_playerLives <= 0)
	{
		m_lost = true;
		m_highScoreManager->setScore(m_score + m_collectiveScore);
	}
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

int Game::scoreByMoving()
{
	if(m_highestPosition > m_frog.m_sprite.getPosition().y)
		m_highestPosition = m_frog.m_sprite.getPosition().y;
	return m_positionScore = config::HEIGHT - m_highestPosition;
}

int Game::scoreByTime()
{
	return m_timeScore = m_levelTimer / 12;
}

void Game::textEntered(sf::Event& _event)
{
	if(m_gameState == GameState::ENDMENU)
		m_highScoreManager->handleInput(_event);
}


