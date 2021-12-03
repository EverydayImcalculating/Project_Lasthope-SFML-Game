#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_MainMenu::~State_MainMenu() {}

void State_MainMenu::OnCreate() {

	sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();

	m_font.loadFromFile(Utils::GetResourceDirectory() + "media/Fonts/arial.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("MAIN MENU :"));
	m_text.setCharacterSize(50);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	
	m_text.setPosition(windowSize.x / 2, windowSize.y / 6);


	m_buttonSize = sf::Vector2f(600.f, 60.0f);
	m_buttonPos = sf::Vector2f(windowSize.x / 2, windowSize.y / 3);
	m_buttonPadding = 20; // 4px.

	std::string str[5];
	str[0] = "PLAY";
	str[1] = "HOW TO";
	str[2] = "SCOREBOARD";
	str[3] = "CREDITS";
	str[4] = "EXIT";

	for (int i = 0; i < 5; ++i) {
		sf::Vector2f buttonPosition(
			m_buttonPos.x, m_buttonPos.y +
			(i * (m_buttonSize.y + m_buttonPadding)));
		m_rects[i].setSize(m_buttonSize);
		m_rects[i].setFillColor(sf::Color::Red);

		m_rects[i].setOrigin(
			m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
		m_rects[i].setPosition(buttonPosition);

		m_labels[i].setFont(m_font);
		m_labels[i].setString(sf::String(str[i]));
		m_labels[i].setCharacterSize(20);

		sf::FloatRect rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(
			rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);

		m_labels[i].setPosition(buttonPosition);
	}

	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::MainMenu, "Mouse_Left", &State_MainMenu::MouseClick, this);
}

void State_MainMenu::OnDestroy() {
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::MainMenu, "Mouse_Left");
}

void State_MainMenu::Activate() {
	if (m_stateMgr->HasState(StateType::Game)
		&& m_labels[0].getString() != "RESUME")
	{
		m_labels[0].setString(sf::String("RESUME"));
	}
	else {
		m_labels[0].setString(sf::String("PLAY"));
	}

	sf::FloatRect rect = m_labels[0].getLocalBounds();
	m_labels[0].setOrigin(rect.left + rect.width / 2.0f,
		rect.top + rect.height / 2.0f);
}

void State_MainMenu::MouseClick(EventDetails* l_details) {
	SharedContext* context = m_stateMgr->GetContext();
	sf::Vector2i mousePos = l_details->m_mouse;

	float halfX = m_buttonSize.x / 2.0f;
	float halfY = m_buttonSize.y / 2.0f;
	for (int i = 0; i < 5; ++i) {
		if (mousePos.x >= m_rects[i].getPosition().x - halfX &&
			mousePos.x <= m_rects[i].getPosition().x + halfX &&
			mousePos.y >= m_rects[i].getPosition().y - halfY &&
			mousePos.y <= m_rects[i].getPosition().y + halfY)
		{
			if (i == 0) {
				if (m_stateMgr->HasState(StateType::Game))
				{
					m_stateMgr->SwitchTo(StateType::Game);
				} 
				else
				{
					m_stateMgr->SwitchTo(StateType::Name);
				}
				//m_stateMgr->SwitchTo(StateType::Game);
			}
			else if (i == 1) {
				m_stateMgr->SwitchTo(StateType::Howto);
			}
			else if (i == 2) {
				m_stateMgr->SwitchTo(StateType::ScoreBoard);
			}
			else if (i == 3) {
				m_stateMgr->SwitchTo(StateType::Credits);
			}
			else if (i == 4) {
				m_stateMgr->GetContext()->m_wind->Close();
			}
		}
	}
}

void State_MainMenu::Draw() {
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	window->draw(m_text);
	for (int i = 0; i < 5; ++i) {
		window->draw(m_rects[i]);
		window->draw(m_labels[i]);
	}
}

void State_MainMenu::Update(const sf::Time& l_time, sf::Event event) {}
void State_MainMenu::Deactivate() {}