#pragma once
class Boss_Shoot;
class Enemy_Boss;
class Boss_Shoot;
#include "Enemy_Boss.h"
class Bullet:public IGameObject
{
public:

	Bullet() {};
	~Bullet();
	bool Start();

	void Update();

	//void Init(Enemy_Boss* boss);

	void Move();

	void Delete();

private:
	Enemy_Boss* m_boss = nullptr;
	Boss_Shoot* m_boss_Shoot = nullptr;
	/// <summary>
	/// Vector3
	/// </summary>
	Vector3 m_pos = Vector3::Zero;
	Vector3 m_shootPos = Vector3::Zero;
	Vector3 m_shot = Vector3::Zero;
	/// <summary>
	/// Collision
	/// </summary>
	CollisionObject* m_shootCollision = nullptr;

	Player* m_player = nullptr;
	EffectEmitter* m_boss_shoot = nullptr;
	Quaternion qRot = Quaternion::Identity;

	float m_deleteTime = 7.0f;
};

