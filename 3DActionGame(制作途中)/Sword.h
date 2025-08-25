#pragma once
#include "GameObject.h"

class Sword :public IGameObject
{
public :
	Sword();

	void Init() override;
	void Load() override;
	void Update() override;
	void Draw() override;

private:


};