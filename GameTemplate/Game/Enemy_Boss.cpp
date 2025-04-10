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
namespace
{
}

void Enemy_Boss::InitSkeleton()
{
	//m_skeleton.Init("Aseets/modelData/Chest/Chest.tks");
}
bool Enemy_Boss::Start()
{
	const Vector3 m_scale = { SCALE,SCALE,SCALE }; //�傫��
	//�R���W�����̔�����ړ�������
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
			//BGM�̍Đ�
	g_soundManager->InitAndPlaySoundSource(enSoundBoss, DEFAULT_BATTLE_BGM, false, true, true);

	m_player = FindGO<Player>("player");
	m_player->AddEnemy_List(this);
	m_game = FindGO<Game>("game");
	m_boss_HP_UI = FindGO<Boss_HP_UI>("boss_hp_ui");
	m_boss_Shoot = NewGO<Boss_Shoot>(0, "boss_shoot");
	//�R���W�����̍쐬
	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateSphere(m_collisionPos, Quaternion::Identity, COLLISION);
	m_collision->SetIsEnableAutoDelete(false);
	m_collision->SetName("boss");
	m_collision->SetIsEnable(true);
	m_rotation.SetRotationY(135.0f);
	//�X�^�[�g�ʒu
	m_pos = { START_POS_X, START_POS_Y, START_POS_Z };
	//�ŏ��̃X�e�[�g��Idle��
	ChangeState(enState_Idle);
	m_charaCon.Init(500.0f, 10.0f, m_pos);


	//�����ł���Ƃ��̃{�[�����󂯎��
	m_flyBoneId = m_modelRender.FindBoneID(L"ValleyFat");
	return true;
}
void Enemy_Boss::InitAnimation()
{
	m_animation.Init(
		m_skeleton,			//�A�j���[�V�����𗬂����ރX�P���g���B
		m_animationClipArray,	//�A�j���[�V�����N���b�v�B
		enAnimClip_Num		//�A�j���[�V�����̐��B
	);
	//�A�j���[�V������i�߂�B
	m_animation.Progress(g_gameTime->GetFrameDeltaTime());
}
void Enemy_Boss::Rotation(float rotation)
{
	if (fabsf(m_moveSpeed.x) < rotation
		&& fabsf(m_moveSpeed.z) < rotation) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��̎�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	m_modelRender.SetRotation(m_rotation);
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}
void Enemy_Boss::Rest()
{
	
}
void Enemy_Boss::Hit(float damagemagnification)
{
	//�q�b�g���̃N�[���^�C��
	m_hitCoolTime -= g_gameTime->GetFrameDeltaTime();

	//�K�E�Z�̂��߂̈ړ�
	//���̎��͕K�E�Z�D��
	if (m_testHP <= FINAL_PHASE && !m_isScream) {
		return;
	}
	//�K�E�Z��
	//�U�����󂯂Ă���Ƃ���return
	if (m_state == enState_Attack_Scream||m_state == enState_Damage || m_state == enState_Defence) {
		return;
	}
	//�q�b�g���Ȃ�return
	if (m_hitCoolTime >= 0) {
		return;
	}

	//�U���R���W�����ƏՓ˂��Ă��邩�𒲂ׂ�
	//���K��̌��̎�
	if (m_state == enState_Rest) {
		//�K�[�h�u���C�N������������
		const auto& collisionList_GuardBreak = g_collisionObjectManager->FindCollisionObjects("player_guardbreak");

		for (auto& collision_GuardBreak : collisionList_GuardBreak) {
			if (collision_GuardBreak->IsHit(m_collision)) {
				//�_���[�W
				ChangeState(enState_Damage);
				m_hitCoolTime = HITCOOLTIME;
				m_testHP -= GUARDBREAK_DAMAGE * damagemagnification;
				//HP_UI�����炷�\��
				m_boss_HP_UI->DecreaseHP(GUARDBREAK_DAMAGE * damagemagnification);
				return;
			}
		}
		//�_�b�V���A�^�b�N������������
		const auto& collisionList_WalkAttack = g_collisionObjectManager->FindCollisionObjects("player_walk_attack");

		for (auto& collision_WalkAttack : collisionList_WalkAttack) {
			if (collision_WalkAttack->IsHit(m_collision)) {
				//�_���[�W
				ChangeState(enState_Damage);
				m_hitCoolTime = HITCOOLTIME;
				m_testHP -= WALKATTACKDAMAGE * damagemagnification;
				//HP_UI�����炷�\��
				m_boss_HP_UI->DecreaseHP(WALKATTACKDAMAGE * damagemagnification);
				return;
			}
		}
		//�ߐڍU��������������
		const auto& collisionList_MeleeAttack = g_collisionObjectManager->FindCollisionObjects("player_biting_attack");

		for (auto& collision_MeleeAttack : collisionList_MeleeAttack) {
			if (collision_MeleeAttack->IsHit(m_collision)) {
				//�_���[�W
				ChangeState(enState_Damage);
				m_hitCoolTime = HITCOOLTIME;
				m_testHP -= BITATTACKDAMAGE * damagemagnification;
				//HP_UI�����炷�\��
				m_boss_HP_UI->DecreaseHP(BITATTACKDAMAGE * damagemagnification);
				return;
			}
		}
		//�������U��������������
		const auto& collisionList_LongAttack = g_collisionObjectManager->FindCollisionObjects("player_long_attack");

		for (auto& collisionLongAttack : collisionList_LongAttack) {
			if (collisionLongAttack->IsHit(m_collision)) {
				//�_���[�W
				ChangeState(enState_Damage);
				m_hitCoolTime = HITCOOLTIME;
				m_testHP -= LONGATTACKDAMAGE * damagemagnification;
				//HP_UI�����炷�\��
				m_boss_HP_UI->DecreaseHP(LONGATTACKDAMAGE * damagemagnification);
				return;
			}
		}
	}
	//�ʏ펞
	//�K�[�h�u���C�N������������
	const auto& collisionList_GuardBreak = g_collisionObjectManager->FindCollisionObjects("player_guardbreak");

	for (auto& collision_GuardBreak : collisionList_GuardBreak) {
		if (collision_GuardBreak->IsHit(m_collision)) {
			//�_���[�W
			ChangeState(enState_Damage);
			m_hitCoolTime = HITCOOLTIME;
			m_testHP -= GUARDBREAK_DAMAGE;
			//HP_UI�����炷�\��
			m_boss_HP_UI->DecreaseHP(GUARDBREAK_DAMAGE);
			return;
		}
	}
	//�_�b�V���A�^�b�N������������
	const auto& collisionList_WalkAttack = g_collisionObjectManager->FindCollisionObjects("player_walk_attack");

	for (auto& collision_WalkAttack : collisionList_WalkAttack) {
		if (collision_WalkAttack->IsHit(m_collision)) {
			//�_���[�W
			ChangeState(enState_Damage);
			m_hitCoolTime = HITCOOLTIME;
			m_testHP -= WALKATTACKDAMAGE;
			//HP_UI�����炷�\��
			m_boss_HP_UI->DecreaseHP(WALKATTACKDAMAGE);
			return;
		}
	}
	//�ߐڍU��������������
	const auto& collisionList_MeleeAttack = g_collisionObjectManager->FindCollisionObjects("player_biting_attack");

	for (auto& collision_MeleeAttack : collisionList_MeleeAttack) {
		if (collision_MeleeAttack->IsHit(m_collision)) {
			//�_���[�W
			ChangeState(enState_Damage);
			m_hitCoolTime = HITCOOLTIME;
			m_testHP -= BITATTACKDAMAGE;
			//HP_UI�����炷�\��
			m_boss_HP_UI->DecreaseHP(BITATTACKDAMAGE);
			return;
		}
	}
	//�������U��������������
	const auto& collisionList_LongAttack = g_collisionObjectManager->FindCollisionObjects("player_long_attack");

	for (auto& collisionLongAttack : collisionList_LongAttack) {
		if (collisionLongAttack->IsHit(m_collision)) {
			//�_���[�W
			m_hitCoolTime = HITCOOLTIME;
			m_testHP -= LONGATTACKDAMAGE;
			//HP_UI�����炷�\��
			m_boss_HP_UI->DecreaseHP(LONGATTACKDAMAGE);
			return;
		}
	}

}
void Enemy_Boss::MeleeAttack()
{
	if (m_isUnderAttackMelee) {
		//���݂��p�̃R���W�����̍쐬
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
	//�R���W�����I�u�W�F�N�g���쐬����
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//���W���{�X�̏����O�ɐݒ�
	collisionPosition += m_forward * BOSS_FORWARD;
	//����̃R���W�������쐬
	collisionObject->CreateSphere(collisionPosition,//���W
		Quaternion::Identity,//��]
		collision_melee//���a
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
			//���Đ�
			g_soundManager->InitAndPlaySoundSource(
				enSoundTail,
				g_soundManager->GetSEVolume()
			);
		}
	}
}
void Enemy_Boss::TailAttackCollision(float collision_tail)
{
	//�R���W�����I�u�W�F�N�g���쐬����
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//���W���{�X�̏����O�ɐݒ�
	collisionPosition += m_forward * BOSS_FORWARD;
	//����̃R���W�������쐬
	collisionObject->CreateSphere(collisionPosition,//���W
		Quaternion::Identity,//��]
		collision_tail//���a
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
			//���Đ�
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
	//�R���W�����I�u�W�F�N�g���쐬����
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//���W���{�X�̏����O�ɐݒ�
	
	//����̃R���W�������쐬
	collisionObject->CreateSphere(collisionPosition,//���W
		Quaternion::Identity,//��]
		collision_flyattack//���a
	);
	collisionObject->SetName("boss_attack_fly");
}
void Enemy_Boss::Defence()
{
	if (m_state!=enState_Defence) {
		return;
	}
	DefenceCollision(1.5f,550.0f, 700.0f,Vector3::Zero);

}
void Enemy_Boss::DefenceCollision(float break_magnification, float collision_defense, float tailknockback,Vector3 knockback)
{
	//�R���W�����I�u�W�F�N�g���쐬����
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//���W���{�X�̏����O�ɐݒ�
	//collisionPosition;
	//����̃R���W�������쐬
	collisionObject->CreateSphere(collisionPosition,//���W
		Quaternion::Identity,//��]
		collision_defense//���a
	);
	collisionObject->SetName("boss_defence");

	if (m_hitCoolTime >= 0) {
		return;
	}

	// �U���R���W�����ƏՓ˂��Ă��邩�𒲂ׂ�
	//�K�[�h�u���C�N���̓_���[�W��������
	const auto& collisionList_GuardBreak = g_collisionObjectManager->FindCollisionObjects("player_guardbreak");

	for (auto& collision_GuardBreak : collisionList_GuardBreak) {
		if (collision_GuardBreak->IsHit(collisionObject)) {
			//�_���[�W
			ChangeState(enState_Damage);
			m_testHP -= GUARDBREAK_DAMAGE * break_magnification;
			//HP_UI�����炷�\��
			m_boss_HP_UI->DecreaseHP(GUARDBREAK_DAMAGE * break_magnification);
			m_hitCoolTime = HITCOOLTIME;
			return;
		}
	}
	const auto& collisionList_WalkAttack = g_collisionObjectManager->FindCollisionObjects("player_walk_attack");

	for (auto& collision_WalkAttack : collisionList_WalkAttack) {
		if (collision_WalkAttack->IsHit(collisionObject)) {
			//�_���[�W�͂O�ŃJ�E���^�[
			ChangeState(enState_Attack_Biting);
			m_player->ChangeState(Player::enState_Arching);
			m_hitCoolTime = HITCOOLTIME;
			return;
		}
	}
	const auto& collisionList_MeleeAttack = g_collisionObjectManager->FindCollisionObjects( "player_biting_attack");

	for (auto& collision_MeleeAttack : collisionList_MeleeAttack) {
		if (collision_MeleeAttack->IsHit(collisionObject)) {
			//�_���[�W�͂O�ŃJ�E���^�[
			ChangeState(enState_Attack_Tail);
			m_player->ChangeState(Player::enState_Arching);
		//	m_player->SetMoveSpeed(knockback * tailknockback);
			m_hitCoolTime = HITCOOLTIME;
			return;
		}
	}

	const auto& collisionList_LongAttack = g_collisionObjectManager->FindCollisionObjects("player_long_attack");

	for (auto& collisionLongAttack : collisionList_LongAttack) {
		if (collisionLongAttack->IsHit(collisionObject)) {
			//�_���[�W�͂O�ŃJ�E���^�[
			ChangeState(enState_Attack_Shoot);
			m_hitCoolTime = HITCOOLTIME;
			return;
		}
	}


}
void Enemy_Boss::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//�L�[�̖��O��Boss_Attack_Melee_start�̏ꍇ
	if (wcscmp(eventName, L"Boss_Attack_Melee_start") == 0)
	{
		//�U�����ɂ���
		m_isUnderAttackMelee = true;
	}
	//�L�[�̖��O��Boss_Attack_Melee_end�̏ꍇ
	else if (wcscmp(eventName, L"Boss_Attack_Melee_end") == 0)
	{
		//�U�����I���
		m_isUnderAttackMelee = false;
	}

	//�L�[�̖��O��Boss_Attack_Tail_start�̏ꍇ
	if (wcscmp(eventName, L"Boss_Attack_Tail_start") == 0)
	{
		//�U�����ɂ���
		m_isUnderTail = true;
	}
	//�L�[�̖��O��Boss_Attack_Tail_end�̏ꍇ
	else if (wcscmp(eventName, L"Boss_Attack_Tail_end") == 0)
	{
		//�U�����I���
		m_isUnderTail = false;
	}

	//�L�[�̖��O��FlyAttack_start�̏ꍇ
	if (wcscmp(eventName, L"FlyAttack_start") == 0)
	{
		//�U�����ɂ���
		m_isUnderFlyAttack = true;
	}
	//�L�[�̖��O��FlyAttack_end�̏ꍇ
	else if (wcscmp(eventName, L"FlyAttack_end") == 0)
	{
		//�U�����I���
		m_isUnderFlyAttack = false;
	}

	//�L�[�̖��O��Boss_Defense_start�̏ꍇ
	if (wcscmp(eventName, L"Boss_Defense_start") == 0)
	{
		//�h�䒆�ɂ���
		m_isUnderDefense = true;
	}

	//�L�[�̖��O��Boss_Attack_Scream_start�̏ꍇ
	if (wcscmp(eventName, L"Boss_Attack_Scream_start") == 0)
	{
		//�U�����ɂ���
		m_isUnderScream = true;
	}
	//�L�[�̖��O��Boss_Attack_Scream_end�̏ꍇ
	else if (wcscmp(eventName, L"Boss_Attack_Scream_end") == 0)
	{
		//�U�����I���
		m_isUnderScream = false;
	}

	//�L�[�̖��O��Boss_Landing_start�̏ꍇ
	if (wcscmp(eventName, L"Boss_Landing_start") == 0)
	{
		//�U�����ɂ���
		m_isUnderLanding = true;
	}
	//�L�[�̖��O��Boss_Landing_end�̏ꍇ
	else if (wcscmp(eventName, L"Boss_Landing_end") == 0)
	{
		//�U�����I���
		m_isUnderLanding = false;
	}

	//�L�[�̖��O��Boss_Fly_start�̏ꍇ
	if (wcscmp(eventName, L"Boss_Fly_start") == 0)
	{
		//��s���ɂ���
		m_isUnderFly = true;
	}
	//�L�[�̖��O��Boss_Fly_end�̏ꍇ
	else if (wcscmp(eventName, L"Boss_Fly_end") == 0)
	{
		//��s���I���
		m_isUnderFly = false;
	}

	//�L�[�̖��O��Boss_Takeoff_end�̏ꍇ
	if (wcscmp(eventName, L"Boss_Takeoff_end") == 0)
	{
		//��s���ɂ���
		m_isUnderTakeoff = true;
	}

}
void Enemy_Boss::FlyPos(float movespeed)
{
	if (m_state != enState_Fly||m_isFly_Set) {
		return;
	}
	//if (!m_isFlyKeepDistance){
		BossFlyPoint::FlyPoint* flypoint;
		flypoint = m_game->GetBossFlyPoint()->GetFlyPoint(m_pos);
		//�{�X����t���C�|�C���g�Ɍ������x�N�g�������߂�
		diff = m_pos-flypoint->m_pos;
		//�x�N�g����Normalize����
		diff.Normalize();
	//	m_isFlyKeepDistance = true;
	//}
	if (m_isSound) {
		//���Đ�
		g_soundManager->InitAndPlaySoundSource(
			enSoundFly,
			g_soundManager->GetSEVolume()
		);
		m_isSound = false;
	}
	//�ړ����x�������
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
			//���Đ�
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
	//�R���W�����I�u�W�F�N�g���쐬����
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//����̃R���W�������쐬
	collisionObject->CreateSphere(collisionPosition,//���W
		Quaternion::Identity,//��]
		collision_scream//���a
	);
	collisionObject->SetName("boss_attack_scream");

}
void Enemy_Boss::Landing()
{
	if (m_state != enState_Landing) {
		return;
	}
	if (m_isUnderLanding) {
		LandingColision(400);
		if (m_isSound) {
			//���Đ�
			g_soundManager->InitAndPlaySoundSource(
				enSoundLanding,
				g_soundManager->GetSEVolume()
			);
			m_isSound = false;
		}
	}
}
void Enemy_Boss::LandingColision(float collision_landing)
{
	//�R���W�����I�u�W�F�N�g���쐬����
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//����̃R���W�������쐬
	collisionObject->CreateSphere(collisionPosition,//���W
		Quaternion::Identity,//��]
		collision_landing//���a
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
	//m_pos += m_moveSpeed * g_gameTime->GetFrameDeltaTime();//���������ɂ��邽��
	m_Iboss_State->Animation();
	m_Iboss_State->Update();
	Rotation(0.001f);
	Hit(2.5f);
	FlyShoot();
	MeleeAttack();
	TailAttack();
	Landing();
	Defence(); 
	FlyPos(300.0f);
	FlyAttack(800.0f);
	Scream();
	//BGM();
	Shoot();
	m_modelRender.SetRotation(m_rotation);
	m_skeleton.Update(m_model.GetWorldMatrix());

	//�{�[���̍��W���󂯎��v���O����
	Matrix matrix = m_modelRender.GetBone(m_flyBoneId)->GetWorldMatrix();
	float boneYPos = matrix.m[3][1];
	m_charaCon.SetPosition({ m_charaCon.GetPosition().x, boneYPos-350.0f, m_charaCon.GetPosition().z });
	//�����蔻��𓮂�������
	m_moveSpeed.y = 0.0f;
	m_pos = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_pos.y = 0.0f;
	//�R���W�����̃Z�b�g
	m_collision->SetPosition(m_pos);
	m_collision->SetRotation(m_rotation);
	m_collision->SetWorldMatrix(matrix);
	m_collision->Update();
	m_modelRender.SetPosition(m_pos);
	m_modelRender.Update();
}
void Enemy_Boss::Render(RenderContext& rc)
{
	//���f����`�悷��B
	m_modelRender.Draw(rc);
}
