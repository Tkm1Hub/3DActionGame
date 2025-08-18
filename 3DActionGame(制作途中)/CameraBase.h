#pragma once
#include "GameObject.h"

class CameraBase: public GameObject
{
public:
	void Init() override;
	void Update() override;
	void Draw() override {};

	void SetCameraPositionAndTarget(const VECTOR& newPos, const VECTOR& newTarget);
	const VECTOR& GetNextPosition() const { return nextPosition; }
	const VECTOR& GetNextTarget() const { return nextTarget; }
	const VECTOR& GetForward() const { return forward; }

protected:
	// �萔
	static constexpr float CAMERA_NEAR = 0.5f;
	static constexpr float CAMERA_FAR = 1000.0f;

	// �ϐ�
	VECTOR currentTarget = VGet(0.0f, 0.0f, 0.0f);		// �J���������_
	VECTOR nextTarget = VGet(0.0f, 0.0f, 0.0f);			// �J���������_�̖ڕW�ʒu
	VECTOR forward = VGet(0.0f, 0.0f, 0.0f);			// �J�����̕���
	VECTOR currentPosition = VGet(0.0f, 0.0f, 0.0f);	// ���݂̃|�W�V����
	VECTOR nextPosition = VGet(0.0f, 0.0f, 0.0f);		// �ڕW�̃|�W�V����
	float angleH = 0.0f;								// �����p�x
	float angleV = 0.0f;								// �������_
	float currentAngleSpeed = 0.0f;						// ���݂̃A���O���ύX���x
	bool isMoveAngle = 0.0f;							// �J�������ړ������ǂ���
};