#pragma once
#include <SpriteRender.h>
#define DecreaseTransitionIN0	m_decrease_TRAN = en_Standby_TRAN;
#define DecreaseTransitionIN1	m_decrease_TRAN = en_DelayTimeON_TRAN
#define DecreaseTransitionIN2	m_decrease_TRAN = en_DelayTimeLoop_TRAN;
#define DecreaseTransitionIN3	m_decrease_TRAN = en_TransparentDecreaseCalc_TRAN;
#define DecreaseTransitionIN4	m_decrease_TRAN = en_TransparentDecreaseON_TRAN
#define DecreaseTransition0 m_decrease_TRAN == en_Standby_TRAN
#define DecreaseTransition1 m_decrease_TRAN == en_DelayTimeON_TRAN
#define DecreaseTransition2	m_decrease_TRAN == en_DelayTimeLoop_TRAN
#define DecreaseTransition3	m_decrease_TRAN == en_TransparentDecreaseCalc_TRAN
#define DecreaseTransition4	m_decrease_TRAN == en_TransparentDecreaseON_TRAN
class Game;
class Player;
class Player_HP_UI :public IGameObject
{
public:
	//����UI�����҈�
	enum DecreaseTransition {
		//�ҋ@0
		en_Standby_TRAN,
		//�x���J�n1
		en_DelayTimeON_TRAN,
		//�x������2
		en_DelayTimeLoop_TRAN,
		//����UI�����v�Z3
		en_TransparentDecreaseCalc_TRAN,
		//����UI�����J�n4
		en_TransparentDecreaseON_TRAN
	};
	////////////////////////////////////////
	//�֐�
	Player_HP_UI() {}
	~Player_HP_UI() {}
	//�X�^�[�g�֐�
	bool Start();
	//�A�b�v�f�[�g
	void Update();
	//�����v�Z
	void Adjustment();
	//���߃o�[�����v�Z
	void AdjustmentTransparent();
	//���f��
	void Render(RenderContext& renderContext);
	//�L�����̕\��
	void Model1P();
	//HP��������
	void DecreaseHP(float decrease)
	{
		//HP�������l���炷
		m_nowhp -= decrease;
		return;
	}

	float GetNowHP()
	{
		return m_nowhp;
	}

private:
	/////////////////////////////////////////�����o�ϐ�
	//HPUI
	SpriteRender m_hpUI_A;
	//HP�o�[
	SpriteRender m_hpUI_B;
	//����HP�o�[
	SpriteRender m_hpUI_C;
	//����UI�����J��
	DecreaseTransition m_decrease_TRAN = en_Standby_TRAN;
	//�Q�[��
	Game* m_game = nullptr;
	//�v���C���[�x�[�X
	Player* m_player = nullptr;
	/////////////////////////////////////////�ϐ�
	//�ő�HP
	float m_fullhp = 50;
	//����HP�@
	float m_nowhp = m_fullhp;
	//�ߋ�HP
	float m_oldhp = m_fullhp;
	//����hp�o�[�X�P�[��(�������̂�m_hpUI_B�Az�͌Œ�)
	Vector3 m_scale_B = { 1.0,1.0,1.0 };
	//���ݓ���hp�o�[�X�P�[��(�������̂�m_hpUI_C�Az�͌Œ�)
	Vector3 m_scale_C = { 1.0,1.0,1.0 };
	//�����x���^�C�}�[
	float m_delaytimer = 0.0f;
	//���ߌ�������
	Vector3 m_changeS_C = m_scale_C;
	//���ݓ��ߌ����l
	Vector3 m_nowScale = m_hpUI_C.GetScale();
	//�v���C���[�̕\���̃|�W�V����
	Vector3 m_pos = { 0.0f,0.0f,0.0f };
	//�v���C���[�̕\���̍ŏ��̃|�W�V����
	Vector3 m_firstPos = { 0.0f,0.0f,0.0f };
	//�X�v���C�g�|�W�V����
	Vector2 m_spritePos = Vector2::Zero;
	//�X�v���C�g�����_�[
	SpriteRender m_spriteRender;
	/////////////////////////////////////////�����ݒ�n��

};