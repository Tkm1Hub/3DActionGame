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

	std::string name;				// ���O
	VECTOR pos;						// ���W
	VECTOR scale;					// ���f���̑傫��
	VECTOR rot;						// ��]
	int modelHandle;				// ���f���n���h��


};