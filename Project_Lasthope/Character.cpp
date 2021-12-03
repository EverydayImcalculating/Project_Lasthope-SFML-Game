#include "Character.h"
#include "EntityManager.h"
#include "StateManager.h"
#include <cmath>

Character::Character(EntityManager* l_entityMgr)
	:EntityBase(l_entityMgr),
	m_spriteSheet(m_entityManager->GetContext()->m_textureManager),
	m_jumpVelocity(250), m_hitpoints(5), m_AttackAni(0), m_timepassed(0), Percent(100)
{
	m_name = "Character";
}

Character::~Character() { }

void Character::Move(const Direction& l_dir) {
	if (GetState() == EntityState::Dying) { return; }
	m_spriteSheet.SetDirection(l_dir);
	if (l_dir == Direction::Left) { Accelerate(-m_speed.x, 0); }
	else { Accelerate(m_speed.x, 0); }
	if (GetState() == EntityState::Idle) { SetState(EntityState::Walking); }
}

void Character::Jump() {
	if (GetState() == EntityState::Dying || GetState() == EntityState::Jumping /*|| GetState() == EntityState::Hurt*/) { return; }
	SetState(EntityState::Jumping);
	AddVelocity(0, -m_jumpVelocity);
}

void Character::Jetpack()
{
	if (GetState() == EntityState::Dying) { return; }
	m_falling = 0;
	SetState(EntityState::Jetpacking);
	AddVelocity(0, -m_jetpackVelocity);
}

void Character::Attack() {
	if (GetState() == EntityState::Dying || GetState() == EntityState::Jumping ||
		GetState() == EntityState::Hurt || GetState() == EntityState::Attacking || GetState() == EntityState::Attacking1 || 
		GetState() == EntityState::Attacking2)
	{
		return;
	}
	if (m_type == EntityType::Enemy)
	{
		SetState(EntityState::Attacking);
	}
	
	if (m_type == EntityType::Player)
	{
		if (m_attacking == 0)
		{
			SetState(EntityState::Attacking);
			m_attacking = 1;
		}
		else if (m_attacking == 1)
		{
			SetState(EntityState::Attacking1);
			m_attacking = 2;
		}
		else if (m_attacking == 2)
		{
			SetState(EntityState::Attacking2);
			m_attacking = 0;
		}
	}
}

void Character::GetHurt(const int& l_damage) {
	if (GetState() == EntityState::Dying || GetState() == EntityState::Hurt) { return; }
	m_hitpoints = (m_hitpoints - l_damage > 0 ? m_hitpoints - l_damage : 0);
	if (m_hitpoints) { SetState(EntityState::Hurt); }
	else { SetState(EntityState::Dying); }
}

int Character::Gethitpoints()const { return m_hitpoints; }
int Character::GetExp()const { return m_exp; }
int Character::GetLevel()const { return m_level; }

void Character::Load(const std::string& l_path) {
	std::ifstream file;
	file.open(Utils::GetResourceDirectory() + std::string("media/Characters/") + l_path);
	if (!file.is_open()) { std::cout << "! Failed loading the character file: " << l_path << std::endl; return; }
	std::string line;
	while (std::getline(file, line)) {
		if (line[0] == '|') { continue; }
		std::stringstream keystream(line);
		std::string type;
		keystream >> type;
		if (type == "Name") {
			keystream >> m_name;
		}
		else if (type == "Spritesheet") {
			std::string path;
			keystream >> path;
			m_spriteSheet.LoadSheet("media/Spritesheets/" + path);
		}
		else if (type == "Hitpoints") {
			keystream >> m_hitpoints;
			if (m_name == "Player")
			{
				m_maxhitpoints = m_hitpoints;
			}
		}
		else if (type == "Attacking")
		{
			keystream >> m_attacking;
		}
		else if (type == "BoundingBox") {
			sf::Vector2f boundingSize;
			keystream >> boundingSize.x >> boundingSize.y;
			SetSize(boundingSize.x, boundingSize.y);
		}
		else if (type == "DamageBox") {
			keystream >> m_attackAABBoffset.x >> m_attackAABBoffset.y
				>> m_attackAABB.width >> m_attackAABB.height;
		}
		else if (type == "Speed") {
			keystream >> m_speed.x >> m_speed.y;
		}
		else if (type == "JumpVelocity") {
			keystream >> m_jumpVelocity;
		}
		else if (type == "JetpackVelocity")
		{
			keystream >> m_jetpackVelocity;
		}
		else if (type == "MaxVelocity") {
			keystream >> m_maxVelocity.x >> m_maxVelocity.y;
		}
		else {
			std::cout << "! Unknown type in character file: " << type << std::endl;
		}
	}
	file.close();
}

