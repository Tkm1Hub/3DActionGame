#include "stdafx.h"
#include "BulletManager.h"
#include "Bullet.h"

BulletManager::BulletManager(){}

BulletManager::~BulletManager(){}

void BulletManager::Init()
{
	// 仮に100発用意
	for (int i = 0; i < 101; i++)
	{
		bullets.push_back(std::make_shared<Bullet>());
	}
}

void BulletManager::Update()
{
	// 仮にスペースキーで弾を生成
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		Create(VGet(20.0f, 25.0f, 0.0f), VGet(1.0f, 0.0f, 0.0f));
	}

	// 有効な弾の更新
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Update();
		}
	}
}

// 弾の生成
void BulletManager::Create(const VECTOR& pos,const VECTOR& moveVec)
{
	for (auto& bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->Activate();
			bullet->SetPosition(pos);
			bullet->SetMoveVec(moveVec);
			return;	// 1発のみ生成してループ解除
		}
	}
}

void BulletManager::Draw()
{
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Draw();
		}
	}
}