#pragma once
#include "BaseState.h"
#include "ScoreBoard.h"
#include <SFML/Graphics.hpp>

class State_Noob : public BaseState {
public:
	State_Noob(StateManager* l_stateManager);
	~State_Noob();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time, sf::Event event);
	void Draw();


private:
	sf::Font m_font;
	sf::Text m_text;
	float m_elapsed;

	ScoreBoard m_score;
};