void Character::UpdateAttackAABB() {
	m_attackAABB.left =
		(m_spriteSheet.GetDirection() == Direction::Left ?
			(m_AABB.left - m_attackAABB.width) - m_attackAABBoffset.x
			: (m_AABB.left + m_AABB.width) + m_attackAABBoffset.x);
	m_attackAABB.top = m_AABB.top + m_attackAABBoffset.y;
}

void Character::Animate() {
	EntityState state = GetState();

	if (state == EntityState::Walking && m_spriteSheet.
		GetCurrentAnim()->GetName() != "Walk")
	{
		m_spriteSheet.SetAnimation("Walk", true, true);
	}
	else if (state == EntityState::Jumping && m_spriteSheet.
		GetCurrentAnim()->GetName() != "Jump")
	{
		m_spriteSheet.SetAnimation("Jump", true, false);
	}
	else if (state == EntityState::Attacking && m_spriteSheet.
		GetCurrentAnim()->GetName() != "Attack")
	{
		m_spriteSheet.SetAnimation("Attack", true, false);
	}
	else if (state == EntityState::Attacking1 && m_spriteSheet.
		GetCurrentAnim()->GetName() != "Attack1") {
		m_spriteSheet.SetAnimation("Attack1", true, false);
	}
	else if (state == EntityState::Attacking2 && m_spriteSheet.
		GetCurrentAnim()->GetName() != "Attack2") {
		m_spriteSheet.SetAnimation("Attack2", true, false);
	}
	else if (state == EntityState::Hurt && m_spriteSheet.
		GetCurrentAnim()->GetName() != "Hurt")
	{
		m_spriteSheet.SetAnimation("Hurt", true, false);
	}
	else if (state == EntityState::Dying && m_spriteSheet.
		GetCurrentAnim()->GetName() != "Death")
	{
		m_spriteSheet.SetAnimation("Death", true, false);
	}
	else if (state == EntityState::Idle && m_spriteSheet.
		GetCurrentAnim()->GetName() != "Idle")
	{
		m_spriteSheet.SetAnimation("Idle", true, true);
	}
	else if (state == EntityState::Jetpacking && m_spriteSheet.
		GetCurrentAnim()->GetName() != "Jetpack")
	{
		m_spriteSheet.SetAnimation("Jetpack", true, false);
	}
	else if (state == EntityState::Fall && m_spriteSheet.
		GetCurrentAnim()->GetName() != "Fall")
	{
		m_spriteSheet.SetAnimation("Fall", true, false);
	}
}

void Character::UpdateGUI()
{

	hpPercent = (m_hitpoints * Percent) / m_maxhitpoints;
	/*std::cout << "hitpoints : " << m_hitpoints << std::endl;
	std::cout << "maxhitpoints : " << m_maxhitpoints << std::endl;
	std::cout << "Percent : " << hpPercent << std::endl;*/
	sf::FloatRect hpBounds = m_hpBar.getGlobalBounds();
	hpProgress.setSize({ (hpBounds.width * hpPercent) / Percent , hpBounds.height });
	/*std::cout << (hpBounds.width * hpPercent) / Percent << std::endl;*/

}

void Character::SetTexture()
{
	
	m_thpBar.loadFromFile(Utils::GetResourceDirectory() + "/media/Textures/hpBar.png");
	m_hpBar.setTexture(m_thpBar);
	m_hpBar.setScale(0.28, 0.28);
	m_hpBar.setOrigin(m_hpBar.getGlobalBounds().left, m_hpBar.getGlobalBounds().height / 2.0f);

	hpProgress.setFillColor(sf::Color::Red);
	hpProgress.setSize({ m_hpBar.getGlobalBounds().width, m_hpBar.getGlobalBounds().height });
	hpProgress.setOrigin(m_hpBar.getGlobalBounds().left, m_hpBar.getGlobalBounds().height / 2.0f);

	m_thpBorder.loadFromFile(Utils::GetResourceDirectory() + "/media/Textures/hpBorder.png");
	m_hpBorder.setTexture(m_thpBorder);
	m_hpBorder.setScale(0.28, 0.28);
	m_hpBorder.setOrigin(m_hpBorder.getGlobalBounds().left, m_hpBorder.getGlobalBounds().height / 2.0f);

	/*m_thpProgress.loadFromFile(Utils::GetResourceDirectory() + "/media/Textures/hpProgress.png");
	m_hpProgress.setTexture(m_thpProgress);
	sf::FloatRect hpBounds = m_hpProgress.getGlobalBounds();
	m_hpProgress.setTextureRect(sf::IntRect(hpBounds.left, hpBounds.top, hpBounds.width, hpBounds.height));
	m_hpProgress.setScale(0.28, 0.28);
	m_hpProgress.setOrigin(m_hpProgress.getGlobalBounds().left, m_hpProgress.getGlobalBounds().height / 2.0f);*/

}

