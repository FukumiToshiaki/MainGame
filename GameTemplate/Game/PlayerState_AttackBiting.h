#pragma once
#include "IPlayer_State.h"
class PlayerState_AttackBiting : public IPlayer_State
{
public:
	PlayerState_AttackBiting(Player* player) :
		IPlayer_State(player) {};

	void Animation() override;

	void Update() override;
};