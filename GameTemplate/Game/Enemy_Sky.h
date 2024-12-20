#pragma once
class Player;
class Game;
#include "EnemyBase.h"

class Enemy_Sky : public EnemyBase
{
public:
	Enemy_Sky() {};
	~Enemy_Sky() {};
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	// �X�P���g����������
	void InitSkeleton();
	// �A�j���[�V�������������B
	void InitAnimation();
	//�L�����̊p�x�̒���
	void Rotation();

	// �A�j���[�V�����N���b�v�̔ԍ���\���񋓌^�B
	enum EnAnimationClip {
		enAnimClip_Idle,	// 0 : �ҋ@�A�j���[�V�����A
		enAnimClip_Walk,	// 2 :�U��
		enAnimClip_Damage,	// 2 :�U��
		enAnimClip_Attack,	// 2 :�U��
		enAnimClip_Death,	// 2 :�U��
		enAnimClip_Num,		// 3 :�A�j���[�V�����N���b�v�̐��B�A�j���[�V������ǉ�����Ȃ炱�̏�ɍ��

	};

private:
	/// <summary>
	/// �x�N�^�[
	/// </summary>
	Vector3 m_moveSpeed;	//�ړ����x
	Vector3		m_forward = Vector3::AxisZ;					//�G�l�~�[�̐��ʃx�N�g���B
	Vector3						m_scale = Vector3::One;			//�傫���B

	/// <summary>
	/// �N���X
	/// </summary>
	Player* m_player = nullptr;
	CollisionObject* m_collision = nullptr;
	Game* m_game = nullptr;


	/// <summary>
	/// �ϐ�
	/// </summary>
	int test = 0;


	/// <summary>
	/// �u�[���^
	/// </summary>
	bool m_isDistance = false;

	ModelRender m_modelRender;
	Animation m_animation;	// �A�j���[�V����
	AnimationClip m_animationClipArray[enAnimClip_Num];	// �A�j���[�V�����N���b�v
	Skeleton m_skeleton;	// �X�P���g��
	Model m_model;			// ���f��
	Quaternion	m_rotation;							//��]

};