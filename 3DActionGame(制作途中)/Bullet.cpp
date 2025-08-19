#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(){}

Bullet::~Bullet(){}

void Bullet::Init()
{
	name = "Bullet";
	pos = VGet(0.0f, 20.0f, 15.0f);
	scale = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	modelHandle = -1;

	isActive = true;
	moveVec = VGet(1.0f, 0.0f, 0.0f);
}

void Bullet::Load()
{

}

void Bullet::Update()
{
	Move();

}

void Bullet::Draw()
{
	// 動作中なら描画
	if (isActive)
	{
		DrawSphere3D(pos, RADIUS, DIVNUM, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
	}
}

void Bullet::Move()
{
	if (isActive)
	{
		moveVec = VScale(moveVec, speed);
		pos = VAdd(pos, moveVec);

		if (pos.x > 100 || pos.x < -100)
		{
			moveVec.x *= -1;
		}
	}
}

void Bullet::HitPlayer()
{
	// プレイヤーに当たったら非表示
	isActive = false;
	pos = VGet(0.0f, 0.0f, 0.0f);
}