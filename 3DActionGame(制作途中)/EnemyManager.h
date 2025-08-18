#pragma once
#include "Character.h"
class EnemyManager
{
public:
	EnemyManager();

	void AddEnemy(Character* enemy);
	void InitAll();
	void LoadAll();
	void UpdateAll();
	void DrawAll();

private:
	std::vector<Character*> enemys;
};