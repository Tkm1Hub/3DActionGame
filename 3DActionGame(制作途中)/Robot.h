#pragma once
#include "Enemy.h"

enum class RobotAnim :int
{
	None = -1,
	Idle = 0,
};

class Robot :public Enemy
{
public:
	Robot();

	void Init() override;
	void Load() override;
	void Update() override{}
	void Draw() override{}

private:
	const char* FILE_PATH = "data/model/character/robot.mv1";
	
	//void Attack() override{}

};