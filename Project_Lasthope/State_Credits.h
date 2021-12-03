#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Credits : public BaseState {
public:
	State_Credits(StateManager* l_stateManager);
	~State_Credits();

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
	sf::Text m_school;
	sf::Text m_exit;
	sf::Vector2f m_creditPos;

	sf::Text m_name;
	sf::Vector2f m_namePos;

	unsigned int m_textPadding;
};



