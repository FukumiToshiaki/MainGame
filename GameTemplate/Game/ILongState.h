#pragma once

class Enemy_Long;

class ILongState
{
public:
	ILongState(Enemy_Long* enemy_long) { m_enemy_Long = enemy_long; };
	virtual ~ILongState() {};

	virtual void Animation() = 0;

	virtual void Update() = 0;

private:
	Enemy_Long* m_enemy_Long = nullptr;
};

