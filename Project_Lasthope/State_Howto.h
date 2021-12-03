#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Howto : public BaseState {
public:
	State_Howto(StateManager* l_stateManager);
	~State_Howto();

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

	unsigned int m_buttonPadding;;
	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};


