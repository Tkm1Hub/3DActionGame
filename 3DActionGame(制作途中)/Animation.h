#pragma once

class Animation
{
public:
	void LoadAnimation(int mHandle);
	void Play(int animIndex);
	void Update();
    void SetBlendRate(float newBrendRate) { animBlendRate = newBrendRate; }

private:
    int modelHandle = -1;                           // モデルハンドル
    int currentPlayAnim = -1;                       // 現在再生しているアニメ番号
    int prevPlayAnim = -1;                          // ひとつ前のアニメ番号
    float currentAnimCount = 0.0f;                  // 現在のアニメカウント
    float prevAnimCount = 0.0f;                     // ひとつ前のアニメカウント
    float animBlendRate = 1.0f;                     // アニメのブレンド率
    static constexpr float ANIM_PLAY_SPEED = 0.4f;  // アニメーションの再生速度
    static constexpr float ANIM_BLEND_SPEED = 0.1f; // アニメーションのブレンド率変化速度
};