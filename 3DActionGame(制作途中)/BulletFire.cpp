#include "stdafx.h"
#include "BulletFire.h"
#include "BulletCreator.h"
#include "Enemy.h"

BulletFire::BulletFire(const std::shared_ptr<Character>& characterPtr)
{
	character = characterPtr;
}

void BulletFire::Init(){}

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

// �S�����ɒe�𔭎�
void BulletFire::FireAllDirection(const VECTOR& pos, int bulletNum,float angleHOffset, float angleVOffset)
{
	// �e�̔��˕���
	VECTOR bulletFireDirection = VGet(0.0f, 0.0f, 1.0f);	// �����l��+Z����
	// �p�x�̊�l����
	bulletFireDirection = RotateFireHorizontal(bulletFireDirection, angleHOffset);
	bulletFireDirection.y = sinf(angleVOffset);

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
		bulletFireDirection = RotateFireHorizontal(bulletFireDirection, bulletAngleDiff);
	}
}

// ���������ɂ̂ݒe������
void BulletFire::FireHorizontalBarrage(const VECTOR& firePos)
{
	// �t���[���J�E���g��0�����[�v�񐔓��̂ݔ���
	if (barrageFrameCount % 10 == 0 && barrageFireLoopCount <= BARRAGE_FIRE_LOOP_NUM)
	{
		FireAllDirection(firePos, BULLET_FIRE_ALL_DIRECTION_NUM, barrageFireAngleH,0.0f);
		barrageFireLoopCount++;
		barrageFireAngleH += BARRAGE_ANGLE_H_OFFSET;
	}

	barrageFrameCount++;

	if (barrageFireLoopCount == BARRAGE_FIRE_LOOP_NUM + 1)
	{
		isActiveHorizontalBarrage = false;
		barrageFireLoopCount = 0;
		barrageFireAngleH = 0;
	}
}

// �E�F�[�u��̒e���𔭎�
void BulletFire::FireWaveBarrage(const VECTOR& firePos)
{
	// �t���[���J�E���g��0�����[�v�񐔓��̂ݔ���
	if (barrageFrameCount % 10 == 0 && barrageFireLoopCount <= WAVE_BARRAGE_FIRE_LOOP_NUM)
	{
		// �p�x���X�V
		barrageFireAngleV = (sinf(barrageFrameCount * WAVE_SPEED) + 1.0f) * 0.5f *  WAVE_MAX_ANGLE_V;
		printf("%f \n", barrageFireAngleV);

		// �e�𔭎�
		FireAllDirection(firePos, BULLET_FIRE_ALL_DIRECTION_NUM, barrageFireAngleH,barrageFireAngleV);
		
		barrageFireLoopCount++;
		barrageFireAngleH += WAVE_BARRAGE_ANGLE_H_OFFSET;
	}

	// 1�t���[�����ƂɃJ�E���g
	barrageFrameCount++;

	if (barrageFireLoopCount == WAVE_BARRAGE_FIRE_LOOP_NUM + 1)
	{
		isActiveWaveBarrage = false;
		barrageFireLoopCount = 0;
		barrageFireAngleH = 0;
		barrageFireAngleV = 0;
		barrageFrameCount = 0;
	}
}

// ���������̉�]
VECTOR BulletFire::RotateFireHorizontal(const VECTOR& dir, float angleH)
{
	float cos = cosf(angleH);
	float sin = sinf(angleH);

	return VGet(
		dir.x * cos - dir.z * sin,	// ��]���x
		dir.y,						// y�͂��̂܂�
		dir.x * sin + dir.z * cos	// ��]���z
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

