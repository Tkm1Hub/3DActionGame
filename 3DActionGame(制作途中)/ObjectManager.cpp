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
/// �I�u�W�F�N�g�����X�g�ɒǉ�
/// </summary>
/// <param name="obj"></param>
void ObjectManager::AddObject(std::shared_ptr<IGameObject> obj)
{
	objects.push_back(obj);
}

/// <summary>
/// �I�u�W�F�N�g�𖼑O�Ō�������
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
/// �I�u�W�F�N�g�̏�����
/// </summary>
void ObjectManager::InitAll()
{
	for (auto obj : objects)
	{
		obj->Init();
	}
}

/// <summary>
/// ���f���Ȃǂ̃��[�h
/// </summary>
void ObjectManager::LoadAll()
{
	for (auto obj : objects)
	{
		obj->Load();
	}
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V
/// </summary>
void ObjectManager::UpdateAll()
{
	for (auto obj : objects)
	{
		obj->Update();
	}
}

/// <summary>
/// �I�u�W�F�N�g�̕`��
/// </summary>
void ObjectManager::DrawAll()
{
	for (auto obj : objects)
	{
		obj->Draw();
	}
}