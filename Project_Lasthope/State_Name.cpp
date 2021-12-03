#include "State_Name.h"
#include "StateManager.h"

State_Name::State_Name(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_Name::~State_Name() {}

void State_Name::OnCreate()
{
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	Map* m_gameMap = m_stateMgr->GetContext()->m_gameMap;

	SetTransparent(true);

	sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();

	evMgr->AddCallback(StateType::Name, "Key_Escape", &State_Name::MainMenu, this);
	evMgr->AddCallback(StateType::Name, "Text_Entered", &State_Name::HandleTextEntered, this);
	evMgr->AddCallback(StateType::Name, "Enter_Name", &State_Name::GointoGame, this);

	m_font.loadFromFile(Utils::GetResourceDirectory() + "media/Fonts/arial.ttf");
	m_text.setFont(m_font);
	m_text.setString("ENTER YOUR NAME : ");
	m_text.setCharacterSize(50);
	m_text.setStyle(sf::Text::Bold);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	m_text.setPosition(windowSize.x / 2, windowSize.y / 5);

	m_name.setFont(m_font);
	m_name.setCharacterSize(40);
	m_name.setString(" ");
	sf::FloatRect nameRect = m_name.getLocalBounds();
	m_name.setOrigin(nameRect.left, nameRect.height / 2.0f);
	sf::Vector2f textPos = m_text.getPosition();
	m_name.setPosition(windowSize.x / 2.3f, textPos.y + textRect.height / 2.0f + 80.0f);

	m_togo.setFont(m_font);
	m_togo.setCharacterSize(30);
	m_togo.setString("Press Enter to Continue");
	sf::FloatRect togoRect = m_togo.getLocalBounds();
	m_togo.setOrigin(togoRect.left + togoRect.width / 2.0f, togoRect.top + togoRect.height / 2.0f);
	m_togo.setPosition(500.f, 500.f);

	m_exit.setFont(m_font);
	m_exit.setString("Esc to go back");
	m_exit.setCharacterSize(20);
	sf::FloatRect exitRect = m_exit.getLocalBounds();
	m_exit.setOrigin(exitRect.left, exitRect.top);
	
	m_rect.setSize(sf::Vector2f(windowSize));
	m_rect.setPosition(0, 0);
	m_rect.setFillColor(sf::Color(0, 0, 0, 230));
	m_exit.setPosition(5.0f, 20.0f);

}

void State_Name::OnDestroy()
{
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;

	evMgr->RemoveCallback(StateType::Name, "Key_Escape");
	evMgr->RemoveCallback(StateType::Name, "Text_Entered");
	evMgr->RemoveCallback(StateType::Name, "Enter_Name");

}

void State_Name::Activate() 
{
	Map* m_gameMap = m_stateMgr->GetContext()->m_gameMap;
	m_gameMap = new Map(m_stateMgr->GetContext(), this);

	name = "";
	m_name.setString("");
}

void State_Name::Deactivate() {}

void State_Name::Update(const sf::Time& l_time, sf::Event event)
{

}

void State_Name::Draw()
{
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	window->draw(m_rect);
	window->draw(m_text);
	window->draw(m_name);
	window->draw(m_togo);
	window->draw(m_exit);
}

void State_Name::MouseClick(EventDetails* l_details) {}

void State_Name::MainMenu(EventDetails* l_details) {
	m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Name::HandleTextEntered(EventDetails* l_details)
{
	Map* m_gameMap = m_stateMgr->GetContext()->m_gameMap;

	if (l_details) {
		if (l_details->m_textEntered == 8 && name.size() > 0) name.erase(name.size() - 1);
		else if (l_details->m_textEntered < 128 && name.size() < 8 && l_details->m_textEntered != 8) name += static_cast<char>(l_details->m_textEntered);
		m_name.setString(name);
		//std::cout << static_cast<char>(l_details->m_textEntered) << std::endl;
	}
	else if (name.size() < 8) {
		name += "_";
		m_name.setString(name);
		name.erase(name.size() - 1);
	}
}

void State_Name::GointoGame(EventDetails* l_details)
{
	m_stateMgr->SetName(name);
	//std::cout << m_stateMgr->GetName() << std::endl;
	m_stateMgr->SwitchTo(StateType::Game);
}

const std::string& State_Name::Getname()
{
	return name;
}