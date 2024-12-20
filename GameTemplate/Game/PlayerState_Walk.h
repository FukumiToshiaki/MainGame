#pragma once
#include "IPlayer_State.h"
class PlayerState_Walk : public IPlayer_State
{
public:
	PlayerState_Walk(Player* player) :
		IPlayer_State(player) {};

	void Animation() override;

	void Update() override;
};

