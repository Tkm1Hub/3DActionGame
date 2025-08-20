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
    // �I�u�W�F�N�g�̃C���X�^���X��
    objMgr = new ObjectManager;
    debug = new Debug;
    input = new Input;
    cameraMgr = new CameraManager;
    shadow = new Shadow;

    //bullet = std::make_shared<Bullet>();
    collisionManager = std::make_shared<CollisionManager>();

    //�I�u�W�F�N�g�����X�g�ɒǉ�
    //objMgr->AddObject(new FreeCamera);
    objMgr->AddObject(new Player);
    objMgr->AddObject(new Enemy);
    objMgr->AddObject(new Stage);
    objMgr->AddObject(new SkyDome);

    //�L���X�g
    player = dynamic_cast<Player*>(objMgr->FindObject("Player"));
    enemy = dynamic_cast<Enemy*>(objMgr->FindObject("Enemy"));
    stage = dynamic_cast<Stage*>(objMgr->FindObject("Stage"));
    skyDome = dynamic_cast<SkyDome*>(objMgr->FindObject("SkyDome"));

    // �I�u�W�F�N�g�̏�����
    objMgr->InitAll();
    cameraMgr->Init();
    shadow->Init();
    //bullet->Init();
    BulletCreator::GetBulletCreator().Init();

    // �I�u�W�F�N�g�̃��[�h����
    objMgr->LoadAll();
    player->Load("modelPath");
    enemy->Load("data/model/character/robot.mv1");
    // �X�e�[�W�̃��f���n���h���𓖂��蔻��ɓn��
    stageColl = new StageCollision(stage->GetModelHandle());

    // �f�o�b�O�N���X�ɃI�u�W�F�N�g��n��
    debug->SetObjectManager(objMgr);
    debug->SetInput(input);
    debug->SetCamera(cameraMgr->GetCurrentCamera());
}

void GameScene::Update()
{
    // �e�I�u�W�F�N�g�̍X�V����
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
    //�V���h�E�}�b�v�̏���
    ShadowMap_DrawSetup(shadow->GetShadowMapHandle());

    // SkyDome�ȊO��`��
    for (auto obj : objMgr->GetObjects()) {
        if (obj->GetName() != "SkyDome") {
            obj->Draw();
        }
    }

    //�V���h�E�}�b�v�ւ̕`����I��
    ShadowMap_DrawEnd();

    // �`��Ɏg�p����V���h�E�}�b�v��ݒ�
    SetUseShadowMap(0, shadow->GetShadowMapHandle());

    // �I�u�W�F�N�g�̕`��
    objMgr->DrawAll();
    //bullet->Draw();
    BulletCreator::GetBulletCreator().Draw();

    // �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
    SetUseShadowMap(0, -1);

    // �f�o�b�O���̕`��
    debug->Draw();
}
