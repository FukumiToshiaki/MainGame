#include "stdafx.h"
#include "Boss_Shoot.h"
#include "Player.h"
#include "Enemy_Boss.h"
#include "Bullet.h"
#include <SoundManager.h>

Boss_Shoot::~Boss_Shoot()
{
	DeleteGO(this);
}
bool Boss_Shoot::Start()
{
	////�{�X�̃u���X�̓ǂݍ���
	//g_soundEngine->ResistWaveFileBank(7, "Assets/sound/Shoot.wav");
	//m_shoot = NewGO<SoundSource>(7);
	return true;
}
void Boss_Shoot::Init(Enemy_Boss* boss)
{
	m_player = FindGO<Player>("player");
	m_boss = boss;
	m_pos = m_boss->GetPos();
}


void Boss_Shoot::Update()
{
	//�G�t�F�N�g�̃|�C���^�[���c���Ă�
	//�G�t�F�N�g�������Ă�����
	if (m_boss != nullptr) {
		Init(m_boss);
		Shoot();
		FlyShoot();
	}
}

void Boss_Shoot::Shoot()
{
	if (m_boss->m_state != Enemy_Boss::enState_Attack_Shoot) {
		return;
	}
	if (!m_isShoot) {
		m_isShoot = true;
		//���Đ�
		g_soundManager->InitAndPlaySoundSource(
			enSoundShoot,
			g_soundManager->GetSEVolume()
		);
		//Bullet�N���X��NewGO
		m_bullet = NewGO<Bullet>(0, "bullet");
	}
}
void Boss_Shoot::FlyShoot()
{
	if (m_boss->m_state != Enemy_Boss::enState_Attack_FlyShoot) {
		return;
	}
	if (!m_isShoot) {
		m_isShoot = true;
		//���Đ�
		g_soundManager->InitAndPlaySoundSource(
			enSoundShoot,
			g_soundManager->GetSEVolume()
		);
		m_bullet = NewGO<Bullet>(0, "bullet");
	}

}
