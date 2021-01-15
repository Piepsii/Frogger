#include "HighScoreManager.h"

HighScoreManager::HighScoreManager()
{
	readScores();
	writeScores();

	float width = static_cast<float>(config::WIDTH);
	float height = static_cast<float>(config::HEIGHT);
	m_font.loadFromFile("../Assets/GamePixies.ttf");
	m_playerText.setFont(m_font);
	m_playerText.setString("");
	m_playerText.setPosition(width / 2, height / 2);
	m_inputCaption.setFont(m_font);
	m_inputCaption.setString("Please enter your name:\n");
	m_inputCaption.setOrigin(m_inputCaption.getGlobalBounds().width / 2, m_inputCaption.getGlobalBounds().height / 2);
	m_inputCaption.setPosition(width / 2, height / 2 - 30);
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(90);
	m_scoreText.setPosition(width / 2, height / 2 - 150);
	m_scoreCaption.setFont(m_font);
	m_scoreCaption.setPosition(width / 2, height / 2 - 180);
	m_scoreCaption.setString("Your score:");
	m_scoreCaption.setOrigin(m_scoreCaption.getGlobalBounds().width / 2, m_scoreCaption.getGlobalBounds().height / 2);
	m_inputReceiving = true;

	for (int i = 0; i < 5; i++)
	{
	m_currentHighScores.push_back(sf::Text());
	}
	updateHighScores();
	m_highScoreCaption.setPosition(30, 5);
	m_highScoreCaption.setString("Current Highscores:");
	m_highScoreCaption.setFont(m_font);
}
	
HighScoreManager::~HighScoreManager()
{

}

int HighScoreManager::Update()
{
	return m_inputReceiving;
}

void HighScoreManager::Draw(sf::RenderWindow& _window)
{
	_window.draw(m_scoreCaption);
	_window.draw(m_scoreText);
	_window.draw(m_inputCaption);
	_window.draw(m_playerText);
	m_playerText.setOrigin(m_playerText.getGlobalBounds().width / 2, 16);
}

void HighScoreManager::DrawHighScores(sf::RenderWindow& _window)
{
	_window.draw(m_highScoreCaption);
	for (int i = 0; i < 5; i++)
	{
		_window.draw(m_currentHighScores[i]);
	}
}

void HighScoreManager::handleInput(sf::Event& _event)
{
	if (_event.type == sf::Event::TextEntered) 
	{
		switch (_event.text.unicode)
		{
		case 8:
			if (m_playerInput.getSize() > 0) 
			{
				m_playerInput.erase(m_playerInput.getSize() - 1, 1);
				m_playerText.setString(m_playerInput);
			}
			break;
		case 13:
			addNewHighScore(m_achievedScore, m_playerInput);
			writeScores();
			m_inputReceiving = false;
			break;
		default:
			m_playerInput += _event.text.unicode;
			m_playerText.setString(m_playerInput);
			break;
		}
	}
}

void HighScoreManager::readScores()
{
	std::string name;
	int score;
	m_file.open("highscore.txt", std::fstream::in);
	while (m_file >> name >> score)
	{
		m_highscoreList.push_back({ name, score });
	}
	m_file.close();
}

void HighScoreManager::writeScores()
{
	std::ofstream clear;
	clear.open("highscore.txt", std::ofstream::out | std::ofstream::trunc);
	clear.close();
	std::sort(m_highscoreList.begin(), m_highscoreList.end(), [](PlayerScore _a, PlayerScore _b) {
		return _a.m_score > _b.m_score;
		});
	m_file.open("highscore.txt", std::fstream::out | std::fstream::app);

	for (int i = 0; i < m_highscoreList.size(); i++)
	{
		m_file << m_highscoreList[i].m_name << " " << m_highscoreList[i].m_score << "\n";
	}

	m_file.close();
}

void HighScoreManager::addNewHighScore(int _score, std::string _name)
{
	for (int i = 0; i < m_highscoreList.size(); i++)
	{
		if (_score > m_highscoreList[i].m_score)
		{
			m_highscoreList.insert(m_highscoreList.begin() + i, { _name, _score });
			break;
		}
	}
}

void HighScoreManager::setScore(int _param)
{
	m_achievedScore = _param;
	m_scoreText.setString(std::to_string(m_achievedScore));
	m_scoreText.setOrigin(m_scoreText.getGlobalBounds().width / 2, m_scoreText.getGlobalBounds().height / 2);
}

void HighScoreManager::updateHighScores()
{
	for (int i = 0; i < (m_highscoreList.size() < 5 ? m_highscoreList.size() : 5); i++)
	{
		m_currentHighScores[i].setFont(m_font);
		m_currentHighScores[i].setString(i + ". " + m_highscoreList[i].m_name + ": " + std::to_string(m_highscoreList[i].m_score));
		m_currentHighScores[i].setPosition(50, i * 30 + 30);
	}
}
