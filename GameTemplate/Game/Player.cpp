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
#include "PlayerState_Run.h"
#include "PlayerState_Arching.h"
#include "PlayerState_Flying_Back.h"
#include "Player_HP_UI.h"
#include "Bullet.h"
#include "SoundManager.h"
#include "sound/SoundEngine.h"

#define START_POS_X 0.0f
#define START_POS_Y 0.0f
#define START_POS_Z -2000.0f
#define PLAYER_WALKSPEED 500.0f
#define PLAYER_RUNSPEED 1000.0f
#define SCALE 2.0f
#define PLAYER_FORWARD 150.0f
#define LONGATTACKCOOLTIME 5.0f
#define KNOCKBACKTIME 0.5f
#define HITCOOLTIME 2.0f
#define KNOCKBACKTIME_SCREAM 0.2f
#define TAILATTACKDAMAGE 2
#define MELEEATTACKDAMAGE 4
#define SHOOTATTACKDAMAGE 5
#define FLYATTACKDAMAGE 6
#define SCREAMATTACKDAMAGE 8
#define LANDINGDAMAGE 3
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
	m_animationClipArray[enAnimClip_Run].Load("Assets/animData/Pico_Anime/Player_Test_Run.tka");
	m_animationClipArray[enAnimClip_Run].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_WalkAttack].Load("Assets/animData/Pico_Anime/Player_Test_WalkAttack.tka");
	m_animationClipArray[enAnimClip_WalkAttack].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_LongAttack].Load("Assets/animData/Pico_Anime/Player_Long_Attack.tka");
	m_animationClipArray[enAnimClip_LongAttack].SetLoopFlag(false);
	//m_animationClipArray[enAnimClip_DefenceStart].Load("Assets/animData/Pico_Anime/Player_Test_Defense.tka");
	//m_animationClipArray[enAnimClip_DefenceStart].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Defense].Load("Assets/animData/Pico_Anime/Player_Test_Defense.tka");
	m_animationClipArray[enAnimClip_Defense].SetLoopFlag(true);
	//m_animationClipArray[enAnimClip_DefenceEnd].Load("Assets/animData/Pico_Anime/Player_Test_DefenseEnd.tka");
	//m_animationClipArray[enAnimClip_DefenceEnd].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_GuardBreak].Load("Assets/animData/Pico_Anime/Player_Test_GuardBreak.tka");
	m_animationClipArray[enAnimClip_GuardBreak].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Damage].Load("Assets/animData/Pico_Anime/Player_Test_Damage.tka");
	m_animationClipArray[enAnimClip_Damage].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Die].Load("Assets/animData/Pico_Anime/Player_Test_Die.tka");
	m_animationClipArray[enAnimClip_Die].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Arching].Load("Assets/animData/Pico_Anime/Player_Test_Arching.tka");
	m_animationClipArray[enAnimClip_Arching].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Landing_Back].Load("Assets/animData/Pico_Anime/Player_Test_Flying_Back.tka");
	m_animationClipArray[enAnimClip_Landing_Back].SetLoopFlag(false);


	
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	m_modelRender.Init("Assets/modelData/Player_Test/Player_Test.tkm", m_animationClipArray, enAnimClip_Num);
	//m_modelRender.Init("Assets/modelData/PlayerData/PicoChan.tkm", m_animationClipArray, enAnimClip_Num);
	//m_spriteRender.Init("Assets/sprite/lock.DDS", 400, 400);
	//スケール
	m_pos = { START_POS_X, START_POS_Y, START_POS_Z };
	m_modelRender.SetPosition(m_pos);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_charaCon.Init(25.0f, 40.0f, m_pos);

	m_game = FindGO<Game>("game");
	m_enemy_Boss = FindGO<Enemy_Boss>("enemy_boss");
	m_enemy_melee = FindGO<Enemy_Melee>("enemy_melee");
	m_enemy_Long = FindGO<Enemy_Long>("enemy_long");
	m_enemy_Shield = FindGO<Enemy_Shield>("enemy_shield");
	m_enemy_Sky = FindGO<Enemy_Sky>("enemy_sky");
	m_player_HP_UI = FindGO<Player_HP_UI>("player_hp_ui");

	ChangeState(enState_Idle);
	////当たり判定の作成。
	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateSphere(m_pos, Quaternion::Identity, 100.0f);
	m_collision->SetName("player_collsion");
	m_collision->SetIsEnableAutoDelete(false);
	////近接攻撃
	////g_soundEngine->ResistWaveFileBank(9, "Assets/sound/BitAttack.wav");
	//m_bitAttack = NewGO<SoundSource>(9);
	//////ガードのノックバック
	////g_soundEngine->ResistWaveFileBank(10, "Assets/sound/Defense.wav");
	//m_defense = NewGO<SoundSource>(10);
	//////ガードブレイク
	////g_soundEngine->ResistWaveFileBank(11, "Assets/sound/GuardBreak.wav");
	//m_guardBreak = NewGO<SoundSource>(11);
	//////走る
	////g_soundEngine->ResistWaveFileBank(12, "Assets/sound/Run.wav");
	//m_run = NewGO<SoundSource>(12);
	//////歩く
	////g_soundEngine->ResistWaveFileBank(13, "Assets/sound/Walk.wav");
	//m_walk = NewGO<SoundSource>(13);
	//////ダッシュ攻撃
	////g_soundEngine->ResistWaveFileBank(14, "Assets/sound/WalkAttack.wav");
	//m_walkAttack = NewGO<SoundSource>(14);

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

	//キーの名前がDefense_startの場合
	if (wcscmp(eventName, L"Defense_start") == 0)
	{
		//防御中にする
		m_isUnderDefense = true;
	}

	//キーの名前がFlying_Back_startの場合
	if (wcscmp(eventName, L"Flying_Back_start") == 0)
	{
		//吹っ飛ばされ中にする
		m_isUnderFlying_Back = true;
	}
	//キーの名前がFlying_Back_endの場合
	else if (wcscmp(eventName, L"Flying_Back_end") == 0) {
		//吹っ飛ばされるのを終わる
		m_isUnderFlying_Back = false;
		m_isFlying_Back_FlyAttack = false;
		m_isFlying_Back_Tail = false;
		m_isFlying_Back_Landing = false;
	}


}

