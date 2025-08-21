#pragma once
#include "Character.h"
#include "StageCollision.h"
#include "Animation.h"

class Animation;
class StageCollision;
class BulletFire;
enum class AnimKind :int
{
    None = -1,      // �Ȃ�
    Idle = 0,       //�����~�܂�
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


    // ��Ԃ̎擾
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

    // �萔��`
    static constexpr VECTOR INIT_POS = { 0.0f,0.0f,30.0f };  // �������W
    static constexpr float	JUMP_POWER = 2.5f;	    // �W�����v��
    static constexpr float	GRAVITY = 0.08f;		// �d��
    static constexpr float ACCEL = 0.01f;           // �ړ������x
    static constexpr float DECEL = 0.01f;           // �ړ������x
    static constexpr float WALK_SPEED = 0.5f;        // �����ő呬�x
    static constexpr float RUN_SPEED = 1.5f;        // ����ő呬�x
    static constexpr float ANGLE_SPEED = 0.2f;      // ���f���̊p�x�ύX���x
    static constexpr float ANIM_PLAY_SPEED = 0.4f;  // �A�j���[�V�����̍Đ����x
    static constexpr float ANIM_BLEND_SPEED = 0.1f; // �A�j���[�V�����̃u�����h���ω����x
    static constexpr float HIT_RADIUS = 4.0f;       // �����蔻�蔼�a
    static constexpr float HIT_HEIGHT = 10.0f;       // �����蔻�荂��

    // �ϐ�
    VECTOR upMoveVec;           // �㉺�̈ړ��x�N�g��
    VECTOR leftMoveVec;         // ���E�̈ړ��x�N�g��
    bool isMove;                // �ړ�����
    bool isJumping;             // �W�����v����
    bool isFalling;             // ���������ǂ���
    bool isRunning;             // �����Ă��邩�ǂ���
    bool pushF1 = false;        // F1��������Ă��邩
    bool pushF2 = false;        // F2��������Ă��邩
    bool isBarrageActive = false;    // �e�����˒���
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