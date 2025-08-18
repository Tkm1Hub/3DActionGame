#include "stdafx.h"
#include "Robot.h"

Robot::Robot()
{
	name = "Robot";
	pos = VGet(0.0f, 0.0f, 0.0f);
	scale = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	modelHandle = -1;
}

void Robot::Init()
{
	name = "Robot";
	pos = VGet(0.0f, 0.0f, 0.0f);
	scale = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	modelHandle = -1;
}

void Robot::Load()
{
	Enemy::Load(FILE_PATH);

}