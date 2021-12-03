#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "ScoreBoard.h"

class State_ScoreBoard : public BaseState {
public:
	State_ScoreBoard(StateManager* l_stateManager);
	~State_ScoreBoard();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time, sf::Event event);
	void Draw();

	void MainMenu(EventDetails* l_details);

	void MouseClick(EventDetails* l_details);
private:
	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_exit;
	ScoreBoard m_score;

	sf::Text m_scoretext;
	sf::Text m_nametext;

	sf::Vector2f m_scorePos;
	sf::Vector2f m_NamePos;
	unsigned int m_textPadding;

	sf::Text m_scorelabels[5];
	sf::Text m_scoreName[5];
};



