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

	const Vector3 m_scale = { SCALE,SCALE,SCALE }; //�傫��

	//�A�j���[�V�����N���b�v�����[�h����B
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
	//�A�j���[�V�����Ȃ��Ȃ瓮��
	//m_modelRender.Init("Assets/modelData/Player_Test/Player_Test.tkm");

	//m_animationClipArray[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	//m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);

	//m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClipArray, enAnimClip_Num, enModelUpAxisY);

	//�X�P���g�������[�h�B
	//InitSkeleton();
	//���f�����������B
	//�A�j���[�V�������������B//
	//InitAnimation();
	//�X�P�[��
	m_pos = { START_POS_X, START_POS_Y, START_POS_Z };
	m_modelRender.SetPosition(m_pos);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	////�����蔻��̍쐬�B
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

	////���̃{�[�����󂯎��
	//m_TestBoneId = m_modelRender.FindBoneID(L"mixamorig:RightHand");
	////�U���p�R���W������p��
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
	//�A�j���[�V�������������B
	m_animation.Init(
		m_skeleton,			//�A�j���[�V�����𗬂����ރX�P���g���B
		m_animationClipArray,	//�A�j���[�V�����N���b�v�B
		enAnimClip_Num		//�A�j���[�V�����̐��B
	);
	////�A�j���[�V������i�߂�B
	m_animation.Progress(g_gameTime->GetFrameDeltaTime());
}

void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//�L�[�̖��O��attack_start�̏ꍇ
	if (wcscmp(eventName, L"attack_start") == 0)
	{
		//�U�����ɂ���
		m_isUnderAttack = true;
	}
	//�L�[�̖��O��attack_end�̏ꍇ
	else if (wcscmp(eventName, L"attack_end") == 0) {
		//�U�����I���
		m_isUnderAttack = false;
	}

	//�L�[�̖��O��attack_start�̏ꍇ
	if (wcscmp(eventName, L"walkattack_start") == 0)
	{
		//�U�����ɂ���
		m_isUnderWalkAttack = true;
	}
	//�L�[�̖��O��attack_end�̏ꍇ
	else if (wcscmp(eventName, L"walkattack_end") == 0) {
		//�U�����I���
		m_isUnderWalkAttack = false;
	}

	//�L�[�̖��O��GuradBreak_start�̏ꍇ
	if (wcscmp(eventName, L"GuradBreak_start") == 0)
	{
		//�U�����ɂ���
		m_isUnderGuradBreak = true;
	}
	//�L�[�̖��O��GuradBreak_end�̏ꍇ
	else if (wcscmp(eventName, L"GuradBreak_end") == 0) {
		//�U�����I���
		m_isUnderGuradBreak = false;
	}
	//�L�[�̖��O��LongAttack_start�̏ꍇ
	if (wcscmp(eventName, L"LongAttack_start") == 0)
	{
		//�U�����ɂ���
		m_isUnderLongAttack = true;
	}
	//�L�[�̖��O��LongAttack_end�̏ꍇ
	else if (wcscmp(eventName, L"LongAttack_end") == 0) {
		//�U�����I���
		m_isUnderLongAttack = false;
	}

}

void Player::BitingAttackCollision()
{
	/*m_forward = m_moveSpeed;
	m_forward.Normalize();*/

	//�R���W�����I�u�W�F�N�g���쐬����
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//���W���v���C���[�̏����O�ɐݒ�
	collisionPosition += m_forward * 150.0f;
	//����̃R���W�������쐬
	collisionObject->CreateSphere(collisionPosition,//���W
		Quaternion::Identity,//��]
		100.0f//���a
	);
	collisionObject->SetName("player_biting_attack");
}

void Player::WalkAttackCollision()
{
	//�R���W�����I�u�W�F�N�g���쐬����
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//���W���v���C���[�̏����O�ɐݒ�
	collisionPosition += m_forward * 150.0f;
	//����̃R���W�������쐬
	collisionObject->CreateSphere(collisionPosition,//���W
		Quaternion::Identity,//��]
		100.0f//���a
	);
	collisionObject->SetName("player_walk_attack");
}

