#include "stdafx.h"
#include "BulletManager.h"

BulletManager::BulletManager(){}

BulletManager::~BulletManager(){}

void BulletManager::Init()
{
	// ����100���p��
	for (int i = 0; i < 101; i++)
	{
		bullets.push_back(std::make_shared<Bullet>());
	}
}

void BulletManager::Update(){}

void BulletManager::Create(VECTOR pos,VECTOR moveVec)
{
}