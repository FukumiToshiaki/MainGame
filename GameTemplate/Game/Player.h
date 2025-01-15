#pragma once
#include <SpriteRender.h>
#include "PlayerStatus.h"
#include "EnemyBase.h"
class Game;
class EnemyBase;
class Enemy_Boss;
class IPlayer_State;
class Enemy_Shield;
class Enemy_Sky;
class Enemy_Melee;
class Enemy_Long;

class Player : public IGameObject
{
public:

	struct LockOnPosition
	{
		Vector3 position;

	};
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	void Move();
	void Rotation();
	void Attack_Biting();
	void WalkAttack();
	void Defense();
	void GuardBreak();
	void Hit();
	//�G�C��
	void TakeAim();
	void AddEnemy_List(EnemyBase* enemybase);
	void RemoveEnemy_List(EnemyBase* enemybase);
	//LockOnPosition* TakeAim(Vector3 position);
	//���b�N�I��
	void LockOn();
	//�������U��
	void LongAttack();
	// �X�P���g����������
	void InitSkeleton();
	// ���f�����������B
	//void InitModel();
	// �A�j���[�V�������������B
	void InitAnimation();

	// �A�j���[�V�����C�x���g�p�̊֐��B
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	
	//�A�j���[�V�����R���W�����ߐڍU���̊֐�
	void BitingAttackCollision();
	//�A�j���[�V�����R���W�����_�b�V���U���̊֐�
	void WalkAttackCollision();
	//�A�j���[�V�����R���W�����K�[�h�u���C�N�̊֐�
	void GuradBreakCollision();
	// �A�j���[�V�����N���b�v�̔ԍ���\���񋓌^�B
	enum EnAnimationClip {
		enAnimClip_Idle,	// 0 : �ҋ@�A�j���[�V�����A
		enAnimClip_Run,		// 1 : ����A�j���[�V�����B
		enAnimClip_Attack,	// 2 :���ōU��
		enAnimClip_Walk,
		enAnimClip_DefenceStart,
		enAnimClip_Defense,
		enAnimClip_DefenceEnd,
		enAnimClip_WalkAttack,
		enAnimClip_GuardBreak,
		enAnimClip_LongAttack,
		enAnimClip_Damage,
		enAnimClip_Die,
		enAnimClip_Num,		// 3 :�A�j���[�V�����N���b�v�̐��B�A�j���[�V������ǉ�����Ȃ炱�̏�ɍ��

	};

	enum EnState {
		enState_Idle,
		enState_Attack_Biting,
		enState_Defense,
		enState_Run,
		enState_Walk,
		enState_WalkAttack,
		enState_GuradBreak,
		enState_Damage,
		enState_LongAttack,
		enState_Die,
	};
	EnState m_state = enState_Idle;
	//�X�e�[�g�̊Ǘ�
	void ChangeState(EnState changeState);

	Vector3 Get_PlayerPos()
	{
		return m_pos;
	}

	ModelRender& GetModelRender()
	{
		return m_modelRender;
	}

	const bool& GetIsPlayingAnimation()const
	{
		return m_modelRender.IsPlayingAnimation();
	}

	//bool GetIsAttack_Biting()
	//{
	//	return m_isAttack_Biting;
	//}
	//void SetIsAttack_Biting(const bool Attack_Biting) {
	//	m_isAttack_Biting = Attack_Biting;
	//}

	//bool GetIsWalk()
	//{
	//	return m_isWalk;
	//}

	//bool GetIsWalkAttack()
	//{
	//	return m_isWalkAttack;
	//}
	//void SetIsWalkAttack(const bool WalkAttack) {
	//	m_isWalkAttack = WalkAttack;
	//}

	//bool GetIsLongAttack()
	//{
	//	return m_isLongAttack;
	//}
	//bool GetIsDefense()
	//{
	//	return m_isDefense;
	//}
	//void SetIsDefense(const bool Defense)
	//{
	//	m_isDefense = Defense;
	//}

