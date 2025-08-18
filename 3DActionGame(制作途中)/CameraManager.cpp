#include "stdafx.h"
#include "CameraManager.h"
#include "FreeCamera.h"
#include "FocusCamera.h"
#include "Player.h"
#include "Input.h"

CameraManager::CameraManager(){}

CameraManager::~CameraManager()
{

}

void CameraManager::Init()
{
	currentMode = CameraMode::Free;

	//camera = new CameraBase;
	//freeCamera = new FreeCamera;
	//focusCamera = new FocusCamera;

	camera->Init();
	freeCamera->Init();
	focusCamera->Init();
}


/// <summary>
///  更新処理
/// </summary>
/// <param name="input"></param>
void CameraManager::Update(const std::shared_ptr<Input>& input,const std::shared_ptr<Player>& player)
{
	// L2ボタンでモード切替
	if (input->GetNowFrameNewInput() & PAD_INPUT_5)
	{
		SwitchMode();
	}

	//モードごとに更新処理
	if (currentMode == CameraMode::Free)
	{
		freeCamera->Update(input,player);
		nextPosition = freeCamera->GetNextPosition();
		nextTarget = freeCamera->GetNextTarget();
	}
	else if (currentMode == CameraMode::Focus)
	{
		focusCamera->Update();
		nextPosition = focusCamera->GetNextPosition();
		nextTarget = focusCamera->GetNextTarget();
	}

	// 座標をスムーズに移動
	moveSmoothing();

	// カメラに位置と注視点を設定
	camera->SetCameraPositionAndTarget(currentPosition, currentTarget);

	// カメラの更新
	camera->Update();

}

/// <summary>
/// カメラの切り替え
/// </summary>
void CameraManager::SwitchMode()
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

/// <summary>
/// スムーズに移動
/// </summary>
void CameraManager::moveSmoothing()
{
	// 目標地点と現在位置の差を取得
	VECTOR diff = VSub(nextPosition, currentPosition);
	VECTOR targetDiff = VSub(nextTarget, currentTarget);

	// 差にスムージングをかける
	diff = VScale(diff, SMOOTHING);
	targetDiff = VScale(targetDiff, SMOOTHING);

	// 現在位置に加算
	currentPosition = VAdd(currentPosition, diff);
	currentTarget = VAdd(currentTarget, targetDiff);
}