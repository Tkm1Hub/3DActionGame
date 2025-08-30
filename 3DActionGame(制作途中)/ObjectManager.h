#pragma once
#include "GameObject.h"


class Player;
class Enemy;
class SkyDome;
class Stage;
class MainCamera;
class FreeCamera;
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void Create();
	void AddObject(std::shared_ptr<IGameObject> obj);
	std::shared_ptr<IGameObject> FindObject(std::string name);
	void InitAll();
	void LoadAll();
	void UpdateAll();
	void DrawAll();

	const std::vector<std::shared_ptr<IGameObject>>& GetObjects() const { return objects; }

private:
	std::vector<std::shared_ptr<IGameObject>> objects;

	std::shared_ptr<Player> player = nullptr;
	std::shared_ptr<Enemy> enemy = nullptr;
	std::shared_ptr<SkyDome> skyDome = nullptr;
	std::shared_ptr<Stage> stage = nullptr;
	std::shared_ptr<MainCamera> camera = nullptr;
	std::shared_ptr<FreeCamera> freeCamera = nullptr;
	//std::shared_ptr<IGameObject> focusCamera = nullptr;
};