#include "Enemy.h"
#include "SharedContext.h"

Enemy::Enemy(EntityManager* l_entityMgr)
	:Character(l_entityMgr), m_hasDestination(false), m_elapsed(0.f){ m_type = EntityType::Enemy; }

Enemy::~Enemy(){}

void Enemy::OnEntityCollision(EntityBase* l_collider, bool l_attack)
{
	if (m_state == EntityState::Dying){ return; }
	if (l_attack){ return; }
	if (l_collider->GetType() != EntityType::Player){ return; }
	Character* player = (Character*)l_collider;
	//SetState(EntityState::Attacking);
	player->GetHurt(1); 
	if(m_position.x > player->GetPosition().x){
		player->AddVelocity(-m_speed.x,0);
		m_spriteSheet.SetDirection(Direction::Left);
	} else {
		player->AddVelocity(m_speed.x,0);
		m_spriteSheet.SetDirection(Direction::Right);
	}
}

void Enemy::Update(float l_dT){
	Character::Update(l_dT);

	EntityBase* player = m_entityManager->Find("Player");
	Character* playerChar = (Character*)player;
	const auto& playerpos = player->GetPosition();
	const auto& playerAABB = player->GetAABB();
	if (m_attackAABB.intersects(playerAABB))
	{
		m_elapsed += l_dT;
		if (m_elapsed >= 0.4f && m_state != EntityState::Dying )
		{
			//std::cout << m_position.x << " " << playerpos.x << std::endl;
			if (m_position.x > playerpos.x) {
				m_spriteSheet.SetDirection(Direction::Left);
				Attack();
				player->AddVelocity(-64, 0);
				m_spriteSheet.SetDirection(Direction::Left);
			}
			else if (m_position.x < playerpos.x) {
				m_spriteSheet.SetDirection(Direction::Right);
				Attack();
				player->AddVelocity(64, 0);
				m_spriteSheet.SetDirection(Direction::Right);
			}
			playerChar->GetHurt(2);
			playerChar->UpdateGUI();
			
			m_elapsed = 0.f;
			//std::cout << m_elapsed << std::endl;
		}
	}

	/*if (m_hasDestination){
		if (abs(m_destination.x - m_position.x) < 16){ m_hasDestination = false; return; }
		if (m_destination.x - m_position.x > 0){ Move(Direction::Right); } else { Move(Direction::Left); }
		if (m_collidingOnX){ m_hasDestination = false; }
		return;
	}
	int random = rand() % 1000 + 1;
	if (random != 1000){ return; }
	int newX = rand() % 65 + 0;
	if (rand() % 2){ newX = -newX; }
	m_destination.x = m_position.x + newX;
	if (m_destination.x < 0){ m_destination.x = 0; }
	m_hasDestination = true;*/

	if (playerpos.x - m_position.x > 0 && m_state != EntityState::Attacking)
	{ 
		if (m_collidingOnX) { return; }
		Move(Direction::Right);
	}
	else if (m_state != EntityState::Attacking)
	{
		if (m_collidingOnX) { return; }
		Move(Direction::Left);
	}
	if (playerpos.y - m_position.y < 0 && m_state != EntityState::Attacking)
	{
		Jump();
	}

}