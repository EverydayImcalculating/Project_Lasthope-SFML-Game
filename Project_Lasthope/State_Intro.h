#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Intro : public BaseState{
public:
	State_Intro(StateManager* l_stateManager);
	~State_Intro();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time, sf::Event event);
	void Draw();

	void Continue(EventDetails* l_details);
private:
	sf::Sprite m_introSprite;
	sf::Font m_font;
	sf::Text m_text;
	bool draw;
	int currentColor;

	float m_timePassed;
	float m_timePassed2;
	float duration;
};