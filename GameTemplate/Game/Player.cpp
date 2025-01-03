#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "EnemyBase.h"
#include "Enemy_Boss.h"
#include "Enemy_Shield.h"
#include "Enemy_Melee.h"
#include "Enemy_Sky.h"
#include "Enemy_Long.h"
#include "IPlayer_State.h"
#include "PlayerState_Idle.h"
#include "PlayerState_AttackBiting.h"
#include "PlayerState_Walk.h"
#include "PlayerState_WalkAttack.h"
#include "PlayerState_Defense.h"
#include "PlayerState_GuardBreak.h"
#include "PlayerState_Damage.h"
#include "PlayerState_AttackLong.h"
#include "PlayerState_Die.h"

#define START_POS_X 0.0f
#define START_POS_Y 0.0f
#define START_POS_Z -2000.0f
#define PLAYER_MOVESPEED 500.0f
#define SCALE 2.0f

void Player::InitSkeleton()
{
	//m_skeleton.Init("Assets/modelData/unityChan.tks");

	//m_skeleton.Init("Assets/modelData/PlayerData/PicoChan.tks");
}

bool Player::Start()
{
	//m_playerStatus.Init();

	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/Effect/Player_LongAttack.efk");

	const Vector3 m_scale = { SCALE,SCALE,SCALE }; //大きさ

	//アニメーションクリップをロードする。
	m_animationClipArray[enAnimClip_Attack].Load("Assets/animData/Pico_Anime/Player_Test_Attack.tka");
	m_animationClipArray[enAnimClip_Attack].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Walk].Load("Assets/animData/Pico_Anime/Player_Test_Walk.tka");
	m_animationClipArray[enAnimClip_Walk].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Idle].Load("Assets/animData/Pico_Anime/Player_Test_Idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_WalkAttack].Load("Assets/animData/Pico_Anime/Player_Test_WalkAttack.tka");
	m_animationClipArray[enAnimClip_WalkAttack].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_LongAttack].Load("Assets/animData/Pico_Anime/Player_Long_Attack.tka");
	m_animationClipArray[enAnimClip_LongAttack].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_DefenceStart].Load("Assets/animData/Pico_Anime/Player_Test_DefenseStart.tka");
	m_animationClipArray[enAnimClip_DefenceStart].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Defense].Load("Assets/animData/Pico_Anime/Player_Test_Defense.tka");
	m_animationClipArray[enAnimClip_Defense].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_DefenceEnd].Load("Assets/animData/Pico_Anime/Player_Test_DefenseEnd.tka");
	m_animationClipArray[enAnimClip_DefenceEnd].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_GuardBreak].Load("Assets/animData/Pico_Anime/Player_Test_GuardBreak.tka");
	m_animationClipArray[enAnimClip_GuardBreak].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Damage].Load("Assets/animData/Pico_Anime/Player_Test_Damage.tka");
	m_animationClipArray[enAnimClip_Damage].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Die].Load("Assets/animData/Pico_Anime/Player_Test_Die.tka");
	m_animationClipArray[enAnimClip_Die].SetLoopFlag(false);



	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	m_modelRender.Init("Assets/modelData/Player_Test/Player_Test.tkm", m_animationClipArray, enAnimClip_Num);
	m_spriteRender.Init("Assets/sprite/lock.DDS", 400, 400);
	//アニメーションなしなら動く
	//m_modelRender.Init("Assets/modelData/Player_Test/Player_Test.tkm");

	//m_animationClipArray[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	//m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);

	//m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClipArray, enAnimClip_Num, enModelUpAxisY);

	//スケルトンをロード。
	//InitSkeleton();
	//モデルを初期化。
	//アニメーションを初期化。//
	//InitAnimation();
	//スケール
	m_pos = { START_POS_X, START_POS_Y, START_POS_Z };
	m_modelRender.SetPosition(m_pos);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	////当たり判定の作成。
	m_collision= NewGO<CollisionObject>(0);
	m_collision->CreateSphere(m_pos, Quaternion::Identity, 100.0f);
	m_collision->SetName("player_collsion");
	m_collision->SetIsEnableAutoDelete(false);
	//m_modelRender.Update();
	//m_attack_Pos = m_pos;
	//m_attack_Pos.x += 100.0f;
	m_charaCon.Init(25.0f, 40.0f, m_pos);

	m_game = FindGO<Game>("game");
	m_enemy_Boss = FindGO<Enemy_Boss>("enemy_boss");
	m_enemy_melee = FindGO<Enemy_Melee>("enemy_melee");
	m_enemy_Long = FindGO<Enemy_Long>("enemy_long");
	m_enemy_Shield = FindGO<Enemy_Shield>("enemy_shield");
	m_enemy_Sky = FindGO<Enemy_Sky>("enemy_sky");

	ChangeState(enState_Idle);

	////手首のボーンを受け取る
	//m_TestBoneId = m_modelRender.FindBoneID(L"mixamorig:RightHand");
	////攻撃用コリジョンを用意
	//m_testAttackCollision = NewGO<CollisionObject>(0);
	//m_testAttackCollision->CreateBox(m_attack_Pos, Quaternion::Identity, { 120.0f,20.0f,20.0f });
	//m_testAttackCollision->SetName("player_attack");
	//m_testAttackCollision->SetIsEnableAutoDelete(false);

	return true;
}

