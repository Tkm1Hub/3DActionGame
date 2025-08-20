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
void BulletFire::FireAllDirection(const VECTOR& pos, int bulletNum)
{
	// �e�̔��˕���
	VECTOR bulletFireDirection = VGet(0.0f, 0.0f, 1.0f);	// �����l��+Z����
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
		RotateXZ(bulletFireDirection, bulletAngleDiff);
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