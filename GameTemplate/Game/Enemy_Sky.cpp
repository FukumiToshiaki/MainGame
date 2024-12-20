#include "stdafx.h"
#include "EnemyBase.h"

#include "Enemy_Sky.h"
#include "Player.h"
#include "Game.h"
#define START_POS_X 800.0f
#define START_POS_Y 0.0f
#define START_POS_Z 500.0f
#define CHASE_SPEED 200.0f
#define DISTANCE_POS 700.0f
#define SCALE 3.5f

namespace
{

}

void Enemy_Sky::InitSkeleton()
{
	m_skeleton.Init("Aseets/modelData/StoneMonster/StoneMonster.tks");
}
bool Enemy_Sky::Start()
{
	const Vector3 m_scale = { SCALE,SCALE,SCALE }; //大きさ
	const Vector3 m_corre = { 0.0f,40.0f,0.0f };//位置修正

	m_modelRender.SetPosition(m_pos);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);

	m_animationClipArray[enAnimClip_Idle].Load("Assets/animData/StoneMon/StoneMonstorIdle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Walk].Load("Assets/animData/StoneMon/StoneMonstorRun.tka");
	m_animationClipArray[enAnimClip_Walk].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Damage].Load("Assets/animData/StoneMon/StoneMonstorDamage.tka");
	m_animationClipArray[enAnimClip_Damage].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Attack].Load("Assets/animData/StoneMon/StoneMonstorAttack.tka");
	m_animationClipArray[enAnimClip_Attack].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Death].Load("Assets/animData/StoneMon/StoneMonstorDeath.tka");

	m_modelRender.Init("Assets/modelData/StoneMonster/StoneMonster.tkm", m_animationClipArray, enAnimClip_Num);
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
	m_collision->SetName("enemy_sky");

	m_pos = { START_POS_X, START_POS_Y, START_POS_Z };

	return true;
}

void Enemy_Sky::InitAnimation()
{
	m_animation.Init(
		m_skeleton,			//アニメーションを流し込むスケルトン。
		m_animationClipArray,	//アニメーションクリップ。
		enAnimClip_Num		//アニメーションの数。
	);
	//アニメーションを進める。
	m_animation.Progress(g_gameTime->GetFrameDeltaTime());
}
void Enemy_Sky::Move()
{
	if ((g_pad[0]->IsTrigger(enButtonX))) {
		test += 1;
	}
	if (test >= 11)
	{
		test = 0;
		m_pos.y = START_POS_Y;
	}
	Vector3 diff;
	Vector3 distance;

	switch (test) {
	case 0:
		m_modelRender.PlayAnimation(enAnimClip_Idle);
		break;
	case 1:
		m_isDistance = true;
		break;
	case 2:
		m_isDistance = false;
		m_modelRender.PlayAnimation(enAnimClip_Damage);
		break;
	case 3:
		m_modelRender.PlayAnimation(enAnimClip_Attack);
		break;
	case 4:
		m_modelRender.PlayAnimation(enAnimClip_Death);
		if (m_pos.y >= 10.0f) {
			m_pos.y -= 10.0f;
		}
		break;
	}
	if (test == 1) {
		m_animationClipArray[enAnimClip_Damage].SetLoopFlag(false);
		diff = m_player->Get_PlayerPos() - m_pos;
		distance = m_player->Get_PlayerPos() - m_pos;
	}
	else if (test != 4) {
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
		}
		//ベクトルの正規化
		diff.Normalize();
		m_moveSpeed = diff * CHASE_SPEED;
	}
	else {
		m_modelRender.PlayAnimation(enAnimClip_Idle);
		m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
		m_animationClipArray[enAnimClip_Walk].SetLoopFlag(false);
		m_moveSpeed = { 0.0f,0.0f,0.0f };
		m_isDistance = false;
	}

}
void Enemy_Sky::Rotation()
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

void Enemy_Sky::Update()
{
	m_pos += m_moveSpeed * g_gameTime->GetFrameDeltaTime();//動きを一定にするため
	//回転処理
	Rotation();
	//移動処理
	Move();
	m_modelRender.SetRotation(m_rotation);
	m_skeleton.Update(m_model.GetWorldMatrix());
	m_modelRender.SetPosition(m_pos);
	m_collision->SetPosition(m_pos);
	m_modelRender.Update();
}

void Enemy_Sky::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
}

