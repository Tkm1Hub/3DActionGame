#include "stdafx.h"
#include "BulletFire.h"
#include "BulletCreator.h"
#include "Enemy.h"

BulletFire::BulletFire(){}

void BulletFire::Init(){}

void BulletFire::Update()
{
}

// �S�����ɒe�𔭎�
void BulletFire::FireAllDirection(const VECTOR& pos, int bulletNum,float angleOffset)
{
	// �e�̔��˕���
	VECTOR bulletFireDirection = VGet(0.0f, 0.0f, 1.0f);	// �����l��+Z����
	// �p�x�̊�l����
	bulletFireDirection = RotateXZ(bulletFireDirection, angleOffset);
	// �e�̔��ˍ��W
	VECTOR bulletFirePos = pos;
	// �e���Ƃ̊p�x�Ԋu
	float bulletAngleDiff = DX_TWO_PI_F / bulletNum;

	// ��x�ɔ��˂��鐔�������[�v
	for (int i = 0; i < bulletNum + 1; i++)
	{
		// �e�𐶐�
		BulletCreator::GetBulletCreator().Create(pos, bulletFireDirection);

		// �p�x�ύX
		bulletFireDirection = RotateXZ(bulletFireDirection, bulletAngleDiff);
	}
}

// ���������ɂ̂ݒe������
void BulletFire::FireHorizontalBarrage(const VECTOR& pos , bool& isFireBarrage)
{
	// �t���[���J�E���g��0�����[�v�񐔓��̂ݔ���
	if (BarrageFrameCount == 0 && barrageFireLoopCount <= BARRAGE_FIRE_LOOP_NUM)
	{
		FireAllDirection(pos, BULLET_FIRE_ALL_DIRECTION_NUM, burrageFireAngle);
		barrageFireLoopCount++;
		burrageFireAngle += BARRAGE_ANGLE_OFFSET;
	}

	BarrageFrameCount++;
	if (BarrageFrameCount == 10)
	{
		BarrageFrameCount = 0;
	}

	if (barrageFireLoopCount == BARRAGE_FIRE_LOOP_NUM + 1)
	{
		isFireBarrage = false;
		barrageFireLoopCount = 0;
		burrageFireAngle = 0;
	}
}

// ���������̉�]
VECTOR BulletFire::RotateXZ(const VECTOR& dir, float angle)
{
	float cos = cosf(angle);
	float sin = sinf(angle);

	return VGet(
		dir.x * cos - dir.z * sin,	// ��]���x
		dir.y,						// y�͂��̂܂�
		dir.x * sin + dir.z * cos	// ��]���z
	);
}