#pragma once
class Player;
class PlayerCamera : public IGameObject
{
public:
	PlayerCamera();
	~PlayerCamera();
	bool Start();
	void Update();
	void NormalCamera();
	void LockOnCamera();

private:
	Player* m_player = nullptr;	//�v���C���[�B
	Vector3 m_toCameraPos = Vector3::One;	//�����_���王�_�Ɍ������x�N�g���B
	Vector3 m_tstsPos;

};

