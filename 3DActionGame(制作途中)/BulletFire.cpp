#include "stdafx.h"
#include "BulletFire.h"
#include "BulletCreator.h"
#include "Enemy.h"

void BulletFire::Init(){}

void BulletFire::Update()
{
	if (isActiveBarrage)
	{
		if (Character* obj = dynamic_cast<Character*>(character))
		{
			FireHorizontalBarrage(obj->GetBulletSpawnPos());
		}
	}
}

// 全方向に弾を発射
void BulletFire::FireAllDirection(const VECTOR& pos, int bulletNum,float angleOffset)
{
	// 弾の発射方向
	VECTOR bulletFireDirection = VGet(0.0f, 0.0f, 1.0f);	// 初期値は+Z方向
	// 角度の基準値を代入
	bulletFireDirection = RotateXZ(bulletFireDirection, angleOffset);
	// 弾の発射座標
	VECTOR bulletFirePos = pos;
	// 弾ごとの角度間隔
	float bulletAngleDiff = DX_TWO_PI_F / bulletNum;

	// 一度に発射する数だけループ
	for (int i = 0; i < bulletNum + 1; i++)
	{
		// 弾を生成
		BulletCreator::GetBulletCreator().Create(pos, bulletFireDirection);

		// 角度変更
		bulletFireDirection = RotateXZ(bulletFireDirection, bulletAngleDiff);
	}
}

// 水平方向にのみ弾幕発射
void BulletFire::FireHorizontalBarrage(const VECTOR& pos)
{
	// フレームカウントが0かつループ回数内のみ発射
	if (BarrageFrameCount == 0 && barrageFireLoopCount <= BARRAGE_FIRE_LOOP_NUM)
	{
		FireAllDirection(pos, BULLET_FIRE_ALL_DIRECTION_NUM, barrageFireAngle);
		barrageFireLoopCount++;
		barrageFireAngle += BARRAGE_ANGLE_OFFSET;
	}

	BarrageFrameCount++;
	if (BarrageFrameCount == 10)
	{
		BarrageFrameCount = 0;
	}

	if (barrageFireLoopCount == BARRAGE_FIRE_LOOP_NUM + 1)
	{
		isActiveBarrage = false;
		barrageFireLoopCount = 0;
		barrageFireAngle = 0;
	}
}

// 水平方向の回転
VECTOR BulletFire::RotateXZ(const VECTOR& dir, float angle)
{
	float cos = cosf(angle);
	float sin = sinf(angle);

	return VGet(
		dir.x * cos - dir.z * sin,	// 回転後のx
		dir.y,						// yはそのまま
		dir.x * sin + dir.z * cos	// 回転後のz
	);
}