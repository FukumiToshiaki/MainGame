#pragma once
class Player;
class Enemy_Boss;
#include "IBossState.h"
#include "Enemy_Boss.h"

//class BossPattern : public IBossState,public Enemy_Boss
//{
//public:
//	BossPattern(Enemy_Boss* enemy_Boss) :
//		IBossState(enemy_Boss) {};
//
//	//BossPattern() {};
//	~BossPattern();
//
//	bool Start();
//	void Update();
//	int MeleePattern();
//	void Melee() override;
//	int LongPattern();
//	void Long() override;
//	void Render(RenderContext& rc);
//
//private:
//	Enemy_Boss* m_enemy_Boss = nullptr;
//	Player* m_player = nullptr;
//
//	/// <summary>
//	/// ïœêî
//	/// </summary>
//	int m_meleePoint = 0;
//	int m_shootPoint = 0;
//
//};
class BossPattern :public Enemy_Boss
{
public:

	BossPattern() {};
	~BossPattern();

	bool Start();
	void Update();
	void CoolTime();
	int MeleePattern();
	void Melee();
	int LongPattern();
	void Long();


private:
	Enemy_Boss* m_enemy_Boss = nullptr;
	Player* m_player = nullptr;
	
	/// <summary>
	/// bool
	/// </summary>
	bool m_isBifurcation = false;

	/// <summary>
	/// ïœêî
	/// </summary>
	float m_meleeAttackCoolTime = 5.0f;
	float m_shootStandTime = 3.0f;
	float m_shootAttack = 4.0f;
	int m_meleePoint = 0;
	int m_shootPoint = 0;

	/// <summary>
	/// ãﬂãóó£ÇÃéû
	/// </summary>
	int m_meleeAttack = 20;
	int m_defend = 5;
	int m_tailAttack = 15;
	int m_fly = 5;
	int m_shoot = 3;
};

