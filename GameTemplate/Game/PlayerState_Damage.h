#pragma once
#include "IPlayer_State.h"
class PlayerState_Damage : public IPlayer_State
{
public:
	PlayerState_Damage(Player* player) :
		IPlayer_State(player) {};

	void Animation() override;

	void Update() override;
};

