#pragma once
#include <fstream>
#include <vector>
#include <algorithm>
#include "SFML/Graphics.hpp"
#include "config.h"
#include "InputManager.h"

class HighScoreManager
{
public:
	HighScoreManager();
	~HighScoreManager();

	struct PlayerScore {
		std::string m_name;
		int m_score;
	};
	int Update();
	void Draw(sf::RenderWindow& _window);
	void DrawHighScores(sf::RenderWindow& _window);
	void handleInput(sf::Event& _event);
	void readScores();
	void writeScores();
	void addNewHighScore(int _score, std::string _name);
	void setScore(int _param);
	void updateHighScores();

private:
	std::fstream m_file;
	std::vector<PlayerScore> m_highscoreList;

	int m_achievedScore;
	sf::Font m_font;
	sf::String m_playerInput;
	sf::Text m_playerText, m_inputCaption, m_scoreText, m_scoreCaption;
	bool m_inputReceiving;

	std::vector<sf::Text> m_currentHighScores;
	sf::Text m_highScoreCaption;
};

