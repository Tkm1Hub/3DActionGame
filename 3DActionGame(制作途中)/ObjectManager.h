#pragma once
#include "GameObject.h"


class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void AddObject(GameObject* obj);
	GameObject* FindObject(const std::string& name);
	void InitAll();
	void LoadAll();
	void UpdateAll();
	void DrawAll();
	void Clear();

	const std::vector<GameObject*>& GetObjects() const { return objects; }

private:
	std::vector<GameObject*> objects;
};