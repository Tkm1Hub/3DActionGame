#include "stdafx.h"
#include "BulletFire.h"
#include "BulletCreator.h"
#include "Enemy.h"

BulletFire::BulletFire(){}

void BulletFire::Init(){}

void BulletFire::Update()
{
}

// ‘S•ûŒü‚É’e‚ğ”­Ë
void BulletFire::FireAllDirection(const VECTOR& pos, int bulletNum)
{
	// ’e‚Ì”­Ë•ûŒü
	VECTOR bulletFireDirection = VGet(0.0f, 0.0f, 1.0f);	// ‰Šú’l‚Í+Z•ûŒü
	// ’e‚Ì”­ËÀ•W
	VECTOR bulletFirePos = pos;
	// ’e‚²‚Æ‚ÌŠp“xŠÔŠu
	float bulletAngleDiff = DX_TWO_PI_F / bulletNum;

	// ˆê“x‚É”­Ë‚·‚é”‚¾‚¯ƒ‹[ƒv
	for (int i = 0; i < bulletNum + 1; i++)
	{
		// ’e‚ğ¶¬
		BulletCreator::GetBulletCreator().Create(pos, bulletFireDirection);

		// Šp“x•ÏX
		RotateXZ(bulletFireDirection, bulletAngleDiff);
	}
}

// …•½•ûŒü‚Ì‰ñ“]
VECTOR BulletFire::RotateXZ(const VECTOR& dir, float angle)
{
	float cos = cosf(angle);
	float sin = sinf(angle);

	return VGet(
		dir.x * cos - dir.z * sin,	// ‰ñ“]Œã‚Ìx
		dir.y,						// y‚Í‚»‚Ì‚Ü‚Ü
		dir.x * sin + dir.z * cos	// ‰ñ“]Œã‚Ìz
	);
}