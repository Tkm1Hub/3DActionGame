#include "stdafx.h"
#include "BulletManager.h"
#include "Bullet.h"

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

void BulletManager::Update()
{
	// ���ɃX�y�[�X�L�[�Œe�𐶐�
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		Create(VGet(20.0f, 25.0f, 0.0f), VGet(1.0f, 0.0f, 0.0f));
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

// �e�̐���
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