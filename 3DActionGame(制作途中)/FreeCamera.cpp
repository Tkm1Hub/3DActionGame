#include "stdafx.h"
#include "FreeCamera.h"
#include "Player.h"
#include "Input.h"

FreeCamera::FreeCamera()
{
	name = "FreeCamera";
	pos = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	currentTarget = VGet(0.0f, 0.0f, 0.0f);
	angleH = 0.0f;	// 180度
	angleV = 0.0f;
	currentAngleSpeed = 0.0f;
	isMoveAngle = false;
}

FreeCamera::~FreeCamera(){}

void FreeCamera::Init()
{
	pos = VGet(0.0f, 0.0f, -20.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	currentTarget = VGet(0.0f, 0.0f, 1.0f);

	// 奥行0.1～300までをカメラの描画範囲とする
	SetCameraNearFar(0.1f, 1000.0f);
}

void FreeCamera::Update(const Input& input,const Player& player)
{
	// カメラの旋回速度を計算
	currentAngleSpeed = CalcAngleSpeed(input);

	CalcCameraAngle(input);

	//カメラの注視点はプレイヤー座標から規定値分高い座標
	nextTarget = VAdd(player.GetPosition(), VGet(0.0f, LOOK_OFFSET_Y, 0.0f));

	// カメラの座標を補正する
	FixCameraPosition();

	// カメラをスムーズに移動
	//moveSmoothing();

	// カメラの方向を保存
	// カメラの方向ベクトルはカメラ座標から注視点座標を引いて正規化
	forward = VSub(nextPosition, currentTarget);
	forward = VNorm(forward);

	// カメラの情報をライブラリのカメラに反映させる
	//SetCameraPositionAndTarget_UpVecY(currentPosition, currentTarget);
}

void FreeCamera::Draw()
{

}

void FreeCamera::CalcCameraAngle(const Input& input)
{
	// X軸
	if (0.0f > input.GetRightStickX())
	{
		angleH -= currentAngleSpeed;
		// １８０度以上になったら角度値が大きくなりすぎないように３６０度を足す
		if (angleH > DX_PI_F)
		{
			angleH += DX_TWO_PI_F;
		}
	}
	else if(input.GetRightStickX() > 0.0f)
	{
		angleH += currentAngleSpeed;
		// －１８０度以下になったら角度値が大きくなりすぎないように３６０度を引く
		if (angleH < -DX_PI_F)
		{
			angleH -= DX_TWO_PI_F;
		}
	}

	// Y軸
	if (0.0f > input.GetRightStickY())
	{
		angleV += currentAngleSpeed;
		// ある一定角度以下にはならないようにする
		if (angleV > DX_PI_F * 0.5f - 0.6f)
		{
			angleV = DX_PI_F * 0.5f - 0.6f;
		}
	}
	else if (input.GetRightStickY() > 0.0f)
	{
		angleV -= currentAngleSpeed;
		// ある一定角度以上にはならないようにする
		if (angleV < -DX_PI_F * 0.5f + 0.6f)
		{
			angleV = -DX_PI_F * 0.5f + 0.6f;
		}
	}
}

float FreeCamera::CalcAngleSpeed(const Input&input)
{
	float stickAngle = input.GetRStickAngle();
	float stickPower = abs(stickAngle) / 1000.0f;

	// 傾きに応じた最大速度を計算
	float maxSpeed = MAX_ANGLE_SPEED * stickPower;

	// 加速 or 減速
	if (input.GetIsMoveRStick())
	{
		currentAngleSpeed += ACCEL; // 加速量
		currentAngleSpeed = min(currentAngleSpeed, maxSpeed); // maxSpeedで制限
	}
	else
	{
		currentAngleSpeed -= DECEL; // 減速は固定
		currentAngleSpeed = max(currentAngleSpeed, 0.0f); // マイナスにならないように
	}

	// フラグ
	isMoveAngle = (currentAngleSpeed > 0.0f);

	return currentAngleSpeed;
}

void FreeCamera::FixCameraPosition()
{
	// 水平方向の回転はＹ軸回転
	auto rotY = MGetRotY(angleH);

	// 垂直方向の回転はＺ軸回転 )
	auto rotZ = MGetRotZ(angleV);

	// カメラからプレイヤーまでの初期距離をセット
	float cameraPlayerLength = DISTANCE_OFFSET;

	// カメラの座標を算出
	// Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを
	// 垂直方向回転( Ｚ軸回転 )させたあと水平方向回転( Ｙ軸回転 )して更に
	// 注視点の座標を足したものがカメラの座標
	nextPosition = VAdd(VTransform(VTransform(VGet(-cameraPlayerLength, 0.0f, 0.0f), rotZ), rotY), nextTarget);

}


void FreeCamera::moveSmoothing()
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