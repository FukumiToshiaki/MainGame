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
	////ボスのブレスの読み込み
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
	//エフェクトのポインターが残ってて
	//エフェクトが消えていたら
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
		//音再生
		g_soundManager->InitAndPlaySoundSource(
			enSoundShoot,
			g_soundManager->GetSEVolume()
		);
		//BulletクラスをNewGO
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
		//音再生
		g_soundManager->InitAndPlaySoundSource(
			enSoundShoot,
			g_soundManager->GetSEVolume()
		);
		m_bullet = NewGO<Bullet>(0, "bullet");
	}

}
