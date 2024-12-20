#pragma once

class Enemy_Boss;

class IBossState
{
public:
	IBossState(Enemy_Boss* enemy_Boss) { m_enemy_Boss = enemy_Boss; };
	virtual ~IBossState() {};

	virtual void Animation() = 0;

	virtual void Update() = 0;

	

protected:
	Enemy_Boss* m_enemy_Boss = nullptr;
};

