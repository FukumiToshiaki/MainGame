#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy_Boss.h"
#include "Boss_Shoot.h"

Bullet::~Bullet()
{
	DeleteGO(m_shootCollision);
	if (m_boss_shoot) {
		m_boss_shoot->RemoveDeadEventFunction(m_onDeadEventFunction);
	}
}

void Bullet::OnDeadEffect()
{

}
bool Bullet::Start()
{
	m_player = FindGO<Player>("player");
	m_boss = FindGO<Enemy_Boss>("enemy_boss");
	m_pos = m_boss->GetPos();
	
	//�n�ォ��u���X�Ȃ�
	if (m_boss->m_state == m_boss->enState_Attack_Shoot) {
		m_pos.y += 300.0f;
	}
	//�󂩂�u���X�Ȃ�
	else if (m_boss->m_state == m_boss->enState_Attack_FlyShoot) {
		m_pos.y += 1700.0f;
	}

	EffectEngine::GetInstance()->ResistEffect(2, u"Assets/Effect/Boss_Shoot_Test.efk");
	///
	Vector3 diff = m_player->Get_PlayerPos() - m_pos;
	diff.Normalize();
	Vector3 PosZ = Vector3::AxisZ;
	qRot.SetRotation(PosZ, diff);
	
	//�u���X�̃��b�N�I��
	m_shootPos = m_player->Get_PlayerPos() - m_pos;
	m_shootPos.Normalize();

	//�G�t�F�N�g�̍쐬
	m_boss_shoot = NewGO<EffectEmitter>(2, "boss_shoot");
	m_boss_shoot->Init(2);
	m_boss_shoot->SetScale(Vector3::One * 10.0f);
	m_boss_shoot->SetPosition(m_boss->GetPos());
	m_boss_shoot->Play();
	// �G�t�F�N�g���S���̃C�x���g����
	m_onDeadEventFunction = [&] { m_boss_shoot = nullptr;};
	// �C�x���g��o�^
	m_boss_shoot->AddDeadEventFunction(m_onDeadEventFunction);

		// �G�t�F�N�g�����S����;
	//�R���W�����I�u�W�F�N�g���쐬����
	m_shootCollision = NewGO<CollisionObject>(0);
	//����̃R���W�������쐬
	m_shootCollision->CreateSphere(
		m_pos,//���W
		qRot,//��]
		50.0f//���a
	);
	m_shootCollision->SetIsEnableAutoDelete(false);

	m_shootCollision->SetName("boss_shoot_collision");

    return true;
}

void Bullet::Update()
{
	Move();
	Delete();
}

void Bullet::Move()
{
	//�ړ����x
	m_pos += m_shootPos * 100.0f;
	if (m_boss_shoot != nullptr) {
		m_boss_shoot->SetPosition(m_pos);
		m_shootCollision->SetPosition(m_pos);
		m_boss_shoot->SetRotation(qRot);
	}

}

void Bullet::Delete()
{
	m_deleteTime -= g_gameTime->GetFrameDeltaTime();
	//�^�C�}�[��0�ɂȂ�����
	if (m_deleteTime <= 0) {
		//�폜
		DeleteGO(this);
		////�^�C�}�[�̃��Z�b�g
		//m_deleteTime = 4.0f;
	}
}
