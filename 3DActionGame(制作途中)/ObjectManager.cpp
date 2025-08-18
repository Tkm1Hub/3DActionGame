#include "stdafx.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager(){}

ObjectManager::~ObjectManager() { Clear(); }

/// <summary>
/// オブジェクトをリストに追加
/// </summary>
/// <param name="obj"></param>
void ObjectManager::AddObject(GameObject* obj)
{
	objects.push_back(obj);
}

/// <summary>
/// オブジェクトを名前で検索する
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
GameObject* ObjectManager::FindObject(const std::string& name)
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

void ObjectManager::Clear()
{
	for (auto obj : objects)
	{
		delete obj;
	}
	objects.clear();

}