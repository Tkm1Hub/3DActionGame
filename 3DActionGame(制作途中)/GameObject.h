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

	std::string name = "null";				// ���O
	VECTOR pos = VGet(0.0f, 0.0f, 0.0f);	// ���W
	VECTOR scale = VGet(0.0f, 0.0f, 0.0f);	// ���f���̑傫��
	VECTOR rot = VGet(0.0f, 0.0f, 0.0f);	// ��]
	int modelHandle = -1;					// ���f���n���h��
};