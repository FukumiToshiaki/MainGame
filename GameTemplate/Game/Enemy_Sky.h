#pragma once
class Player;
class Game;
#include "EnemyBase.h"

class Enemy_Sky : public EnemyBase
{
public:
	Enemy_Sky() {};
	~Enemy_Sky() {};
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	// スケルトンを初期化
	void InitSkeleton();
	// アニメーションを初期化。
	void InitAnimation();
	//キャラの角度の調整
	void Rotation();

	// アニメーションクリップの番号を表す列挙型。
	enum EnAnimationClip {
		enAnimClip_Idle,	// 0 : 待機アニメーション、
		enAnimClip_Walk,	// 2 :攻撃
		enAnimClip_Damage,	// 2 :攻撃
		enAnimClip_Attack,	// 2 :攻撃
		enAnimClip_Death,	// 2 :攻撃
		enAnimClip_Num,		// 3 :アニメーションクリップの数。アニメーションを追加するならこの上に作る

	};

private:
	/// <summary>
	/// ベクター
	/// </summary>
	Vector3 m_moveSpeed;	//移動速度
	Vector3		m_forward = Vector3::AxisZ;					//エネミーの正面ベクトル。
	Vector3						m_scale = Vector3::One;			//大きさ。

	/// <summary>
	/// クラス
	/// </summary>
	Player* m_player = nullptr;
	CollisionObject* m_collision = nullptr;
	Game* m_game = nullptr;


	/// <summary>
	/// 変数
	/// </summary>
	int test = 0;


	/// <summary>
	/// ブール型
	/// </summary>
	bool m_isDistance = false;

	ModelRender m_modelRender;
	Animation m_animation;	// アニメーション
	AnimationClip m_animationClipArray[enAnimClip_Num];	// アニメーションクリップ
	Skeleton m_skeleton;	// スケルトン
	Model m_model;			// モデル
	Quaternion	m_rotation;							//回転

};