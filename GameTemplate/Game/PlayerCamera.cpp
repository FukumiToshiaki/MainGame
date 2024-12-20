#include "stdafx.h"
#include "PlayerCamera.h"
#include "Player.h"

#define CAMERATARGET_Y 130.0f
#define CAMERATARGET_Z 60.0f
#define CAMERA_POS_Y 60.0f

PlayerCamera::PlayerCamera()
{

}

PlayerCamera::~PlayerCamera()
{

}

bool PlayerCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(0.0f, 300.0f, -600.0f);
	m_toCameraPos *= 0.3f;
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("player");
	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ�B
	/*g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(30000.0f);*/

	return true;
}

void PlayerCamera::Update()
{
	if (m_player->GetIsLockOn() == false)
	{
		NormalCamera();
	}
	else {
		LockOnCamera();
	}

}

void PlayerCamera::NormalCamera()
{
	///////////////////////////////////////////////////////////
////�J�������X�V
////�����_���v�Z
//	Vector3 target = m_player->Get_PlayerPos();
//	//�����_ �v���C���[�̍��W�ɐݒ�
//	target.y += CAMERATARGET_Y;
//	target.z -= CAMERATARGET_Z;
//
//	//���_���v�Z����B
//	Vector3 toCameraPosOld = m_toCameraPos;
//
//	//�p�b�h�̓��͂��g���ăJ��������
//	float x = g_pad[0]->GetRStickXF();
//	float y = g_pad[0]->GetRStickYF();
//	//Y������̉�]
//	Quaternion qRot;
//	qRot.SetRotationDeg(Vector3::AxisY, 2.4f * x);
//	qRot.Apply(m_toCameraPos);
//	//X������̉�]�B
//	Vector3 axisX;
//	if (y != 0.0f) {
//		axisX.Cross(Vector3::AxisY, m_toCameraPos);
//		axisX.Normalize();
//		qRot.SetRotationDeg(axisX, 1.6f * y);
//	}
//	qRot.Apply(m_toCameraPos);
//	//�J�����̉�]�̏�����`�F�b�N����B
//	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
//	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
//	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
//	Vector3 toPosDir = m_toCameraPos;
//	toPosDir.Normalize();
//	if (toPosDir.y < -0.7f) {
//		//�J����������������B
//		m_toCameraPos = toCameraPosOld;
//	}
//	else if (toPosDir.y > 0.7f) {
//		//�J�����������������B
//		m_toCameraPos = toCameraPosOld;
//	}
//
//
//	//���_���v�Z����B
//	Vector3 pos = target + m_toCameraPos;
//
//	//���C���J�����ɒ����_�Ǝ��_��ݒ�
//	g_camera3D->SetTarget(target);
//	g_camera3D->SetPosition(pos);
//	g_camera3D->SetNear(1.0f);
//	g_camera3D->SetFar(10000.0f);
//	//�J�����̍X�V
//	g_camera3D->Update();
		//�J�������X�V�B
	//�����_���v�Z����B
	Vector3 target = m_player->Get_PlayerPos();
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += 80.0f;
	target += g_camera3D->GetForward() * 20.0f;

	Vector3 toCameraPosOld = m_toCameraPos;
	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y������̉�]
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 3.5f * x);
	qRot.Apply(m_toCameraPos);
	//X������̉�]�B
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 3.5f * y);
	qRot.Apply(m_toCameraPos);
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//�J����������������B
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//�J�����������������B
		m_toCameraPos = toCameraPosOld;
	}

	//���_���v�Z����B
	Vector3 pos = target + m_toCameraPos;

	g_camera3D->SetPosition(pos);
	g_camera3D->SetTarget(target);
}

void PlayerCamera::LockOnCamera()
{
	Vector3 target = m_player->GetTargetPosition();
	Vector3 toPos = target - m_player->Get_PlayerPos();
	float r = toPos.Length() + 200.0f;
	toPos.y = 0.0f;
	toPos.Normalize();
	Vector3 position = target - toPos * r;
	position.y = m_player->Get_PlayerPos().y + 200.0f;

	g_camera3D->SetPosition(position);
	g_camera3D->SetTarget(target);
}
