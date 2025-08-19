#pragma once
#include "CameraBase.h"

class Player;
class Input;
class Enemy;

class FocusCamera:public CameraBase
{
public:
	FocusCamera();

	void Init() override;
	void Update() override;
	//void Update(const Input& input, const Player& player, const Enemy& enemy);
	void Draw() override{};

private:
	static constexpr float ANGLESPEED = 0.03f;
};