#pragma once
class Player;

class IPlayer_State
{
public:
	IPlayer_State(Player* player) { m_player = player; };
	virtual ~IPlayer_State() {};
	
	virtual void Animation() = 0;

	virtual void Update() = 0;

protected:
	Player* m_player = nullptr;
};

