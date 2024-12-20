#include "stdafx.h"
#include "EnemyBase.h"

#include "Enemy_Melee.h"
#include "Player.h"
#include "Game.h"
#define START_POS_X -400.0f
#define START_POS_Y 0.0f
#define START_POS_Z 500.0f
#define CHASE_SPEED 250.0f
#define DISTANCE_POS 800.0f
#define SCALE 6.5f

namespace
{

}
void Enemy_Melee::InitSkeleton()
{
	m_skeleton.Init("Aseets/modelData/SlimeRabbit/SlimeRabbit.tks");
}
bool Enemy_Melee::Start()
{
	const Vector3 m_scale = { SCALE,SCALE,SCALE }; //大きさ
	const Vector3 m_corre = { 0.0f,40.0f,0.0f };//位置修正

	m_modelRender.SetPosition(m_pos);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);

	m_animationClipArray[enAnimClip_Idle].Load("Assets/animData/SlimeRabbit/SlimeRabbit_Idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);

	m_animationClipArray[enAnimClip_Damage].Load("Assets/animData/SlimeRabbit/SlimeRabbit_Damage.tka");
	m_animationClipArray[enAnimClip_Damage].SetLoopFlag(true);

	m_animationClipArray[enAnimClip_Walk].Load("Assets/animData/SlimeRabbit/SlimeRabbit_Move.tka");
	m_animationClipArray[enAnimClip_Walk].SetLoopFlag(true);

	m_animationClipArray[enAnimClip_Death].Load("Assets/animData/SlimeRabbit/SlimeRabbit_Death.tka");
	//m_animationClipArray[enAnimClip_Death].SetLoopFlag(true);

	m_modelRender.Init("Assets/modelData/SlimeRabbit/SlimeRabbit.tkm", m_animationClipArray, enAnimClip_Num);
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
	m_collision->SetName("enemy_melee");

	m_pos = { START_POS_X, START_POS_Y, START_POS_Z };

	return true;
}

void Enemy_Melee::InitAnimation()
{
	m_animation.Init(
		m_skeleton,			//アニメーションを流し込むスケルトン。
		m_animationClipArray,	//アニメーションクリップ。
		enAnimClip_Num		//アニメーションの数。
	);
	//アニメーションを進める。
	m_animation.Progress(g_gameTime->GetFrameDeltaTime());
}
void Enemy_Melee::Move()
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
			m_modelRender.PlayAnimation(enAnimClip_Damage);
			break;
		case 2:
			m_isDistance = true;
			break;
		case 3:
			m_isDistance = false;
			m_modelRender.PlayAnimation(enAnimClip_Death);
			break;
		}
		//if (m_playerPosDistance.x <= 0.0f) {
		//	m_playerPosDistance.x *= -1.0f;
		//}
		//if (m_playerPosDistance.z <= 0.0f) {
		//	m_playerPosDistance.z *= -1.0f;
		//}

		//if (m_posDistance.x <= 0.0f) {
		//	m_posDistance.x *= -1.0f;
		//}if (m_posDistance.z <= 0.0f) {
		//	m_posDistance.z *= -1.0f;
		//}
		//テスト　プレイヤーに向かって追跡
		if (test == 2) {
			m_animationClipArray[enAnimClip_Damage].SetLoopFlag(false);
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
		m_AccelTimerStart += g_gameTime->GetFrameDeltaTime();
		if (m_AccelTimerStart >= 10.0f) {
			m_player->RemoveEnemy_List(this);
			DeleteGO(this);
		}

}

void Enemy_Melee::Rotation()
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

void Enemy_Melee::Update()
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

void Enemy_Melee::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
}
