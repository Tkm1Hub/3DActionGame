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
class CollisionManager;
class Shadow;
class Bullet;

class GameScene : public Scene
{
public:

    /// @brief SceneManager �ւ̎Q�Ƃ��󂯎��܂��B
    // @param manager SceneManager �ւ̎Q��
    GameScene(SceneManager& manager);
    ~GameScene();

    /// @brief �^�C�g�������������܂��B
    void Init() override;

    /// @brief �^�C�g�����X�V���܂��B
    void Update() override;

    /// @brief �^�C�g����`�悵�܂��B
    void Draw() const override;


private:

    // �I�u�W�F�N�g�̃|�C���^
    ObjectManager* objMgr = nullptr;
    Input* input = nullptr;
    Debug* debug = nullptr;
    Player* player = nullptr;
    Enemy* enemy = nullptr;
    CameraManager* cameraMgr = nullptr;
    Stage* stage = nullptr;
    StageCollision* stageColl = nullptr;
    Shadow* shadow = nullptr;
    SkyDome* skyDome = nullptr;

    std::shared_ptr<Bullet>bullet = nullptr;
    std::shared_ptr<CollisionManager>collisionManager = nullptr;
};