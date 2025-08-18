#pragma once
#include "GameObject.h"

enum class State :int
{
	Stand = 0,      // 立ち止まり
	Walk = 1,       // 歩き
	Run = 2,        // 走り
	Jump = 3,       // ジャンプ
};


class Character:public GameObject
{
public:
	// モデルのロード
	virtual void Load(const char* FinePath) = 0;

	// 状態の変更
	virtual void ChangeState(int newState) = 0;
	virtual void ChangeAnimState(int animKind) = 0;

	// ゲッター
	virtual const enum class State GetState() const = 0;
	virtual const float GetJumpPower() const = 0;

	// 当たり判定
	virtual const float GetHitRadius() const = 0;
	virtual const float GetHitHeight() const = 0;

	virtual void OnFall() = 0;
	virtual void OnHitFloor() = 0;
	virtual void OnHitRoof() = 0;


protected:
	// 定数
	static constexpr float	FallUpPower = 0.05f;	// 足を踏み外した時のジャンプ力
	
	// キャラクター用変数
	VECTOR moveVec;						// 移動ベクトル
	VECTOR targetMoveDirection;			// モデルが向くべき方向のベクトル
	float angle;						// モデルの角度
	float currentMoveSpeed;				// 現在の移動速度
	float currentJumpPower;				// Y軸方向の速度

};