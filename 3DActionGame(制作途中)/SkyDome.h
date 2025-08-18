#pragma once
#include "GameObject.h"

class SkyDome:public GameObject
{
public:
	SkyDome();
	~SkyDome();

	void Init() override;
	void Load() override;
	void Update() override {}
	void Update(const VECTOR& player);
	void Draw() override;

private:
};