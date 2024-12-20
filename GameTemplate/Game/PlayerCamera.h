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
	Player* m_player = nullptr;	//プレイヤー。
	Vector3 m_toCameraPos = Vector3::One;	//注視点から視点に向かうベクトル。
	Vector3 m_tstsPos;

};

