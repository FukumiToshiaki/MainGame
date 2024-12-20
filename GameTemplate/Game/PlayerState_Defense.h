#pragma once
#include "IPlayer_State.h"
class PlayerState_Defense : public IPlayer_State
{
public:
	PlayerState_Defense(Player* player) :
		IPlayer_State(player) {};

	void Animation() override;

	void Update() override;

	//void SetIsDefenseStart(const bool DefenseStart) {
	//	m_isDefenseStart = DefenseStart;
	//}
private:
	bool m_isDefense = false;
	bool m_isDefenseStart = false;
	bool m_isDefenseEnd = false;
};

