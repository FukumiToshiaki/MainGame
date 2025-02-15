#pragma once
class Player;
class Enemy_Boss;
#include "IBossState.h"
#include "Enemy_Boss.h"

class BossPattern :public Enemy_Boss
{
public:

	BossPattern() {};
	~BossPattern();

	//スタート関数
	bool Start();
	//アップデート関数
	void Update();
	//クールタイマー関数
	void CoolTime();
	//行動数値決めの関数
	void DistancePattern();
	//最後の攻撃モード関数
	void AttackModeLast();
	//最後の防御モード関数
	void DefenseModeLast();
	//パターン決めの関数
	void BossPatternMode();
	//必殺技
	void Scream(int screamcount, float screamdistance);
	//ボスのモード関数
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
	//近距離か遠距離か判定するbool
	bool m_isBifurcation = false;
	//クールタイムをスタートさせるか判定するbool
	bool m_iscoolTimeStart = false;
	/// <summary>
	/// 変数
	/// </summary>
	//攻撃のクールタイム
	float m_coolTime = 5.0f;
	//ボスのパターン数値
	int m_pattern = 0;
	/// <summary>
	/// 近距離の時
	/// </summary>
	Vector3 m_screamPos = Vector3::Zero;

	//int m_meleeAttack = 20;
	//int m_defend = 5;
	//int m_tailAttack = 15;
	//int m_fly = 5;
	//int m_shoot = 3;
};

