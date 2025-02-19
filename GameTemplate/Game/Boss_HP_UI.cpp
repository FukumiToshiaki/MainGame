#include "stdafx.h"
#include "Boss_HP_UI.h"
#include "Game.h"
#include "Enemy_Boss.h"

namespace {
	//HP�̈ʒu
	const Vector3 n_position_HP{ 110.0f,410.0f,0.0f };
	//HP�̈ʒu
	const Vector3 n_position_Damage{ 110.0f,410.0f,0.0f };
	//B��C�̊�_
	const Vector2 n_pivot_HP_Damage{ 0,0.5 };
	//�X�P�[��
	const Vector3 n_scale{ 0.8f,0.7f,0.7f };
	//delaytimer�̏����ݒ莞��
	float m_delaytime = 0.7f;
}

bool Boss_HP_UI::Start()
{
	m_game = FindGO<Game>("game");
	m_enemy_boss = FindGO<Enemy_Boss>("enemy_boss");//�ꏊ��������
	//�摜�ݒ�
	m_hpUI_A.Init("Assets/Sprite/Boss_HP_RED.DDS", 900.0f, 600.0f);
	//�摜�ݒ�
	m_hpUI_B.Init("Assets/Sprite/Boss_HP.DDS", 900.0f, 600.0f);
	//�ʒu�ݒ�
	m_hpUI_A.SetPosition(n_position_HP);
	//�ʒu�ݒ�
	m_hpUI_B.SetPosition(n_position_Damage);
	//��_�ݒ�
	m_hpUI_A.SetPivot(n_pivot_HP_Damage);
	m_hpUI_B.SetPivot(n_pivot_HP_Damage);
	//�X�P�[��
	m_hpUI_A.SetScale(n_scale);
	m_hpUI_B.SetScale(n_scale);
	m_firstPos = m_pos;
	return true;
}

void Boss_HP_UI::Update()
{
	//���Z�v�Z����
	Adjustment();
	//���ߌ��Z�v�Z����
	AdjustmentTransparent();
	//�`�揈��
	m_hpUI_A.Update();
	m_hpUI_B.Update();
}

void Boss_HP_UI::Adjustment()
{
	//0�ȉ��ɂ��Ȃ�
	if (m_nowhp < 0) {
		m_nowhp = 0;
	}
	//����HP������������
	if (m_nowhp < m_oldhp)
	{
		float a = m_nowhp;
		float b = m_fullhp;
		//����HP�ƍő�HP�̊������v�Z
		float ratio = a / b;
		//���݂�m_hpUI_B��scale.x�Ɗ������v�Z
		Vector3 changeS_B = m_scale_B;
		changeS_B.x = m_scale_B.x * ratio;
		m_hpUI_B.SetScale(changeS_B);
		//�ߋ�HP�Ɍ��݂�HP��ۑ�
		m_oldhp = m_nowhp;
		//���ߒx���J�n
		DecreaseTransitionIN1;
	}
}

void Boss_HP_UI::AdjustmentTransparent()
{
	if (DecreaseTransition0) {
		return;
	}
	if (DecreaseTransition3 || DecreaseTransition4)
	{
		if (DecreaseTransition3)
		{
			float a = m_nowhp;
			float b = m_fullhp;
			//����HP�ƍő�HP�̊������v�Z
			float ratio = a / b;
			//���݂�m_hpUI_B��scale.x�Ɗ������v�Z
			m_changeS_C.x = m_scale_C.x * ratio;
			//���������Ɉڍs
			DecreaseTransitionIN4;
		}
		//���������A�J��Ԃ������Ōv�Z���������ƌ��݂�Scale.x�Ɠ��l�ɂȂ�܂Ō��Z
		if (DecreaseTransition4)
		{
			//�߂��Ⴍ����ׂ������炷
			m_nowScale.x -= 0.009f;
			//0�ȉ���������0�ɖ߂�
			if (m_nowScale.x < 0)
			{
				m_nowScale.x = 0;
			}
			//�傫����ύX����
			m_hpUI_C.SetScale(m_nowScale);

			//����scale���ύX��scale�ȉ��ɂȂ�����
			if (m_changeS_C.x > m_nowScale.x)
			{
				//�O�̂��ߏ�����
				m_changeS_C = m_scale_C;
				m_nowScale = m_hpUI_C.GetScale();
				//�X�^���o�C�Ɉڍs
				DecreaseTransitionIN0;
				return;
			}
			//�ύX��ȏ�̏ꍇ
			else
				return;
		}
	}
	//�������牺�̏����͌����x���̃^�C�}�[����

	//delaytimer��������
	if (0.0 < m_delaytimer && DecreaseTransition2)
	{
		m_delaytimer -= g_gameTime->GetFrameDeltaTime();
	}
	//delaytimer��0�ɂȂ�����
	else if (m_delaytimer < 0.0 && DecreaseTransition2)
	{
		//����UI���Z�����v�Z�����Ɉڍs
		DecreaseTransitionIN3;
		return;
	}

	//m_delayloop��true�̎��͂��������͏������Ȃ�
	if (DecreaseTransition2)
		return;

	//���ߌ����x���^�C�}�[������
	m_delaytimer = m_delaytime;
	//�x�������Ɉڍs
	DecreaseTransitionIN2;
}

void Boss_HP_UI::Render(RenderContext& rc)
{
	m_game = FindGO<Game>("game");
	//HPUI�̕`�揈������
	m_hpUI_A.Draw(rc);
	//�o�[�̕`�揈�������
	m_hpUI_B.Draw(rc);
}