void Player::InitAnimation()
{
	//m_animationClipArray[enAnimClip_Run].Load("Assets/animData/walk.tka");
	//m_animationClipArray[enAnimClip_Run].SetLoopFlag(true);
	//アニメーションを初期化。
	m_animation.Init(
		m_skeleton,			//アニメーションを流し込むスケルトン。
		m_animationClipArray,	//アニメーションクリップ。
		enAnimClip_Num		//アニメーションの数。
	);
	////アニメーションを進める。
	m_animation.Progress(g_gameTime->GetFrameDeltaTime());
}

void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//キーの名前がattack_startの場合
	if (wcscmp(eventName, L"attack_start") == 0)
	{
		//攻撃中にする
		m_isUnderAttack = true;
	}
	//キーの名前がattack_endの場合
	else if (wcscmp(eventName, L"attack_end") == 0) {
		//攻撃を終わる
		m_isUnderAttack = false;
	}

	//キーの名前がattack_startの場合
	if (wcscmp(eventName, L"walkattack_start") == 0)
	{
		//攻撃中にする
		m_isUnderWalkAttack = true;
	}
	//キーの名前がattack_endの場合
	else if (wcscmp(eventName, L"walkattack_end") == 0) {
		//攻撃を終わる
		m_isUnderWalkAttack = false;
	}

	//キーの名前がGuradBreak_startの場合
	if (wcscmp(eventName, L"GuradBreak_start") == 0)
	{
		//攻撃中にする
		m_isUnderGuradBreak = true;
	}
	//キーの名前がGuradBreak_endの場合
	else if (wcscmp(eventName, L"GuradBreak_end") == 0) {
		//攻撃を終わる
		m_isUnderGuradBreak = false;
	}
	//キーの名前がLongAttack_startの場合
	if (wcscmp(eventName, L"LongAttack_start") == 0)
	{
		//攻撃中にする
		m_isUnderLongAttack = true;
	}
	//キーの名前がLongAttack_endの場合
	else if (wcscmp(eventName, L"LongAttack_end") == 0) {
		//攻撃を終わる
		m_isUnderLongAttack = false;
	}

}

void Player::BitingAttackCollision()
{
	/*m_forward = m_moveSpeed;
	m_forward.Normalize();*/

	//コリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//座標をプレイヤーの少し前に設定
	collisionPosition += m_forward * 150.0f;
	//球状のコリジョンを作成
	collisionObject->CreateSphere(collisionPosition,//座標
		Quaternion::Identity,//回転
		100.0f//半径
	);
	collisionObject->SetName("player_biting_attack");
}

