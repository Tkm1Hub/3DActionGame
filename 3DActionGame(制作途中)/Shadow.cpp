#include "stdafx.h"
#include "Shadow.h"

Shadow::Shadow()
{
	shadowMapHandle = -1;
}

Shadow::~Shadow() {}

void Shadow::Init()
{
	shadowMapHandle = MakeShadowMap(SHADOW_QUALITY, SHADOW_QUALITY);
	lightDirection = VGet(0.5f, -1.0f, -0.5f);

	// ���C�g�̕�����ݒ�
	SetLightDirection(lightDirection);

	// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	SetShadowMapLightDirection(shadowMapHandle, lightDirection);
}

void Shadow::Update(const VECTOR& pos)
{

	//�V���h�E��`�悷��͈͂��w��
	VECTOR minPos = VSub(pos, VGet(100.0f, 50.0f, 100.0f));
	VECTOR maxPos = VAdd(pos, VGet(100.0f, 25.0f, 100.0f));

	SetShadowMapDrawArea(shadowMapHandle, minPos, maxPos);


}