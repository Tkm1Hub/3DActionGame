#pragma once
#include "CameraBase.h"

class Input;
class Player;

class FreeCamera : public CameraBase
{
public:
	FreeCamera();
	~FreeCamera();

	void Init() override;
	void Update()override {};
	void Update(const Input& input, const Player& player);
	void Draw() override;

	const VECTOR& GetTarget() const { return nextTarget; }
	bool GetIsMoveAngle() const { return isMoveAngle; }
	float GetCurrentAngleSpeed() const { return currentAngleSpeed; }
private:

	// �萔
	static constexpr float MAX_ANGLE_SPEED = 0.04f;		// �ő���񑬓x
	static constexpr float ANGLESPEED = 0.03f;			// �J�������x
	static constexpr float ACCEL = 0.01f;				// �J���������x
	static constexpr float DECEL = 0.005f;				// �J���������x
	static constexpr float LOOK_OFFSET_Y = 20.0f;		// �����_�̍���
	static constexpr float DISTANCE_OFFSET = 40.0f;		// �v���C���[����̋���
	static constexpr float SMOOTHING = 0.1f;			// �J�����̃X���[�W���O

	Player* player;

	std::shared_ptr<Player>

	void CalcCameraAngle(const Input& input);		// �J�����̃A���O�����v�Z
	float CalcAngleSpeed(const Input& input);		// �J�����̐��񑬓x���v�Z
	void FixCameraPosition();	// �J�������W��␳����
	void moveSmoothing();							// �J�������X���[�Y�Ɉړ�
};