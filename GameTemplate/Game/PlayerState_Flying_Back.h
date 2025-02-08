#pragma once
#include "IPlayer_State.h"
class PlayerState_Flying_Back : public IPlayer_State
{
public:
	PlayerState_Flying_Back(Player* player) :
		IPlayer_State(player) {};

	void Animation() override;

	void Update() override;
};

