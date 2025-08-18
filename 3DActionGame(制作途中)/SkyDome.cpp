#include "stdafx.h"
#include "SkyDome.h"

SkyDome::SkyDome()
{
	name = "SkyDome";
	pos = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	scale = VGet(0.0f, 0.0f, 0.0f);
	modelHandle = -1;
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

void SkyDome::Update(const VECTOR& playerPos)
{
	// スカイドームの中心をプレイヤーの座標に設定
	pos = playerPos;
	MV1SetPosition(modelHandle,pos);
}

void SkyDome::Draw()
{
	MV1DrawModel(modelHandle);
}