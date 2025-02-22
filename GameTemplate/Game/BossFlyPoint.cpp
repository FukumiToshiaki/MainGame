#include "stdafx.h"
#include "BossFlyPoint.h"
#include "Enemy_Boss.h"


namespace
{
    const float TO_FLYPOINT_DISTANCE = 2000.0f;	//��ƂȂ���W����t���C�|�C���g�܂ł̋���
}

BossFlyPoint::BossFlyPoint()

{	//�A�^�b�N�|�C���g�̃i���o�[������������
    for (int i = 0; i < FLY_POINT_NUM; i++)
    {
        m_flyPointList[i].m_number = i;
    }

}

BossFlyPoint::~BossFlyPoint()
{
}

void BossFlyPoint::Update(Vector3 position)
{
    //�|�C���g��ݒu�������
    Vector3 direction = Vector3::AxisZ;

    //�|�C���g��ݒu�����������]������N�I�[�^�j�I��
    Quaternion directionRot;

    //360�x���t���C�|�C���g�z��̗v�f���Ŋ����ē��Ԋu�Œu�����߂̊p�x��ݒ肷��
    directionRot.SetRotationDegY(360.0f / FLY_POINT_NUM);

    //�|�C���g�̔z����񂵂č��W��ݒ肷��
    for (FlyPoint& attackPoint : m_flyPointList)
    {
        //�|�C���g�̍��W��ݒ肷��
        attackPoint.m_pos = position + direction * TO_FLYPOINT_DISTANCE;

        //�ݒu�����������]
        directionRot.Apply(direction);
    }

}

BossFlyPoint::FlyPoint* BossFlyPoint::GetFlyPoint(Vector3 position)
{
    //�����������ɂ���
    float distance = 1.0f;

    //��ԉ����t���C�|�C���g�̃A�h���X������|�C���^
    FlyPoint* point = nullptr;

    //�t���C�|�C���g�̔z�����
    for (FlyPoint& flypoint : m_flyPointList)
    {
        //�t���C�|�C���g�̋��������߂�
        float flypointDistance = (flypoint.m_pos - position).Length();

        //�ێ����Ă���t���C�|�C���g�̋�����
        //����o�����t���C�|�C���g�̋������傫�����
        if (distance < flypointDistance)
        {
            //�ێ����Ă���t���C�|�C���g�̋�����
            //����o�����t���C�|�C���g�ɕύX����
            distance = flypointDistance;
            //���̃t���C�|�C���g�̃A�h���X��ۑ�����
            point = &flypoint;
        }
    }
    //��ԉ����t���C�|�C���g�̃A�h���X��Ԃ�
    return point;
}

BossFlyPoint::FlyPoint* BossFlyPoint::ReGetFlyPoint(Enemy_Boss* boss, FlyPoint* flypoint)
{
    //�����������ɂ���
    float distance = 1.0f;

    //��ԉ����t���C�|�C���g�̃A�h���X������|�C���^
    FlyPoint* point = nullptr;

    //�t���C�|�C���g�̔z�����
    for (FlyPoint& flypoint : m_flyPointList)
    {
        //�t���C�|�C���g�̋��������߂�
        float flypointDistance = (flypoint.m_pos - boss->GetPos()).Length();
    
        //�ێ����Ă���t���C�|�C���g�̋�����
        //����o�����t���C�|�C���g�̋������傫�����
        if (distance < flypointDistance)
        {
            //�ێ����Ă���t���C�|�C���g�̋�����
            //����o�����t���C�|�C���g�ɕύX����
            distance = flypointDistance;
            //���̃t���C�|�C���g�̃A�h���X��ۑ�����
            point = &flypoint;
        }
        
    }
    //��ԉ����t���C�|�C���g�̃A�h���X��Ԃ�
    return point;
}
