#pragma once

namespace 
{
	const int FLY_POINT_NUM = 8;
}
class Enemy_Boss;
class BossFlyPoint
{
public:
	//�������Ƃ鎞�Ɉړ�������W
	struct FlyPoint
	{
		Vector3 m_pos = Vector3::Zero;//�t���C�|�C���g�̍��W
		int m_number;					//�t���C�|�C���g�̗v�f�ԍ�
	};
	BossFlyPoint();
	~BossFlyPoint();

	//�t���C�|�C���g�̍��W���X�V����֐�
	void Update(Vector3 position);
	//�߂��ɂ���g�p�\�ȃt���C�|�C���g���A�h���X���擾����֐�
	FlyPoint* GetFlyPoint(Vector3 position);
	//�����t���C�|�C���g���擾���Ȃ����֐�
	FlyPoint* ReGetFlyPoint(Enemy_Boss* boss, FlyPoint* flypoint);

private:
	FlyPoint m_flyPointList[FLY_POINT_NUM];
};

