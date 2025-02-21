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
class Player_HP_UI;
class Player : public IGameObject
{
public:

	struct LockOnPosition
	{
		Vector3 position;

	};
	//�X�^�[�g�֐�
	bool Start() override;
	//�A�b�v�f�[�g�֐�
	void Update() override;
	//���f�������_�[
	void Render(RenderContext& rc) override;
	//�ړ��̊֐�
	void Move(float walk_speed, float run_speed, float walkattack_speed);
	//��]�֐�
	void Rotation(float rotation);
	//�ߋ����U���̊֐�
	void Attack_Biting();
	//�_�b�V���A�^�b�N�̊֐�
	void WalkAttack();
	//�h��֐�
	void Defense();
	//�h��R���W�����̊֐�
	void DefenseCollision(float melee_knockback, float melee_magnification, float tail_knockback, float tail_magnification,
		float flyattack_knockback, float flyattack_magnification, float scream_knockback, float scream_magnification,float scream_hittime,
		float shoot_knockback, float shoot_magnification, float landing_knockback, float landing_magnification);
	//�K�[�h�u���C�N�֐�
	void GuardBreak();
	//�q�b�g�֐�
	void Hit(float screamhitcooltime, float tail_knockback, float flyattack_knockback, float landing_knockback);
	//�G�C��
	void TakeAim(float maximum, float smallest);
	//�G�l�~�[�̃��X�g
	void AddEnemy_List(EnemyBase* enemybase);
	void RemoveEnemy_List(EnemyBase* enemybase);
	//LockOnPosition* TakeAim(Vector3 position);
	//���b�N�I��
	void LockOn();
	//�������U��
	void LongAttack(float hitstartframe, float hitendframe, float effect_speed);
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
		//enAnimClip_DefenceStart,
		enAnimClip_Defense,
		//enAnimClip_DefenceEnd,
		enAnimClip_WalkAttack,
		enAnimClip_GuardBreak,
		enAnimClip_LongAttack,
		enAnimClip_Damage,
		enAnimClip_Die,
		enAnimClip_Arching,
		enAnimClip_Landing_Back,
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
		enState_Arching,
		enState_Die,
		enState_Flying_Back,
	};
	EnState m_state = enState_Idle;
	//�X�e�[�g�̊Ǘ�
	void ChangeState(EnState changeState);

	Vector3 Get_PlayerPos()
	{
		return m_pos;
	}

	void SetMoveSpeed(Vector3 MoveSpeed) {
		m_moveSpeed = MoveSpeed;
	}

	ModelRender& GetModelRender()
	{
		return m_modelRender;
	}

	const bool& GetIsPlayingAnimation()const
	{
		return m_modelRender.IsPlayingAnimation();
	}

	bool GetisOver()
	{
		return m_isOver;
	}
	void SetisOver(bool Over)
	{
		m_isOver = Over;
	}

	void SetisWalkAttack(bool WalkAttack) {
		m_isUnderWalkAttack = WalkAttack;
	}
	void SetisBitAttack(bool BitAttack) {
		m_isUnderAttack = BitAttack;
	}
	void SetisGuradBreak(bool GuradBreak) {
		m_isUnderGuradBreak = GuradBreak;
	}
	void SetisLongAttack(bool LongAttack) {
		m_isUnderLongAttack = LongAttack;
	}
	void SetisDefense(bool defense) {
		m_isUnderDefense = defense;
	}
	const bool GetIsLockOn() const
	{
		return m_isLockOn;
	}

	int GetEnemyNo()
	{
		return m_enemyNo;
	}

	float GetHP()
	{
		return m_testHP;
	}

	void SetisSound(bool Sound) {
		m_isSound = Sound;
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
	// ���W
	Vector3 m_pos = Vector3::Zero;;
	//�ړ����x�B
	Vector3 m_moveSpeed = Vector3::Zero;	
	//����
	Vector3	m_forward = Vector3::AxisZ;
	//�傫��
	Vector3 m_scale = Vector3::One;			
	//�X�e�B�b�N
	Vector3 m_stickL = Vector3::Zero;;
	Vector3 m_attack_Pos = Vector3::Zero;;
	//�G�̃|�W�V����
	Vector3 m_targetPosition = Vector3::Zero;
	//�m�b�N�o�b�N
	Vector3 m_KnockBack = Vector3::Zero;;
	//�������U���̃|�W�V����
	Vector3 m_longAttackPos = Vector3::Zero;;
	//�G�̃��X�g
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
	Player_HP_UI* m_player_HP_UI = nullptr;
	/// <summary>
/// �ϐ�
/// </summary>
	//�G�̃i���o�[
	int m_enemyNo = 0;
	//�G�C���̐؂�ւ�
	int m_count = -1;
	//�^�[�Q�b�g
	int m_targetCount = -1;
	//�G�t�F�N�g�J�E���^�[
	int m_effectCount = 0;
	//HP
	float m_testHP = 70.0f;
	//�q�b�g���̃N�[���^�C��
	float m_hitCoolTime = 1.5f;
	//�������U���̃N�[���^�C��
	float m_longAttackCoolTime = 5.0f;
	//�m�b�N�o�b�N�̔���̃N�[���^�C��
	float m_knockBackTime = 0.3f;
/// <summary>
/// �u�[���^
/// </summary>
	bool m_isNowAttack = false;//�U�����Ȃ�true
	//�m�b�N�o�b�N����
	bool m_isKnockBack = false;
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
	bool m_isUnderDefense = false;//�K�[�h���Ȃ�true
	bool m_isTakeAim = false;
	bool m_isLockOn = false;
	bool m_isLockOnCamera = false;
	bool m_isEffect = false;		//�G�t�F�N�g���o�Ă���Ȃ�true
	bool m_isOver = false;
	bool m_isUnderFlying_Back = false;//������΂��ꒆ�Ȃ�true
	bool m_isFlying_Back_Tail = false;		//�K���U���̍U���q�b�g��true
	bool m_isFlying_Back_FlyAttack = false;		//����ːi�̍U���q�b�g��true
	bool m_isFlying_Back_Landing = false;
	bool m_isSound = false;					//���ʉ�

	Model m_model;			// ���f��
	Animation m_animation;	// �A�j���[�V����
	AnimationClip m_animationClipArray[enAnimClip_Num];	// �A�j���[�V�����N���b�v
	Quaternion m_rotation= Quaternion::Identity;;	// ��]
	Sprite m_sprite;	// �X�v���C�g
	Skeleton m_skeleton;	// �X�P���g��
	ModelRender m_modelRender;
	CharacterController m_charaCon;	//�L�����N�^�[�R���g���[���[
	PlayerStatus *m_playerStatus = nullptr;
	EffectEmitter* effectEmitter = nullptr;
	SoundSource* m_bitAttack = nullptr;			//No9
	SoundSource* m_defense = nullptr;			//No10
	SoundSource* m_guardBreak = nullptr;		//No11
	SoundSource* m_run = nullptr;				//No12
	SoundSource* m_walk = nullptr;				//No13
	SoundSource* m_walkAttack = nullptr;		//No14

};
