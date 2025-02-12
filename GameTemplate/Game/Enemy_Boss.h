#pragma once
class Player;
class Game;
class IBossState;
class Boss_Shoot;
class Boss_HP_UI;
#include "EnemyBase.h"
#include "BossFlyPoint.h"
#include "sound/SoundEngine.h"

class Enemy_Boss : public EnemyBase
{
public:
	Enemy_Boss() {};
	~Enemy_Boss() {};
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	//void FlyAttackMove();
	// �X�P���g����������
	void InitSkeleton();
	// �A�j���[�V�������������B
	void InitAnimation();
	//��]�̏�����
	void Rotation(int rotation);
	//�ߋ����U���̊��݂�
	void MeleeAttack();
	//�������U���̒n�ォ��̃u���X
	void Shoot();//(int movespeed, int hitstartframe, int hitendframe);
	//��Z��̋x�e���[�V����
	void Rest();
	//�R���W�����̓����蔻��
	void Hit(int damagemagnification);
	//���݂��U���̃R���W����
	void MeleeAttackCollision(int collision_melee);
	//�K���̓ガ����
	void TailAttack();
	//�K���̓ガ�����̃R���W����
	void TailAttackCollision(int collision_tail);
	//�󒆓ːi
	void FlyAttack(float movespeed);
	//�󒆓ːi�̓����蔻��
	void FlyAttackCollision(int collision_flyattack);
	//�K�[�h�̔���
	void Defence();
	//�K�[�h�̃R���W����
	void DefenceCollision(int break_magnification,int collision_defense);
	// �A�j���[�V�����C�x���g�p�̊֐��B
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	//�������Ƃ�֐�
	void FlyPos(float movespeed);
	//�K�E�Z�̙��K
	void Scream();
	//�K�E�Z�̃R���W����
	void ScreamCollision(int collision_scream);
	//���n���̃_���[�W
	void Landing();
	//���n���̃R���W����
	void LandingDamage(int collision_landing);
	//HP��30%�ȉ��ɂȂ�������BGM�֐�
	void BGM();
	//��u���X�̎�
	void FlyShoot();
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
		enState_Defence_Counter_Animation,
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
		enState_Defence_Counter,
		enState_Rest,
		enState_Move,
		enState_Die,
		enState_Takeoff,
		enState_Fly,
		enState_Landing,
		enState_Landing_Back,
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

	

	void SetisUnderMelee(bool UnderMelee)
	{
		m_isUnderAttackMelee = UnderMelee;
	}

	void SetisUnderTail(bool UnderTail)
	{
		m_isUnderTail = UnderTail;
	}

	void SetisUnderFlyAttack(bool UnderFlyAttack)
	{
		m_isUnderFlyAttack = UnderFlyAttack;
	}

	float GetHP()
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

	void SetidUnderDefencePattern(bool UnderDefence)
	{
		m_isUnderDefence = UnderDefence;
	}

	void SetEffectCount(int effectcount) {
		m_effectCount = effectcount;
	}

	void SetisScream_Normal(bool Scream) {
		m_isScream_Normal = Scream;
	}
	bool GetisScream_Normal()	{
		return m_isScream_Normal;
	}
	bool GetisScream_Set() {
		return m_isScream_Set;
	}

protected:
	/// <summary>
	/// �x�N�^�[
	/// </summary>
	Vector3 m_distance = Vector3::Zero;
	Vector3 m_diff = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;	//�ړ����x
	Vector3	m_scale = Vector3::One;			//�傫���B
	Vector3	m_forward = Vector3::AxisZ;					//�G�l�~�[�̐��ʃx�N�g���B
	Vector3 m_collisionPos = Vector3::Zero;
	Vector3 m_flyPos = Vector3::Zero;
	//Vector3 m_moveSpeed_Shoot = Vector3::Zero;
	//Vector3 m_shootPos = Vector3::Zero;
	//Vector3 m_shot = Vector3::Zero;
	Vector3 diff = Vector3::Zero;
	/// <summary>
	/// �N���X
	/// </summary>
	//BossPattern* m_bossPattern = nullptr;
	/// <summary>
	/// �ϐ�
	/// </summary>
	int m_attack_Rand = 0;
	int m_attack_Count = -1;
	//HP
	float m_testHP = 19.0f;
	//��񂾎��̃{�[���擾�̂���
	int m_flyBoneId = 0;
	//�K�E�Z�������߂̃J�E���g
	int m_screamCount = 0;
	//�G�t�F�N�g�J�E���^�[
	int m_effectCount = 0;

	float m_angle = 0.0f;
	float m_radius = 2.0f;
	//�q�b�g���̃N�[���^�C��
	float m_hitCoolTime = 2.0f;
	//float m_testFlyTime = 3.0f;
	/// <summary>
	/// �u�[���^
	/// </summary>
	
	bool m_isUnderAttackMelee = false;	//�U�����Ȃ�true
	bool m_isUnderTail = false;			//�U�����Ȃ�true
	bool m_isUnderFlyAttack = false;	//�U�����Ȃ�true
	bool m_isClear = false;				//�N���A����
	bool m_isUnderPattern = false;		//�s�����Ȃ�true
	bool m_isUnderDefence = false;		//�h�䒆�Ȃ�true
	bool m_isUnderScream = false;		//�K�E�Z���Ȃ�true
	bool m_isUnderLanding = false;		//���n���Ȃ�true
	bool m_isUnderFly = false;			//�����ł���Ȃ�true
	bool m_isUnderTakeoff= false;		//��ɔ�ڂ��Ƃ��Ă���Ȃ�true
	bool m_isScream = false;		//
	bool m_isScream_Normal = false;				//���K���ʏ�s���őI�΂ꂽ��true
	bool m_isEffect = false;		//�G�t�F�N�g���o�Ă���Ȃ�true
	bool m_isFlyKeepDistance = false;	//�����ŋ������Ƃ��Ă���Ȃ�true
	bool m_isScream_Set = false;

	ModelRender m_modelRender;
	Player* m_player = nullptr;
	Boss_HP_UI* m_boss_HP_UI = nullptr;
	CollisionObject* m_collision = nullptr;
	CollisionObject* m_flyPosCollision = nullptr;
	//CollisionObject* m_shootCollision = nullptr;
	Game* m_game = nullptr;
	IBossState* m_Iboss_State = nullptr;
	Boss_Shoot* m_boss_Shoot = nullptr;
	Animation m_animation;	// �A�j���[�V����
	Skeleton m_skeleton;	// �X�P���g��
	Model m_model;			// ���f��
	Quaternion	m_rotation=Quaternion::Identity;							//��]
	Quaternion m_wait=Quaternion::Identity;
	AnimationClip m_animationClipArray[enAnimClip_Num];	// �A�j���[�V�����N���b�v
	CharacterController m_charaCon;	//�L�����N�^�[�R���g���[���[
	BossFlyPoint::FlyPoint* m_flyPoint = nullptr;
	SoundSource* m_bossLastButtle = nullptr;
	SoundSource* m_bossButtle = nullptr;
	
	//EffectEmitter* Boss_Shoot_Start = nullptr;
};

