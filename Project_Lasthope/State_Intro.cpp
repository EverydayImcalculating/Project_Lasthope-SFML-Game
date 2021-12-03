#include "State_Intro.h"
#include "StateManager.h"

State_Intro::State_Intro(StateManager* l_stateManager)
	: BaseState(l_stateManager){}

State_Intro::~State_Intro(){}

void State_Intro::OnCreate(){

	draw = false;
	m_timePassed = 0.0f;
	m_timePassed2 = 0.0f;
	duration = float();
	currentColor = 255;
	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();

	TextureManager* textureMgr = m_stateMgr->GetContext()->m_textureManager;
	textureMgr->RequireResource("Intro");
	m_introSprite.setTexture(*textureMgr->GetResource("Intro"));
	m_introSprite.setOrigin(textureMgr->GetResource("Intro")->getSize().x / 2.0f,
							textureMgr->GetResource("Intro")->getSize().y / 2.0f);

	m_introSprite.setPosition(windowSize.x / 2.0f, 0);

	m_font.loadFromFile(Utils::GetResourceDirectory() + "media/Fonts/arial.ttf");
	m_text.setFont(m_font);
	m_text.setString("Press Spacebar to Continue");
	m_text.setCharacterSize(18);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.1f);

	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::Intro, "Intro_Continue",&State_Intro::Continue,this);
}

void State_Intro::OnDestroy(){
	TextureManager* textureMgr = m_stateMgr->GetContext()->m_textureManager;
	textureMgr->ReleaseResource("Intro");

	EventManager* evMgr = m_stateMgr->
		GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::Intro,"Intro_Continue");
}

void State_Intro::Draw(){
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();

	window->draw(m_introSprite);
	if (m_timePassed >= 5.0f)
	{
		window->draw(m_text);
		draw = true;
	}
}

void State_Intro::Continue(EventDetails* l_details){
	if (m_timePassed >= 5.0f)
	{
		m_stateMgr->SwitchTo(StateType::MainMenu);
		m_stateMgr->Remove(StateType::Intro);
	}
}

void State_Intro::Update(const sf::Time& l_time, sf::Event event)
{

	
	if (m_timePassed < 5.0f) // Less than five seconds.
	{
		m_timePassed += l_time.asSeconds();
		m_introSprite.setPosition(m_introSprite.getPosition().x, m_introSprite.getPosition().y + (45 * l_time.asSeconds()));
	}
	if (draw)
	{
		duration += l_time.asSeconds();
		if (duration > 0.01f) {
			// Restart calculation of the duration
			duration = 0;

			// Loop through the animation colors
			if (currentColor > 0) {
				currentColor -= 3;
			}
			else {
				// Start from first frame if last frame reached
				currentColor = 255;
			}
			m_text.setFillColor(sf::Color(255, 255, 255, currentColor));
		}
	}

	
}
void State_Intro::Activate(){}
void State_Intro::Deactivate(){}