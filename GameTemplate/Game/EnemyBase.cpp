#include "stdafx.h"
#include "EnemyBase.h"


float EnemyBase::ToEnemyTargetLength(Vector3 targetPosition)
{
	Vector3 NearenemyPosition;
	NearenemyPosition = targetPosition - m_pos;

	return NearenemyPosition.Length();
}
