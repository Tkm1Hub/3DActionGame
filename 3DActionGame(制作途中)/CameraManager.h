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
	void Update(const std::shared_ptr<Input>& input,const std::shared_ptr<Player>& player);
	
	CameraBase* GetCurrentCamera() const { return camera.get(); }
private:
	void SwitchMode();		// �J�����؂�ւ�
	void moveSmoothing();	// �X���[�Y�ړ�

	static constexpr float SMOOTHING = 0.1f;			// �J�����̃X���[�W���O

	VECTOR currentTarget = VGet(0.0f, 0.0f, 0.0f);		// �J���������_
	VECTOR nextTarget = VGet(0.0f, 0.0f, 0.0f);			// �J���������_�̖ڕW�ʒu
	VECTOR forward = VGet(0.0f, 0.0f, 0.0f);			// �J�����̕���
	VECTOR currentPosition = VGet(0.0f, 0.0f, 0.0f);	// ���݂̃|�W�V����
	VECTOR nextPosition = VGet(0.0f, 0.0f, 0.0f);		// �ڕW�̃|�W�V����
	float angleH = 0.0f;								// �����p�x
	float angleV = 0.0f;								// �������_
	float currentAngleSpeed = 0.0f;						// ���݂̃A���O���ύX���x
	bool isMoveAngle = 0.0f;							// �J�������ړ������ǂ���

	CameraMode currentMode = CameraMode::Free;

	std::shared_ptr<Player> player = nullptr;
	std::shared_ptr<Input> input = nullptr;

	std::shared_ptr<CameraBase> camera;
	std::shared_ptr<FreeCamera> freeCamera;
	std::shared_ptr<FocusCamera> focusCamera;

};