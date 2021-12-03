#include "State_Credits.h"
#include "StateManager.h"

State_Credits::State_Credits(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_Credits::~State_Credits() {}

void State_Credits::OnCreate()
{
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
	evMgr->AddCallback(StateType::Credits, "Key_Escape", &State_Credits::MainMenu, this);

	m_font.loadFromFile(Utils::GetResourceDirectory() + "media/Fonts/arial.ttf");
	m_text.setFont(m_font);
	m_text.setString("CREDITS");
	m_text.setCharacterSize(50);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	

	m_name.setFont(m_font);
	m_name.setString("Dev : 64010182 Chinnwat Chuabkhwamsuk");
	m_name.setCharacterSize(30);
	sf::FloatRect nameRect = m_name.getLocalBounds();
	m_name.setOrigin(nameRect.left + nameRect.width / 2.0f, nameRect.top + nameRect.height / 2.0f);

	m_exit.setFont(m_font);
	m_exit.setString("Esc to go back");
	m_exit.setCharacterSize(20);
	sf::FloatRect exitRect = m_exit.getLocalBounds();
	m_exit.setOrigin(exitRect.left, exitRect.top);

	m_school.setFont(m_font);
	m_school.setString("Special Thanks : Thanunchai Threepak (Profressor)");
	m_school.setCharacterSize(30);
	sf::FloatRect schoolRect = m_school.getLocalBounds();
	m_school.setOrigin(schoolRect.left + schoolRect.width / 2.0f, schoolRect.top + schoolRect.height / 2.0f);

	m_namePos = sf::Vector2f(150.f, 400.f);

	m_exit.setPosition(5.0f, 20.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 6.0f);
	m_name.setPosition(windowSize.x / 2.0f, windowSize.y / 2.5f);
	m_school.setPosition(windowSize.x / 2.0f, windowSize.y / 1.8f);
}

void State_Credits::OnDestroy()
{
	EventManager* evMgr = m_stateMgr->
		GetContext()->m_eventManager;

	evMgr->RemoveCallback(StateType::Credits, "Key_Escape");

}

void State_Credits::Activate() {}
void State_Credits::Deactivate() {}

void State_Credits::Update(const sf::Time& l_time, sf::Event event)
{

}
void State_Credits::Draw()
{
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	window->draw(m_text);
	window->draw(m_name);
	window->draw(m_school);
	window->draw(m_exit);
}

void State_Credits::MouseClick(EventDetails* l_details) {}

void State_Credits::MainMenu(EventDetails* l_details) {
	m_stateMgr->SwitchTo(StateType::MainMenu);
}