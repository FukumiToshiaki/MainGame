#pragma once
#include "IBossState.h"

class Player;
class BossState_Biting :public IBossState
{
public:
	BossState_Biting(Enemy_Boss* enemy_Boss) :
		IBossState(enemy_Boss) {};

	struct MelleAttack
	{
		Vector3 m_pos;
		float m_coolTime;
		bool m_melee = false;
		Enemy_Boss* m_meleeBoss = nullptr;
	};

	void Animation() override;

	void Update() override;

	//Šš‚İ‚Â‚«UŒ‚‚Ì‚ÌƒvƒŒƒCƒ„[‚Æ‚Ì‹——£Š´

private:
	Player* m_player = nullptr;
	Vector3 m_distance;
};
