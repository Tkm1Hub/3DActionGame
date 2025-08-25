#pragma once
#include "GameObject.h"

class Player;
class SkyDome:public IGameObject
{
public:
	SkyDome(const std::shared_ptr<Player>& playerPtr);
	~SkyDome();

	void Init() override;
	void Load() override;
	void Update() override;
	void Draw() override;

private:
	std::shared_ptr<Player> player = nullptr;
};