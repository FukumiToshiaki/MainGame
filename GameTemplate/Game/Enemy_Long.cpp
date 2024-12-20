#include "stdafx.h"
#include "EnemyBase.h"

#include "Enemy_Long.h"
#include "Player.h"
#include "Game.h"
#define START_POS_X -800.0f
#define START_POS_Y 0.0f
#define START_POS_Z 500.0f
#define ESCAPE_SPEED 200.0f
#define DISTANCE_POS 900.0f
#define SCALE 10.5f
namespace
{
	
}

void Enemy_Long::InitSkeleton()
{
	m_skeleton.Init("Aseets/modelData/Skel/Skeleton.tks");
}
bool Enemy_Long::Start()
{
	const Vector3 m_scale = { SCALE,SCALE,SCALE }; //大きさ
	const Vector3 m_corre = { 0.0f,40.0f,0.0f };//位置修正

	m_modelRender.SetPosition(m_pos);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);

	m_animationClipArray[enAnimClip_Idle].Load("Assets/animData/Skel/SkeletonIdle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Run].Load("Assets/animData/Skel/SkeletonRun.tka");
	m_animationClipArray[enAnimClip_Run].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Attack].Load("Assets/animData/Skel/SkeletonAttack.tka");
	m_animationClipArray[enAnimClip_Attack].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Damage].Load("Assets/animData/Skel/SkeletonDamage.tka");
	m_animationClipArray[enAnimClip_Damage].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Knockback].Load("Assets/animData/Skel/SkeletonKnockback.tka");
	m_animationClipArray[enAnimClip_Knockback].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Walk].Load("Assets/animData/Skel/SkeletonWalk.tka");
	m_animationClipArray[enAnimClip_Walk].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Death].Load("Assets/animData/Skel/SkeletonDeath.tka");
	//m_animationClipArray[enAnimClip_Death].SetLoopFlag(true);

	m_modelRender.Init("Assets/modelData/Skel/Skeleton.tkm", m_animationClipArray, enAnimClip_Num);
	//スケルトンをロード。
	InitSkeleton();
	//アニメーションを初期化。//
	//InitAnimation();
	m_player = FindGO<Player>("player");
	m_player->AddEnemy_List(this);
	m_game = FindGO<Game>("game");
	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateSphere(m_pos, Quaternion::Identity, 75.0f);
	m_collision->SetIsEnableAutoDelete(false);
	m_collision->SetName("enemy_long");
	//m_rotation.SetRotationY(135.0f);

	m_pos = { START_POS_X, START_POS_Y, START_POS_Z };

	return true;
}

void Enemy_Long::InitAnimation()
{
	m_animation.Init(
		m_skeleton,			//アニメーションを流し込むスケルトン。
		m_animationClipArray,	//アニメーションクリップ。
		enAnimClip_Num		//アニメーションの数。
	);
	//アニメーションを進める。
	m_animation.Progress(g_gameTime->GetFrameDeltaTime());
}
void Enemy_Long::Rotation()
{
	//弾丸を移動方向に向かせるプログラム
		//移動速度を↓に入れるとできる
	if (m_isDistance) {
		m_moveSpeed.z *= -1.0f;
	}
	float angle = atan2(-m_moveSpeed.x, -m_moveSpeed.z);
	m_rotation.SetRotationY(-angle);
	m_modelRender.SetRotation(m_rotation);
	m_rotation.Apply(m_forward);
}


void Enemy_Long::Move()
{
	if ((g_pad[0]->IsTrigger(enButtonX))) {
		test += 1;
	}
	if (test >= 11)
	{
		test = 0;
	}
	//プレイヤーの追跡の変数
	Vector3 diff;
	Vector3 distance;
	switch (test) {
	case 0:
		m_modelRender.PlayAnimation(enAnimClip_Idle);
		break;
	case 1:
		m_modelRender.PlayAnimation(enAnimClip_Run);
		break;
	case 2:
		m_modelRender.PlayAnimation(enAnimClip_Attack);
		break;
	case 3:
		m_modelRender.PlayAnimation(enAnimClip_Damage);
		break;
	case 4:
		m_modelRender.PlayAnimation(enAnimClip_Knockback);
		break;
	case 5:
		m_isDistance = true;
		break;
	case 6:
		m_isDistance = false;
		m_modelRender.PlayAnimation(enAnimClip_Death);
		break;
	}
	
	//if (m_playerPosDistance.x <= 0.0f) {
	//	m_playerPosDistance.x *= -1.0f;
	//	}
	//if (m_playerPosDistance.z <= 0.0f) {
	//	m_playerPosDistance.z *= -1.0f;
	//}

	//if (m_posDistance.x <= 0.0f) {
	//	m_posDistance.x *= -1.0f;
	//}
	//if (m_posDistance.z <= 0.0f) {
	//	m_posDistance.z *= -1.0f;
	//}
	//テスト　プレイヤ
	// ーに向かって追跡
	if (test == 5) {
		m_animationClipArray[enAnimClip_Knockback].SetLoopFlag(false);
		//distance.Distance(m_pos, m_player->Get_PlayerPos());
		diff = m_player->Get_PlayerPos() - m_pos;
		distance = m_player->Get_PlayerPos() - m_pos;
	}
	else {
		m_pos = { START_POS_X, START_POS_Y, START_POS_Z };
	}
	if (distance.x <= 0.0f) {
		distance.x *= -1.0f;
	}
	if (distance.z <= 0.0f) {
		distance.z *= -1.0f;
	}
	if (distance.x <= DISTANCE_POS && distance.z <= DISTANCE_POS) {
		if (m_isDistance) {
			m_modelRender.PlayAnimation(enAnimClip_Walk);
			m_animationClipArray[enAnimClip_Walk].SetLoopFlag(true);
			//ベクトルの正規化
			diff.Normalize();
			m_moveSpeed = diff * -ESCAPE_SPEED;
		}
	}
	else {
		m_modelRender.PlayAnimation(enAnimClip_Idle);
		m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
		m_animationClipArray[enAnimClip_Walk].SetLoopFlag(false);
		m_moveSpeed = { 0.0f,0.0f,0.0f };
		m_isDistance = false;
	}

	//if (distance.x <= 200.0f || distance.z <= 200.0f) {
	//	//ベクトルの正規化
	//	diff.Normalize();
	//	m_moveSpeed = diff * -ESCAPE_SPEED;
	//}
}
void Enemy_Long::Update()
{
	m_pos += m_moveSpeed * g_gameTime->GetFrameDeltaTime();//動きを一定にするため
	//回転処理
	Rotation();
	//移動処理
	Move();
	//m_modelRender.SetRotation(m_rotation);
	m_skeleton.Update(m_model.GetWorldMatrix());
	m_modelRender.SetPosition(m_pos);
	m_collision->SetPosition(m_pos);
	m_modelRender.Update();
}

void Enemy_Long::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
}

