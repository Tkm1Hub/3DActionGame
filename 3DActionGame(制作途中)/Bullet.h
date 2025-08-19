#pragma once
#include "GameObject.h"

class Bullet:public GameObject
{
public:
	Bullet();
	~Bullet();

	void Init() override;
	void Load() override;
	void Update() override;
	void Draw() override;

	VECTOR GetPosition() const { return pos; }
	float GetRadius() const { return RADIUS; }

	void HitPlayer();
	void Activate();

private:
	// 定数
	static constexpr float RADIUS = 3.0f;	// 弾の半径
	static constexpr int LIFETIME = 300;	// 弾が消えるまでのフレーム数
	static constexpr int DIVNUM = 32;		// ポリゴンの細かさ

	// 変数
	float speed = 1.0f;							// 弾の速度
	bool isActive = true;						// 動作中か
	VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);	// 移動ベクトル
	int lifeCount = 0;							// 弾が発射されてからのフレーム
	
	void Move();
};