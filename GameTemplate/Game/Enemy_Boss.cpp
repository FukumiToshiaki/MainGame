#include "stdafx.h"
#include "EnemyBase.h"
#include "BossPattern.h"

#include "Enemy_Boss.h"
#include "Player.h"
#include "Game.h"
#include "BossState_Idle.h"
#include "BossState_Walk.h"
#include "BossState_Biting.h"
#include "BossState_Shoot.h"
#include "BossState_Damage.h"
#include "BossState_Tail.h"
#include "BossState_Fly.h"
#include "BossState_FlyAttack.h"
#include "BossState_Landing.h"
#include "BossState_Takeoff.h"
#include "BossState_FlyShoot.h"
#include "BossState_Scream.h"
#include "BossState_Die.h"

#define START_POS_X 0.0f
#define START_POS_Y 0.0f
#define START_POS_Z 500.0f
#define SCALE 4.5f
//#define CHASE_SPEED 200.0f
#define DISTANCE_POS 1400.0f
#define BITING_DISTANCE 500.0f
#define REST_DISTANCE 1200.0f
#define BOSS_FORWARD 500.0f
#define COLLISION_TAIL 600.0f
#define COLLISION_FLYATTACK 700.0f
#define COLLISION_MELEE 300.0f
#define COLLISION 670.0f
#define TAIL_DISTANCE 900.0f
#define ATTACK_RAND 4
namespace
{
}

void Enemy_Boss::InitSkeleton()
{
	//m_skeleton.Init("Aseets/modelData/Chest/Chest.tks");
}
bool Enemy_Boss::Start()
{
	const Vector3 m_scale = { SCALE,SCALE,SCALE }; //大きさ
	//const Vector3 m_corre = { 0.0f,40.0f,0.0f };//位置修正
	
	//コリジョンの判定を移動させる
	m_collisionPos = m_pos;
	m_collisionPos.y += 300.0f;
	m_collisionPos.z -= 300.0f;
	m_modelRender.SetPosition(m_collisionPos);

	m_modelRender.SetPosition(m_pos);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);

	m_animationClipArray[enState_Idle].SetLoopFlag(true);
	m_animationClipArray[enState_Attack_Biting].SetLoopFlag(false);
	m_animationClipArray[enState_Attack_Shoot].SetLoopFlag(false);
	m_animationClipArray[enState_Attack_Tail].SetLoopFlag(false);
	m_animationClipArray[enState_Attack_Scream].SetLoopFlag(false);
	m_animationClipArray[enState_Attack_FlyShoot].SetLoopFlag(false);
	m_animationClipArray[enState_Damage].SetLoopFlag(false);
	m_animationClipArray[enState_Defence].SetLoopFlag(true);
	m_animationClipArray[enState_Rest].SetLoopFlag(true);
	m_animationClipArray[enState_Move].SetLoopFlag(true);
	m_animationClipArray[enState_Die].SetLoopFlag(false);
	m_animationClipArray[enState_Fly].SetLoopFlag(true);
	m_animationClipArray[enState_Attack_Fly].SetLoopFlag(true);
	m_animationClipArray[enState_Takeoff].SetLoopFlag(false);
	m_animationClipArray[enState_Landing].SetLoopFlag(false);

		m_animationClipArray[enState_Idle].Load("Assets/animData/Dragon_Frag/Dragon_Idle.tka");
		m_animationClipArray[enState_Attack_Biting].Load("Assets/animData/Dragon_Frag/Dragon_adjcent.tka");
		m_animationClipArray[enState_Attack_Shoot].Load("Assets/animData/Dragon_Frag/Dragon_Shoot.tka");
		m_animationClipArray[enState_Attack_Tail].Load("Assets/animData/Dragon_Frag/Dragon_Tail.tka");
		m_animationClipArray[enState_Attack_Scream].Load("Assets/animData/Dragon_Frag/Dragon_Scream.tka");
		m_animationClipArray[enState_Attack_FlyShoot].Load("Assets/animData/Dragon_Frag/Dragon_FlyShoot.tka");
		m_animationClipArray[enState_Damage].Load("Assets/animData/Dragon_Frag/Dragon_Gethit.tka");
		m_animationClipArray[enState_Defence].Load("Assets/animData/Dragon_Frag/Dragon_Defense.tka");
		m_animationClipArray[enState_Rest].Load("Assets/animData/Dragon_Frag/Dragon_Sleep.tka");
		m_animationClipArray[enState_Move].Load("Assets/animData/Dragon_Frag/Dragon_Walk.tka");
		m_animationClipArray[enState_Die].Load("Assets/animData/Dragon_Frag/Dragon_Die.tka");
		m_animationClipArray[enState_Fly].Load("Assets/animData/Dragon_Frag/Dragon_Fly.tka");
		m_animationClipArray[enState_Attack_Fly].Load("Assets/animData/Dragon_Frag/Dragon_Fly_Forward.tka");
		m_animationClipArray[enState_Takeoff].Load("Assets/animData/Dragon_Frag/Dragon_Takeoff.tka");
		m_animationClipArray[enState_Landing].Load("Assets/animData/Dragon_Frag/Dragon_Land.tka");

		//case 10:
		//	m_animationClipArray[enState_Die].Load("Assets/animData/Dragon_Frag/Dragon_Idle.tka");
		//	break;
		m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
			OnAnimationEvent(clipName, eventName);
			});

	m_modelRender.Init("Assets/modelData/Dragon_Frog/Doragon.tkm", m_animationClipArray, enAnimClip_Num);
	//スケルトンをロード。
	//InitSkeleton();
	//アニメーションを初期化。//
	//InitAnimation();
	m_player = FindGO<Player>("player");
	m_player->AddEnemy_List(this);
	m_game = FindGO<Game>("game");
	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateSphere(m_collisionPos, Quaternion::Identity, COLLISION);
	m_collision->SetIsEnableAutoDelete(false);
	m_collision->SetName("boss");
	m_rotation.SetRotationY(135.0f);
	m_pos = { START_POS_X, START_POS_Y, START_POS_Z };
	ChangeState(enState_Idle);
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//空を飛んでいるときのボーンを受け取る
	//m_flyBoneId = m_modelRender.FindBoneID(L"m_pos");
	return true;
}

