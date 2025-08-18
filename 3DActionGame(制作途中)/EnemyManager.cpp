#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager(){}

/// <summary>
///  �G�����X�g�ɒǉ�
/// </summary>
/// <param name="enemy"></param>
void EnemyManager::AddEnemy(Character* enemy)
{
	enemys.push_back(enemy);
}

/// <summary>
/// �G�̏�����
/// </summary>
void EnemyManager::InitAll()
{
	for (auto enemy : enemys)
	{
		enemy->Init();
	}
}

/// <summary>
///  ���f���Ȃǂ̃��[�h
/// </summary>
void EnemyManager::LoadAll()
{
	for (auto enemy : enemys)
	{
		//enemy->Load();
	}
}

/// <summary>
/// �X�V����
/// </summary>
void EnemyManager::UpdateAll()
{
	for (auto enemy : enemys)
	{
		enemy->Update();
	}
}

/// <summary>
///  �`�揈��
/// </summary>
void EnemyManager::DrawAll()
{
	for (auto enemy : enemys)
	{
		enemy->Draw();
	}
}