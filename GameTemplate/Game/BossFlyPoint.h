#pragma once

namespace 
{
	const int FLY_POINT_NUM = 8;
}
class Enemy_Boss;
class BossFlyPoint
{
public:
	//距離をとる時に移動する座標
	struct FlyPoint
	{
		Vector3 m_pos = Vector3::Zero;//フライポイントの座標
		int m_number;					//フライポイントの要素番号
	};
	BossFlyPoint();
	~BossFlyPoint();

	//フライポイントの座標を更新する関数
	void Update(Vector3 position);
	//近くにある使用可能なフライポイントをアドレスを取得する関数
	FlyPoint* GetFlyPoint(Vector3 position);
	//遠いフライポイントを取得しなおす関数
	FlyPoint* ReGetFlyPoint(Enemy_Boss* boss, FlyPoint* flypoint);

private:
	FlyPoint m_flyPointList[FLY_POINT_NUM];
};

