#include "stdafx.h"
#include "EnemyBase.h"
#include "BossPattern.h"
#include "Enemy_Boss.h"
#include "Player.h"
#include "Game.h"
#include "BossFlyPoint.h"
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
#include "BossState_Defence.h"
#include "BossState_Rest.h"
#include "Boss_Shoot.h"
#include "Boss_HP_UI.h"
#include "sound/SoundEngine.h"
#include "SoundManager.h"

#define START_POS_X 0.0f
#define START_POS_Y 0.0f
#define START_POS_Z 500.0f
#define SCALE 4.5f
#define BOSS_FORWARD 600.0f
#define COLLISION 600.0f
#define GUARDBREAK_DAMAGE 4.0f
#define BITATTACKDAMAGE 2.5f
#define LONGATTACKDAMAGE 3.5f
#define WALKATTACKDAMAGE 3.0f
#define HITCOOLTIME 1.5f
#define FINAL_PHASE 50.0f
#define DEFAULT_BATTLE_BGM 0.8f
//#define FLYATTACK_SPEED 5.0f
//#define DISTANCE_POS 1400.0f
//#define BITING_DISTANCE 1000.0f
//#define REST_DISTANCE 1200.0f
//#define COLLISION_TAIL 400.0f
//#define COLLISION_FLYATTACK 450.0f
//#define COLLISION_MELEE 300.0f
//#define COLLISION_DEFENCE 700.0f
//#define COLLISION_SCREAM 5500.0f
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
	//コリジョンの判定を移動させる
	m_collisionPos = m_pos;
	m_collisionPos.y += 300.0f;
	m_collisionPos.z -= 300.0f;
	//m_modelRender.SetPosition(m_collisionPos);
	//EffectEngine::GetInstance()->ResistEffect(2, u"Assets/Effect/Boss_Shoot_Start.efk");
	//EffectEngine::GetInstance()->ResistEffect(2, u"Assets/Effect/Boss_Shoot.efk");

	m_modelRender.SetPosition(m_pos);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);

	m_animationClipArray[enState_Idle_Animation].SetLoopFlag(true);
	m_animationClipArray[enState_Attack_Biting_Animation].SetLoopFlag(false);
	m_animationClipArray[enState_Attack_Shoot_Animation].SetLoopFlag(false);
	m_animationClipArray[enState_Attack_Tail_Animation].SetLoopFlag(false);
	m_animationClipArray[enState_Attack_Scream_Animation].SetLoopFlag(false);
	m_animationClipArray[enState_Attack_FlyShoot_Animation].SetLoopFlag(false);
	m_animationClipArray[enState_Damage_Animation].SetLoopFlag(false);
	m_animationClipArray[enState_Defence_Animation].SetLoopFlag(false);
	m_animationClipArray[enState_Defence_Counter_Animation].SetLoopFlag(true);
	m_animationClipArray[enState_Rest_Animation].SetLoopFlag(true);
	m_animationClipArray[enState_Move_Animation].SetLoopFlag(true);
	m_animationClipArray[enState_Die_Animation].SetLoopFlag(false);
	m_animationClipArray[enState_Fly_Animation].SetLoopFlag(true);
	m_animationClipArray[enState_Attack_Fly_Animation].SetLoopFlag(true);
	m_animationClipArray[enState_Takeoff_Animation].SetLoopFlag(false);
	m_animationClipArray[enState_Landing_Animation].SetLoopFlag(false);

		m_animationClipArray[enState_Idle_Animation].Load("Assets/animData/Dragon_Frag/Dragon_Idle.tka");
		m_animationClipArray[enState_Attack_Biting_Animation].Load("Assets/animData/Dragon_Frag/Dragon_adjcent.tka");
		m_animationClipArray[enState_Attack_Shoot_Animation].Load("Assets/animData/Dragon_Frag/Dragon_Shoot.tka");
		m_animationClipArray[enState_Attack_Tail_Animation].Load("Assets/animData/Dragon_Frag/Dragon_Tail.tka");
		m_animationClipArray[enState_Attack_Scream_Animation].Load("Assets/animData/Dragon_Frag/Dragon_Scream.tka");
		m_animationClipArray[enState_Attack_FlyShoot_Animation].Load("Assets/animData/Dragon_Frag/Dragon_FlyShoot.tka");
		m_animationClipArray[enState_Damage_Animation].Load("Assets/animData/Dragon_Frag/Dragon_Gethit.tka");
		m_animationClipArray[enState_Defence_Animation].Load("Assets/animData/Dragon_Frag/Dragon_Defense.tka");
		m_animationClipArray[enState_Defence_Counter_Animation].Load("Assets/animData/Dragon_Frag/Dragon_Defense_Counter.tka");
		m_animationClipArray[enState_Rest_Animation].Load("Assets/animData/Dragon_Frag/Dragon_Sleep.tka");
		m_animationClipArray[enState_Move_Animation].Load("Assets/animData/Dragon_Frag/Dragon_Walk.tka");
		m_animationClipArray[enState_Die_Animation].Load("Assets/animData/Dragon_Frag/Dragon_Die.tka");
		m_animationClipArray[enState_Fly_Animation].Load("Assets/animData/Dragon_Frag/Dragon_Fly.tka");
		m_animationClipArray[enState_Attack_Fly_Animation].Load("Assets/animData/Dragon_Frag/Dragon_Fly_Forward.tka");
		m_animationClipArray[enState_Takeoff_Animation].Load("Assets/animData/Dragon_Frag/Dragon_Takeoff.tka");
		m_animationClipArray[enState_Landing_Animation].Load("Assets/animData/Dragon_Frag/Dragon_Land.tka");

		m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
			OnAnimationEvent(clipName, eventName);
			});

	m_modelRender.Init("Assets/modelData/Dragon_Frog/Doragon.tkm", m_animationClipArray, enAnimClip_Num);
	//スケルトンをロード。
	//InitSkeleton();
	//アニメーションを初期化。
	
	////ボスのHPが30%以上の時BGMの読み込み
	//g_soundEngine->ResistWaveFileBank(1, "Assets/sound/Boss_Battle.wav");
	//m_bossButtle = NewGO<SoundSource>(1);
	//m_bossButtle->Init(1);
	//m_bossButtle->Play(true);
	//////ボス戦BGMの読み込み
	////g_soundEngine->ResistWaveFileBank(2, "Assets/sound/Boss_LastBattle.wav");
	//m_bossLastButtle = NewGO<SoundSource>(2);
	//////ボスの羽ばたきの読み込み
	////g_soundEngine->ResistWaveFileBank(3, "Assets/sound/Fly.wav");
	//m_fly = NewGO<SoundSource>(3);
	//////ボスの滑空突進の読み込み
	////g_soundEngine->ResistWaveFileBank(4, "Assets/sound/FlyAttack.wav");
	//m_flyAttack = NewGO<SoundSource>(4);
	//////ボスの着地の読み込み
	////g_soundEngine->ResistWaveFileBank(5, "Assets/sound/Landing.wav");
	//m_landing = NewGO<SoundSource>(5);
	//////咆哮の読み込み
	////g_soundEngine->ResistWaveFileBank(6, "Assets/sound/Scream.wav");
	//m_scream = NewGO<SoundSource>(6);
	//////ボスの尻尾攻撃の読み込み
	////g_soundEngine->ResistWaveFileBank(8, "Assets/sound/Tail.wav");
	//m_tail = NewGO<SoundSource>(8);

	//m_bossLastButtle = NewGO<SoundSource>(2);
	//m_bossButtle->Init(2);
	//m_bossButtle->Play(true);
	////ボスの読み込み
	//g_soundEngine->ResistWaveFileBank(2, "Assets/sound/Boss_LastBattle.wav");
	//m_bossButtle = NewGO<SoundSource>(2);
	//m_bossButtle->Init(2);
	//m_bossButtle->Play(true);
	//ボスの咆哮の読み込み
	////尻尾攻撃のエフェクト
	//EffectEngine::GetInstance()->ResistEffect(3, u"Assets/Effect/Boss_Tail.efk");
			//BGMの再生
	g_soundManager->InitAndPlaySoundSource(enSoundBoss, DEFAULT_BATTLE_BGM, false, true, true);

	//InitAnimation();
	m_player = FindGO<Player>("player");
	m_player->AddEnemy_List(this);
	m_game = FindGO<Game>("game");
	m_boss_HP_UI = FindGO<Boss_HP_UI>("boss_hp_ui");
	m_boss_Shoot = NewGO<Boss_Shoot>(0, "boss_shoot");
	//コリジョンの作成
	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateSphere(m_collisionPos, Quaternion::Identity, COLLISION);
	m_collision->SetIsEnableAutoDelete(false);
	m_collision->SetName("boss");
	m_collision->SetIsEnable(true);
	m_rotation.SetRotationY(135.0f);
	//スタート位置
	m_pos = { START_POS_X, START_POS_Y, START_POS_Z };
	//最初のステートはIdleに
	ChangeState(enState_Idle);
	m_charaCon.Init(500.0f, 10.0f, m_pos);


	//空を飛んでいるときのボーンを受け取る
	m_flyBoneId = m_modelRender.FindBoneID(L"ValleyFat");
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
void Enemy_Boss::Rotation(float rotation)
{
	if (fabsf(m_moveSpeed.x) < rotation
		&& fabsf(m_moveSpeed.z) < rotation) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下の時
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	m_modelRender.SetRotation(m_rotation);
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}
//void Enemy_Boss::FlyAttackMove()
//{
//	if (m_state!=enState_Attack_Fly)
//	{
//		return;
//	}
//	//m_pos += m_moveSpeed * FLYATTACK_SPEED;
//	////プレイヤーの追跡の変数
//	//m_distance = m_player->Get_PlayerPos() - m_pos;
//	//m_diff = m_player->Get_PlayerPos() - m_pos;
//	//m_diff.Normalize();
//}
//void Enemy_Boss::Shoot(int movespeed, int hitstartframe, int hitendframe)
//{
//	///
//	Quaternion qRot;
//	Vector3 diff = m_player->Get_PlayerPos() - m_pos;
//	diff.Normalize();
//	Vector3 PosZ = Vector3::AxisZ;
//	qRot.SetRotation(PosZ, diff);
//	///
//
//	//if (m_shootPos.Length() <= 150.0f) {
//	//	EffectEmitter* Boss_Shoot = NewGO<EffectEmitter>(3, "boss_shoot");
//	//	Boss_Shoot->Init(3);
//	//	Boss_Shoot->SetScale(Vector3::One * 10.0f);
//	//	Boss_Shoot->SetPosition(diff);
//	//	Boss_Shoot->Play();
//	//}
//	if (m_state != enState_Attack_Shoot) {
//		return;
//	}
//		if (!m_isShoot) {
//			Boss_Shoot_Start = NewGO<EffectEmitter>(2, "boss_shoot");
//			Boss_Shoot_Start->Init(2);
//			Boss_Shoot_Start->SetScale(Vector3::One * 10.0f);
//			Boss_Shoot_Start->SetPosition(m_pos);
//			Boss_Shoot_Start->Play();
//			m_isShoot = true;
//			//エフェクトカウンターが数値の間にあるなら当たり判定をつける
//			if (m_effectCount <= 0) {
//				if (Boss_Shoot_Start != nullptr) {
//					Boss_Shoot_Start->SetRotation(qRot);
//				}
//			}
//			//ブレスのロックオン
//			m_moveSpeed_Shoot = m_player->Get_PlayerPos() - m_pos;
//			m_shootPos = m_moveSpeed_Shoot;
//			m_moveSpeed_Shoot.Normalize();
//			m_effectCount++;
//		}
//		m_shot += m_moveSpeed_Shoot * movespeed;
//		//コリジョンオブジェクトを作成する
//		m_shootCollision = NewGO<CollisionObject>(0);
//		//球状のコリジョンを作成
//		m_shootCollision->CreateSphere(m_shot,//座標
//			qRot,//回転
//			50.0f//半径
//		);
//		m_shootCollision->SetName("boss_shot");
//}
void Enemy_Boss::Rest()
{
	
}
void Enemy_Boss::Hit(float damagemagnification)
{
	//ヒット時のクールタイム
	m_hitCoolTime -= g_gameTime->GetFrameDeltaTime();

	//必殺技のための移動
	//その時は必殺技優先
	if (m_testHP <= FINAL_PHASE && !m_isScream) {
		return;
	}
	//必殺技中
	//攻撃を受けているときはreturn
	if (m_state == enState_Attack_Scream||m_state == enState_Damage || m_state == enState_Defence) {
		return;
	}
	//ヒット時ならreturn
	if (m_hitCoolTime >= 0) {
		return;
	}

	//攻撃コリジョンと衝突しているかを調べる
	//咆哮後の隙の時
	if (m_state == enState_Rest) {
		//ガードブレイクが当たった時
		const auto& collisionList_GuardBreak = g_collisionObjectManager->FindCollisionObjects("player_guardbreak" /*"player_walk_attack" "player_biting_attack"*/);

		for (auto& collision_GuardBreak : collisionList_GuardBreak) {
			if (collision_GuardBreak->IsHit(m_collision)) {
				//ダメージ
				ChangeState(enState_Damage);
				m_hitCoolTime = HITCOOLTIME;
				m_testHP -= GUARDBREAK_DAMAGE * damagemagnification;
				//HP_UIを減らす表示
				m_boss_HP_UI->DecreaseHP(GUARDBREAK_DAMAGE * damagemagnification);
				return;
			}
		}
		//ダッシュアタックが当たった時
		const auto& collisionList_WalkAttack = g_collisionObjectManager->FindCollisionObjects/*("player_guardbreak"*/("player_walk_attack" /*"player_biting_attack"*/);

		for (auto& collision_WalkAttack : collisionList_WalkAttack) {
			if (collision_WalkAttack->IsHit(m_collision)) {
				//ダメージ
				ChangeState(enState_Damage);
				m_hitCoolTime = HITCOOLTIME;
				m_testHP -= WALKATTACKDAMAGE * damagemagnification;
				//HP_UIを減らす表示
				m_boss_HP_UI->DecreaseHP(WALKATTACKDAMAGE * damagemagnification);
				return;
			}
		}
		//近接攻撃が当たった時
		const auto& collisionList_MeleeAttack = g_collisionObjectManager->FindCollisionObjects(/*"player_guardbreak"*/ /*"player_walk_attack"*/ "player_biting_attack");

		for (auto& collision_MeleeAttack : collisionList_MeleeAttack) {
			if (collision_MeleeAttack->IsHit(m_collision)) {
				//ダメージ
				ChangeState(enState_Damage);
				m_hitCoolTime = HITCOOLTIME;
				m_testHP -= BITATTACKDAMAGE * damagemagnification;
				//HP_UIを減らす表示
				m_boss_HP_UI->DecreaseHP(BITATTACKDAMAGE * damagemagnification);
				return;
			}
		}
		//遠距離攻撃が当たった時
		const auto& collisionList_LongAttack = g_collisionObjectManager->FindCollisionObjects(/*"player_guardbreak"*/ /*"player_walk_attack"*/ "player_long_attack");

		for (auto& collisionLongAttack : collisionList_LongAttack) {
			if (collisionLongAttack->IsHit(m_collision)) {
				//ダメージ
				ChangeState(enState_Damage);
				m_hitCoolTime = HITCOOLTIME;
				m_testHP -= LONGATTACKDAMAGE * damagemagnification;
				//HP_UIを減らす表示
				m_boss_HP_UI->DecreaseHP(LONGATTACKDAMAGE * damagemagnification);
				return;
			}
		}
	}
	//通常時
	//ガードブレイクが当たった時
	const auto& collisionList_GuardBreak = g_collisionObjectManager->FindCollisionObjects("player_guardbreak" /*"player_walk_attack" "player_biting_attack"*/);

	for (auto& collision_GuardBreak : collisionList_GuardBreak) {
		if (collision_GuardBreak->IsHit(m_collision)) {
			//ダメージ
			ChangeState(enState_Damage);
			m_hitCoolTime = HITCOOLTIME;
			m_testHP -= GUARDBREAK_DAMAGE;
			//HP_UIを減らす表示
			m_boss_HP_UI->DecreaseHP(GUARDBREAK_DAMAGE);
			return;
		}
	}
	//ダッシュアタックが当たった時
	const auto& collisionList_WalkAttack = g_collisionObjectManager->FindCollisionObjects/*("player_guardbreak"*/("player_walk_attack" /*"player_biting_attack"*/);

	for (auto& collision_WalkAttack : collisionList_WalkAttack) {
		if (collision_WalkAttack->IsHit(m_collision)) {
			//ダメージ
			ChangeState(enState_Damage);
			m_hitCoolTime = HITCOOLTIME;
			m_testHP -= WALKATTACKDAMAGE;
			//HP_UIを減らす表示
			m_boss_HP_UI->DecreaseHP(WALKATTACKDAMAGE);
			return;
		}
	}
	//近接攻撃が当たった時
	const auto& collisionList_MeleeAttack = g_collisionObjectManager->FindCollisionObjects(/*"player_guardbreak"*/ /*"player_walk_attack"*/ "player_biting_attack");

	for (auto& collision_MeleeAttack : collisionList_MeleeAttack) {
		if (collision_MeleeAttack->IsHit(m_collision)) {
			//ダメージ
			ChangeState(enState_Damage);
			m_hitCoolTime = HITCOOLTIME;
			m_testHP -= BITATTACKDAMAGE;
			//HP_UIを減らす表示
			m_boss_HP_UI->DecreaseHP(BITATTACKDAMAGE);
			return;
		}
	}
	//遠距離攻撃が当たった時
	const auto& collisionList_LongAttack = g_collisionObjectManager->FindCollisionObjects(/*"player_guardbreak"*/ /*"player_walk_attack"*/ "player_long_attack");

	for (auto& collisionLongAttack : collisionList_LongAttack) {
		if (collisionLongAttack->IsHit(m_collision)) {
			//ダメージ
			m_hitCoolTime = HITCOOLTIME;
			m_testHP -= LONGATTACKDAMAGE;
			//HP_UIを減らす表示
			m_boss_HP_UI->DecreaseHP(LONGATTACKDAMAGE);
			return;
		}
	}

}
void Enemy_Boss::MeleeAttack()
{
	if (m_isUnderAttackMelee) {
		//噛みつき用のコリジョンの作成
		MeleeAttackCollision(300.0f);
	}
}
void Enemy_Boss::Shoot()
{
	m_boss_Shoot->Init(this);
	m_boss_Shoot->Update();
}
void Enemy_Boss::MeleeAttackCollision(float collision_melee)
{
	//コリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//座標をボスの少し前に設定
	collisionPosition += m_forward * BOSS_FORWARD;
	//球状のコリジョンを作成
	collisionObject->CreateSphere(collisionPosition,//座標
		Quaternion::Identity,//回転
		collision_melee//半径
	);
	collisionObject->SetName("boss_attack_melee");

}
void Enemy_Boss::TailAttack()
{
	if (m_state != enState_Attack_Tail) {
		return;
	}
	if (m_isUnderTail) {
		//m_tailEffectPos = m_forward;
		TailAttackCollision(400.0f);
		if (m_isSound) {
			//音再生
			g_soundManager->InitAndPlaySoundSource(
				enSoundTail,
				g_soundManager->GetSEVolume()
			);
		}
		//m_tailEffect = { 90.0f,0.0f,0.0f,0.0f };
		//m_tailEffect.AddRotationY(1.0f);
		//m_tailEffect.Apply(m_tailEffectPos);
		//エフェクト
		//m_boss_Tail = NewGO<EffectEmitter>(3, "boss_tail");
		//m_boss_Tail->Init(3);
		//m_boss_Tail->SetScale(Vector3::One * 10.0f);
		//m_boss_Tail->SetPosition(m_forward *BOSS_FORWARD);
		//m_boss_Tail->Play();
		////m_boss_Tail->SetRotation(m_tailEffect);
		//// エフェクト死亡時のイベント処理
		//m_onDeadEventFunction = [&] { m_boss_Tail = nullptr; };
		//// イベントを登録
		//m_boss_Tail->AddDeadEventFunction(m_onDeadEventFunction);

	}
}
void Enemy_Boss::TailAttackCollision(float collision_tail)
{
	//コリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//座標をボスの少し前に設定
	collisionPosition += m_forward * BOSS_FORWARD;
	//球状のコリジョンを作成
	collisionObject->CreateSphere(collisionPosition,//座標
		Quaternion::Identity,//回転
		collision_tail//半径
	);
	collisionObject->SetName("boss_attack_tail");
}
void Enemy_Boss::FlyAttack(float movespeed)
{
	if (m_state != enState_Attack_Fly) {
		return;
	}
	if (m_isUnderFlyAttack) {
		FlyAttackCollision(450.0f);
		if (m_isSound) {
			//音再生
			g_soundManager->InitAndPlaySoundSource(
				enSoundFlyAttack,
				g_soundManager->GetSEVolume()
			);
			m_isSound=false;		}
	}
	else {
		g_soundManager->StopSound(enSoundFlyAttack);
	}
	Vector3 diff = m_player->Get_PlayerPos() - m_pos;
	diff.Normalize();
	m_moveSpeed = diff * movespeed;
}
void Enemy_Boss::FlyAttackCollision(float collision_flyattack)
{
	//コリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//座標をボスの少し前に設定
	
	//球状のコリジョンを作成
	collisionObject->CreateSphere(collisionPosition,//座標
		Quaternion::Identity,//回転
		collision_flyattack//半径
	);
	collisionObject->SetName("boss_attack_fly");
}
void Enemy_Boss::Defence()
{
	if (m_state!=enState_Defence) {
		return;
	}
	DefenceCollision(1.5f,550.0f);

}
void Enemy_Boss::DefenceCollision(float break_magnification, float collision_defense)
{
	//コリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//座標をボスの少し前に設定
	//collisionPosition;
	//球状のコリジョンを作成
	collisionObject->CreateSphere(collisionPosition,//座標
		Quaternion::Identity,//回転
		collision_defense//半径
	);
	collisionObject->SetName("boss_defence");

	if (m_hitCoolTime >= 0) {
		return;
	}

	// 攻撃コリジョンと衝突しているかを調べる
	//ガードブレイク時はダメージが増える
	const auto& collisionList_GuardBreak = g_collisionObjectManager->FindCollisionObjects("player_guardbreak" /*"player_walk_attack" "player_biting_attack"*/);

	for (auto& collision_GuardBreak : collisionList_GuardBreak) {
		if (collision_GuardBreak->IsHit(collisionObject)) {
			//ダメージ
			ChangeState(enState_Damage);
			m_testHP -= GUARDBREAK_DAMAGE * break_magnification;
			//HP_UIを減らす表示
			m_boss_HP_UI->DecreaseHP(GUARDBREAK_DAMAGE * break_magnification);
			m_hitCoolTime = HITCOOLTIME;
			return;
		}
	}
	const auto& collisionList_WalkAttack = g_collisionObjectManager->FindCollisionObjects/*("player_guardbreak"*/("player_walk_attack" /*"player_biting_attack"*/);

	for (auto& collision_WalkAttack : collisionList_WalkAttack) {
		if (collision_WalkAttack->IsHit(collisionObject)) {
			//ダメージは０でカウンター
			ChangeState(enState_Attack_Biting);
			m_player->ChangeState(Player::enState_Arching);
			m_hitCoolTime = HITCOOLTIME;
			return;
		}
	}
	const auto& collisionList_MeleeAttack = g_collisionObjectManager->FindCollisionObjects(/*"player_guardbreak"*/ /*"player_walk_attack"*/ "player_biting_attack");

	for (auto& collision_MeleeAttack : collisionList_MeleeAttack) {
		if (collision_MeleeAttack->IsHit(collisionObject)) {
			//ダメージは０でカウンター
			ChangeState(enState_Attack_Tail);
			m_player->ChangeState(Player::enState_Arching);
			m_hitCoolTime = HITCOOLTIME;
			return;
		}
	}

	const auto& collisionList_LongAttack = g_collisionObjectManager->FindCollisionObjects(/*"player_guardbreak"*/ /*"player_walk_attack"*/ "player_long_attack");

	for (auto& collisionLongAttack : collisionList_LongAttack) {
		if (collisionLongAttack->IsHit(collisionObject)) {
			//ダメージは０でカウンター
			ChangeState(enState_Attack_Shoot);
			m_hitCoolTime = HITCOOLTIME;
			return;
		}
	}


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

	//キーの名前がBoss_Defence_startの場合
	if (wcscmp(eventName, L"Boss_Defence_start") == 0)
	{
		//防御中にする
		m_isUnderDefence = true;
	}

	//キーの名前がBoss_Attack_Scream_startの場合
	if (wcscmp(eventName, L"Boss_Attack_Scream_start") == 0)
	{
		//攻撃中にする
		m_isUnderScream = true;
	}
	//キーの名前がBoss_Attack_Scream_endの場合
	else if (wcscmp(eventName, L"Boss_Attack_Scream_end") == 0)
	{
		//攻撃を終わる
		m_isUnderScream = false;
	}

	//キーの名前がBoss_Landing_startの場合
	if (wcscmp(eventName, L"Boss_Landing_start") == 0)
	{
		//攻撃中にする
		m_isUnderLanding = true;
	}
	//キーの名前がBoss_Landing_endの場合
	else if (wcscmp(eventName, L"Boss_Landing_end") == 0)
	{
		//攻撃を終わる
		m_isUnderLanding = false;
	}

	//キーの名前がBoss_Fly_startの場合
	if (wcscmp(eventName, L"Boss_Fly_start") == 0)
	{
		//飛行中にする
		m_isUnderFly = true;
	}
	//キーの名前がBoss_Fly_endの場合
	else if (wcscmp(eventName, L"Boss_Fly_end") == 0)
	{
		//飛行を終わる
		m_isUnderFly = false;
	}

	//キーの名前がBoss_Takeoff_endの場合
	if (wcscmp(eventName, L"Boss_Takeoff_end") == 0)
	{
		//飛行中にする
		m_isUnderTakeoff = true;
	}

}
void Enemy_Boss::FlyPos(float movespeed)
{
	if (m_state != enState_Fly||m_isFly_Set) {
		return;
	}
	if (!m_isFlyKeepDistance){
		BossFlyPoint::FlyPoint* flypoint;
		flypoint = m_game->GetBossFlyPoint()->GetFlyPoint(m_pos);
		//ボスからフライポイントに向かうベクトルを求める
		diff = flypoint->m_pos - m_pos;
		//ベクトルのNormalizeする
		diff.Normalize();
		m_isFlyKeepDistance = true;
	}
	if (m_isSound) {
		//音再生
		g_soundManager->InitAndPlaySoundSource(
			enSoundFly,
			g_soundManager->GetSEVolume()
		);
		m_isSound = false;
	}
	//移動速度をいれる
	m_moveSpeed = diff * movespeed;
}
void Enemy_Boss::Scream()
{

	if (m_state != enState_Attack_Scream) {
		return;
	}
	if (m_isUnderScream) {
		ScreamCollision(5500.0f);
		if (m_isSound) {
			//音再生
			g_soundManager->InitAndPlaySoundSource(
				enSoundScream,
				g_soundManager->GetSEVolume()
			);
			m_isSound = false;
		}
	}
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_isScream = true;
}
void Enemy_Boss::ScreamCollision(float collision_scream)
{
	//コリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//球状のコリジョンを作成
	collisionObject->CreateSphere(collisionPosition,//座標
		Quaternion::Identity,//回転
		collision_scream//半径
	);
	collisionObject->SetName("boss_attack_scream");

}
void Enemy_Boss::Landing()
{
	if (m_state != enState_Landing) {
		return;
	}
	if (m_isUnderLanding) {
		LandingDamage(500);
		if (m_isSound) {
			//音再生
			g_soundManager->InitAndPlaySoundSource(
				enSoundLanding,
				g_soundManager->GetSEVolume()
			);
			m_isSound = false;
		}
	}
}
void Enemy_Boss::LandingDamage(float collision_landing)
{
	//コリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//球状のコリジョンを作成
	collisionObject->CreateSphere(collisionPosition,//座標
		Quaternion::Identity,//回転
		collision_landing//半径
	);
	collisionObject->SetName("boss_attack_landing");
}
void Enemy_Boss::FlyShoot()
{
	if (m_isUnderTakeoff) {
		m_moveSpeed = Vector3::Zero;
		m_moveSpeed = m_diff;
		m_isUnderTakeoff = false;
	}
}
void Enemy_Boss::ChangeState(EnState changeState, int integerArgument0)
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
		m_Iboss_State = new BossState_Defence(this);
		break;
	case Enemy_Boss::enState_Rest:
		m_Iboss_State = new BossState_Rest(this);
		break;
	case Enemy_Boss::enState_Move:
		m_Iboss_State = new BossState_Walk(this);
		break;
	case Enemy_Boss::enState_Takeoff:
		m_Iboss_State = new BossState_Takeoff(this, (EnState)integerArgument0);
		break;
	case Enemy_Boss::enState_Fly:
		m_Iboss_State = new BossState_Fly(this, (EnState)integerArgument0);
		break;
	case Enemy_Boss::enState_Landing:
		m_Iboss_State = new BossState_Landing(this);
		break;
	case Enemy_Boss::enState_Attack_Fly:
		m_Iboss_State = new BossState_FlyAttack(this,(EnState)integerArgument0);
		break;
	case Enemy_Boss::enState_Die:
		m_Iboss_State = new BossState_Die(this);
		break;
	}
	m_state = changeState;
}
void Enemy_Boss::Update()
{
	//m_pos += m_moveSpeed * g_gameTime->GetFrameDeltaTime();//動きを一定にするため
	m_Iboss_State->Animation();
	m_Iboss_State->Update();
	Rotation(0.001f);
	Hit(2.5f);
	FlyShoot();
	MeleeAttack();
	TailAttack();
	Defence(); 
	FlyPos(300.0f);
	FlyAttack(800.0f);
	Scream();
	Landing();
	//BGM();
	Shoot();
	m_modelRender.SetRotation(m_rotation);
	m_skeleton.Update(m_model.GetWorldMatrix());

	//ボーンの座標を受け取るプログラム
	Matrix matrix = m_modelRender.GetBone(m_flyBoneId)->GetWorldMatrix();
	float boneYPos = matrix.m[3][1];
	m_charaCon.SetPosition({ m_charaCon.GetPosition().x, boneYPos-350.0f, m_charaCon.GetPosition().z });
	m_moveSpeed.y = 0.0f;
	m_pos = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_pos.y = 0.0f;
	//m_charaCon.SetPosition(m_pos);
	//コリジョンの当たり判定
	//m_collision->SetPosition(m_collisionPos);
	//m_collision->Update();
	
	m_collision->SetPosition(m_pos);
	m_collision->SetRotation(m_rotation);
	m_collision->SetWorldMatrix(matrix);
	m_collision->Update();
	m_modelRender.SetPosition(m_pos);
	m_modelRender.Update();
}
void Enemy_Boss::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
}
