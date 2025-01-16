#pragma once
class Player;
class Game;
class IBossState;
//class BossPattern;
#include "EnemyBase.h"

class Enemy_Boss : public EnemyBase
{
public:
	Enemy_Boss() {};
	~Enemy_Boss() {};
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void FlyAttackMove();
	// �X�P���g����������
	void InitSkeleton();
	// �A�j���[�V�������������B
	void InitAnimation();
	//��]�̏�����
	void Rotation();
	//�ߋ����U���̊��݂�
	void Biting();
	//�������U���̒n�ォ��̃u���X
	void Shoot();
	//��Z��̋x�e���[�V����
	void Rest();
	//�R���W�����̓����蔻��
	void Hit();
	//���݂��U���̃R���W����
	void MeleeAttackCollision();
	//�K���̓ガ����
	void TailAttack();
	//�K���̓ガ�����̃R���W����
	void TailAttackCollision();
	//�󒆓ːi
	void FlyAttack();
	//�󒆓ːi�̓����蔻��
	void FlyAttackCollision();
	//�؋󎞊�
	void FlyTime();
	// �A�j���[�V�����C�x���g�p�̊֐��B
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	// �A�j���[�V�����N���b�v�̔ԍ���\���񋓌^�B
	enum EnAnimationClip {
		enState_Idle_Animation,
		enState_Attack_Biting_Animation,
		enState_Attack_Shoot_Animation,
		enState_Attack_Tail_Animation,
		enState_Attack_Scream_Animation,
		enState_Attack_FlyShoot_Animation,
		enState_Attack_Fly_Animation,
		enState_Damage_Animation,
		enState_Defence_Animation,
		enState_Rest_Animation,
		enState_Move_Animation,
		enState_Die_Animation,
		enState_Takeoff_Animation,
		enState_Fly_Animation,
		enState_Landing_Animation,
		enAnimClip_Num,		// 2 :�A�j���[�V�����N���b�v�̐��B�A�j���[�V������ǉ�����Ȃ炱�̏�ɍ��
	};
	enum EnState {
		enState_Idle,
		enState_Attack_Biting,
		enState_Attack_Shoot,
		enState_Attack_Tail,
		enState_Attack_Scream,
		enState_Attack_FlyShoot,
		enState_Attack_Fly,
		enState_Damage,
		enState_Defence,
		enState_Rest,
		enState_Move,
		enState_Die,
		enState_Takeoff,
		enState_Fly,
		enState_Landing,
	};
	EnState m_state = enState_Idle;
	//�X�e�[�g�̊Ǘ�
	void ChangeState(EnState changeState, int integerArgument0 = 0);

	const bool& GetIsPlayingAnimation()const
	{
		return m_modelRender.IsPlayingAnimation();
	}

	ModelRender& GetModelRender()
	{
		return m_modelRender;
	}

	

	bool GetisClear()
	{
		return m_isClear;
	}
	void SetisClear(bool Clear)
	{
		m_isClear = Clear;
	}

	

	void SetUnderMelee(bool UnderMelee)
	{
		m_isUnderAttackMelee = UnderMelee;
	}

	void SetUnderTail(bool UnderTail)
	{
		m_isUnderTail = UnderTail;
	}

	void SetUnderFlyAttack(bool UnderFlyAttack)
	{
		m_isUnderFlyAttack = UnderFlyAttack;
	}

	int GetHP()
	{
		return m_testHP;
	}

	void SetisUnderPattern(bool Pattern)
	{
		m_isUnderPattern = Pattern;
	}

	void SetMoveSpeed(Vector3 movespeed)
	{
		m_moveSpeed = movespeed;
	}

	Vector3 GetDiff()
	{
		return m_diff;
	}

	//float GetFlyTime()
	//{
	//	return m_testFlyTime;
	//}
	//void SetDiff(Vector3 diff)
	//{
	//	m_diff = diff;
	//}
protected:
	/// <summary>
	/// �x�N�^�[
	/// </summary>
	Vector3 m_distance;
	Vector3 m_diff;
	Vector3 m_moveSpeed;	//�ړ����x
	Vector3						m_scale = Vector3::One;			//�傫���B
	Vector3		m_forward = Vector3::AxisZ;					//�G�l�~�[�̐��ʃx�N�g���B
	Vector3 m_collisionPos;
	Vector3 m_flyPos;
	/// <summary>
	/// �N���X
	/// </summary>
	//BossPattern* m_bossPattern = nullptr;
	/// <summary>
	/// �ϐ�
	/// </summary>
	int m_attack_Rand = 0;
	int m_attack_Count = -1;
	int m_testHP = 1;
	int m_flyBoneId = 0;
	float m_angle = 0.0f;
	float m_radius = 2.0f;
	//float m_testFlyTime = 3.0f;
	/// <summary>
	/// �u�[���^
	/// </summary>
	
	bool m_isUnderAttackMelee = false;	//�U�����Ȃ�true
	bool m_isUnderTail = false;			//�U�����Ȃ�true
	bool m_isUnderFlyAttack = false;	//�U�����Ȃ�true
	bool m_isClear = false;				//�N���A����
	bool m_isUnderPattern = false;		//�s�����Ȃ�true

	ModelRender m_modelRender;
	Player* m_player = nullptr;
	CollisionObject* m_collision = nullptr;
	CollisionObject* m_flyPosCollision = nullptr;
	Game* m_game = nullptr;
	IBossState* m_Iboss_State = nullptr;
	Animation m_animation;	// �A�j���[�V����
	Skeleton m_skeleton;	// �X�P���g��
	Model m_model;			// ���f��
	Quaternion	m_rotation;							//��]
	Quaternion m_wait;
	AnimationClip m_animationClipArray[enAnimClip_Num];	// �A�j���[�V�����N���b�v

};

