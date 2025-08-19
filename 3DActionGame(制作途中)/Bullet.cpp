#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(){}

Bullet::~Bullet(){}

void Bullet::Init()
{
	name = "Bullet";
	pos = VGet(0.0f, 5.0f, 0.0f);
	scale = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	modelHandle = -1;

	isActive = true;
	moveVec = VGet(0.0f, 0.0f, 0.0f);
}

void Bullet::Load()
{

}

void Bullet::Update()
{

}

void Bullet::Draw()
{
	// ìÆçÏíÜÇ»ÇÁï`âÊ
	if (isActive)
	{
		DrawSphere3D(pos, RADIUS, DIVNUM, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
	}
}

void Bullet::Move()
{
	if (isActive)
	{

	}
}