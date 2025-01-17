#pragma once
class Player;
class Game;
class IBossState;
//class BossPattern;
#include "EnemyBase.h"

class Enemy_Boss : public EnemyBase
{
public:
	Enemy_Boss() {};
	~Enemy_Boss() {};
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void FlyAttackMove();
	// スケルトンを初期化
	void InitSkeleton();
	// アニメーションを初期化。
	void InitAnimation();
	//回転の初期化
	void Rotation();
	//近距離攻撃の噛みつき
	void Biting();
	//遠距離攻撃の地上からのブレス
	void Shoot();
	//大技後の休憩モーション
	void Rest();
	//コリジョンの当たり判定
	void Hit();
	//噛みつき攻撃のコリジョン
	void MeleeAttackCollision();
	//尻尾の薙ぎ払い
	void TailAttack();
	//尻尾の薙ぎ払いのコリジョン
	void TailAttackCollision();
	//空中突進
	void FlyAttack();
	//空中突進の当たり判定
	void FlyAttackCollision();
	//ガードの判定
	void Defence();
	//ガードのコリジョン
	void DefenceCollision();
	// アニメーションイベント用の関数。
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	//距離をとる関数
	void FlyDistance();
	
	// アニメーションクリップの番号を表す列挙型。
	enum EnAnimationClip {
		enState_Idle_Animation,
		enState_Attack_Biting_Animation,
		enState_Attack_Shoot_Animation,
		enState_Attack_Tail_Animation,
		enState_Attack_Scream_Animation,
		enState_Attack_FlyShoot_Animation,
		enState_Attack_Fly_Animation,
		enState_Damage_Animation,
		enState_Defence_Animation,
		enState_Rest_Animation,
		enState_Move_Animation,
		enState_Die_Animation,
		enState_Takeoff_Animation,
		enState_Fly_Animation,
		enState_Landing_Animation,
		enAnimClip_Num,		// 2 :アニメーションクリップの数。アニメーションを追加するならこの上に作る
	};
	enum EnState {
		enState_Idle,
		enState_Attack_Biting,
		enState_Attack_Shoot,
		enState_Attack_Tail,
		enState_Attack_Scream,
		enState_Attack_FlyShoot,
		enState_Attack_Fly,
		enState_Damage,
		enState_Defence,
		enState_Rest,
		enState_Move,
		enState_Die,
		enState_Takeoff,
		enState_Fly,
		enState_Landing,
	};
	EnState m_state = enState_Idle;
	//ステートの管理
	void ChangeState(EnState changeState, int integerArgument0 = 0);

	const bool& GetIsPlayingAnimation()const
	{
		return m_modelRender.IsPlayingAnimation();
	}

	ModelRender& GetModelRender()
	{
		return m_modelRender;
	}

	

	bool GetisClear()
	{
		return m_isClear;
	}
	void SetisClear(bool Clear)
	{
		m_isClear = Clear;
	}

	

	void SetisUnderMelee(bool UnderMelee)
	{
		m_isUnderAttackMelee = UnderMelee;
	}

	void SetisUnderTail(bool UnderTail)
	{
		m_isUnderTail = UnderTail;
	}

	void SetisUnderFlyAttack(bool UnderFlyAttack)
	{
		m_isUnderFlyAttack = UnderFlyAttack;
	}

	int GetHP()
	{
		return m_testHP;
	}

	void SetisUnderPattern(bool Pattern)
	{
		m_isUnderPattern = Pattern;
	}

	void SetMoveSpeed(Vector3 movespeed)
	{
		m_moveSpeed = movespeed;
	}

	Vector3 GetDiff()
	{
		return m_diff;
	}

	void SetidUnderDefencePattern(bool UnderDefence)
	{
		m_isUnderDefence = UnderDefence;
	}
	//float GetFlyTime()
	//{
	//	return m_testFlyTime;
	//}
	//void SetDiff(Vector3 diff)
	//{
	//	m_diff = diff;
	//}
protected:
	/// <summary>
	/// ベクター
	/// </summary>
	Vector3 m_distance;
	Vector3 m_diff;
	Vector3 m_moveSpeed;	//移動速度
	Vector3						m_scale = Vector3::One;			//大きさ。
	Vector3		m_forward = Vector3::AxisZ;					//エネミーの正面ベクトル。
	Vector3 m_collisionPos;
	Vector3 m_flyPos;
	/// <summary>
	/// クラス
	/// </summary>
	//BossPattern* m_bossPattern = nullptr;
	/// <summary>
	/// 変数
	/// </summary>
	int m_attack_Rand = 0;
	int m_attack_Count = -1;
	int m_testHP = 10;
	int m_flyBoneId = 0;
	float m_angle = 0.0f;
	float m_radius = 2.0f;
	float m_hitCoolTime = 2.0f;
	//float m_testFlyTime = 3.0f;
	/// <summary>
	/// ブール型
	/// </summary>
	
	bool m_isUnderAttackMelee = false;	//攻撃中ならtrue
	bool m_isUnderTail = false;			//攻撃中ならtrue
	bool m_isUnderFlyAttack = false;	//攻撃中ならtrue
	bool m_isClear = false;				//クリア判定
	bool m_isUnderPattern = false;		//行動中ならtrue
	bool m_isUnderDefence = false;		//防御中ならtrue

	ModelRender m_modelRender;
	Player* m_player = nullptr;
	CollisionObject* m_collision = nullptr;
	CollisionObject* m_flyPosCollision = nullptr;
	Game* m_game = nullptr;
	IBossState* m_Iboss_State = nullptr;
	Animation m_animation;	// アニメーション
	Skeleton m_skeleton;	// スケルトン
	Model m_model;			// モデル
	Quaternion	m_rotation;							//回転
	Quaternion m_wait;
	AnimationClip m_animationClipArray[enAnimClip_Num];	// アニメーションクリップ
	CharacterController m_charaCon;	//キャラクターコントローラー

};