void Player::WalkAttackCollision()
{
	//コリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//座標をプレイヤーの少し前に設定
	collisionPosition += m_forward * 150.0f;
	//球状のコリジョンを作成
	collisionObject->CreateSphere(collisionPosition,//座標
		Quaternion::Identity,//回転
		100.0f//半径
	);
	collisionObject->SetName("player_walk_attack");
}

void Player::GuradBreakCollision()
{
	//コリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//座標をプレイヤーの少し前に設定
	collisionPosition += m_forward * 150.0f;
	//球状のコリジョンを作成
	collisionObject->CreateSphere(collisionPosition,//座標
		Quaternion::Identity,//回転
		100.0f//半径
	);
	collisionObject->SetName("player_guardbreak");

}

void Player::ChangeState(EnState changeState)
{
	m_Iplayer_State = nullptr;
	switch (changeState)
	{
	case Player::enState_Idle:
		m_Iplayer_State = new PlayerState_Idle(this);
		break;
	case Player::enState_Attack_Biting:
		m_Iplayer_State = new PlayerState_AttackBiting(this);
		break;
	case Player::enState_Defense:
		m_Iplayer_State = new PlayerState_Defense(this);
		break;
	case Player::enState_Run:
		break;
	case Player::enState_Walk:
		m_Iplayer_State = new PlayerState_Walk(this);
		break;
	case Player::enState_WalkAttack:
		m_Iplayer_State = new PlayerState_WalkAttack(this);
		break;
	case Player::enState_GuradBreak:
		m_Iplayer_State = new PlayerState_GuardBreak(this);
		break;
	case Player::enState_Damage:
		m_Iplayer_State = new PlayerState_Damage(this);
		break;
	case Player::enState_LongAttack:
		m_Iplayer_State = new PlayerState_AttackLong(this);
	case Player::enState_Die:
		m_Iplayer_State = new PlayerState_Die(this);
		break;
	}
	m_state = changeState;
}

void Player::Update()
{
	

	Move();
	Rotation();
	WalkAttack();
	Attack_Biting();
	Defense();
	GuardBreak();
	Hit();
	TakeAim();
	LockOn();
	LongAttack();
	//// 回転
	//m_rotation.AddRotationY(g_pad[0]->GetRStickXF() * 0.05f);
	m_Iplayer_State->Animation();
	m_Iplayer_State->Update();
	//InitAnimation();
	m_spriteRender.Update();
	m_skeleton.Update(m_model.GetWorldMatrix());
	m_pos = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_charaCon.SetPosition(m_pos);
	m_collision->SetPosition(m_pos);
	m_collision->Update();
	m_modelRender.SetPosition(m_pos);
	m_modelRender.Update();

	////ボーンの座標を受け取るプログラムテスト
	//Matrix matrix = m_modelRender.GetBone(m_TestBoneId)->GetWorldMatrix();
	//m_testAttackCollision->SetPosition(m_attack_Pos);
	//m_testAttackCollision->SetRotation(m_rotation);
	//m_testAttackCollision->Update();
	//m_testAttackCollision->SetWorldMatrix(matrix);

}

