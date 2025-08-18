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
	// 定数
	static constexpr float CAMERA_NEAR = 0.5f;
	static constexpr float CAMERA_FAR = 1000.0f;

	// 変数
	VECTOR currentTarget = VGet(0.0f, 0.0f, 0.0f);		// カメラ注視点
	VECTOR nextTarget = VGet(0.0f, 0.0f, 0.0f);			// カメラ注視点の目標位置
	VECTOR forward = VGet(0.0f, 0.0f, 0.0f);			// カメラの方向
	VECTOR currentPosition = VGet(0.0f, 0.0f, 0.0f);	// 現在のポジション
	VECTOR nextPosition = VGet(0.0f, 0.0f, 0.0f);		// 目標のポジション
	float angleH = 0.0f;								// 水平角度
	float angleV = 0.0f;								// 垂直視点
	float currentAngleSpeed = 0.0f;						// 現在のアングル変更速度
	bool isMoveAngle = 0.0f;							// カメラが移動中かどうか
};