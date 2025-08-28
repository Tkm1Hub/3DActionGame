#pragma once
#include "Scene.h"

class ObjectManager;
class Debug;
class CameraSelector;
class StageCollision;
class CollisionManager;
class Shadow;
class Player;

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
    std::shared_ptr<ObjectManager> objectMgr = nullptr;

    Debug* debug = nullptr;
    std::shared_ptr<CameraSelector>cameraSelector = nullptr;
    StageCollision* stageColl = nullptr;
    Shadow* shadow = nullptr;

    std::shared_ptr<Player> player = nullptr;

    //std::shared_ptr<Bullet>bullet = nullptr;
    std::shared_ptr<CollisionManager>collisionManager = nullptr;
};