#pragma once
#include "IPlayer_State.h"
class PlayerState_AttackLong : public IPlayer_State
{
public:
	PlayerState_AttackLong(Player* player) :
		IPlayer_State(player) {};

	void Animation() override;

	void Update() override;

};

