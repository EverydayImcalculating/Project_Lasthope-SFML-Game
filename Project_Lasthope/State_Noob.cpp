#include "State_Noob.h"
#include "StateManager.h"

State_Noob::State_Noob(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_Noob::~State_Noob() {}

void State_Noob::OnCreate() {

	m_elapsed = 0;
	m_font.loadFromFile(Utils::GetResourceDirectory() + "media/Fonts/arial.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(25);
	m_text.setString("Noob!");
	m_text.setFillColor(sf::Color::White);
	m_text.setOrigin(m_text.getLocalBounds().width / 2,
		m_text.getLocalBounds().height / 2);
	m_text.setPosition(400, 300);

	m_stateMgr->Remove(StateType::Game);
}

void State_Noob::OnDestroy() {}

void State_Noob::Activate()
{

	Map* m_gameMap = m_stateMgr->GetContext()->m_gameMap;
	std::cout << "NAME : " << m_stateMgr->GetName() << std::endl;
	int playerScore = m_gameMap->GetScore();
	std::cout << "Score : " << playerScore << std::endl;
	m_scoreMgr.writeFile(m_stateMgr->GetName(), playerScore);
	m_scoreMgr.clearScore();

}

void State_Noob::Deactivate() {}

void State_Noob::Update(const sf::Time& l_time, sf::Event event) {
	m_elapsed += l_time.asSeconds();
	if (m_elapsed >= 5.0f) {
		m_stateMgr->Remove(StateType::Noob);
		m_stateMgr->SwitchTo(StateType::MainMenu);
	}
}

void State_Noob::Draw() {
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	window->draw(m_text);
}
