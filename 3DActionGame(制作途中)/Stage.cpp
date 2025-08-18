#include "stdafx.h"
#include "Stage.h"

Stage::Stage()
{
	name = "Stage";
	pos = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	scale = VGet(0.0f, 0.0f, 0.0f);
	modelHandle = -1;
}

Stage::~Stage(){}

void Stage::Init()
{
	pos = VGet(0.0f, -5.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	scale = VGet(0.05f, 0.05f, 0.05f);
}

void Stage::Load()
{
	modelHandle = MV1LoadModel("data/model/stage/Test_Frat.mv1");
	MV1SetScale(modelHandle, scale);
}

void Stage::Update(){}

void Stage::Draw()
{
	MV1DrawModel(modelHandle);
}