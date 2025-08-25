#pragma once
#include "GameObject.h"
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();

	void Init() override;
	void Load() override;
	void Update() override;
	void Draw() override;

	const int GetModelHandle() const { return modelHandle; }
private:
};