void Player::GuradBreakCollision()
{
	//�R���W�����I�u�W�F�N�g���쐬����
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_pos;
	//���W���v���C���[�̏����O�ɐݒ�
	collisionPosition += m_forward * 150.0f;
	//����̃R���W�������쐬
	collisionObject->CreateSphere(collisionPosition,//���W
		Quaternion::Identity,//��]
		100.0f//���a
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
	//// ��]
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

	////�{�[���̍��W���󂯎��v���O�����e�X�g
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
	//xz�̈ړ����x��0.0f�ɂ���B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//�e�̃e�X�g�p
	m_moveSpeed.y = 0.0f;
	
	//���X�e�B�b�N�̓��͗ʂ��擾�B
	m_stickL.x = g_pad[0]->GetLStickXF();
	m_stickL.z = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y�����ɂ͈ړ������Ȃ��B
	forward.y = 0.0f;
	right.y = 0.0f;

	forward.Normalize();
	right.Normalize();
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
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
	////�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����B
	m_moveSpeed += right + forward;

	//���W���ړ�
		////�X�P���g�����X�V�B
}
void Player::Rotation()
{
	//if (fabsf(m_moveSpeed.x) < 0.001f
	//	&& fabsf(m_moveSpeed.z) < 0.001f) {
	//	//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
	//	//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
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
	//�U�����蒆�Ȃ�
	if (m_isUnderAttack) {
		//�U���p�̃R���W�������쐬����
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

	// �U���R���W�����ƏՓ˂��Ă��邩�𒲂ׂ�
	const auto& collisionList_MeleeAttack = g_collisionObjectManager->FindCollisionObjects("boss_attack_melee" /*"player_walk_attack" "player_biting_attack"*/);
	for (auto& collision : collisionList_MeleeAttack) {
		if (collision->IsHit(m_collision)) {
			//�_���[�W
			m_isDamage = true;
			m_testHP--;
			return;
		}
	}
	// �U���R���W�����ƏՓ˂��Ă��邩�𒲂ׂ�
	const auto& collisionList_TailAttack = g_collisionObjectManager->FindCollisionObjects("boss_attack_tail");
	for (auto& collision : collisionList_TailAttack) {
		if (collision->IsHit(m_collision)) {
			//�_���[�W
			m_isDamage = true;
			m_testHP--;
			return;
		}
	}
	//// �U���R���W�����ƏՓ˂��Ă��邩�𒲂ׂ�
	//const auto& collisionList_Attack = g_collisionObjectManager->FindCollisionObjects("boss_attack_melee" /*"player_walk_attack" "player_biting_attack"*/);
	//for (auto& collision : collisionList_Attack) {
	//	if (collision->IsHit(m_collision)) {
	//		//�_���[�W
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
	//�v���C���[�ƃG�l�~�[�����ȏ㗣��Ă�����
	//�^�[�Q�b�e�B���O���Ȃ�
	//�߂����Ă��^�[�Q�b�e�B���O���Ȃ�
	if (diff.Length() >= 3000.0f || diff.Length() <= 20.0f)
	{
		m_isTakeAim = false;
		return;
	}
	diff.y = 0.0f;
	diff.Normalize();

	float angle = acosf(m_forward.Dot(diff));
	//�v���C���[�̐��ʃx�N�g���ƁB
	//�v���C���[����G�l�~�[�Ɍ������x�N�g���́B
	//�p�x��90�x�ȏォ�B
	//���b�N�I����ԂłȂ�������B
	//�^�[�Q�b�e�B���O���Ȃ��B
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

	//�^�[�Q�b�e�B���O������Ă��Ȃ�������B
	//���b�N�I�����Ȃ��B
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
