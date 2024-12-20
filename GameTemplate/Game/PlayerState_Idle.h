#pragma once
#include "IPlayer_State.h"
class PlayerState_Idle : public IPlayer_State
{
public:
	PlayerState_Idle(Player* player) :
	IPlayer_State(player) {};

	void Animation() override;

	void Update() override;
};

