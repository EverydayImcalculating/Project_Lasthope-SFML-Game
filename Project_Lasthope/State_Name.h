#pragma once
#include "BaseState.h"
#include "State_GameOver.h"
#include "EventManager.h"

class State_Name : public BaseState {
public:
	State_Name(StateManager* l_stateManager);
	~State_Name();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time, sf::Event event);
	void Draw();

	void MainMenu(EventDetails* l_details);

	void HandleTextEntered(EventDetails* l_details);
	void MouseClick(EventDetails* l_details);
	void GointoGame(EventDetails* l_details);

	const std::string& Getname();

private:
	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_name;
	sf::Text m_togo;
	sf::Text m_exit;
	std::string name;
	sf::RectangleShape m_rect;
	float m_timepassed;

	sf::Event m_event;
};


