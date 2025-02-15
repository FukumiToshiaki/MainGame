#pragma once
class Player;
class Enemy_Boss;
#include "IBossState.h"
#include "Enemy_Boss.h"

class BossPattern :public Enemy_Boss
{
public:

	BossPattern() {};
	~BossPattern();

	//�X�^�[�g�֐�
	bool Start();
	//�A�b�v�f�[�g�֐�
	void Update();
	//�N�[���^�C�}�[�֐�
	void CoolTime();
	//�s�����l���߂̊֐�
	void DistancePattern();
	//�Ō�̍U�����[�h�֐�
	void AttackModeLast();
	//�Ō�̖h�䃂�[�h�֐�
	void DefenseModeLast();
	//�p�^�[�����߂̊֐�
	void BossPatternMode();
	//�K�E�Z
	void Scream(int screamcount, float screamdistance);
	//�{�X�̃��[�h�֐�
	void SuperDefenseMode();
	void DefenseMode();
	void NormalMode();
	void AttackMode();
	void SuperAttackMode();

private:
	Enemy_Boss* m_enemy_Boss = nullptr;
	Player* m_player = nullptr;
	
	/// <summary>
	/// bool
	/// </summary>
	//�ߋ����������������肷��bool
	bool m_isBifurcation = false;
	//�N�[���^�C�����X�^�[�g�����邩���肷��bool
	bool m_iscoolTimeStart = false;
	/// <summary>
	/// �ϐ�
	/// </summary>
	//�U���̃N�[���^�C��
	float m_coolTime = 5.0f;
	//�{�X�̃p�^�[�����l
	int m_pattern = 0;
	/// <summary>
	/// �ߋ����̎�
	/// </summary>
	Vector3 m_screamPos = Vector3::Zero;

	//int m_meleeAttack = 20;
	//int m_defend = 5;
	//int m_tailAttack = 15;
	//int m_fly = 5;
	//int m_shoot = 3;
};

