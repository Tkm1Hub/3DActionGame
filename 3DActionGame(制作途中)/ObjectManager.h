#pragma once
#include "GameObject.h"


class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void Create();
	void AddObject(std::shared_ptr<GameObject> obj);
	std::shared_ptr<GameObject> FindObject(const std::string& name);
	void InitAll();
	void LoadAll();
	void UpdateAll();
	void DrawAll();

	const std::vector<std::shared_ptr<GameObject>>& GetObjects() const { return objects; }

private:
	std::vector<std::shared_ptr<GameObject>> objects;

	std::shared_ptr<GameObject> player = nullptr;
	std::shared_ptr<GameObject> enemy = nullptr;
	std::shared_ptr<GameObject> skyDome = nullptr;
	std::shared_ptr<GameObject> stage = nullptr;
	std::shared_ptr<GameObject> sword = nullptr;

};