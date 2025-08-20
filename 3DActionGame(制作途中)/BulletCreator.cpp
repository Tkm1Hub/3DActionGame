#include "stdafx.h"
#include "BulletCreator.h"
#include "Bullet.h"
#include "Robot.h"
#include "Player.h"

void BulletCreator::Init()
{
	// ����100���p��
	for (int i = 0; i < 101; i++)
	{
		bullets.push_back(std::make_shared<Bullet>());
	}
}

void BulletCreator::Update(const Enemy& enemy,const Player& player)
{
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
void BulletCreator::Create(const VECTOR& pos,const VECTOR& moveVec)
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

void BulletCreator::Draw()
{
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Draw();
		}
	}
}