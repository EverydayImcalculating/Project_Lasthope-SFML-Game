#include "State_Howto.h"
#include "StateManager.h"

State_Howto::State_Howto(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_Howto::~State_Howto() {}

void State_Howto::OnCreate()
{
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();

	evMgr->AddCallback(StateType::Howto, "Key_Escape", &State_Howto::MainMenu, this);

	m_font.loadFromFile(Utils::GetResourceDirectory() + "media/Fonts/arial.ttf");
	m_exit.setFont(m_font);
	m_exit.setString("Esc to go back");
	m_exit.setCharacterSize(20);
	sf::FloatRect exitRect = m_exit.getLocalBounds();
	m_exit.setOrigin(exitRect.left, exitRect.top);

	m_texture.loadFromFile(Utils::GetResourceDirectory() + "media/Textures/Instruction.png");
	m_sprite.setTexture(m_texture);
	sf::FloatRect textureRect = m_sprite.getGlobalBounds();
	m_sprite.setOrigin(textureRect.left,textureRect.top);
	m_sprite.setPosition(0, 0);
	m_exit.setPosition(5.0f, 20.0f);
}

void State_Howto::OnDestroy()
{
	EventManager* evMgr = m_stateMgr->
		GetContext()->m_eventManager;

	evMgr->RemoveCallback(StateType::Howto, "Key_Escape");

}

void State_Howto::Activate()
{
	
}
void State_Howto::Deactivate() {}

void State_Howto::Update(const sf::Time& l_time, sf::Event event)
{

}

void State_Howto::Draw()
{
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	window->draw(m_sprite);
	window->draw(m_exit);

}

void State_Howto::MouseClick(EventDetails* l_details)
{
	SharedContext* context = m_stateMgr->GetContext();
	sf::Vector2i mousePos = l_details->m_mouse;

}

void State_Howto::MainMenu(EventDetails* l_details) {
	m_stateMgr->SwitchTo(StateType::MainMenu);
}