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
//	/// 変数
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
	void DistancePattern();
	void AttackModeLast();
	void DefenseModeLast();
	void Long();

	int BossPatternMode();
	void SuperDefenseMode();
	void DefenseMode();
	void NormalMode();
	void AttackMode();
	void SuperAttackMode();

private:
	Enemy_Boss* m_enemy_Boss = nullptr;
	Player* m_player = nullptr;
	
	/// <summary>
	/// bool
	/// </summary>
	bool m_isBifurcation = false;
	bool m_istest = false;
	/// <summary>
	/// 変数
	/// </summary>
	float m_coolTime = 5.0f;
	//float m_coolTimeLastMode = 3.0f;
	float m_shootAttack = 4.0f;
	int m_pattern = 0;
	int m_shootPoint = 0;

	/// <summary>
	/// 近距離の時
	/// </summary>
	int m_meleeAttack = 20;
	int m_defend = 5;
	int m_tailAttack = 15;
	int m_fly = 5;
	int m_shoot = 3;
};

