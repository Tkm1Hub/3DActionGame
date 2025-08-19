#pragma once

class Player;
class Input;
class CameraBase;
class FreeCamera;
class FocusCamera;

enum class CameraMode
{
	Free,
	Focus,
};

class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	void Init();
	void Update(const Input& input, const Player& player);
	
	CameraBase* GetCurrentCamera() const { return camera; }
private:
	void SwitchMode();		// �J�����؂�ւ�
	void moveSmoothing();	// �X���[�Y�ړ�

	static constexpr float SMOOTHING = 0.1f;			// �J�����̃X���[�W���O


	VECTOR currentTarget;		// �J���������_
	VECTOR nextTarget;			// �J���������_�̖ڕW�ʒu
	VECTOR forward;				// �J�����̕���
	VECTOR currentPosition;		// ���݂̃|�W�V����
	VECTOR nextPosition;		// �ڕW�̃|�W�V����
	float angleH;				// �����p�x
	float angleV;				// �������_
	float currentAngleSpeed;	// ���݂̃A���O���ύX���x
	bool isMoveAngle;			// �J�������ړ������ǂ���

	CameraMode currentMode = CameraMode::Free;
	CameraBase* camera = nullptr;
	FreeCamera* freeCamera = nullptr;
	FocusCamera* focusCamera = nullptr;
};