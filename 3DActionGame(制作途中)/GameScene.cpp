#include "stdafx.h"
#include "GameScene.h"
#include "Input.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "CameraManager.h"
#include "SkyDome.h"
#include "Stage.h"
#include "StageCollision.h"
#include "CollisionManager.h"
#include "Shadow.h"
#include "Debug.h"
//#include "Bullet.h"
#include "BulletCreator.h"

GameScene::GameScene(SceneManager& manager)
    : Scene{ manager } {
}

GameScene::~GameScene()
{
    delete objMgr;
    delete debug;
    delete input;
    delete cameraMgr;
    delete shadow;
}

void GameScene::Init()
{
    // オブジェクトのインスタンス化
    objMgr = new ObjectManager;
    debug = new Debug;
    input = new Input;
    cameraMgr = new CameraManager;
    shadow = new Shadow;

    //bullet = std::make_shared<Bullet>();
    collisionManager = std::make_shared<CollisionManager>();

    //オブジェクトをリストに追加
    //objMgr->AddObject(new FreeCamera);
    objMgr->AddObject(new Player);
    objMgr->AddObject(new Enemy);
    objMgr->AddObject(new Stage);
    objMgr->AddObject(new SkyDome);

    //キャスト
    player = dynamic_cast<Player*>(objMgr->FindObject("Player"));
    enemy = dynamic_cast<Enemy*>(objMgr->FindObject("Enemy"));
    stage = dynamic_cast<Stage*>(objMgr->FindObject("Stage"));
    skyDome = dynamic_cast<SkyDome*>(objMgr->FindObject("SkyDome"));

    // オブジェクトの初期化
    objMgr->InitAll();
    cameraMgr->Init();
    shadow->Init();
    //bullet->Init();
    BulletCreator::GetBulletCreator().Init();

    // オブジェクトのロード処理
    objMgr->LoadAll();
    player->Load("modelPath");
    enemy->Load("data/model/character/robot.mv1");
    // ステージのモデルハンドルを当たり判定に渡す
    stageColl = new StageCollision(stage->GetModelHandle());

    // デバッグクラスにオブジェクトを渡す
    debug->SetObjectManager(objMgr);
    debug->SetInput(input);
    debug->SetCamera(cameraMgr->GetCurrentCamera());
}

void GameScene::Update()
{
    // 各オブジェクトの更新処理
    input->Update();
    cameraMgr->Update(*input, *player);

    player->Update(*input, *cameraMgr->GetCurrentCamera(), *stageColl);
    enemy->Update(*stageColl);
    skyDome->Update(player->GetPosition());
    objMgr->UpdateAll();
    //bullet->Update();
    BulletCreator::GetBulletCreator().Update();

    //collisionManager->Update(*player, bulletMgr->GetBullets());

    shadow->Update(player->GetPosition());
}

void GameScene::Draw() const
{
    //シャドウマップの準備
    ShadowMap_DrawSetup(shadow->GetShadowMapHandle());

    // SkyDome以外を描画
    for (auto obj : objMgr->GetObjects()) {
        if (obj->GetName() != "SkyDome") {
            obj->Draw();
        }
    }

    //シャドウマップへの描画を終了
    ShadowMap_DrawEnd();

    // 描画に使用するシャドウマップを設定
    SetUseShadowMap(0, shadow->GetShadowMapHandle());

    // オブジェクトの描画
    objMgr->DrawAll();
    //bullet->Draw();
    BulletCreator::GetBulletCreator().Draw();

    // 描画に使用するシャドウマップの設定を解除
    SetUseShadowMap(0, -1);

    // デバッグ情報の描画
    debug->Draw();
}
