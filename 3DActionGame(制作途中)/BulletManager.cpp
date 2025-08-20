#include "stdafx.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "Robot.h"
#include "Player.h"

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

void BulletManager::Update(const Enemy& enemy,const Player& player)
{
	// 仮にスペースキーで弾を生成
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// 弾の発射方向ベクトル
		VECTOR moveVec = VSub(player.GetPosition(), enemy.GetPosition());
		if (VSize(moveVec) != 0.0f)
		{
			moveVec = VNorm(moveVec);
		}

		Create(VGet(enemy.GetPosition().x, enemy.GetPosition().y + enemy.GetHitHeight(),enemy.GetPosition().z), moveVec);
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

// 弾の生成（生成する座標 , 発射する方向）
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