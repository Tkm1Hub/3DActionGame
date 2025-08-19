#pragma once
#include "Character.h"
#include "StageCollision.h"
#include "Animation.h"

class Input;
class CameraBase;
class StageCollision;
class Animation;

enum class PlayerAnim:int
{
    None = -1,      // なし
    TPose = 0,      // 不明
    Idle = 0,       // アイドル
    Walk = 1,       // 歩き
    Run = 2,        // 走り
    RunPose = 3,    // ダッシュポーズ
    RunStop = 5,    // ストップ
    Jump = 7,       // ジャンプ
    Fall = 8,       // 落下中
};

class Player:public Character
{
public:

    Player();

    void Init() override;
    void Load(const char* FiePath) override;
    void Update() override {};
    void Update( const Input& input, const CameraBase& camera, StageCollision& collision);
    void Draw() override;

    void OnHitRoof() override;       // 天井に当たった時
    void OnHitFloor() override;      // 床に当たった時
    void OnFall() override;          // 落下が確定したとき


    // 状態の取得
    const enum class State GetState() const override { return currentState; }
    const float GetJumpPower() const override { return currentJumpPower; }

    // ゲッター
    const float GetBrendRate() const { return animBlendRate; }
    const float GetCurrentAnim() const { return currentAnimCount; }
    const float GetPrevAnim() const { return prevAnimCount; }
    const float GetHitRadius() const override { return HIT_RADIUS; }
    const float GetHitHeight() const override { return HIT_HEIGHT; }
    const int GetRunFrameCount() const { return runFrameCount; }

    const VECTOR GetCapsuleA();
    const VECTOR GetCapsuleB();

private:
    // 定数定義
    static constexpr VECTOR INIT_POS = { 0.0f,0.0f,0.0f };  // 初期座標
    static constexpr float	JUMP_POWER = 2.5f;	    // ジャンプ力
    static constexpr float	GRAVITY = 0.08f;		// 重力
    static constexpr float ACCEL = 0.01f;           // 移動加速度
    static constexpr float DECEL = 0.03f;           // 移動減速度
    static constexpr float WALK_SPEED = 0.5f;       // 歩き最大速度
    static constexpr float RUN_SPEED = 1.5f;        // 走り最大速度
    static constexpr float ANGLE_SPEED = 0.2f;      // モデルの角度変更速度
    static constexpr float ANIM_PLAY_SPEED = 0.4f;  // アニメーションの再生速度
    static constexpr float ANIM_BLEND_SPEED = 0.1f; // アニメーションのブレンド率変化速度
    static constexpr float HIT_RADIUS = 3.0f;       // 当たり判定半径
    static constexpr float HIT_HEIGHT = 13.5f;       // 当たり判定高さ
    static constexpr int STOP_ANIM_DURATION = 27;   // ストップアニメーションの最大フレーム数

    // 変数
    VECTOR upMoveVec = VGet(0.0f, 0.0f, 0.0f);           // 上下の移動ベクトル
    VECTOR leftMoveVec = VGet(0.0f, 0.0f, 0.0f);         // 左右の移動ベクトル
    bool isMove = false;                // 移動中か
    bool isJumping = false;             // ジャンプ中か
    bool isFalling = false;             // 落下中かどうか
    bool isRunning = false;             // 走っているかどうか
    bool isPlayingStopAnim = false;     // ストップアニメ中か
    int runFrameCount = 0;          // 走り始めてからのフレーム
    int stopAnimCount = 0;          // ストップアニメーションのフレーム


    // アニメーション関連変数
    int			currentPlayAnim;		// 再生しているアニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
    float		currentAnimCount;		// 再生しているアニメーションの再生時間
    int			prevPlayAnim;			// 前の再生アニメーションのアタッチ番号( -1:何もアニメーションがアタッチされていない )
    float		prevAnimCount;			// 前の再生アニメーションの再生時間
    float		animBlendRate;			// 現在と過去のアニメーションのブレンド率

    State currentState;
    PlayerAnim currentAnimState;
    Animation anim;
    Input* input;
    CameraBase* camera;

    void DisableRootFrameZMove();
    void UpdateMoveParameterWithPad(const Input& input, const CameraBase& camera);
    void CulcMoveSpeed();
    void ChangeState(int newState) override;
    void UpdateState();
    void Move(const VECTOR& MoveVector, StageCollision& collision, const Input& input);
    void UpdateAnimation();
    void PlayAnim(PlayerAnim animkind);
    void ChangeAnimState(int animKind) override;
    void UpdateAnimState(State prevState);
    void UpdateAngle();

};