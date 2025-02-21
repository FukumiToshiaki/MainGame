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
class Player_HP_UI;
class Player : public IGameObject
{
public:

	struct LockOnPosition
	{
		Vector3 position;

	};
	//スタート関数
	bool Start() override;
	//アップデート関数
	void Update() override;
	//モデルレンダー
	void Render(RenderContext& rc) override;
	//移動の関数
	void Move(float walk_speed, float run_speed, float walkattack_speed);
	//回転関数
	void Rotation(float rotation);
	//近距離攻撃の関数
	void Attack_Biting();
	//ダッシュアタックの関数
	void WalkAttack();
	//防御関数
	void Defense();
	//防御コリジョンの関数
	void DefenseCollision(float melee_knockback, float melee_magnification, float tail_knockback, float tail_magnification,
		float flyattack_knockback, float flyattack_magnification, float scream_knockback, float scream_magnification,float scream_hittime,
		float shoot_knockback, float shoot_magnification, float landing_knockback, float landing_magnification);
	//ガードブレイク関数
	void GuardBreak();
	//ヒット関数
	void Hit(float screamhitcooltime, float tail_knockback, float flyattack_knockback, float landing_knockback);
	//エイム
	void TakeAim(float maximum, float smallest);
	//エネミーのリスト
	void AddEnemy_List(EnemyBase* enemybase);
	void RemoveEnemy_List(EnemyBase* enemybase);
	//LockOnPosition* TakeAim(Vector3 position);
	//ロックオン
	void LockOn();
	//遠距離攻撃
	void LongAttack(float hitstartframe, float hitendframe, float effect_speed);
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
		//enAnimClip_DefenceStart,
		enAnimClip_Defense,
		//enAnimClip_DefenceEnd,
		enAnimClip_WalkAttack,
		enAnimClip_GuardBreak,
		enAnimClip_LongAttack,
		enAnimClip_Damage,
		enAnimClip_Die,
		enAnimClip_Arching,
		enAnimClip_Landing_Back,
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
		enState_Arching,
		enState_Die,
		enState_Flying_Back,
	};
	EnState m_state = enState_Idle;
	//ステートの管理
	void ChangeState(EnState changeState);

	Vector3 Get_PlayerPos()
	{
		return m_pos;
	}

	void SetMoveSpeed(Vector3 MoveSpeed) {
		m_moveSpeed = MoveSpeed;
	}

	ModelRender& GetModelRender()
	{
		return m_modelRender;
	}

	const bool& GetIsPlayingAnimation()const
	{
		return m_modelRender.IsPlayingAnimation();
	}

	bool GetisOver()
	{
		return m_isOver;
	}
	void SetisOver(bool Over)
	{
		m_isOver = Over;
	}

	void SetisWalkAttack(bool WalkAttack) {
		m_isUnderWalkAttack = WalkAttack;
	}
	void SetisBitAttack(bool BitAttack) {
		m_isUnderAttack = BitAttack;
	}
	void SetisGuradBreak(bool GuradBreak) {
		m_isUnderGuradBreak = GuradBreak;
	}
	void SetisLongAttack(bool LongAttack) {
		m_isUnderLongAttack = LongAttack;
	}
	void SetisDefense(bool defense) {
		m_isUnderDefense = defense;
	}
	const bool GetIsLockOn() const
	{
		return m_isLockOn;
	}

	int GetEnemyNo()
	{
		return m_enemyNo;
	}

	float GetHP()
	{
		return m_testHP;
	}

	void SetisSound(bool Sound) {
		m_isSound = Sound;
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
	// 座標
	Vector3 m_pos = Vector3::Zero;;
	//移動速度。
	Vector3 m_moveSpeed = Vector3::Zero;	
	//向き
	Vector3	m_forward = Vector3::AxisZ;
	//大きさ
	Vector3 m_scale = Vector3::One;			
	//スティック
	Vector3 m_stickL = Vector3::Zero;;
	Vector3 m_attack_Pos = Vector3::Zero;;
	//敵のポジション
	Vector3 m_targetPosition = Vector3::Zero;
	//ノックバック
	Vector3 m_KnockBack = Vector3::Zero;;
	//遠距離攻撃のポジション
	Vector3 m_longAttackPos = Vector3::Zero;;
	//敵のリスト
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
	Player_HP_UI* m_player_HP_UI = nullptr;
	/// <summary>
/// 変数
/// </summary>
	//敵のナンバー
	int m_enemyNo = 0;
	//エイムの切り替え
	int m_count = -1;
	//ターゲット
	int m_targetCount = -1;
	//エフェクトカウンター
	int m_effectCount = 0;
	//HP
	float m_testHP = 70.0f;
	//ヒット時のクールタイム
	float m_hitCoolTime = 1.5f;
	//遠距離攻撃のクールタイム
	float m_longAttackCoolTime = 5.0f;
	//ノックバックの判定のクールタイム
	float m_knockBackTime = 0.3f;
/// <summary>
/// ブール型
/// </summary>
	bool m_isNowAttack = false;//攻撃中ならtrue
	//ノックバック中か
	bool m_isKnockBack = false;
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
	bool m_isUnderDefense = false;//ガード中ならtrue
	bool m_isTakeAim = false;
	bool m_isLockOn = false;
	bool m_isLockOnCamera = false;
	bool m_isEffect = false;		//エフェクトが出ているならtrue
	bool m_isOver = false;
	bool m_isUnderFlying_Back = false;//吹っ飛ばされ中ならtrue
	bool m_isFlying_Back_Tail = false;		//尻尾攻撃の攻撃ヒット時true
	bool m_isFlying_Back_FlyAttack = false;		//滑空突進の攻撃ヒット時true
	bool m_isFlying_Back_Landing = false;
	bool m_isSound = false;					//効果音

	Model m_model;			// モデル
	Animation m_animation;	// アニメーション
	AnimationClip m_animationClipArray[enAnimClip_Num];	// アニメーションクリップ
	Quaternion m_rotation= Quaternion::Identity;;	// 回転
	Sprite m_sprite;	// スプライト
	Skeleton m_skeleton;	// スケルトン
	ModelRender m_modelRender;
	CharacterController m_charaCon;	//キャラクターコントローラー
	PlayerStatus *m_playerStatus = nullptr;
	EffectEmitter* effectEmitter = nullptr;
	SoundSource* m_bitAttack = nullptr;			//No9
	SoundSource* m_defense = nullptr;			//No10
	SoundSource* m_guardBreak = nullptr;		//No11
	SoundSource* m_run = nullptr;				//No12
	SoundSource* m_walk = nullptr;				//No13
	SoundSource* m_walkAttack = nullptr;		//No14

};
