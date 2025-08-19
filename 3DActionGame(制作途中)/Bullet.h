#pragma once
#include "GameObject.h"

class Bullet:public GameObject
{
public:
	Bullet();
	~Bullet();

	void Init() override;
	void Load() override;
	void Update() override;
	void Draw() override;

	VECTOR GetPosition() const { return pos; }

private:
	// ’è”
	static constexpr float RADIUS = 3.0f;	// ’e‚Ì”¼Œa
	static constexpr int DIVNUM = 32;		// ƒ|ƒŠƒSƒ“‚Ì×‚©‚³

	// •Ï”
	float speed = 1.0f;							// ’e‚Ì‘¬“x
	bool isActive = true;						// “®ì’†‚©
	VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);	// ˆÚ“®ƒxƒNƒgƒ‹
	
	void Move();
};