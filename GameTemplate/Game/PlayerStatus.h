#pragma once
#include <fstream>
#include <sstream>

struct PlayerStatusStruct
{
	float HP;
	float MeleeAttack;
	float Defense;
};

class PlayerStatus
{
public:
	void Init();


	std::vector<PlayerStatusStruct> GetplayerStatusStructs()
	{
		return playerStatusStructs;
	}
	
private:
	std::vector<PlayerStatusStruct> playerStatusStructs;
};