void Enemy_Boss::InitAnimation()
{
	m_animation.Init(
		m_skeleton,			//アニメーションを流し込むスケルトン。
		m_animationClipArray,	//アニメーションクリップ。
		enAnimClip_Num		//アニメーションの数。
	);
	//アニメーションを進める。
	m_animation.Progress(g_gameTime->GetFrameDeltaTime());
}
void Enemy_Boss::Rotation()
{
	////弾丸を移動方向に向かせるプログラム
	////移動速度を↓に入れるとできる
	//if (m_isDistance || m_isBiting || m_isShoot) {
	//	m_moveSpeed.z *= -1.0f;
	//}
	//if (m_moveSpeed.Length() > 0.1f) {
	//	float angle = atan2(-m_moveSpeed.x, -m_moveSpeed.z);
	//	m_rotation.SetRotationY(-angle);
	//}
	//m_modelRender.SetRotation(m_rotation);
	//m_rotation.Apply(m_forward);
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下の時
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	m_modelRender.SetRotation(m_rotation);
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}
void Enemy_Boss::Biting()
{
	//if (m_distance.Length()<=BITING_DISTANCE) {
	//	m_isBiting = true;
	//	m_moveSpeed = { 0.0f,0.0f,0.0f };
	//	m_isDistance = false;
	//	m_moveSpeed = m_diff;
	//}
	////追跡中に攻撃範囲に入ったら噛みつき
	//else {
	//	m_isBiting = false;
	//}
	if (m_isUnderAttackMelee) {
		//噛みつき用のコリジョンの作成
		MeleeAttackCollision();
	}
}
void Enemy_Boss::Move()
{
	////プレイヤーの追跡の変数
	//m_distance = m_player->Get_PlayerPos() - m_pos;
	//m_diff = m_player->Get_PlayerPos() - m_pos;
	//m_diff.Normalize();

	////if (m_state == enState_Move)
	////{
	////}
	//if (m_distance.Length()<=DISTANCE_POS) {
	//	
	//	m_isShoot = false;
	//	m_isDistance = true;
	//	m_moveSpeed = m_diff* CHASE_SPEED;

	//	Quaternion qRot;
	//	qRot.SetRotationDeg(Vector3::AxisY, CHASE_SPEED);
	//	qRot.Apply(m_moveSpeed);
	//	//Vector3 testX;
	//	//testX.Cross(Vector3::AxisY, m_moveSpeed);
	//	//testX.Normalize();
	//	qRot.SetRotationDegY(CHASE_SPEED);
	//	qRot.Apply(m_moveSpeed);
	//	
	//}
	//else {
	//	m_moveSpeed = { 0.0f,0.0f,0.0f };
	//	m_isDistance = false;
	////	m_isShoot = true;
	//}

}
void Enemy_Boss::Shoot()
{
	//if (m_isShoot) {
	//	m_moveSpeed = m_diff;
	//}
}
void Enemy_Boss::Rest()
{
	
}
void Enemy_Boss::Hit()
{
	if (m_isDamage) {
		return;
	}
	// 攻撃コリジョンと衝突しているかを調べる
	
	//ダッシュアタック
	//近接攻撃
	const auto& collisionList_GuardBreak = g_collisionObjectManager->FindCollisionObjects("player_guardbreak" /*"player_walk_attack" "player_biting_attack"*/);

	for (auto& collision_GuardBreak : collisionList_GuardBreak) {
		if (collision_GuardBreak->IsHit(m_collision)) {
			//ダメージ
			m_isDamage = true;
			m_testHP=m_testHP - 2;
			return;
		}
	}
	const auto& collisionList_WalkAttack = g_collisionObjectManager->FindCollisionObjects/*("player_guardbreak"*/("player_walk_attack" /*"player_biting_attack"*/);

	for (auto& collision_WalkAttack : collisionList_WalkAttack) {
		if (collision_WalkAttack->IsHit(m_collision)) {
			//ダメージ
			m_isDamage = true;
			m_testHP--;
			return;
		}
	}
	const auto& collisionList_MeleeAttack = g_collisionObjectManager->FindCollisionObjects(/*"player_guardbreak"*/ /*"player_walk_attack"*/ "player_biting_attack");

	for (auto& collision_MeleeAttack : collisionList_MeleeAttack) {
		if (collision_MeleeAttack->IsHit(m_collision)) {
			//ダメージ
			m_isDamage = true;
			m_testHP--;
			return;
		}
	}
	//const auto& collisionList_BitingAttack=g_collisionObjectManager->
}
void Enemy_Boss::MeleeAttackCollision()
{
	//コリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//座標をボスの少し前に設定
	collisionPosition -= m_forward * BOSS_FORWARD;
	//球状のコリジョンを作成
	collisionObject->CreateSphere(collisionPosition,//座標
		Quaternion::Identity,//回転
		COLLISION_MELEE//半径
	);
	collisionObject->SetName("boss_attack_melee");

}
void Enemy_Boss::TailAttack()
{
	////追跡中に攻撃範囲に入ったら薙ぎ払い
	//if (m_distance.Length()<=TAIL_DISTANCE)
	//{
	//	m_isTail = true;
	//	m_moveSpeed = { 0.0f,0.0f,0.0f };
	//	m_isDistance = false;
	//	m_moveSpeed = m_diff;
	//}
	//else if (m_isDistance) {
	//	m_isTail = false;
	//}
	if (m_isUnderTail) {
		TailAttackCollision();
	}
}
void Enemy_Boss::TailAttackCollision()
{
	//コリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//座標をボスの少し前に設定
	collisionPosition += m_forward * BOSS_FORWARD;
	//球状のコリジョンを作成
	collisionObject->CreateSphere(collisionPosition,//座標
		Quaternion::Identity,//回転
		COLLISION_TAIL//半径
	);
	collisionObject->SetName("boss_attack_tail");
}
void Enemy_Boss::FlyAttack()
{
	if (m_isUnderFlyAttack) {
		FlyAttackCollision();
	}
}
void Enemy_Boss::FlyAttackCollision()
{
	//コリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//座標をボスの少し前に設定
	collisionPosition += m_forward * BOSS_FORWARD;
	//球状のコリジョンを作成
	collisionObject->CreateSphere(collisionPosition,//座標
		Quaternion::Identity,//回転
		COLLISION_FLYATTACK//半径
	);
	collisionObject->SetName("boss_attack_fly");
}
void Enemy_Boss::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//キーの名前がBoss_Attack_Melee_startの場合
	if (wcscmp(eventName, L"Boss_Attack_Melee_start") == 0)
	{
		//攻撃中にする
		m_isUnderAttackMelee = true;
	}
	//キーの名前がBoss_Attack_Melee_endの場合
	else if (wcscmp(eventName, L"Boss_Attack_Melee_end") == 0)
	{
		//攻撃を終わる
		m_isUnderAttackMelee = false;
	}

	//キーの名前がBoss_Attack_Tail_startの場合
	if (wcscmp(eventName, L"Boss_Attack_Tail_start") == 0)
	{
		//攻撃中にする
		m_isUnderTail = true;
	}
	//キーの名前がBoss_Attack_Tail_endの場合
	else if (wcscmp(eventName, L"Boss_Attack_Tail_end") == 0)
	{
		//攻撃を終わる
		m_isUnderTail = false;
	}

	//キーの名前がFlyAttack_startの場合
	if (wcscmp(eventName, L"FlyAttack_start") == 0)
	{
		//攻撃中にする
		m_isUnderFlyAttack = true;
	}
	//キーの名前がFlyAttack_endの場合
	else if (wcscmp(eventName, L"FlyAttack_end") == 0)
	{
		//攻撃を終わる
		m_isUnderFlyAttack = false;
	}

}
void Enemy_Boss::ChangeState(EnState changeState)
{
	m_Iboss_State = nullptr;
	switch (changeState)
	{
	case Enemy_Boss::enState_Idle:
		m_Iboss_State = new BossState_Idle(this);
		break;
	case Enemy_Boss::enState_Attack_Biting://
		m_Iboss_State = new BossState_Biting(this);
		break;
	case Enemy_Boss::enState_Attack_Shoot:
		m_Iboss_State = new BossState_Shoot(this);
		break;
	case Enemy_Boss::enState_Attack_Tail://
		m_Iboss_State = new BossState_Tail(this);
		break;
	case Enemy_Boss::enState_Attack_Scream:
		m_Iboss_State = new BossState_Scream(this);
		break;
	case Enemy_Boss::enState_Attack_FlyShoot:
		m_Iboss_State = new BossState_FlyShoot(this);
		break;
	case Enemy_Boss::enState_Damage:
		m_Iboss_State = new BossState_Damage(this);
		break;
	case Enemy_Boss::enState_Defence:
		break;
	case Enemy_Boss::enState_Rest:
		break;
	case Enemy_Boss::enState_Move:
		m_Iboss_State = new BossState_Walk(this);
		break;
	case Enemy_Boss::enState_Takeoff:
		m_Iboss_State = new BossState_Takeoff(this);
		break;
	case Enemy_Boss::enState_Fly:
		m_Iboss_State = new BossState_Fly(this);
		break;
	case Enemy_Boss::enState_Landing:
		m_Iboss_State = new BossState_Landing(this);
		break;
	case Enemy_Boss::enState_Attack_Fly:
		m_Iboss_State = new BossState_FlyAttack(this);
		break;
	case Enemy_Boss::enState_Die:
		m_Iboss_State = new BossState_Die(this);
		break;
	}
	m_state = changeState;
}
void Enemy_Boss::Update()
{
	m_pos += m_moveSpeed * g_gameTime->GetFrameDeltaTime();//動きを一定にするため
	//m_isScream = true;
	//m_isBiting = true;
	//Biting();
	//m_attackCoolTime -= g_gameTime->GetFrameDeltaTime();
		//攻撃速度
	/*if (m_attackCoolTime >= 0.0f) {
		m_attack_Rand = rand() % ATTACK_RAND;
		m_attackCoolTime = ATTACK_COOLTIME;
	}

	switch (m_attack_Rand)
	{
	case 0:
		Biting();
		break;
	case 1:
		Shoot();
		break;
	case 2:
		TailAttack();
		break;
	case 3:
		FlyAttack();
		break;
	}*/
	//コリジョンの当たり判定
	m_collisionPos = m_pos;
	m_collisionPos.y += 300.0f;
	m_collisionPos.z += 300.0f;
	m_modelRender.SetPosition(m_collisionPos);


	//if ((g_pad[0]->IsTrigger(enButtonX))) {
	//	test += 1;
	//}
	//if (test >= 11)
	//{
	//	test = 0;
	//}
	//if ((g_pad[0]->IsTrigger(enButtonLB1))) {
	//	ChangeState(enState_Move);
	//}
	//if ((g_pad[0]->IsTrigger(enButtonLB2))) {
	//	ChangeState(enState_Idle);
	//}
	m_Iboss_State->Animation();
	m_Iboss_State->Update();
	Rotation();
	Hit();
	Move();
	m_modelRender.SetRotation(m_rotation);
	m_skeleton.Update(m_model.GetWorldMatrix());
	m_modelRender.SetPosition(m_pos);
	m_collision->SetPosition(m_collisionPos);
	m_collision->Update();
	m_modelRender.Update();
	//ボーンの座標を受け取るプログラムテスト
//Matrix matrix = m_modelRender.GetBone(m_flyBoneId)->GetWorldMatrix();
//m_flyPosCollision->SetPosition(m_flyPos);
//m_flyPosCollision->SetRotation(m_rotation);
//m_flyPosCollision->Update();
//m_flyPosCollision->SetWorldMatrix(matrix);

}

void Enemy_Boss::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
}
