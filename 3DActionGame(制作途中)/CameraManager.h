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
	void SwitchMode();		// カメラ切り替え
	void moveSmoothing();	// スムーズ移動

	static constexpr float SMOOTHING = 0.1f;			// カメラのスムージング

	VECTOR currentTarget = VGet(0.0f, 0.0f, 0.0f);		// カメラ注視点
	VECTOR nextTarget = VGet(0.0f, 0.0f, 0.0f);			// カメラ注視点の目標位置
	VECTOR forward = VGet(0.0f, 0.0f, 0.0f);			// カメラの方向
	VECTOR currentPosition = VGet(0.0f, 0.0f, 0.0f);	// 現在のポジション
	VECTOR nextPosition = VGet(0.0f, 0.0f, 0.0f);		// 目標のポジション
	float angleH = 0.0f;								// 水平角度
	float angleV = 0.0f;								// 垂直視点
	float currentAngleSpeed = 0.0f;						// 現在のアングル変更速度
	bool isMoveAngle = 0.0f;							// カメラが移動中かどうか

	CameraMode currentMode = CameraMode::Free;

	std::shared_ptr<Player> player = nullptr;
	std::shared_ptr<Input> input = nullptr;

	std::shared_ptr<CameraBase> camera;
	std::shared_ptr<FreeCamera> freeCamera;
	std::shared_ptr<FocusCamera> focusCamera;

};