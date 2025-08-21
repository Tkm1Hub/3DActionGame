#pragma once

class BulletFire
{
public:
	BulletFire();

	void Init();
	void Update();
	void FireAllDirection(const VECTOR& pos,int bulletNum, float angleOffset);
	void FireHorizontalBarrage(const VECTOR& pos, bool& isFireBarrage);
		
private:
	// 定数
	static constexpr int BULLET_NUM = 6;	// 一度に発車する弾の数
	// 全方向に弾を発射する際、一度に発射する弾の数
	static constexpr int BULLET_FIRE_ALL_DIRECTION_NUM = 6;
	// 一度の弾幕で繰り返す発射回数
	static constexpr int BARRAGE_FIRE_LOOP_NUM = 30;
	// 弾幕発射ごとにずらす角度
	static constexpr float BARRAGE_ANGLE_OFFSET = 0.15f;

	// 変数
	float burrageFireAngle = 0.0f; // 弾幕発射角度の基準値
	int barrageFireLoopCount = 0;        // 弾幕ループ回数のカウント
	float BarrageFrameCount = 0.0f;  // 弾幕を発射するフレームのカウント

	float shotAngle = 0.0f;					// 発射角度
	
	VECTOR RotateXZ(const VECTOR& dir,float angle);	// 水平方向に回転
};