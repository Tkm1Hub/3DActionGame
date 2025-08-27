#include "stdafx.h"
#include "GameScene.h"
#include "Input.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "CameraSelector.h"
#include "SkyDome.h"
#include "Stage.h"
#include "StageCollision.h"
#include "CollisionManager.h"
#include "Shadow.h"
#include "Debug.h"
#include "BulletCreator.h"

GameScene::GameScene(SceneManager& manager)
    : Scene{ manager } {
}

GameScene::~GameScene()
{
    delete debug;
    delete shadow;
}

void GameScene::Init()
{
    // オブジェクトのインスタンス化
    debug = new Debug;
    shadow = new Shadow;

    objectMgr = std::make_shared<ObjectManager>();
    cameraSelector = std::make_shared<CameraSelector>();

    collisionManager = std::make_shared<CollisionManager>();

    // オブジェクトの生成
    objectMgr->Create();

    // オブジェクトの初期化
    objectMgr->InitAll();
    cameraSelector->Init();
    shadow->Init();
    //bullet->Init();
    BulletCreator::GetBulletCreator().Init();

    // ステージのモデルハンドルを当たり判定に渡す
    stageColl = new StageCollision(stage->GetModelHandle());

    // デバッグクラスにオブジェクトを渡す
    debug->SetObjectManager(objMgr);
}

void GameScene::Update()
{
    // 各オブジェクトの更新処理
    cameraSelector->Update();

    objMgr->UpdateAll();
    //bullet->Update();
    BulletCreator::GetBulletCreator().Update();

    collisionManager->Update(*player, BulletCreator::GetBulletCreator().GetBullets());

    shadow->Update(player->GetPosition());
}

void GameScene::Draw() const
{
    //シャドウマップの準備
    ShadowMap_DrawSetup(shadow->GetShadowMapHandle());

    // SkyDome以外を描画
    for (auto obj : objectMgr->GetObjects()) {
        if (obj->GetName() != "SkyDome") {
            obj->Draw();
        }
    }

    //シャドウマップへの描画を終了
    ShadowMap_DrawEnd();

    // 描画に使用するシャドウマップを設定
    SetUseShadowMap(0, shadow->GetShadowMapHandle());

    // オブジェクトの描画
    objectMgr->DrawAll();
    BulletCreator::GetBulletCreator().Draw();

    // 描画に使用するシャドウマップの設定を解除
    SetUseShadowMap(0, -1);

    // デバッグ情報の描画
    debug->Draw();
}
