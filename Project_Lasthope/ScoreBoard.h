#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "Utilities.h"

class ScoreBoard
{
public:
	ScoreBoard();
	static bool sortDes(const std::pair<int, std::string>& a,
		const std::pair<int, std::string>& b);
	inline const std::vector<std::pair<int, std::string>> getName() { return scorePair; }
	void clearScore();
	void readFile();
	void writeFile(std::string playerName, int playerScore);

private:
	std::FILE* fp;
	sf::RenderWindow* m_window;
	sf::View m_view;
	sf::Font m_font;

	std::string name[6];

	char temp[255];
	int score[6];
	std::vector<std::pair<int, std::string>> scorePair;
};