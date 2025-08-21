#include "stdafx.h"
#include "BulletFire.h"
#include "BulletCreator.h"
#include "Enemy.h"

void BulletFire::Init(){}

void BulletFire::SetCharacter(Character* characterPtr)
{
	character = characterPtr;
}

void BulletFire::Update()
{
	if (character)
	{
		if (isActiveHorizontalBarrage)
		{
			FireHorizontalBarrage(character->GetBulletSpawnPos());
		}

		if (isActiveWaveBarrage)
		{
			FireWaveBarrage(character->GetBulletSpawnPos());
		}
	}
}

// 全方向に弾を発射
void BulletFire::FireAllDirection(const VECTOR& pos, int bulletNum,float angleHOffset, float angleVOffset)
{
	// 弾の発射方向
	VECTOR bulletFireDirection = VGet(0.0f, 0.0f, 1.0f);	// 初期値は+Z方向
	// 角度の基準値を代入
	bulletFireDirection = RotateFireHorizontal(bulletFireDirection, angleHOffset);
	bulletFireDirection = RotateFireVertical(bulletFireDirection, angleVOffset);
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
		bulletFireDirection = RotateFireHorizontal(bulletFireDirection, bulletAngleDiff);
	}
}

// 水平方向にのみ弾幕発射
void BulletFire::FireHorizontalBarrage(const VECTOR& firePos)
{
	// フレームカウントが0かつループ回数内のみ発射
	if (BarrageFrameCount == 0 && barrageFireLoopCount <= BARRAGE_FIRE_LOOP_NUM)
	{
		FireAllDirection(firePos, BULLET_FIRE_ALL_DIRECTION_NUM, barrageFireAngleH,0.0f);
		barrageFireLoopCount++;
		barrageFireAngleH += BARRAGE_ANGLE_H_OFFSET;
	}

	BarrageFrameCount++;
	if (BarrageFrameCount >= 10)
	{
		BarrageFrameCount = 0;
	}

	if (barrageFireLoopCount == BARRAGE_FIRE_LOOP_NUM + 1)
	{
		isActiveHorizontalBarrage = false;
		barrageFireLoopCount = 0;
		barrageFireAngleH = 0;
	}
}

// ウェーブ状の弾幕を発射
void BulletFire::FireWaveBarrage(const VECTOR& firePos)
{
	barrageFireAngleVOffset = BARRAGE_ANGLE_V_OFFSET;
	// フレームカウントが0かつループ回数内のみ発射
	if (BarrageFrameCount == 0 && barrageFireLoopCount <= BARRAGE_FIRE_LOOP_NUM)
	{
		FireAllDirection(firePos, BULLET_FIRE_ALL_DIRECTION_NUM, barrageFireAngleH,barrageFireAngleV);
		barrageFireLoopCount++;
		barrageFireAngleH += BARRAGE_ANGLE_H_OFFSET;
		barrageFireAngleV += barrageFireAngleVOffset;
	}

	BarrageFrameCount++;
	if (BarrageFrameCount >= 10)
	{
		BarrageFrameCount = 0;
	}

	barrageFireAngleV = std::clamp(barrageFireAngleV, 0.0f, 0.8f);

	if (barrageFireAngleV <= -0.4f || barrageFireAngleV >= 0.0f)
	{
		barrageFireAngleVOffset *= -1;
	}

	if (barrageFireLoopCount == BARRAGE_FIRE_LOOP_NUM + 1)
	{
		isActiveWaveBarrage = false;
		barrageFireLoopCount = 0;
		barrageFireAngleH = 0;
		barrageFireAngleV = 0;
	}

}



// 水平方向の回転
VECTOR BulletFire::RotateFireHorizontal(const VECTOR& dir, float angleH)
{
	float cos = cosf(angleH);
	float sin = sinf(angleH);

	return VGet(
		dir.x * cos - dir.z * sin,	// 回転後のx
		dir.y,						// yはそのまま
		dir.x * sin + dir.z * cos	// 回転後のz
	);
}


VECTOR BulletFire::RotateFireVertical(const VECTOR& dir, float angleV)
{
	float cos = cosf(angleV);
	float sin = sinf(angleV);

	return VGet(
		dir.x,
		dir.y * cos - dir.z * sin,
		dir.y * sin + dir.z * cos
	);
}