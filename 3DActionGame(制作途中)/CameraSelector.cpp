#include "stdafx.h"
#include "CameraSelector.h"
#include "MainCamera.h"
#include "FreeCamera.h"
#include "FocusCamera.h"
#include "Input.h"

CameraSelector::CameraSelector(
	std::shared_ptr<MainCamera>& cameraPtr,
	const std::shared_ptr<FreeCamera>& freeCameraPtr,
	const std::shared_ptr<FocusCamera>& focusCameraPtr)
{
	mainCamera = cameraPtr;
	freeCamera = freeCameraPtr;
	focusCamera = focusCameraPtr;
}

CameraSelector::~CameraSelector(){}

void CameraSelector::Init()
{
	currentMode = CameraMode::Free;
}


/// <summary>
///  更新処理
/// </summary>
/// <param name="input"></param>
void CameraSelector::Update()
{
	// L2ボタンでモード切替
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_5)
	{
		SwitchMode();
	}

	//モードごとに更新処理
	if (currentMode == CameraMode::Free)
	{
		nextPosition = freeCamera->GetNextPosition();
		nextTarget = freeCamera->GetNextTarget();
	}
	else if (currentMode == CameraMode::Focus)
	{
		nextPosition = focusCamera->GetNextPosition();
		nextTarget = focusCamera->GetNextTarget();
	}

	// カメラに位置と注視点を設定
	mainCamera->SetCameraPositionAndTarget(nextPosition, nextTarget);
}

/// <summary>
/// カメラの切り替え
/// </summary>
void CameraSelector::SwitchMode()
{
	if (currentMode == CameraMode::Free)
	{
		currentMode = CameraMode::Focus;
	}
	else if(currentMode == CameraMode::Focus)
	{
		currentMode = CameraMode::Free;
	}
}