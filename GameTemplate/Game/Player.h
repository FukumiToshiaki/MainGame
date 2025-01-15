#pragma once
#include <SpriteRender.h>
#include "PlayerStatus.h"
#include "EnemyBase.h"
class Game;
class EnemyBase;
class Enemy_Boss;
class IPlayer_State;
class Enemy_Shield;
class Enemy_Sky;
class Enemy_Melee;
class Enemy_Long;

class Player : public IGameObject
{
public:

	struct LockOnPosition
	{
		Vector3 position;

	};
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	void Move();
	void Rotation();
	void Attack_Biting();
	void WalkAttack();
	void Defense();
	void GuardBreak();
	void Hit();
	//エイム
	void TakeAim();
	void AddEnemy_List(EnemyBase* enemybase);
	void RemoveEnemy_List(EnemyBase* enemybase);
	//LockOnPosition* TakeAim(Vector3 position);
	//ロックオン
	void LockOn();
	//遠距離攻撃
	void LongAttack();
	// スケルトンを初期化
	void InitSkeleton();
	// モデルを初期化。
	//void InitModel();
	// アニメーションを初期化。
	void InitAnimation();

	// アニメーションイベント用の関数。
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	
	//アニメーションコリジョン近接攻撃の関数
	void BitingAttackCollision();
	//アニメーションコリジョンダッシュ攻撃の関数
	void WalkAttackCollision();
	//アニメーションコリジョンガードブレイクの関数
	void GuradBreakCollision();
	// アニメーションクリップの番号を表す列挙型。
	enum EnAnimationClip {
		enAnimClip_Idle,	// 0 : 待機アニメーション、
		enAnimClip_Run,		// 1 : 走りアニメーション。
		enAnimClip_Attack,	// 2 :剣で攻撃
		enAnimClip_Walk,
		enAnimClip_DefenceStart,
		enAnimClip_Defense,
		enAnimClip_DefenceEnd,
		enAnimClip_WalkAttack,
		enAnimClip_GuardBreak,
		enAnimClip_LongAttack,
		enAnimClip_Damage,
		enAnimClip_Die,
		enAnimClip_Num,		// 3 :アニメーションクリップの数。アニメーションを追加するならこの上に作る

	};

	enum EnState {
		enState_Idle,
		enState_Attack_Biting,
		enState_Defense,
		enState_Run,
		enState_Walk,
		enState_WalkAttack,
		enState_GuradBreak,
		enState_Damage,
		enState_LongAttack,
		enState_Die,
	};
	EnState m_state = enState_Idle;
	//ステートの管理
	void ChangeState(EnState changeState);

	Vector3 Get_PlayerPos()
	{
		return m_pos;
	}

	ModelRender& GetModelRender()
	{
		return m_modelRender;
	}

	const bool& GetIsPlayingAnimation()const
	{
		return m_modelRender.IsPlayingAnimation();
	}

	//bool GetIsAttack_Biting()
	//{
	//	return m_isAttack_Biting;
	//}
	//void SetIsAttack_Biting(const bool Attack_Biting) {
	//	m_isAttack_Biting = Attack_Biting;
	//}

	//bool GetIsWalk()
	//{
	//	return m_isWalk;
	//}

	//bool GetIsWalkAttack()
	//{
	//	return m_isWalkAttack;
	//}
	//void SetIsWalkAttack(const bool WalkAttack) {
	//	m_isWalkAttack = WalkAttack;
	//}

	//bool GetIsLongAttack()
	//{
	//	return m_isLongAttack;
	//}
	//bool GetIsDefense()
	//{
	//	return m_isDefense;
	//}
	//void SetIsDefense(const bool Defense)
	//{
	//	m_isDefense = Defense;
	//}

	//bool GetIsGuradBreak()
	//{
	//	return m_isGuardBreak;
	//}
	//void SetIsGuradBreak(const bool Break)
	//{
	//	m_isGuardBreak = Break;
	//}

	//bool GetisDamage()
	//{
	//	return m_isDamage;
	//}
	//void SetisDamage(const bool damage) {
	//	m_isDamage = damage;
	//}

	//bool GetisDie()
	//{
	//	return m_isDie;
	//}
	//void SetisDie(bool Die)
	//{
	//	m_isDie = Die;
	//}

	bool GetisOver()
	{
		return m_isOver;
	}
	void SetisOver(bool Over)
	{
		m_isOver = Over;
	}


	const bool GetIsLockOn() const
	{
		return m_isLockOn;
	}

	int GetEnemyNo()
	{
		return m_enemyNo;
	}

	int GetHP()
	{
		return m_testHP;
	}
	/// <summary>
	/// ターゲットの座標を取得。
	/// </summary>
	/// <returns></returns>
	const Vector3& GetTargetPosition() const
	{
		return m_targetPosition;
	}

private:
/// <summary>
/// ベクター
/// </summary>
	Vector3 m_pos;		// 座標
	Vector3 m_moveSpeed;									//移動速度。
	Vector3	m_forward = Vector3::AxisZ;
	Vector3 m_scale = Vector3::One;			//大きさ。
	Vector3 m_stickL;
	Vector3 m_attack_Pos;
	Vector3 m_targetPosition = Vector3::Zero;
	std::vector<EnemyBase*> m_enemyList;
/// <summary>
/// クラス
/// </summary>
	Game* m_game = nullptr;									//ゲーム
	Enemy_Boss* m_enemy_Boss = nullptr;		//ボス
	Enemy_Shield* m_enemy_Shield = nullptr;
	Enemy_Melee* m_enemy_melee = nullptr;
	Enemy_Long* m_enemy_Long = nullptr;
	Enemy_Sky* m_enemy_Sky = nullptr;
	IPlayer_State* m_Iplayer_State = nullptr;
	CollisionObject* m_collision = nullptr;
	SpriteRender		m_spriteRender;
	/// <summary>
/// 変数
/// </summary>
	int m_enemyNo = 0;
	float m_testHP = 10;
	int m_count = -1;
	int m_targetCount = -1;
	float m_longAttackCoolTime = 5.0f;
/// <summary>
/// ブール型
/// </summary>
	bool m_isNowAttack = false;//攻撃中ならtrue
	//bool m_isAttack_Biting = false;	//
	//bool m_isWalk = false;			//
	//bool m_isWalkAttack = false;	//
	//bool m_isDefense = false;		//	
	//bool m_isGuardBreak = false;	//
	//bool m_isLongAttack = false;	//遠距離攻撃
	bool m_isUnderAttack = false;	//攻撃中ならtrue
	bool m_isUnderWalkAttack = false;//ダッシュ攻撃中ならtrue
	bool m_isUnderGuradBreak = false;//ガードブレイク中ならtrue
	bool m_isUnderLongAttack = false;//ロングアタック中ならtrue
	//bool m_isDamage = false;		//
	bool m_isTakeAim = false;
	bool m_isLockOn = false;
	bool m_isLockOnCamera = false;
	//bool m_isDie = false;
	bool m_isOver = false;

	Model m_model;			// モデル
	Animation m_animation;	// アニメーション
	AnimationClip m_animationClipArray[enAnimClip_Num];	// アニメーションクリップ
	Quaternion m_rotation;	// 回転
	Sprite m_sprite;	// スプライト
	Skeleton m_skeleton;	// スケルトン
	ModelRender m_modelRender;
	CharacterController m_charaCon;	//キャラクターコントローラー
	PlayerStatus m_playerStatus;
};
