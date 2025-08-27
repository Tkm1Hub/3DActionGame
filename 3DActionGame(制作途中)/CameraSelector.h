#pragma once

class MainCamera;
class FreeCamera;
class FocusCamera;

enum class CameraMode
{
	Free,
	Focus,
};

class CameraSelector
{
public:
	CameraSelector(
		std::shared_ptr<MainCamera>& cameraPtr,
		const std::shared_ptr<FreeCamera>& freeCameraPtr,
		const std::shared_ptr<FocusCamera>& focusCameraPtr
	);

	~CameraSelector();

	void Init();
	void Update();
	
private:
	void SwitchMode();		// カメラ切り替え

	VECTOR nextTarget = VGet(0.0f, 0.0f, 0.0f);			// カメラ注視点の目標位置
	VECTOR nextPosition = VGet(0.0f, 0.0f, 0.0f);		// 目標のポジション

	CameraMode currentMode = CameraMode::Free;
	std::shared_ptr<MainCamera> mainCamera = nullptr;
	std::shared_ptr<FreeCamera> freeCamera = nullptr;
	std::shared_ptr<FocusCamera> focusCamera = nullptr;
};