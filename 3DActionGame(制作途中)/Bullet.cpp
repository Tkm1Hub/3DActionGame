#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	Init();
}

Bullet::~Bullet(){}

void Bullet::Init()
{
	name = "Bullet";
	pos = VGet(0.0f, 0.0f, 0.0f);
	scale = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	modelHandle = -1;

	isActive = false;
	moveVec = VGet(0.0f, 0.0f, 0.0f);
}

void Bullet::Load()
{

}

void Bullet::Update()
{
	if (!isActive) return;
	Move();

	//lifeCount--;

	//if (lifeCount <= 0)
	//{
	//	isActive = false;
	//}
}

void Bullet::Draw()
{
	// 動作中なら描画
	if (!isActive) return;
	DrawSphere3D(pos, RADIUS, DIVNUM, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
}

void Bullet::Move()
{
	moveVec = VScale(moveVec, speed);
	pos = VAdd(pos, moveVec);

	if (pos.x > 50 || pos.x < -50)
	{
		moveVec.x *= -1;
	}
}

void Bullet::HitPlayer()
{
	// プレイヤーに当たったら非表示
	isActive = false;
	pos = VGet(0.0f, 0.0f, 0.0f);
}

void Bullet::Activate()
{
	isActive = true;
	lifeCount = LIFETIME;
}