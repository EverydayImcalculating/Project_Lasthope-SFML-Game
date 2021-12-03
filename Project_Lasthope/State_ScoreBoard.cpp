#include "State_ScoreBoard.h"
#include "StateManager.h"

State_ScoreBoard::State_ScoreBoard(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_ScoreBoard::~State_ScoreBoard() {}

void State_ScoreBoard::OnCreate()
{
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
	evMgr->AddCallback(StateType::ScoreBoard, "Key_Escape", &State_ScoreBoard::MainMenu, this);

	m_font.loadFromFile(Utils::GetResourceDirectory() + "media/Fonts/arial.ttf");
	m_text.setFont(m_font);
	m_text.setString("SCORE BOARD");
	m_text.setCharacterSize(50);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);


	m_scoretext.setFont(m_font);
	m_scoretext.setString("SCORE");
	m_scoretext.setCharacterSize(30);
	sf::FloatRect scoreRect = m_scoretext.getLocalBounds();
	m_scoretext.setOrigin(scoreRect.left + scoreRect.width / 2.0f,
		scoreRect.top + scoreRect.height / 2.0f);


	m_exit.setFont(m_font);
	m_exit.setString("Esc to go back");
	m_exit.setCharacterSize(20);
	sf::FloatRect exitRect = m_exit.getLocalBounds();
	m_exit.setOrigin(exitRect.left ,exitRect.top );

	m_nametext.setFont(m_font);
	m_nametext.setString("NAME");
	m_nametext.setCharacterSize(30);;
	sf::FloatRect nameRect = m_scoretext.getLocalBounds();
	m_nametext.setOrigin(nameRect.left + nameRect.width / 2.0f,
		nameRect.top + nameRect.height / 2.0f);

	m_scorePos = sf::Vector2f(80.0f, 200.f);
	m_NamePos = sf::Vector2f(615.f, 200.f);
	m_textPadding = 50;

	m_exit.setPosition(5.0f, 20.0f);
	m_text.setPosition(windowSize.x / 2, windowSize.y / 8);
	m_scoretext.setPosition(windowSize.x / 8, windowSize.y / 4);
	m_nametext.setPosition(windowSize.x - windowSize.x / 6, windowSize.y / 4);
}

void State_ScoreBoard::OnDestroy()
{
	EventManager* evMgr = m_stateMgr->
		GetContext()->m_eventManager;

	evMgr->RemoveCallback(StateType::ScoreBoard, "Key_Escape");

}

void State_ScoreBoard::Activate()
{
	m_score.readFile();

	for (int i = 0; i < 5; ++i)
	{
		sf::Vector2f TextPosition(
			m_scorePos.x, m_scorePos.y + (i * m_textPadding));
		sf::Vector2f NamePosition(
			m_NamePos.x, m_NamePos.y + (i * m_textPadding));

		m_scoreName[i].setFont(m_font);
		m_scoreName[i].setCharacterSize(20);
		m_scoreName[i].setString(m_score.getName()[i].second);
		m_scoreName[i].setPosition(NamePosition);

		m_scorelabels[i].setFont(m_font);
		m_scorelabels[i].setCharacterSize(20);
		m_scorelabels[i].setString(std::to_string(m_score.getName()[i].first));
		m_scorelabels[i].setPosition(TextPosition);
	}
	m_score.clearScore();
}
void State_ScoreBoard::Deactivate() {}

void State_ScoreBoard::Update(const sf::Time& l_time, sf::Event event) { }
void State_ScoreBoard::Draw()
{
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	window->draw(m_text);
	window->draw(m_scoretext);
	window->draw(m_nametext);
	window->draw(m_exit);

	for (int i = 0; i < 5; ++i) {
		window->draw(m_scorelabels[i]);
		window->draw(m_scoreName[i]);
	}
}

void State_ScoreBoard::MouseClick(EventDetails* l_details) {}

void State_ScoreBoard::MainMenu(EventDetails* l_details) {
	m_stateMgr->SwitchTo(StateType::MainMenu);
}