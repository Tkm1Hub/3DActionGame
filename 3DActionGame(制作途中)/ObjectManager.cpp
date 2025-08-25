#include "stdafx.h"
#include "ObjectManager.h"
#include "Player.h"
#include "enemy.h"
#include "skyDome.h"
#include "stage.h"
#include "Sword.h"

ObjectManager::ObjectManager(){}

ObjectManager::~ObjectManager() {}

void ObjectManager::Create()
{
	player = std::make_shared<Player>();
	enemy = std::make_shared<Enemy>();
	skyDome = std::make_shared<SkyDome>();
	stage = std::make_shared<Stage>();
	sword = std::make_shared<Sword>();

	AddObject(player);
	AddObject(enemy);
	AddObject(skyDome);
	AddObject(stage);
	AddObject(sword);
}

/// <summary>
/// オブジェクトをリストに追加
/// </summary>
/// <param name="obj"></param>
void ObjectManager::AddObject(std::shared_ptr<IGameObject> obj)
{
	objects.push_back(obj);
}

/// <summary>
/// オブジェクトを名前で検索する
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
std::shared_ptr<IGameObject> ObjectManager::FindObject(const std::string& name)
{
	for (auto obj : objects) {
		if (obj->GetName() == name) {
			return obj;
		}
	}
	return nullptr;
}

/// <summary>
/// オブジェクトの初期化
/// </summary>
void ObjectManager::InitAll()
{
	for (auto obj : objects)
	{
		obj->Init();
	}
}

/// <summary>
/// モデルなどのロード
/// </summary>
void ObjectManager::LoadAll()
{
	for (auto obj : objects)
	{
		obj->Load();
	}
}

/// <summary>
/// オブジェクトの更新
/// </summary>
void ObjectManager::UpdateAll()
{
	for (auto obj : objects)
	{
		obj->Update();
	}
}

/// <summary>
/// オブジェクトの描画
/// </summary>
void ObjectManager::DrawAll()
{
	for (auto obj : objects)
	{
		obj->Draw();
	}
}