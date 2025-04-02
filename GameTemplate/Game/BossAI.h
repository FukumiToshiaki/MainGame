#pragma once
class Player;
class Enemy_Boss;
#include "IBossState.h"
#include "Enemy_Boss.h"

class BossAI :public Enemy_Boss
{
public:
	struct BossActions 
	{
		int m_melee = 0;
		int m_distance = 0;
		int m_shoot = 0;
		int m_defense = 0;
		int m_tail = 0;
		int m_flyshoot = 0;
		int m_flyattack = 0;
		int m_move = 0;
	};
	BossAI() {};
	~BossAI();

	//�X�^�[�g�֐�
	bool Start();
	//�A�b�v�f�[�g�֐�
	void Update();
	//�N�[���^�C�}�[�֐�
	void CoolTime();
	//�e�[�u���̏�����
	void BossTable(const string& state);
	//�{�X�̍s��
	void BossValue(const string& state, int action, double reward, const string& next_state);

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
	//�v���C���[�̍s������
	int m_player_history[3];
	/// <summary>
	/// �ߋ����̎�
	/// </summary>
	Vector3 m_screamPos = Vector3::Zero;

};

