#include "stdafx.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "Robot.h"
#include "Player.h"

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

void BulletManager::Update(const Enemy& enemy,const Player& player)
{
	// ���ɃX�y�[�X�L�[�Œe�𐶐�
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// �e�̔��˕����x�N�g��
		VECTOR moveVec = VSub(player.GetPosition(), enemy.GetPosition());
		if (VSize(moveVec) != 0.0f)
		{
			moveVec = VNorm(moveVec);
		}

		Create(VGet(enemy.GetPosition().x, enemy.GetPosition().y + enemy.GetHitHeight(),enemy.GetPosition().z), moveVec);
	}

	// �L���Ȓe�̍X�V
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Update();
		}
	}
}

// �e�̐����i����������W , ���˂�������j
void BulletManager::Create(const VECTOR& pos,const VECTOR& moveVec)
{
	for (auto& bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->Activate();
			bullet->SetPosition(pos);
			bullet->SetMoveVec(moveVec);
			return;	// 1���̂ݐ������ă��[�v����
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