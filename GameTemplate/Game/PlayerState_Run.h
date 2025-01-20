#pragma once
#include "IPlayer_State.h"
class PlayerState_Run : public IPlayer_State
{
public:
	PlayerState_Run(Player* player) :
		IPlayer_State(player) {};

	void Animation() override;

	void Update() override;

private:

};


