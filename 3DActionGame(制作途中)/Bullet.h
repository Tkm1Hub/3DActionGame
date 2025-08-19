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
	float GetRadius() const { return RADIUS; }

	void HitPlayer();
	void Activate();

private:
	// �萔
	static constexpr float RADIUS = 3.0f;	// �e�̔��a
	static constexpr int LIFETIME = 300;	// �e��������܂ł̃t���[����
	static constexpr int DIVNUM = 32;		// �|���S���ׂ̍���

	// �ϐ�
	float speed = 1.0f;							// �e�̑��x
	bool isActive = true;						// ���쒆��
	VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);	// �ړ��x�N�g��
	int lifeCount = 0;							// �e�����˂���Ă���̃t���[��
	
	void Move();
};