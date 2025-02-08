#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy_Boss.h"
#include "Boss_Shoot.h"

Bullet::~Bullet()
{
	DeleteGO(m_shootCollision);
}

bool Bullet::Start()
{
	m_player = FindGO<Player>("player");
	m_boss = FindGO<Enemy_Boss>("enemy_boss");
	m_pos = m_boss->GetPos();

	EffectEngine::GetInstance()->ResistEffect(2, u"Assets/Effect/Boss_Shoot.efk");
	///
	Vector3 diff = m_player->Get_PlayerPos() - m_pos;
	diff.Normalize();
	Vector3 PosZ = Vector3::AxisZ;
	qRot.SetRotation(PosZ, diff);
	
	//ブレスのロックオン
	m_shootPos = m_player->Get_PlayerPos() - m_pos;
	m_shootPos.Normalize();


	m_boss_shoot = NewGO<EffectEmitter>(2, "boss_shoot");
	m_boss_shoot->Init(2);
	m_boss_shoot->SetScale(Vector3::One * 10.0f);
	m_boss_shoot->SetPosition(m_boss->GetPos());
	m_boss_shoot->Play();
	//コリジョンオブジェクトを作成する
	m_shootCollision = NewGO<CollisionObject>(0);
	//球状のコリジョンを作成
	m_shootCollision->CreateSphere(
		m_pos,//座標
		qRot,//回転
		50.0f//半径
	);
	m_shootCollision->SetIsEnableAutoDelete(false);

	m_shootCollision->SetName("boss_shoot_collision");

    return true;
}

void Bullet::Update()
{
	//Init(m_boss);
	Move();
	Delete();
}

//void Bullet::Init(Enemy_Boss* boss)
//{
//	m_boss = boss;
//	m_pos = m_boss->GetPos();
//
//}

void Bullet::Move()
{
	m_pos += m_shootPos * 200.0f;
	//if (m_shootCollision != nullptr) {
	m_shootCollision->SetPosition(m_pos);
	//}
	if (m_boss_shoot != nullptr) {
		m_boss_shoot->SetRotation(qRot);
	}

}

void Bullet::Delete()
{
	m_deleteTime -= g_gameTime->GetFrameDeltaTime();

	if (m_deleteTime <= 0) {
		DeleteGO(this);
		m_deleteTime = 7.0f;
	}
}
