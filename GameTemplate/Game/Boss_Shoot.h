#pragma once
#include "Enemy_Boss.h"
class Player;
class Bullet;
class Boss_Shoot :public IGameObject
{
public:

	bool Start();

	void Init(Enemy_Boss* boss);

	void Update();

	 void Shoot(int movespeed, int hitstartframe, int hitendframe);

	 void SetisShoot(bool bossshoot) {
		 m_isShoot = bossshoot;
	 }
	 bool GetisShoot() {
		 return m_isShoot;
	 }
private:
	Enemy_Boss* m_boss = nullptr;
	/// <summary>
	/// Vector3
	/// </summary>
	Vector3 m_moveSpeed_Shoot = Vector3::Zero;
	Vector3 m_shootPos = Vector3::Zero;
	Vector3 m_shot = Vector3::Zero;

	/// <summary>
	/// bool
	/// </summary>
	bool m_isShoot = false;				//ƒuƒŒƒX‚ðŒ‚‚Á‚½‚©‚çtrue

	/// <summary>
	/// Collision
	/// </summary>
	CollisionObject* m_shootCollision = nullptr;

	Player* m_player = nullptr;
	Bullet* m_bullet = nullptr;
	Vector3 m_pos = Vector3::Zero;
	EffectEmitter* m_boss_shoot = nullptr;
};

