#pragma once

class EnemyBase:public IGameObject
{
public:
	virtual ~EnemyBase() {};

	float ToEnemyTargetLength(Vector3 targetPosition);
	
	Vector3 GetPos()
	{
		return m_pos;
	}

protected:
	Vector3 m_pos;			//ç¿ïW

};

