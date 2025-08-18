#pragma once
#include "DxLib.h"
#include <iostream>

class GameObject
{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void Load(){};

	virtual VECTOR GetPosition() const { return pos; }
	std::string GetName() const { return name; }
protected:

	std::string name = "null";				// 名前
	VECTOR pos = VGet(0.0f, 0.0f, 0.0f);	// 座標
	VECTOR scale = VGet(0.0f, 0.0f, 0.0f);	// モデルの大きさ
	VECTOR rot = VGet(0.0f, 0.0f, 0.0f);	// 回転
	int modelHandle = -1;					// モデルハンドル
};