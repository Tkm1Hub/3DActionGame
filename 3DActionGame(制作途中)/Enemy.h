#pragma once
#include "Character.h"
#include "StageCollision.h"
#include "Animation.h"

class Animation;
class StageCollision;
class BulletFire;
enum class AnimKind :int
{
    None = -1,      // なし
    Idle = 0,       //立ち止まり
};

class Enemy:public Character 
{
public:
	Enemy();
    ~Enemy();

	void Init() override;
    void Load() override{}
    void Load(const char* FilePath);
	void Update() override{}
    void Update(StageCollision& collision);
	void Draw() override;


    // 状態の取得
    const enum class State GetState() const override { return currentState; }
    const VECTOR GetHeadPos() const { return VGet(pos.x, pos.y + HIT_HEIGHT, pos.z); }
    const float GetJumpPower() const override { return currentJumpPower; }

    const float GetHitRadius() const override { return HIT_RADIUS; }
    const float GetHitHeight() const override { return HIT_HEIGHT; }
    const VECTOR GetBulletSpawnPos() override { return GetHeadPos(); }

	void OnHitRoof() override;
	void OnHitFloor() override;
	void OnFall() override;

protected:

    // 定数定義
    static constexpr VECTOR INIT_POS = { 0.0f,0.0f,30.0f };  // 初期座標
    static constexpr float	JUMP_POWER = 2.5f;	    // ジャンプ力
    static constexpr float	GRAVITY = 0.08f;		// 重力
    static constexpr float ACCEL = 0.01f;           // 移動加速度
    static constexpr float DECEL = 0.01f;           // 移動減速度
    static constexpr float WALK_SPEED = 0.5f;        // 歩き最大速度
    static constexpr float RUN_SPEED = 1.5f;        // 走り最大速度
    static constexpr float ANGLE_SPEED = 0.2f;      // モデルの角度変更速度
    static constexpr float ANIM_PLAY_SPEED = 0.4f;  // アニメーションの再生速度
    static constexpr float ANIM_BLEND_SPEED = 0.1f; // アニメーションのブレンド率変化速度
    static constexpr float HIT_RADIUS = 4.0f;       // 当たり判定半径
    static constexpr float HIT_HEIGHT = 10.0f;       // 当たり判定高さ

    // 変数
    VECTOR upMoveVec;           // 上下の移動ベクトル
    VECTOR leftMoveVec;         // 左右の移動ベクトル
    bool isMove;                // 移動中か
    bool isJumping;             // ジャンプ中か
    bool isFalling;             // 落下中かどうか
    bool isRunning;             // 走っているかどうか
    bool pushF1 = false;        // F1が押されているか
    bool pushF2 = false;        // F2が押されているか
    bool isBarrageActive = false;    // 弾幕発射中か
    State currentState;
    AnimKind currentAnimState; 
    Animation* animation;

    void DisableRootFrameZMove();
    void Move(VECTOR& moveVec,StageCollision& collision);
    void UpdateState();
    void ChangeState(int newState) override {};
    void ChangeAnimState(int animKind) override {};

    //virtual void Attack() = 0;
    //std::shared_ptr<BulletFire>bulletFire = nullptr;
    BulletFire* bulletFire = nullptr;
};