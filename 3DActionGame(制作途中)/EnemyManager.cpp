#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager(){}

/// <summary>
///  敵をリストに追加
/// </summary>
/// <param name="enemy"></param>
void EnemyManager::AddEnemy(Character* enemy)
{
	enemys.push_back(enemy);
}

/// <summary>
/// 敵の初期化
/// </summary>
void EnemyManager::InitAll()
{
	for (auto enemy : enemys)
	{
		enemy->Init();
	}
}

/// <summary>
///  モデルなどのロード
/// </summary>
void EnemyManager::LoadAll()
{
	for (auto enemy : enemys)
	{
		//enemy->Load();
	}
}

/// <summary>
/// 更新処理
/// </summary>
void EnemyManager::UpdateAll()
{
	for (auto enemy : enemys)
	{
		enemy->Update();
	}
}

/// <summary>
///  描画処理
/// </summary>
void EnemyManager::DrawAll()
{
	for (auto enemy : enemys)
	{
		enemy->Draw();
	}
}