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
	void SwitchMode();		// カメラ切り替え
	void moveSmoothing();	// スムーズ移動

	static constexpr float SMOOTHING = 0.1f;			// カメラのスムージング


	VECTOR currentTarget;		// カメラ注視点
	VECTOR nextTarget;			// カメラ注視点の目標位置
	VECTOR forward;				// カメラの方向
	VECTOR currentPosition;		// 現在のポジション
	VECTOR nextPosition;		// 目標のポジション
	float angleH;				// 水平角度
	float angleV;				// 垂直視点
	float currentAngleSpeed;	// 現在のアングル変更速度
	bool isMoveAngle;			// カメラが移動中かどうか

	CameraMode currentMode = CameraMode::Free;
	CameraBase* camera = nullptr;
	FreeCamera* freeCamera = nullptr;
	FocusCamera* focusCamera = nullptr;
};