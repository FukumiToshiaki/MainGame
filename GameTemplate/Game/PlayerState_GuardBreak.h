#pragma once
#include "IPlayer_State.h"
class PlayerState_GuardBreak : public IPlayer_State
{
public:
	PlayerState_GuardBreak(Player* player) :
		IPlayer_State(player) {};
	void Animation() override;

	void Update() override;

};

