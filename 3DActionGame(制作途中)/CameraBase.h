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
	VECTOR currentTarget;		// カメラ注視点
	VECTOR nextTarget;			// カメラ注視点の目標位置
	VECTOR forward;				// カメラの方向
	VECTOR currentPosition;		// 現在のポジション
	VECTOR nextPosition;		// 目標のポジション
	float angleH;				// 水平角度
	float angleV;				// 垂直視点
	float currentAngleSpeed;	// 現在のアングル変更速度
	bool isMoveAngle;			// カメラが移動中かどうか

};