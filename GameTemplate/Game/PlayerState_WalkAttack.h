#pragma once
#include "IPlayer_State.h"
class PlayerState_WalkAttack : public IPlayer_State
{
public:
	PlayerState_WalkAttack(Player* player) :
		IPlayer_State(player) {};

	void Animation() override;

	void Update() override;

};