void Player::Move()
{
	if (m_isDie){
		return;
	}
	if (m_isAttack_Biting || m_isGuardBreak || m_isWalkAttack) {
		m_isNowAttack = true;
		return;
	}
	m_isNowAttack = false;
	//xzの移動速度を0.0fにする。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//影のテスト用
	m_moveSpeed.y = 0.0f;
	
	//左スティックの入力量を取得。
	m_stickL.x = g_pad[0]->GetLStickXF();
	m_stickL.z = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動させない。
	forward.y = 0.0f;
	right.y = 0.0f;

	forward.Normalize();
	right.Normalize();
	//キャラクターコントローラーを使用して、座標を更新。
	m_pos += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
	m_modelRender.SetPosition(m_pos);
	right *= m_stickL.x * PLAYER_MOVESPEED;
	forward *= m_stickL.z * PLAYER_MOVESPEED;

	if (m_stickL.x != 0.0f || m_stickL.z != 0.0f) {
		m_isWalk = true;
	}
	else {
		m_isWalk = false;
	}
	////移動速度にスティックの入力量を加算する。
	m_moveSpeed += right + forward;

	//座標を移動
		////スケルトンを更新。
}
void Player::Rotation()
{
	//if (fabsf(m_moveSpeed.x) < 0.001f
	//	&& fabsf(m_moveSpeed.z) < 0.001f) {
	//	//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
	//	//このフレームではキャラは移動していないので旋回する必要はない。
	//	return;
	//}
	//m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	//m_modelRender.SetRotation(m_rotation);
	//m_forward = Vector3::AxisZ;
	//m_rotation.Apply(m_forward);
	if (m_moveSpeed.Length() > 0.1f) {
		float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
		m_rotation.SetRotationY(-angle);
		m_forward = m_moveSpeed;
		m_forward.Normalize();
	}
	m_rotation.SetRotationYFromDirectionXZ(m_forward);

	m_rotation.Apply(m_forward);
	m_modelRender.SetRotation(m_rotation);

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

}
void Player::Attack_Biting()
{
	if (g_pad[0]->IsTrigger(enButtonRB2) && !m_isWalkAttack&&!m_isNowAttack) {
		m_isAttack_Biting = true;
	}
	//攻撃判定中なら
	if (m_isUnderAttack) {
		//攻撃用のコリジョンを作成する
		BitingAttackCollision();
	}
		if (m_isAttack_Biting) {
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
		}
}
void Player::WalkAttack()
{
	if (g_pad[0]->IsTrigger(enButtonRB2) && !m_isNowAttack) {
		if (m_stickL.x != 0.0f || m_stickL.z != 0.0f)
		{
			m_isWalkAttack = true;
		}
	}
	if (m_isWalkAttack)
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}
	if (m_isUnderWalkAttack) {
		WalkAttackCollision();
	}
}
void Player::Defense()
{
	if (g_pad[0]->IsPress(enButtonRB1) && !m_isNowAttack) {
		m_isDefense = true;
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}
	else {
		m_isDefense = false;
	}
}
void Player::GuardBreak()
{
	if (g_pad[0]->IsTrigger(enButtonY) && !m_isNowAttack) {
		m_isGuardBreak = true;
	}
	if (m_isGuardBreak) {
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		//m_rotation = { 0.0f,0.0f,0.0f,0.0f };
	}
	if (m_isUnderGuradBreak)	{
		GuradBreakCollision();
	}
}
void Player::Hit()
{
	if (m_isDamage) {
		return;
	}

	// 攻撃コリジョンと衝突しているかを調べる
	const auto& collisionList_MeleeAttack = g_collisionObjectManager->FindCollisionObjects("boss_attack_melee" /*"player_walk_attack" "player_biting_attack"*/);
	for (auto& collision : collisionList_MeleeAttack) {
		if (collision->IsHit(m_collision)) {
			//ダメージ
			m_isDamage = true;
			m_testHP--;
			return;
		}
	}
	// 攻撃コリジョンと衝突しているかを調べる
	const auto& collisionList_TailAttack = g_collisionObjectManager->FindCollisionObjects("boss_attack_tail");
	for (auto& collision : collisionList_TailAttack) {
		if (collision->IsHit(m_collision)) {
			//ダメージ
			m_isDamage = true;
			m_testHP--;
			return;
		}
	}
	//// 攻撃コリジョンと衝突しているかを調べる
	//const auto& collisionList_Attack = g_collisionObjectManager->FindCollisionObjects("boss_attack_melee" /*"player_walk_attack" "player_biting_attack"*/);
	//for (auto& collision : collisionList_Attack) {
	//	if (collision->IsHit(m_collision)) {
	//		//ダメージ
	//		m_isDamage = true;

	//	}
	//}
}
void Player::TakeAim()
{
	Vector3 NearenemyPosition;
	//float NearLength = 10000.0f;
	//for (auto enemy : m_enemyList) {
	//	Vector3 enemyPosition;
	//	enemyPosition = enemy->GetPos() - m_pos;
	//	float Length = enemyPosition.Length();
	//	if (NearLength >= Length) {
	//		NearenemyPosition = enemyPosition;
	//		NearLength = Length;
	//	}
	//}
	if (m_count == 0) {
		std::sort(m_enemyList.begin(), m_enemyList.end(),
			[this](EnemyBase* a, EnemyBase* b)
			{
				return a->ToEnemyTargetLength(this->Get_PlayerPos()) < b->ToEnemyTargetLength(this->Get_PlayerPos());
			}
		);
		m_count++;
	}
	
	if (m_targetCount >= static_cast<int>(m_enemyList.size())) {
		m_targetCount = 0;
		m_count = 0;
	}
	m_isTakeAim = true;
	if (m_targetCount < 0) {
		return;
	}
	NearenemyPosition = m_enemyList[m_targetCount]->GetPos();

		Vector3 diff = NearenemyPosition;
	//プレイヤーとエネミーが一定以上離れていたら
	//ターゲッティングしない
	//近すぎてもターゲッティングしない
	if (diff.Length() >= 3000.0f || diff.Length() <= 20.0f)
	{
		m_isTakeAim = false;
		return;
	}
	diff.y = 0.0f;
	diff.Normalize();

	float angle = acosf(m_forward.Dot(diff));
	//プレイヤーの正面ベクトルと。
	//プレイヤーからエネミーに向かうベクトルの。
	//角度が90度以上かつ。
	//ロックオン状態でなかったら。
	//ターゲッティングしない。
	if (angle > Math::PI * 2 && m_isLockOn == false) {
		m_isTakeAim = false;
		return;
	}

	Vector2 screenPosition;
	g_camera3D->CalcScreenPositionFromWorldPosition(screenPosition, NearenemyPosition);
	m_spriteRender.SetPosition(Vector3(screenPosition.x, screenPosition.y, 0.0f));
	m_targetPosition = NearenemyPosition;

}
void Player::AddEnemy_List(EnemyBase* enemybase)
{
	m_enemyList.emplace_back(enemybase);
}
void Player::RemoveEnemy_List(EnemyBase* enemybase)
{
	std::vector<EnemyBase*>::iterator it = std::find(
		m_enemyList.begin(),
		m_enemyList.end(),
		enemybase
	);
	if (it != m_enemyList.end()) {
		m_enemyList.erase(it);
	}
}
void Player::LockOn()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_isLockOn = true;
		m_targetCount++;
		m_count++;
	}
	else if (g_pad[0]->IsTrigger(enButtonB))
	{
		m_isLockOn = false;
		m_targetCount = -1;
		m_count = -1;
	}

	//ターゲッティングがされていなかったら。
	//ロックオンしない。
	if (m_isTakeAim == false)
	{
		m_isLockOn = false;
		m_targetCount = -1;
		m_count = -1;
		return;
	}

}
void Player::LongAttack()
{
	if (g_pad[0]->IsTrigger(enButtonLB1))
	{
		m_isLongAttack = true;
	}
	if (m_isLongAttack) {
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0, "long_attack");
		effectEmitter->Init(0);
		effectEmitter->SetScale(Vector3::One * 10.0f);
		effectEmitter->SetPosition(m_pos);
		effectEmitter->Play();
	}
	if (!this->GetIsPlayingAnimation()&&!m_isUnderLongAttack) {
		m_isLongAttack = false;
	}
}
void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	if (m_isTakeAim == false)
	{
		return;
	}
	m_spriteRender.Draw(rc);
}
