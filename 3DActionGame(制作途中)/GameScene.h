#pragma once
#include "Scene.h"

class ObjectManager;
class Debug;
class Input;
class Player;
class Enemy;
class CameraManager;
class SkyDome;
class Stage;
class StageCollision;
class Shadow;

class GameScene : public Scene
{
public:

    /// @brief SceneManager �ւ̎Q�Ƃ��󂯎��܂��B
    // @param manager SceneManager �ւ̎Q��
    GameScene(SceneManager& manager);

    /// @brief �^�C�g�������������܂��B
    void Init() override;

    /// @brief �^�C�g�����X�V���܂��B
    void Update() override;

    /// @brief �^�C�g����`�悵�܂��B
    void Draw() const override;


private:

    // �I�u�W�F�N�g�̃|�C���^
    ObjectManager* objMgr;
    Input* input;
    Debug* debug;
    Player* player = nullptr;
    Enemy* enemy = nullptr;
    CameraManager* cameraMgr = nullptr;
    Stage* stage = nullptr;
    StageCollision* stageColl = nullptr;
    Shadow* shadow = nullptr;
    SkyDome* skyDome = nullptr;
};