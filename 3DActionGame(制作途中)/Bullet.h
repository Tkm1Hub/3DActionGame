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

private:
	// �萔
	static constexpr float RADIUS = 1.0f;	// �e�̔��a
	static constexpr int DIVNUM = 32;		// �|���S���ׂ̍���

	// �ϐ�
	float speed = 0.5f;							// �e�̑��x
	bool isActive = true;						// ���쒆��
	VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);	// �ړ��x�N�g��
	
	void Move();
};