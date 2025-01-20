#pragma once
#include "IPlayer_State.h"

class PlayerState_Arching : public IPlayer_State
{
public:
	PlayerState_Arching(Player* player) :
		IPlayer_State(player) {};

	void Animation() override;

	void Update() override;
};

