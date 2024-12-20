#pragma once
#include "IPlayer_State.h"
class PlayerState_Die : public IPlayer_State
{
public:
	PlayerState_Die(Player* player) :
		IPlayer_State(player) {};

	void Animation() override;

	void Update() override;

};


