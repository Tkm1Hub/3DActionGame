#pragma once

class Input
{
public:
    Input();
    ~Input();

    //�L�[�̎��
    enum KeyKinds
    {
        Move = 0,  //�ړ��L�[�̂ǂꂩ
        Left = 1,  //�E
        Right = 2,  //��
        Up = 3,  //��
        Down = 4,  //��
        Space = 5,  //�X�y�[�X
        LB = 6,  //����̎�O�̃{�^��
        LT = 7,  //����̉����̃{�^��
        RB = 8,  //�E��̎�O�̃{�^��
        RT = 9,  //�E�����̃{�^��
        X = 10,
        Y = 11,
        A = 12,
        B = 13,
        LeftStick = 14,  //���X�e�B�b�N��������
        None = 15,  //�g�p���Ȃ��L�[�������͉�����Ă��Ȃ�
    };

    void Update();

    int GetNowFrameInput() const { return nowFrameInput; }
    int GetNowFrameNewInput() const { return nowFrameNewInput; }

    bool GetIsMoveLStick() const { return isMoveLStick; }
    bool GetIsMoveRStick() const { return isMoveRStick; }

    float GetLeftStickX() const { return leftStickX; }
    float GetLeftStickY() const { return leftStickY; }
    float GetRightStickX() const { return rightStickX; }
    float GetRightStickY() const { return rightStickY; }

    float GetRStickAngle() const { return RStickAngle; }
    float GetLStickAngle() const { return LStickAngle; }
private:
    static constexpr int DEADZONE = 10;     // �X�e�B�b�N��|���Ă������������Ȃ��̈�

    int nowFrameInput;          // ���݂̃t���[���ŉ�����Ă���{�^��
    int nowFrameNewInput;       // ���݂̃t���[���ŐV���ɉ����ꂽ�{�^��
    bool isMoveRStick;          // �E�X�e�B�b�N���X���Ă��邩
    bool isMoveLStick;          // ���X�e�B�b�N���X���Ă��邩

    float leftStickX;           // ���X�e�B�b�N��X���̌X��
    float leftStickY;           // ���X�e�B�b�N��Y���̌X��
    float rightStickX;          // �E�X�e�B�b�N��X���̌X��
    float rightStickY;          // �E�X�e�B�b�N��Y���̌X��
    float LStickAngle;          // ���X�e�B�b�N�̌X���x
    float RStickAngle;          // �E�X�e�B�b�N�̌X���x

    void CalcStickInput();
};