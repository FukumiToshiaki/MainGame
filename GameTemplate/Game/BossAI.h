#pragma once
class Player;
class Enemy_Boss;
#include "IBossState.h"
#include "Enemy_Boss.h"

class BossAI :public Enemy_Boss
{
public:
	struct BossActions 
	{
		int m_melee = 0;
		int m_distance = 0;
		int m_shoot = 0;
		int m_defense = 0;
		int m_tail = 0;
		int m_flyshoot = 0;
		int m_flyattack = 0;
		int m_move = 0;
	};
	BossAI() {};
	~BossAI();

	//スタート関数
	bool Start();
	//アップデート関数
	void Update();
	//クールタイマー関数
	void CoolTime();
	//テーブルの初期化
	void BossTable(const string& state);
	//ボスの行動
	void BossValue(const string& state, int action, double reward, const string& next_state);

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
	//プレイヤーの行動履歴
	int m_player_history[3];
	/// <summary>
	/// 近距離の時
	/// </summary>
	Vector3 m_screamPos = Vector3::Zero;

};

