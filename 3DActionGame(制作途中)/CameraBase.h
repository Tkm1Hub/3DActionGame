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
	VECTOR currentTarget;		// �J���������_
	VECTOR nextTarget;			// �J���������_�̖ڕW�ʒu
	VECTOR forward;				// �J�����̕���
	VECTOR currentPosition;		// ���݂̃|�W�V����
	VECTOR nextPosition;		// �ڕW�̃|�W�V����
	float angleH;				// �����p�x
	float angleV;				// �������_
	float currentAngleSpeed;	// ���݂̃A���O���ύX���x
	bool isMoveAngle;			// �J�������ړ������ǂ���

};