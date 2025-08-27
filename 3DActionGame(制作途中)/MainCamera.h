#pragma once
#include "CameraBase.h"
class MainCamera : CameraBase
{
public:
	void Init() override;
	void Update() override;

	// カメラの座標と注視点を設定
	void SetCameraPositionAndTarget(const VECTOR& newPos, const VECTOR& newTarget);

private:
	static constexpr float SMOOTHING = 0.1f;			// カメラのスムージング

	void moveSmoothing();	// スムーズ移動
};