#include "stdafx.h"
#include "BossFlyPoint.h"
#include "Enemy_Boss.h"


namespace
{
    const float TO_FLYPOINT_DISTANCE = 2000.0f;	//基準となる座標からフライポイントまでの距離
}

BossFlyPoint::BossFlyPoint()

{	//アタックポイントのナンバーを初期化する
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
    //ポイントを設置する方向
    Vector3 direction = Vector3::AxisZ;

    //ポイントを設置する方向を回転させるクオータニオン
    Quaternion directionRot;

    //360度をフライポイント配列の要素数で割って等間隔で置くための角度を設定する
    directionRot.SetRotationDegY(360.0f / FLY_POINT_NUM);

    //ポイントの配列を回して座標を設定する
    for (FlyPoint& attackPoint : m_flyPointList)
    {
        //ポイントの座標を設定する
        attackPoint.m_pos = position + direction * TO_FLYPOINT_DISTANCE;

        //設置する方向を回転
        directionRot.Apply(direction);
    }

}

BossFlyPoint::FlyPoint* BossFlyPoint::GetFlyPoint(Vector3 position)
{
    //小さい数字にする
    float distance = 1.0f;

    //一番遠いフライポイントのアドレスを入れるポインタ
    FlyPoint* point = nullptr;

    //フライポイントの配列を回す
    for (FlyPoint& flypoint : m_flyPointList)
    {
        //フライポイントの距離を求める
        float flypointDistance = (flypoint.m_pos - position).Length();

        //保持しているフライポイントの距離が
        //今回出したフライポイントの距離より大きければ
        if (distance < flypointDistance)
        {
            //保持しているフライポイントの距離を
            //今回出したフライポイントに変更する
            distance = flypointDistance;
            //そのフライポイントのアドレスを保存する
            point = &flypoint;
        }
    }
    //一番遠いフライポイントのアドレスを返す
    return point;
}

BossFlyPoint::FlyPoint* BossFlyPoint::ReGetFlyPoint(Enemy_Boss* boss, FlyPoint* flypoint)
{
    //小さい数字にする
    float distance = 1.0f;

    //一番遠いフライポイントのアドレスを入れるポインタ
    FlyPoint* point = nullptr;

    //フライポイントの配列を回す
    for (FlyPoint& flypoint : m_flyPointList)
    {
        //フライポイントの距離を求める
        float flypointDistance = (flypoint.m_pos - boss->GetPos()).Length();
    
        //保持しているフライポイントの距離が
        //今回出したフライポイントの距離より大きければ
        if (distance < flypointDistance)
        {
            //保持しているフライポイントの距離を
            //今回出したフライポイントに変更する
            distance = flypointDistance;
            //そのフライポイントのアドレスを保存する
            point = &flypoint;
        }
        
    }
    //一番遠いフライポイントのアドレスを返す
    return point;
}