void Player::BitingAttackCollision()
{
	//コリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//座標をプレイヤーの少し前に設定
	collisionPosition += m_forward * PLAYER_FORWARD;
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
	collisionPosition += m_forward * PLAYER_FORWARD;
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
	collisionPosition += m_forward * PLAYER_FORWARD;
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
		m_Iplayer_State = new PlayerState_Run(this);
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
		break;
	case Player::enState_Die:
		m_Iplayer_State = new PlayerState_Die(this);
		break;
	case Player::enState_Arching:
		m_Iplayer_State = new PlayerState_Arching(this);
		break;
	case Player::enState_Flying_Back:
		m_Iplayer_State = new PlayerState_Flying_Back(this);
		break;
	}
	m_state = changeState;
}

void Player::Update()
{
	m_hitCoolTime -= g_gameTime->GetFrameDeltaTime();

	m_Iplayer_State->Animation();
	m_Iplayer_State->Update();
	//InitAnimation();
	//m_spriteRender.Update();
	m_skeleton.Update(m_model.GetWorldMatrix());
	m_pos = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_charaCon.SetPosition(m_pos);
	m_collision->SetPosition(m_pos);
	m_collision->Update();
	m_modelRender.SetPosition(m_pos);
	m_modelRender.Update();

	if (m_state == enState_Die) {
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		return;
	}
	Move(500.0f,1000.0f,5.0f);
	Rotation(0.001f);
	Hit(0.1f, 700.0f, 500.0f, 400.0f);
	TakeAim(4000.0f, 100.0f);
	LockOn();
	//ダメージステート中ならreturn
	if (m_state == enState_Damage || m_state == enState_Arching || m_state == enState_Flying_Back) {
		return;
	}
	WalkAttack();
	Attack_Biting();
	Defense();
	GuardBreak();
	LongAttack(137,200,30.0f);
	//// 回転
	////ボーンの座標を受け取るプログラムテスト
	//Matrix matrix = m_modelRender.GetBone(m_TestBoneId)->GetWorldMatrix();
	//m_testAttackCollision->SetPosition(m_attack_Pos);
	//m_testAttackCollision->SetRotation(m_rotation);
	//m_testAttackCollision->Update();
	//m_testAttackCollision->SetWorldMatrix(matrix);

}