void Character::AddExp(int l_exp) { m_exp += l_exp; }
void Character::SetExp(int l_exp) { m_oldexp = l_exp; }

void Character::Update(float l_dT) {

	EntityBase::Update(l_dT);
	EntityBase* player = m_entityManager->Find("Player");
	EntityBase* enemy = m_entityManager->Find("DroidZapper");
	Map* m_gameMap = m_entityManager->GetContext()->m_gameMap;

	sf::FloatRect viewSpace = m_entityManager->GetContext()->m_wind->GetViewSpace();

	if (m_attackAABB.width != 0 && m_attackAABB.height != 0) {
		UpdateAttackAABB();

		// Debug.
		if (m_entityManager->GetContext()->m_debugOverlay.Debug()) {
			sf::RectangleShape* arect = new sf::RectangleShape(sf::Vector2f(m_attackAABB.width, m_attackAABB.height));
			sf::RectangleShape* playerrect = new sf::RectangleShape(sf::Vector2f(m_AABB.width, m_AABB.height));
			arect->setPosition(m_attackAABB.left, m_attackAABB.top);
			arect->setFillColor(sf::Color(255, 0, 0,
				(m_state == EntityState::Attacking || m_state == EntityState::Attacking1 || m_state == EntityState::Attacking2 && m_spriteSheet.GetCurrentAnim()->IsInAction()
					? 200 : 100)));
			playerrect->setPosition(m_AABB.left, m_AABB.top);
			playerrect->setFillColor(sf::Color::Transparent);
			playerrect->setOutlineColor(sf::Color(146, 216, 43));
			playerrect->setOutlineThickness(1.f);
			m_entityManager->GetContext()->m_debugOverlay.Add(playerrect);
			m_entityManager->GetContext()->m_debugOverlay.Add(arect);
		}
		// End debug.
	}
	m_text.setPosition(viewSpace.left + viewSpace.width / 2, viewSpace.top + viewSpace.height / 2);
	m_timepassed += l_dT;
	//std::cout << m_timepassed << std::endl;
	//std::cout << m_spriteSheet.GetCurrentAnim()->GetName() << std::endl;
	if (GetState() != EntityState::Dying && GetState() != EntityState::Attacking && GetState() != EntityState::Hurt && 
		GetState() != EntityState::Attacking1 && GetState() != EntityState::Attacking2) 
	{
		if (abs(m_velocity.y) >= 0.001f && GetState() != EntityState::Jetpacking && GetState() != EntityState::Fall) {
			SetState(EntityState::Jumping);
		}
		else if (abs(m_velocity.y) >= 0.001f && GetState() != EntityState::Jumping && m_id == 0) {
			SetState(EntityState::Jetpacking);
		}
		else if (abs(m_velocity.x) >= 0.1f) {
			SetState(EntityState::Walking);
		}
		else {
			SetState(EntityState::Idle);
		}
	}
	else if (GetState() == EntityState::Attacking || GetState() == EntityState::Attacking1 || GetState() == EntityState::Attacking2 || GetState() == EntityState::Hurt) {
		if (!m_spriteSheet.GetCurrentAnim()->IsPlaying()) {
			SetState(EntityState::Idle);
		}
	}
	else if (GetState() == EntityState::Dying) {
		if (!m_spriteSheet.GetCurrentAnim()->IsPlaying()) {
			m_entityManager->Remove(m_id);
			if (m_id > 0)
			{
				m_gameMap->UpdateScore();
				m_gameMap->AddKilled(1);
			}
		}
	}

	m_hpBar.setPosition(viewSpace.left + viewSpace.width / 16, viewSpace.top + viewSpace.height / 30);
	hpProgress.setPosition(viewSpace.left + viewSpace.width / 16, viewSpace.top + viewSpace.height / 25);
	m_hpBorder.setPosition(viewSpace.left + viewSpace.width / 17, viewSpace.top + viewSpace.height / 34);

	Animate();

	m_spriteSheet.Update(l_dT);
	m_spriteSheet.SetSpritePosition(m_position);
}

void Character::Draw(sf::RenderWindow* l_wind) {
	m_spriteSheet.Draw(l_wind);
	l_wind->draw(m_hpBar);
	l_wind->draw(hpProgress);
	l_wind->draw(m_hpBorder);
}