#pragma once
#include "EntityBase.h"
#include "SpriteSheet.h"

class Character : public EntityBase{
friend class EntityManager;
public:
	Character(EntityManager* l_entityMgr);
	virtual ~Character();

	void Move(const Direction& l_dir);

	void Jump();
	void Jetpack();
	void Attack();
	void GetHurt(const int& l_damage);
	void UpdateGUI();
	void SetTexture();

	void AddExp(int l_exp);
	void SetExp(int l_exp);
	int Gethitpoints()const;
	int GetExp()const;
	int GetLevel()const;

	void Load(const std::string& l_path);

	virtual void OnEntityCollision(
		EntityBase* l_collider, bool l_attack) = 0;

	virtual void Update(float l_dT);
	void Draw(sf::RenderWindow* l_wind);

protected:
	void UpdateAttackAABB();
	void Animate();
	SpriteSheet m_spriteSheet;
	float m_jumpVelocity;
	float m_jetpackVelocity;
	int m_hitpoints;
	int m_maxhitpoints;
	int m_AttackAni;
	float m_timepassed;
	bool m_falling;
	int m_oldexp;
	int m_exp;
	int m_maxexp;
	int m_level;
	int hpPercent;
	int Percent;
	int m_killed;
	int m_attacking;
	bool Set;

	sf::Text m_text;
	sf::Font m_font;

	sf::Texture m_thpBar;
	sf::Texture m_thpProgress;
	sf::Texture m_thpBorder;

	sf::RectangleShape hpProgress;

	sf::Sprite m_hpBar;
	sf::Sprite m_hpProgress;
	sf::Sprite m_hpBorder;

	sf::FloatRect m_attackAABB;
	sf::Vector2f m_attackAABBoffset;
};