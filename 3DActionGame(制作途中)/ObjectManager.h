#pragma once
#include "GameObject.h"


class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void Create();
	void AddObject(std::shared_ptr<IGameObject> obj);
	std::shared_ptr<IGameObject> FindObject(const std::string& name);
	void InitAll();
	void LoadAll();
	void UpdateAll();
	void DrawAll();

	const std::vector<std::shared_ptr<IGameObject>>& GetObjects() const { return objects; }

private:
	std::vector<std::shared_ptr<IGameObject>> objects;

	std::shared_ptr<IGameObject> player = nullptr;
	std::shared_ptr<IGameObject> enemy = nullptr;
	std::shared_ptr<IGameObject> skyDome = nullptr;
	std::shared_ptr<IGameObject> stage = nullptr;
	std::shared_ptr<IGameObject> sword = nullptr;

};