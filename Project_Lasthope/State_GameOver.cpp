#include "State_GameOver.h"
#include "StateManager.h"

State_GameOver::State_GameOver(StateManager* l_stateManager)
	: BaseState(l_stateManager){}

State_GameOver::~State_GameOver(){}

void State_GameOver::OnCreate(){

	m_elapsed = 0;
	m_font.loadFromFile(Utils::GetResourceDirectory() + "media/Fonts/arial.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(25);
	m_text.setString("Well play! You did your best!");
	m_text.setFillColor(sf::Color::White);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, 
		m_text.getLocalBounds().height / 2);
	m_text.setPosition(400, 300);

	m_stateMgr->Remove(StateType::Game);
}

void State_GameOver::OnDestroy() {}

void State_GameOver::Activate()
{
	/*Map* m_gameMap = m_stateMgr->GetContext()->m_gameMap;
	std::string playerName = m_gameMap->Getname();
	std::cout << "Name : " << playerName << std::endl;
	int playerScore = m_gameMap->GetScore();

	m_score.writeFile(playerName, playerScore);
	m_score.clearScore();*/

	Map* m_gameMap = m_stateMgr->GetContext()->m_gameMap;
	std::cout << "NAME : " << m_stateMgr->GetName() << std::endl;
	int playerScore = m_gameMap->GetScore();
	std::cout << "Score : " << playerScore << std::endl;
	m_scoreMgr.writeFile(m_stateMgr->GetName(), playerScore);
	m_scoreMgr.clearScore();

}

void State_GameOver::Deactivate(){}

void State_GameOver::Update(const sf::Time& l_time, sf::Event event){
	m_elapsed += l_time.asSeconds();
	if(m_elapsed >= 5.0f){
		m_stateMgr->Remove(StateType::GameOver);
		m_stateMgr->SwitchTo(StateType::MainMenu);
	}
}

void State_GameOver::Draw(){
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	window->draw(m_text);
}
