#include "stdafx.h"
#include "Boss_Shoot.h"
#include "Player.h"
#include "Enemy_Boss.h"
#include "Bullet.h"
Boss_Shoot::~Boss_Shoot()
{
	DeleteGO(this);
}
bool Boss_Shoot::Start()
{
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
	////nullptrにする
	//if (m_boss_shoot != nullptr) {
	//	if (m_boss_shoot->IsDead())	{
	//		m_boss_shoot = nullptr;
	//		DeleteGO(m_shootCollision);
	//		m_shot = m_boss->GetPos();
	//	}
	//}
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

		m_bullet = NewGO<Bullet>(0, "bullet");
	}

}
