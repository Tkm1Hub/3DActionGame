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

	active = false;
	moveVec = VGet(0.0f, 0.0f, 0.0f);
}

void Bullet::Load()
{

}

// 更新処理
void Bullet::Update()
{
	// 無効なら早期リターン
	if (!active) return;
	Move();

	lifeCount--;

	if (lifeCount <= 0)
	{
		Reset();
	}
}


void Bullet::Draw()
{
	// 無効なら早期リターン
	if (!active) return;
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

// プレイヤーに当たった際の処理
void Bullet::HitPlayer()
{
	// プレイヤーに当たったら非表示
	active = false;
	pos = VGet(0.0f, 0.0f, 0.0f);
}

// 有効化
void Bullet::Activate()
{
	active = true;
	lifeCount = LIFETIME;
}

// 無効化
void Bullet::Reset()
{
	active = false;
	pos = VGet(0.0f, 0.0f, 0.0f);
}