	//bool GetIsGuradBreak()
	//{
	//	return m_isGuardBreak;
	//}
	//void SetIsGuradBreak(const bool Break)
	//{
	//	m_isGuardBreak = Break;
	//}

	//bool GetisDamage()
	//{
	//	return m_isDamage;
	//}
	//void SetisDamage(const bool damage) {
	//	m_isDamage = damage;
	//}

	//bool GetisDie()
	//{
	//	return m_isDie;
	//}
	//void SetisDie(bool Die)
	//{
	//	m_isDie = Die;
	//}

	bool GetisOver()
	{
		return m_isOver;
	}
	void SetisOver(bool Over)
	{
		m_isOver = Over;
	}


	const bool GetIsLockOn() const
	{
		return m_isLockOn;
	}

	int GetEnemyNo()
	{
		return m_enemyNo;
	}

	int GetHP()
	{
		return m_testHP;
	}
	/// <summary>
	/// �^�[�Q�b�g�̍��W���擾�B
	/// </summary>
	/// <returns></returns>
	const Vector3& GetTargetPosition() const
	{
		return m_targetPosition;
	}

private:
/// <summary>
/// �x�N�^�[
/// </summary>
	Vector3 m_pos;		// ���W
	Vector3 m_moveSpeed;									//�ړ����x�B
	Vector3	m_forward = Vector3::AxisZ;
	Vector3 m_scale = Vector3::One;			//�傫���B
	Vector3 m_stickL;
	Vector3 m_attack_Pos;
	Vector3 m_targetPosition = Vector3::Zero;
	std::vector<EnemyBase*> m_enemyList;
/// <summary>
/// �N���X
/// </summary>
	Game* m_game = nullptr;									//�Q�[��
	Enemy_Boss* m_enemy_Boss = nullptr;		//�{�X
	Enemy_Shield* m_enemy_Shield = nullptr;
	Enemy_Melee* m_enemy_melee = nullptr;
	Enemy_Long* m_enemy_Long = nullptr;
	Enemy_Sky* m_enemy_Sky = nullptr;
	IPlayer_State* m_Iplayer_State = nullptr;
	CollisionObject* m_collision = nullptr;
	SpriteRender		m_spriteRender;
	/// <summary>
/// �ϐ�
/// </summary>
	int m_enemyNo = 0;
	float m_testHP = 10;
	int m_count = -1;
	int m_targetCount = -1;
	float m_longAttackCoolTime = 5.0f;
/// <summary>
/// �u�[���^
/// </summary>
	bool m_isNowAttack = false;//�U�����Ȃ�true
	//bool m_isAttack_Biting = false;	//
	//bool m_isWalk = false;			//
	//bool m_isWalkAttack = false;	//
	//bool m_isDefense = false;		//	
	//bool m_isGuardBreak = false;	//
	//bool m_isLongAttack = false;	//�������U��
	bool m_isUnderAttack = false;	//�U�����Ȃ�true
	bool m_isUnderWalkAttack = false;//�_�b�V���U�����Ȃ�true
	bool m_isUnderGuradBreak = false;//�K�[�h�u���C�N���Ȃ�true
	bool m_isUnderLongAttack = false;//�����O�A�^�b�N���Ȃ�true
	//bool m_isDamage = false;		//
	bool m_isTakeAim = false;
	bool m_isLockOn = false;
	bool m_isLockOnCamera = false;
	//bool m_isDie = false;
	bool m_isOver = false;

	Model m_model;			// ���f��
	Animation m_animation;	// �A�j���[�V����
	AnimationClip m_animationClipArray[enAnimClip_Num];	// �A�j���[�V�����N���b�v
	Quaternion m_rotation;	// ��]
	Sprite m_sprite;	// �X�v���C�g
	Skeleton m_skeleton;	// �X�P���g��
	ModelRender m_modelRender;
	CharacterController m_charaCon;	//�L�����N�^�[�R���g���[���[
	PlayerStatus m_playerStatus;
};
