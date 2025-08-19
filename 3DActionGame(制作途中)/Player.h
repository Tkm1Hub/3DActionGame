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
    None = -1,      // �Ȃ�
    TPose = 0,      // �s��
    Idle = 0,       // �A�C�h��
    Walk = 1,       // ����
    Run = 2,        // ����
    RunPose = 3,    // �_�b�V���|�[�Y
    RunStop = 5,    // �X�g�b�v
    Jump = 7,       // �W�����v
    Fall = 8,       // ������
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

    void OnHitRoof() override;       // �V��ɓ���������
    void OnHitFloor() override;      // ���ɓ���������
    void OnFall() override;          // �������m�肵���Ƃ�


    // ��Ԃ̎擾
    const enum class State GetState() const override { return currentState; }
    const float GetJumpPower() const override { return currentJumpPower; }

    // �Q�b�^�[
    const float GetBrendRate() const { return animBlendRate; }
    const float GetCurrentAnim() const { return currentAnimCount; }
    const float GetPrevAnim() const { return prevAnimCount; }
    const float GetHitRadius() const override { return HIT_RADIUS; }
    const float GetHitHeight() const override { return HIT_HEIGHT; }
    const int GetRunFrameCount() const { return runFrameCount; }

    const VECTOR GetCapsuleA();
    const VECTOR GetCapsuleB();

private:
    // �萔��`
    static constexpr VECTOR INIT_POS = { 0.0f,0.0f,0.0f };  // �������W
    static constexpr float	JUMP_POWER = 2.5f;	    // �W�����v��
    static constexpr float	GRAVITY = 0.08f;		// �d��
    static constexpr float ACCEL = 0.01f;           // �ړ������x
    static constexpr float DECEL = 0.03f;           // �ړ������x
    static constexpr float WALK_SPEED = 0.5f;       // �����ő呬�x
    static constexpr float RUN_SPEED = 1.5f;        // ����ő呬�x
    static constexpr float ANGLE_SPEED = 0.2f;      // ���f���̊p�x�ύX���x
    static constexpr float ANIM_PLAY_SPEED = 0.4f;  // �A�j���[�V�����̍Đ����x
    static constexpr float ANIM_BLEND_SPEED = 0.1f; // �A�j���[�V�����̃u�����h���ω����x
    static constexpr float HIT_RADIUS = 3.0f;       // �����蔻�蔼�a
    static constexpr float HIT_HEIGHT = 13.5f;       // �����蔻�荂��
    static constexpr int STOP_ANIM_DURATION = 27;   // �X�g�b�v�A�j���[�V�����̍ő�t���[����

    // �ϐ�
    VECTOR upMoveVec = VGet(0.0f, 0.0f, 0.0f);           // �㉺�̈ړ��x�N�g��
    VECTOR leftMoveVec = VGet(0.0f, 0.0f, 0.0f);         // ���E�̈ړ��x�N�g��
    bool isMove = false;                // �ړ�����
    bool isJumping = false;             // �W�����v����
    bool isFalling = false;             // ���������ǂ���
    bool isRunning = false;             // �����Ă��邩�ǂ���
    bool isPlayingStopAnim = false;     // �X�g�b�v�A�j������
    int runFrameCount = 0;          // ����n�߂Ă���̃t���[��
    int stopAnimCount = 0;          // �X�g�b�v�A�j���[�V�����̃t���[��


    // �A�j���[�V�����֘A�ϐ�
    int			currentPlayAnim;		// �Đ����Ă���A�j���[�V�����̃A�^�b�`�ԍ�( -1:�����A�j���[�V�������A�^�b�`����Ă��Ȃ� )
    float		currentAnimCount;		// �Đ����Ă���A�j���[�V�����̍Đ�����
    int			prevPlayAnim;			// �O�̍Đ��A�j���[�V�����̃A�^�b�`�ԍ�( -1:�����A�j���[�V�������A�^�b�`����Ă��Ȃ� )
    float		prevAnimCount;			// �O�̍Đ��A�j���[�V�����̍Đ�����
    float		animBlendRate;			// ���݂Ɖߋ��̃A�j���[�V�����̃u�����h��

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