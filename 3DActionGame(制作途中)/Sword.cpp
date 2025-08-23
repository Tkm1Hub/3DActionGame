#include "stdafx.h"
#include "Sword.h"

Sword::Sword(){}

void::Sword::Init()
{
	name = "Sword";
}

void Sword::Load()
{
	modelHandle = MV1LoadModel("data/model/item/Heat-KatanaV2.mv1");
	MV1SetPosition(modelHandle, pos);
}

void Sword::Update(){}

void Sword::Draw()
{
	MV1DrawModel(modelHandle);
}