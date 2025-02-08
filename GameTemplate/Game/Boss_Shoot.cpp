#include "stdafx.h"
#include "Boss_Shoot.h"
#include "Player.h"
#include "Enemy_Boss.h"

bool Boss_Shoot::Start() 
{
	EffectEngine::GetInstance()->ResistEffect(2, u"Assets/Effect/Boss_Shoot.efk");

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
	//nullptrにする
	//if (m_boss_shoot != nullptr) {
	//	if (m_boss_shoot->IsDead())	{
	//		m_boss_shoot = nullptr;
	//		DeleteGO(m_shootCollision);
	//		m_shot = m_boss->GetPos();
	//	}
	//}
	//Init(m_boss);
	//Shoot(100.0f, 3, 50);
}

void Boss_Shoot::Shoot(int movespeed, int hitstartframe, int hitendframe)
{
	///
	Quaternion qRot;
	Vector3 diff = m_player->Get_PlayerPos() - m_pos;
	diff.Normalize();
	Vector3 PosZ = Vector3::AxisZ;
	qRot.SetRotation(PosZ, diff);
	///
			//ブレスのロックオン
	m_moveSpeed_Shoot = m_player->Get_PlayerPos() - m_pos;
	m_shootPos = m_moveSpeed_Shoot;
	m_moveSpeed_Shoot.Normalize();

	//if (m_shootPos.Length() <= 150.0f) {
	//	EffectEmitter* Boss_Shoot = NewGO<EffectEmitter>(3, "boss_shoot");
	//	Boss_Shoot->Init(3);
	//	Boss_Shoot->SetScale(Vector3::One * 10.0f);
	//	Boss_Shoot->SetPosition(diff);
	//	Boss_Shoot->Play();
	//}


	if (m_boss->m_state != Enemy_Boss::enState_Attack_Shoot) {
		return;
	}
	m_shot += m_moveSpeed_Shoot * movespeed;

	if (!m_isShoot) {
		m_boss_shoot = NewGO<EffectEmitter>(2, "boss_shoot");
		m_boss_shoot->Init(2);
		m_boss_shoot->SetScale(Vector3::One * 10.0f);
		m_boss_shoot->SetPosition(m_boss->GetPos());
		m_boss_shoot->Play();
		m_isShoot = true;
		//エフェクトカウンターが数値の間にあるなら当たり判定をつける
		//if (m_effectCount <= 0) {
		if (m_boss_shoot != nullptr) {
			m_boss_shoot->SetRotation(qRot);
		}
		//コリジョンオブジェクトを作成する
		m_shootCollision = NewGO<CollisionObject>(0);
		//球状のコリジョンを作成
		m_shootCollision->CreateSphere(m_shot,//座標
			qRot,//回転
			50.0f//半径
		);
	}
	//m_shootCollision->GetGhostObject().SetRotation(qRot);

		m_shootCollision->SetName("boss_shoot_collision");

	}