void Player::Move(float walk_speed, float run_speed, float walkattack_speed)
{
	//死んでいたりダメージやよろけ中return
	if (m_state == enState_Die || m_state == enState_Damage || m_state == enState_Arching || m_state == enState_Flying_Back) {
		return;
	}
	//攻撃中ならreturn
	if (m_state == enState_Attack_Biting || m_state == enState_GuradBreak || m_state == enState_LongAttack) {
		m_isNowAttack = true;
		return;
	}
	//ダッシュアタック中なら少し進む
	if (m_state == enState_WalkAttack)
	{
		m_moveSpeed = m_attack_Pos * walkattack_speed;
		m_isNowAttack = true;
		return;
	}
	//攻撃の判定をリセット
	m_isNowAttack = false;
	//xzの移動速度を0.0fにする。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
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
	//Xボタンを押されながら移動したら走る
	if (g_pad[0]->IsPress(enButtonX) && m_stickL.x != 0.0f || g_pad[0]->IsPress(enButtonX) && m_stickL.z != 0.0f) {
		right *= m_stickL.x * run_speed;
		forward *= m_stickL.z * run_speed;
		ChangeState(Player::enState_Run);
		m_isSound = false;
		////音再生
		//g_soundManager->InitAndPlaySoundSource(
		//	enSoundRun,
		//	g_soundManager->GetSEVolume()
		//);
	}
	//何も押されず移動なら歩く
	else if (m_stickL.x != 0.0f || m_stickL.z != 0.0f) {
		right *= m_stickL.x * walk_speed;
		forward *= m_stickL.z * walk_speed;
		ChangeState(Player::enState_Walk);
		m_isSound = false;
		////音再生
		//g_soundManager->InitAndPlaySoundSource(
		//	enSoundWalk,
		//	g_soundManager->GetSEVolume()
		//);
	}
	else {
		//移動しないならIdle状態
		right *= m_stickL.x * 0.0f;;
		forward *= m_stickL.z * 0.0f;
		ChangeState(Player::enState_Idle);
		//if (m_walk != nullptr) {
		//	m_walk->Stop();
		//}
		//else if (m_run != nullptr) {
		//	m_run->Stop();
		//}
	}
	////移動速度にスティックの入力量を加算する。
	m_moveSpeed += right + forward;
}
void Player::Rotation(float rotation)
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
	
	//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下の時
	//このフレームではキャラは移動していないので旋回する必要はない。
	if (m_moveSpeed.Length() > rotation) {

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
	//ボタンが押されたときに攻撃中じゃなく
	// ダッシュアタックでなければ
	if (g_pad[0]->IsTrigger(enButtonRB2) && m_state != enState_WalkAttack && !m_isNowAttack) {
		ChangeState(Player::enState_Attack_Biting);
		m_isSound = true;
	}
	//攻撃判定中なら
	if (m_isUnderAttack) {
		//攻撃用のコリジョンを作成する
		BitingAttackCollision();
		if (m_isSound) {
			//音再生
			g_soundManager->InitAndPlaySoundSource(
				enSoundBitAttack,
				g_soundManager->GetSEVolume()
			);
			m_isSound = false;
		}
	}
	if (m_state == enState_Attack_Biting) {
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
		}
}
void Player::WalkAttack()
{
	//走っているとき
	if (m_state == enState_Run)
	{
		//ボタンが押されたときに攻撃中でなければダッシュアタック
		if (g_pad[0]->IsTrigger(enButtonRB2) && !m_isNowAttack) {
			ChangeState(Player::enState_WalkAttack);
			m_isSound = true;
		}
	}
	if (m_isUnderWalkAttack) {
		WalkAttackCollision();
		if (m_isSound) {
			//音再生
			g_soundManager->InitAndPlaySoundSource(
				enSoundWalkAttack,
				g_soundManager->GetSEVolume()
			);
			m_isSound = false;
		}
	}
}
void Player::Defense()
{
	//ボタンが押されたときに攻撃中でなければDefense
	if (g_pad[0]->IsPress(enButtonRB1) && !m_isNowAttack) {
		ChangeState(Player::enState_Defense);
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}
	else {
		//防御のコリジョンをリセット
		m_isUnderDefense = false;
	}
	if (m_state != enState_Defense) {
		return;
	}
	if (m_isUnderDefense) {
		DefenseCollision(500.0f, 2.0f, 1500.0f, 4.0f, 1200.0f, 6.0f, 800.0f, 8.0f, 0.2f, 500.0f, 5.0f, 4000.0f, 3.0f);
		if (m_isSound) {
			//音再生
			g_soundManager->InitAndPlaySoundSource(
				enSoundDefense,
				g_soundManager->GetSEVolume()
			);
			m_isSound = false;
		}
	}
	//ノックバックに使うVector
	m_KnockBack = m_pos - m_enemy_Boss->GetPos();
	m_KnockBack.Normalize();
}
void Player::DefenseCollision(float melee_knockback, float melee_magnification, float tail_knockback, float tail_magnification,
	float flyattack_knockback, float flyattack_magnification, float scream_knockback, float scream_magnification,float scream_hittime,
	float shoot_knockback, float shoot_magnification,float landing_knockback,float landing_magnification)
{
	//コリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//座標をプレイヤーの少し前に設定
	collisionPosition += m_forward * 120.0f;
	//球状のコリジョンを作成
	collisionObject->CreateSphere(collisionPosition,//座標
		Quaternion::Identity,//回転
		120.0f//半径
	);
	collisionObject->SetName("player_defense");

	//ノックバックタイマーが0以下ならノックバック
	if (m_knockBackTime <= 0) {
		m_isKnockBack = false;
	}
	//攻撃を受けたらタイマースタート
	if (m_isKnockBack) {
		m_knockBackTime -= g_gameTime->GetFrameDeltaTime();
		return;
	}
	//嚙みつき
	const auto& collisionList_MeleeAttack = g_collisionObjectManager->FindCollisionObjects("boss_attack_melee");
	for (auto& collision : collisionList_MeleeAttack) {
		if (collision->IsHit(collisionObject)) {
			//ダメージ
			m_testHP -= MELEEATTACKDAMAGE / melee_magnification;
			m_isKnockBack = true;
			m_isSound = true;
			//タイマーのリセット
			m_knockBackTime = KNOCKBACKTIME;
			//HP_UIを減らす表示
			m_player_HP_UI->DecreaseHP(MELEEATTACKDAMAGE / melee_magnification);
			//ノックバック距離
			if (m_isKnockBack) {
				m_moveSpeed = m_KnockBack * melee_knockback;
			}
			return;
		}
	}
	//尻尾攻撃
	const auto& collisionList_TailAttack = g_collisionObjectManager->FindCollisionObjects("boss_attack_tail");
	for (auto& collision : collisionList_TailAttack) {
		if (collision->IsHit(collisionObject)) {
			//ダメージ
			m_testHP -= TAILATTACKDAMAGE / tail_magnification;			
			m_isKnockBack = true;
			m_isSound = true;
			//タイマーのリセット
			m_knockBackTime = KNOCKBACKTIME;
			//HP_UIを減らす表示
			m_player_HP_UI->DecreaseHP(TAILATTACKDAMAGE / tail_magnification);
			//ノックバック距離
			if (m_isKnockBack) {
				m_moveSpeed = m_KnockBack * tail_knockback;
			}
			return;
		}
	}
	//滑空突進
	const auto& collisionList_FlyAttack = g_collisionObjectManager->FindCollisionObjects("boss_attack_fly");
	for (auto& collision : collisionList_FlyAttack) {
		if (collision->IsHit(collisionObject)) {
			//ダメージ
			m_testHP -= FLYATTACKDAMAGE / flyattack_magnification;
			m_isKnockBack = true;
			m_isSound = true;
			//タイマーのリセット
			m_knockBackTime = KNOCKBACKTIME;
			//HP_UIを減らす表示
			m_player_HP_UI->DecreaseHP(FLYATTACKDAMAGE / flyattack_magnification);
			//ノックバック距離
			if (m_isKnockBack) {
				m_moveSpeed = m_KnockBack * flyattack_knockback;
			}
			return;
		}
	}
	//咆哮
	const auto& collisionList_ScreamAttack = g_collisionObjectManager->FindCollisionObjects("boss_attack_scream");
	for (auto& collision : collisionList_ScreamAttack) {
		if (collision->IsHit(collisionObject)) {
			//ダメージ
			m_testHP -= SCREAMATTACKDAMAGE / scream_magnification;
			m_isKnockBack = true;
			m_isSound = true;
			//タイマーのリセット
			m_knockBackTime = scream_hittime;
			//HP_UIを減らす表示
			m_player_HP_UI->DecreaseHP(SCREAMATTACKDAMAGE / scream_magnification);
			//ノックバック距離
			if (m_isKnockBack) {
				m_moveSpeed = m_KnockBack * scream_knockback;
			}
			return;
		}
	}
	//押しつぶし
	const auto& collisionList_LandingAttack = g_collisionObjectManager->FindCollisionObjects("boss_attack_landing");
	for (auto& collision : collisionList_LandingAttack) {
		if (collision->IsHit(collisionObject)) {
			//ダメージ
			m_testHP -= LANDINGDAMAGE / landing_magnification;
			m_isKnockBack = true;
			m_isSound = true;
			//タイマーのリセット
			m_knockBackTime = HITCOOLTIME;
			//HP_UIを減らす表示
			m_player_HP_UI->DecreaseHP(LANDINGDAMAGE / landing_magnification);
			//ノックバック距離
			if (m_isKnockBack) {
				m_moveSpeed = m_KnockBack * landing_knockback;
			}
			return;
		}
	}
	//ブレス
	const auto& collisionList_ShootAttack = g_collisionObjectManager->FindCollisionObjects("boss_shoot_collision");
	for (auto& collision : collisionList_ShootAttack) {
		if (collision->IsHit(collisionObject)) {
			//ダメージ
			m_testHP -= SHOOTATTACKDAMAGE / shoot_magnification;
			m_isKnockBack = true;
			m_isSound = true;
			//タイマーのリセット
			m_knockBackTime = KNOCKBACKTIME;
			//HP_UIを減らす表示
			m_player_HP_UI->DecreaseHP(SHOOTATTACKDAMAGE / shoot_magnification);
			//ノックバック距離
			if (m_isKnockBack) {
				m_moveSpeed = m_KnockBack * shoot_knockback;
			}
			//コリジョンを消すとエフェクトを消す
			QueryGOs<Bullet>("bullet", [&](Bullet* Shoot) {
				Shoot->Dead();
				Shoot->OnDeadEffect();
				return true;
				});
			return;
		}
	}


}
void Player::GuardBreak()
{
	//ボタンが押されたときに攻撃中ではないなら攻撃
	if (g_pad[0]->IsTrigger(enButtonY) && !m_isNowAttack) {
		ChangeState(Player::enState_GuradBreak);
		m_isSound = true;
	}
	if (m_state == enState_GuradBreak) {
		//その場に止まらせる
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}
	//アニメーションのシーンが来たら
	//コリジョンを作る
	if (m_isUnderGuradBreak)	{
		GuradBreakCollision();
		if (m_isSound) {
			//音再生
			g_soundManager->InitAndPlaySoundSource(
				enSoundGuardBreak,
				g_soundManager->GetSEVolume()
			);
			m_isSound = false;
		}
	}
}
void Player::Hit(float screamhitcooltime,float tail_knockback,float flyattack_knockback,float landing_knockback)
{
	//吹っ飛ばされる
	if (m_isUnderFlying_Back&& m_isFlying_Back_FlyAttack) {
		m_moveSpeed = m_KnockBack * flyattack_knockback;
	}
	else if (m_isUnderFlying_Back && m_isFlying_Back_Tail) {
		m_moveSpeed = m_KnockBack * tail_knockback;
	}
	else if (m_isUnderFlying_Back && m_isFlying_Back_Landing) {
		m_moveSpeed = m_KnockBack * landing_knockback;
	}


	//ヒット中ならreturn
	if (m_state == enState_Damage || m_isUnderDefense) {
		return;
	}
	//ヒットクールタイムが終わってないならreturn
	if (m_hitCoolTime >= 0) {
		return;
	}
	// 攻撃コリジョンと衝突しているかを調べる
	//噛みつき
	const auto& collisionList_MeleeAttack = g_collisionObjectManager->FindCollisionObjects("boss_attack_melee");
	for (auto& collision : collisionList_MeleeAttack) {
		if (collision->IsHit(m_collision)) {
			//ダメージ
			ChangeState(Player::enState_Damage);
			m_testHP-= MELEEATTACKDAMAGE;
			//クールタイム
			m_hitCoolTime = HITCOOLTIME;
			//ダメージ中に動かないように
			m_moveSpeed = Vector3::Zero;
			//HP_UIを減らす表示
			m_player_HP_UI->DecreaseHP(MELEEATTACKDAMAGE);
			return;
		}
	}
	//尻尾攻撃
	const auto& collisionList_TailAttack = g_collisionObjectManager->FindCollisionObjects("boss_attack_tail");
	for (auto& collision : collisionList_TailAttack) {
		if (collision->IsHit(m_collision)) {
			//ダメージ
			ChangeState(Player::enState_Flying_Back);
			m_testHP-=TAILATTACKDAMAGE;
			//クールタイム
			m_hitCoolTime = HITCOOLTIME;
			//吹っ飛ばされる攻撃を受けたためtrue
			m_isFlying_Back_Tail = true;
			//HP_UIを減らす表示
			m_player_HP_UI->DecreaseHP(TAILATTACKDAMAGE);
			return;
		}
	}
	//滑空突進
	const auto& collisionList_FlyAttack = g_collisionObjectManager->FindCollisionObjects("boss_attack_fly");
	for (auto& collision : collisionList_FlyAttack) {
		if (collision->IsHit(m_collision)) {
			//ダメージ
			ChangeState(Player::enState_Flying_Back);
			m_testHP-=FLYATTACKDAMAGE;
			//クールタイム
			m_hitCoolTime = HITCOOLTIME;
			//吹っ飛ばされる攻撃を受けたためtrue
			m_isFlying_Back_FlyAttack = true;
			//HP_UIを減らす表示
			m_player_HP_UI->DecreaseHP(FLYATTACKDAMAGE);
			return;
		}
	}
	//咆哮
	const auto& collisionList_ScreamAttack = g_collisionObjectManager->FindCollisionObjects("boss_attack_scream");
	for (auto& collision : collisionList_ScreamAttack) {
		if (collision->IsHit(m_collision)) {
			//ダメージ
			ChangeState(Player::enState_Damage);
			m_testHP -= SCREAMATTACKDAMAGE;
			//クールタイム
			m_hitCoolTime = screamhitcooltime;
			//ダメージ中に動かないように
			m_moveSpeed = Vector3::Zero;
			//HP_UIを減らす表示
			m_player_HP_UI->DecreaseHP(SCREAMATTACKDAMAGE);
			return;
		}
	}
	//着地時に近くにいたら吹き飛ばされる
	const auto& collisionList_Landing = g_collisionObjectManager->FindCollisionObjects("boss_attack_landing");
	for (auto& collision : collisionList_Landing) {
		if (collision->IsHit(m_collision)) {
			//ダメージ
			ChangeState(Player::enState_Flying_Back);
			m_testHP -= LANDINGDAMAGE;
			//クールタイム
			m_hitCoolTime = HITCOOLTIME;
			//HP_UIを減らす表示
			m_player_HP_UI->DecreaseHP(LANDINGDAMAGE);
			//吹っ飛ばされる攻撃を受けたためtrue
			m_isFlying_Back_Landing = true;
			return;
		}
	}
	//ブレス
	const auto& collisionList_ShootAttack = g_collisionObjectManager->FindCollisionObjects("boss_shoot_collision");
	for (auto& collision : collisionList_ShootAttack) {
		if (collision->IsHit(m_collision)) {
			//ダメージ
			ChangeState(Player::enState_Damage);
			m_testHP -= SHOOTATTACKDAMAGE;
			//クールタイム
			m_hitCoolTime = HITCOOLTIME;
			//ダメージ中に動かないように
			m_moveSpeed = Vector3::Zero;
			//ブレスの判定を消す
			//コリジョンを消す+エフェクトを消す
			QueryGOs<Bullet>("bullet", [&](Bullet* Shoot) {
				Shoot->Dead();
				Shoot->OnDeadEffect();
				return true;
				});
			//HP_UIを減らす表示
			m_player_HP_UI->DecreaseHP(SHOOTATTACKDAMAGE);
			return;
		}
	}
}
void Player::TakeAim(float maximum, float smallest)
{
	Vector3 NearenemyPosition;
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

	Vector3 diff = m_pos - NearenemyPosition;
	//プレイヤーとエネミーが一定以上離れていたら
	//ターゲッティングしない
	//近すぎてもターゲッティングしない
	if (diff.Length() >= maximum || diff.Length() <= smallest)
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
	//m_spriteRender.SetPosition(Vector3(screenPosition.x, screenPosition.y, 0.0f));
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
	//ロックオンする
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_isLockOn = true;
		m_targetCount++;
		m_count++;
	}
	//ロックオンを戻す
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
void Player::LongAttack(float hitstartframe, float hitendframe, float effect_speed)
{
	//ダメージステート中ならreturn
	if (m_state == enState_Damage || m_state == enState_Arching) {
		return;
	}

	//エフェクトのポインターが残ってて
	//エフェクトが消えていたら
	//nullptrにする
	if (effectEmitter != nullptr)
	{
		if (effectEmitter->IsDead())
		{
			effectEmitter = nullptr;
		}
	}

	//エフェクトの軌道の計算
	Quaternion qRot;
	Vector3 diff = m_enemy_Boss->GetPos() - m_pos;
	diff.Normalize();
	Vector3 PosZ = Vector3::AxisZ;
	qRot.SetRotation(PosZ, diff);
	//クールタイム
	m_longAttackCoolTime -= g_gameTime->GetFrameDeltaTime();
	//クールタイムがあけているならtrue
	if (m_longAttackCoolTime <= 0) {
		//攻撃中ではなくLB1を押されたら
		if (g_pad[0]->IsTrigger(enButtonLB1)&&!m_isNowAttack) {
			ChangeState(Player::enState_LongAttack);
			effectEmitter = NewGO<EffectEmitter>(0, "long_attack");
			effectEmitter->Init(0);
			effectEmitter->SetScale(Vector3::One * 10.0f);
			effectEmitter->SetPosition(m_pos);
			//ボスに向かって飛ばすための回転クォータニオンを計算する
			//qRot.Apply(diff);
			effectEmitter->Play();
			m_isEffect = true;
			m_longAttackCoolTime = LONGATTACKCOOLTIME;
		}
	}		
	if (effectEmitter != nullptr) {
		effectEmitter->SetRotation(qRot);
	}
	//エフェクトカウンターを1フレームに1足す
	if (m_isEffect) {
		m_effectCount++;
	}

	//エフェクトカウンターが数値の間にあるなら当たり判定をつける
	if (m_effectCount >= hitstartframe && m_effectCount <= hitendframe) {
		//コリジョンオブジェクトを作成する
		auto collisionObject = NewGO<CollisionObject>(0);
		//座標をプレイヤーの少し前に設定
		if (m_effectCount == hitstartframe) {
			m_longAttackPos = m_pos;
		}
		//プレイヤーとボスの間の距離を求める
		Vector3 diff = m_enemy_Boss->GetPos() - m_pos;
		diff.Normalize();
		m_longAttackPos += diff * effect_speed;
		//球状のコリジョンを作成
		collisionObject->CreateSphere(m_longAttackPos,//座標
			qRot,//回転
			50.0f//半径
		);
		collisionObject->SetName("player_long_attack");
	}
	//カウントを超えたら0に戻す
	if (m_effectCount > hitendframe) {
		m_effectCount = 0;
		m_isEffect = false;
	}

	if (m_isEffect && m_effectCount <= hitstartframe) {
		//その場に止まらせる
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}
}
void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	if (m_isTakeAim == false)
	{
		return;
	}
	//m_spriteRender.Draw(rc);
}
