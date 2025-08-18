#pragma once

class Animation
{
public:
	void LoadAnimation(int mHandle);
	void Play(int animIndex);
	void Update();
    void SetBlendRate(float newBrendRate) { animBlendRate = newBrendRate; }

private:
    int modelHandle = -1;                           // ���f���n���h��
    int currentPlayAnim = -1;                       // ���ݍĐ����Ă���A�j���ԍ�
    int prevPlayAnim = -1;                          // �ЂƂO�̃A�j���ԍ�
    float currentAnimCount = 0.0f;                  // ���݂̃A�j���J�E���g
    float prevAnimCount = 0.0f;                     // �ЂƂO�̃A�j���J�E���g
    float animBlendRate = 1.0f;                     // �A�j���̃u�����h��
    static constexpr float ANIM_PLAY_SPEED = 0.4f;  // �A�j���[�V�����̍Đ����x
    static constexpr float ANIM_BLEND_SPEED = 0.1f; // �A�j���[�V�����̃u�����h���ω����x
};