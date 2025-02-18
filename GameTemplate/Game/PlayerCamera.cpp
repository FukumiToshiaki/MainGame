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
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(0.0f, 500.0f, -750.0f);
	m_toCameraPos *= 0.3f;
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("player");
	//カメラのニアクリップとファークリップを設定。
	g_camera3D->SetFar(30000.0f);

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
////カメラを更新
////注視点を計算
//	Vector3 target = m_player->Get_PlayerPos();
//	//注視点 プレイヤーの座標に設定
//	target.y += CAMERATARGET_Y;
//	target.z -= CAMERATARGET_Z;
//
//	//視点を計算する。
//	Vector3 toCameraPosOld = m_toCameraPos;
//
//	//パッドの入力を使ってカメラを回す
//	float x = g_pad[0]->GetRStickXF();
//	float y = g_pad[0]->GetRStickYF();
//	//Y軸周りの回転
//	Quaternion qRot;
//	qRot.SetRotationDeg(Vector3::AxisY, 2.4f * x);
//	qRot.Apply(m_toCameraPos);
//	//X軸周りの回転。
//	Vector3 axisX;
//	if (y != 0.0f) {
//		axisX.Cross(Vector3::AxisY, m_toCameraPos);
//		axisX.Normalize();
//		qRot.SetRotationDeg(axisX, 1.6f * y);
//	}
//	qRot.Apply(m_toCameraPos);
//	//カメラの回転の上限をチェックする。
//	//注視点から視点までのベクトルを正規化する。
//	//正規化すると、ベクトルの大きさが１になる。
//	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
//	Vector3 toPosDir = m_toCameraPos;
//	toPosDir.Normalize();
//	if (toPosDir.y < -0.7f) {
//		//カメラが上向きすぎ。
//		m_toCameraPos = toCameraPosOld;
//	}
//	else if (toPosDir.y > 0.7f) {
//		//カメラが下向きすぎ。
//		m_toCameraPos = toCameraPosOld;
//	}
//
//
//	//視点を計算する。
//	Vector3 pos = target + m_toCameraPos;
//
//	//メインカメラに注視点と視点を設定
//	g_camera3D->SetTarget(target);
//	g_camera3D->SetPosition(pos);
//	g_camera3D->SetNear(1.0f);
//	g_camera3D->SetFar(10000.0f);
//	//カメラの更新
//	g_camera3D->Update();
		//カメラを更新。
	//注視点を計算する。
	Vector3 target = m_player->Get_PlayerPos();
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 120.0f;
	target += g_camera3D->GetForward() * 20.0f;

	Vector3 toCameraPosOld = m_toCameraPos;
	//パッドの入力を使ってカメラを回す。
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 3.5f * x);
	qRot.Apply(m_toCameraPos);
	//X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 3.5f * y);
	qRot.Apply(m_toCameraPos);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}

	//視点を計算する。
	Vector3 pos = target + m_toCameraPos;

	g_camera3D->SetPosition(pos);
	g_camera3D->SetTarget(target);
}

void PlayerCamera::LockOnCamera()
{
	Vector3 target = m_player->GetTargetPosition();
	Vector3 toPos = target - m_player->Get_PlayerPos();
	float r = toPos.Length() + 200.0f;
	//toPos.y = 0.0f;
	toPos.Normalize();
	Vector3 position = target - toPos * r;
	position.y = m_player->Get_PlayerPos().y + 200.0f;

	g_camera3D->SetPosition(position);
	g_camera3D->SetTarget(target);
}
