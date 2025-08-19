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

    /// @brief SceneManager への参照を受け取ります。
    // @param manager SceneManager への参照
    GameScene(SceneManager& manager);
    ~GameScene();

    /// @brief タイトルを初期化します。
    void Init() override;

    /// @brief タイトルを更新します。
    void Update() override;

    /// @brief タイトルを描画します。
    void Draw() const override;


private:

    // オブジェクトのポインタ
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