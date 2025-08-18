#include "stdafx.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager(){}

ObjectManager::~ObjectManager() { Clear(); }

/// <summary>
/// �I�u�W�F�N�g�����X�g�ɒǉ�
/// </summary>
/// <param name="obj"></param>
void ObjectManager::AddObject(GameObject* obj)
{
	objects.push_back(obj);
}

/// <summary>
/// �I�u�W�F�N�g�𖼑O�Ō�������
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

void ObjectManager::Clear()
{
	for (auto obj : objects)
	{
		delete obj;
	}
	objects.clear();

}