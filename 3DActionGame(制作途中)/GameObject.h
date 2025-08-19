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

	std::string name;				// 名前
	VECTOR pos;						// 座標
	VECTOR scale;					// モデルの大きさ
	VECTOR rot;						// 回転
	int modelHandle;				// モデルハンドル


};