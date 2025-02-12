#pragma once
class Player;
class Game;
class IBossState;
class Boss_Shoot;
class Boss_HP_UI;
#include "EnemyBase.h"
#include "BossFlyPoint.h"
#include "sound/SoundEngine.h"

class Enemy_Boss : public EnemyBase
{
public:
	Enemy_Boss() {};
	~Enemy_Boss() {};
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	//void FlyAttackMove();
	// スケルトンを初期化
	void InitSkeleton();
	// アニメーションを初期化。
	void InitAnimation();
	//回転の初期化
	void Rotation(int rotation);
	//近距離攻撃の噛みつき
	void MeleeAttack();
	//遠距離攻撃の地上からのブレス
	void Shoot();//(int movespeed, int hitstartframe, int hitendframe);
	//大技後の休憩モーション
	void Rest();
	//コリジョンの当たり判定
	void Hit(int damagemagnification);
	//噛みつき攻撃のコリジョン
	void MeleeAttackCollision(int collision_melee);
	//尻尾の薙ぎ払い
	void TailAttack();
	//尻尾の薙ぎ払いのコリジョン
	void TailAttackCollision(int collision_tail);
	//空中突進
	void FlyAttack(float movespeed);
	//空中突進の当たり判定
	void FlyAttackCollision(int collision_flyattack);
	//ガードの判定
	void Defence();
	//ガードのコリジョン
	void DefenceCollision(int break_magnification,int collision_defense);
	// アニメーションイベント用の関数。
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	//距離をとる関数
	void FlyPos(float movespeed);
	//必殺技の咆哮
	void Scream();
	//必殺技のコリジョン
	void ScreamCollision(int collision_scream);
	//着地時のダメージ
	void Landing();
	//着地時のコリジョン
	void LandingDamage(int collision_landing);
	//HPが30%以下になった時のBGM関数
	void BGM();
	//空ブレスの時
	void FlyShoot();
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
		enState_Defence_Counter_Animation,
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
		enState_Defence_Counter,
		enState_Rest,
		enState_Move,
		enState_Die,
		enState_Takeoff,
		enState_Fly,
		enState_Landing,
		enState_Landing_Back,
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

	float GetHP()
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

	void SetEffectCount(int effectcount) {
		m_effectCount = effectcount;
	}

	void SetisScream_Normal(bool Scream) {
		m_isScream_Normal = Scream;
	}
	bool GetisScream_Normal()	{
		return m_isScream_Normal;
	}
	bool GetisScream_Set() {
		return m_isScream_Set;
	}

protected:
	/// <summary>
	/// ベクター
	/// </summary>
	Vector3 m_distance = Vector3::Zero;
	Vector3 m_diff = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;	//移動速度
	Vector3	m_scale = Vector3::One;			//大きさ。
	Vector3	m_forward = Vector3::AxisZ;					//エネミーの正面ベクトル。
	Vector3 m_collisionPos = Vector3::Zero;
	Vector3 m_flyPos = Vector3::Zero;
	//Vector3 m_moveSpeed_Shoot = Vector3::Zero;
	//Vector3 m_shootPos = Vector3::Zero;
	//Vector3 m_shot = Vector3::Zero;
	Vector3 diff = Vector3::Zero;
	/// <summary>
	/// クラス
	/// </summary>
	//BossPattern* m_bossPattern = nullptr;
	/// <summary>
	/// 変数
	/// </summary>
	int m_attack_Rand = 0;
	int m_attack_Count = -1;
	//HP
	float m_testHP = 19.0f;
	//飛んだ時のボーン取得のため
	int m_flyBoneId = 0;
	//必殺技を撃つためのカウント
	int m_screamCount = 0;
	//エフェクトカウンター
	int m_effectCount = 0;

	float m_angle = 0.0f;
	float m_radius = 2.0f;
	//ヒット時のクールタイム
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
	bool m_isUnderScream = false;		//必殺技中ならtrue
	bool m_isUnderLanding = false;		//着地中ならtrue
	bool m_isUnderFly = false;			//空を飛んでいるならtrue
	bool m_isUnderTakeoff= false;		//空に飛ぼうとしているならtrue
	bool m_isScream = false;		//
	bool m_isScream_Normal = false;				//咆哮が通常行動で選ばれたらtrue
	bool m_isEffect = false;		//エフェクトが出ているならtrue
	bool m_isFlyKeepDistance = false;	//空を飛んで距離をとっているならtrue
	bool m_isScream_Set = false;

	ModelRender m_modelRender;
	Player* m_player = nullptr;
	Boss_HP_UI* m_boss_HP_UI = nullptr;
	CollisionObject* m_collision = nullptr;
	CollisionObject* m_flyPosCollision = nullptr;
	//CollisionObject* m_shootCollision = nullptr;
	Game* m_game = nullptr;
	IBossState* m_Iboss_State = nullptr;
	Boss_Shoot* m_boss_Shoot = nullptr;
	Animation m_animation;	// アニメーション
	Skeleton m_skeleton;	// スケルトン
	Model m_model;			// モデル
	Quaternion	m_rotation=Quaternion::Identity;							//回転
	Quaternion m_wait=Quaternion::Identity;
	AnimationClip m_animationClipArray[enAnimClip_Num];	// アニメーションクリップ
	CharacterController m_charaCon;	//キャラクターコントローラー
	BossFlyPoint::FlyPoint* m_flyPoint = nullptr;
	SoundSource* m_bossLastButtle = nullptr;
	SoundSource* m_bossButtle = nullptr;
	
	//EffectEmitter* Boss_Shoot_Start = nullptr;
};

