#include "stdafx.h"
#include "SkyDome.h"
#include "Player.h"

SkyDome::SkyDome(const std::shared_ptr<Player>& playerPtr)
{
	name = "SkyDome";
	pos = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	scale = VGet(0.0f, 0.0f, 0.0f);
	modelHandle = -1;

	player = playerPtr;
}

SkyDome::~SkyDome(){}

void SkyDome::Init()
{
	pos = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	scale = VGet(0.8f, 0.8f, 0.8f);
}

void SkyDome::Load()
{
	modelHandle = MV1LoadModel("data/model/stage/SkyDome_Sunny.mv1");
	MV1SetScale(modelHandle, scale);
}

void SkyDome::Update()
{
	// �X�J�C�h�[���̒��S���v���C���[�̍��W�ɐݒ�
	pos = player->GetPosition();
	MV1SetPosition(modelHandle,pos);
}

void SkyDome::Draw()
{
	MV1DrawModel(modelHandle);
}