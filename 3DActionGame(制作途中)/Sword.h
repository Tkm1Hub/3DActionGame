#pragma once
#include "GameObject.h"

class Sword :public GameObject
{
public :
	Sword();

	void Init() override;
	void Load() override;
	void Update() override;
	void Draw() override;

private:


};