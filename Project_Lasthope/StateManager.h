#pragma once
#include <vector>
#include <unordered_map>
#include "State_Intro.h"
#include "State_MainMenu.h"
#include "State_Game.h"
#include "State_Paused.h"
#include "State_GameOver.h"
#include "State_ScoreBoard.h"
#include "State_Credits.h"
#include "State_Howto.h"
#include "State_Name.h"
#include "State_Noob.h"
#include "SharedContext.h"

enum class StateType { Intro = 1, MainMenu, Game, Paused, GameOver, Credits, ScoreBoard, Name, Howto, Noob};

// State container.
using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
// Type container.
using TypeContainer = std::vector<StateType>;
// State factory.
using StateFactory = std::unordered_map<StateType, std::function<BaseState* (void)>>;

class StateManager {
public:
	StateManager(SharedContext* l_shared);
	~StateManager();

	void Update(const sf::Time& l_time, sf::Event event);
	void Draw();

	void ProcessRequests();

	SharedContext* GetContext();
	bool HasState(const StateType& l_type);

	void SwitchTo(const StateType& l_type);
	void Remove(const StateType& l_type);
	void SetName(std::string l_name);
	std::string GetName();
private:
	// Methods.
	void CreateState(const StateType& l_type);
	void RemoveState(const StateType& l_type);

	template<class T>
	void RegisterState(const StateType& l_type) {
		m_stateFactory[l_type] = [this]() -> BaseState*
		{
			return new T(this);
		};
	}

	// Members.
	SharedContext* m_shared;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;

	std::string receivedName;
};