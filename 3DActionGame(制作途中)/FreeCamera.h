#pragma once
#include "CameraBase.h"

class FreeCamera : public CameraBase
{
public:
	FreeCamera(const std::shared_ptr<Player>& playerPtr);
	~FreeCamera();

	void Init() override;
	void Update()override;

	const VECTOR& GetTarget() const { return nextTarget; }
	bool GetIsMoveAngle() const { return isMoveAngle; }
	float GetCurrentAngleSpeed() const { return currentAngleSpeed; }
private:

	// 定数
	static constexpr float MAX_ANGLE_SPEED = 0.04f;		// 最大旋回速度
	static constexpr float ANGLESPEED = 0.03f;			// カメラ感度
	static constexpr float ACCEL = 0.01f;				// カメラ加速度
	static constexpr float DECEL = 0.005f;				// カメラ減速度
	static constexpr float LOOK_OFFSET_Y = 20.0f;		// 注視点の高さ
	static constexpr float DISTANCE_OFFSET = 40.0f;		// プレイヤーからの距離
	static constexpr float SMOOTHING = 0.1f;			// カメラのスムージング

	std::shared_ptr<Player> player = nullptr;

	void CalcCameraAngle();		// カメラのアングルを計算
	float CalcAngleSpeed();		// カメラの旋回速度を計算
	void FixCameraPosition();	// カメラ座標を補正する
	void moveSmoothing();		// カメラをスムーズに移動
};