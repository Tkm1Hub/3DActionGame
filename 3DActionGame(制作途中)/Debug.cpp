#include "stdafx.h"
#include "Debug.h"
#include "Input.h"
#include "ObjectManager.h"
#include "CameraBase.h"
#include "Player.h"
#include "Enemy.h"

void Debug::SetObjectManager(ObjectManager* mgr)
{
	objMgr = mgr;
}

void Debug::SetInput(Input* inputPtr)
{
	input = inputPtr;
}

void Debug::SetCamera(CameraBase* cameraBase)
	{
		camera = cameraBase;
	}

void Debug::Draw()
{
	// �O�t���[���̕���������
	clsDx();

	// �I�u�W�F�N�g���Ȃ���Α������^�[��
	if (!objMgr) return;

	for (auto obj : objMgr->GetObjects())
	{
		auto pos = obj->GetPosition();
		auto name = obj->GetName();

		printfDx("%s : Pos[%f, %f, %f] \n", name.c_str(), pos.x, pos.y, pos.z);

		if (name == "Player")
		{
			Player* player = dynamic_cast<Player*>(obj);
			if (player)
			{
				printfDx("AnimBlendRate : %f\n", player->GetBrendRate());
				printfDx("currentAnimCount : %f\n", player->GetCurrentAnim());
				printfDx("prevAnimCount : %f\n", player->GetPrevAnim());
				printfDx("runFramwCount : %f\n", player->GetRunFrameCount());

				DrawCapsule(player);
				// �v���C���[�̒��_�̋���`��
				DrawSphere3D(player->GetCapsuleA(), player->GetHitRadius(), 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
				// �v���C���[�̑����̋���`��
				DrawSphere3D(player->GetCapsuleB(), player->GetHitRadius(), 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

			}
		}

		if (name == "Enemy")
		{
			Enemy* enemy = dynamic_cast<Enemy*>(obj);
			if (enemy)
			{
				DrawCapsule(enemy);
			}
		}
	}

	printfDx("camera : Pos[%f, %f, %f]\n", camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);

	printfDx("RStickX : %f \n", input->GetRightStickX());
	printfDx("RStickY : %f \n", input->GetRightStickY());
	printfDx("LStickX : %f \n", input->GetLeftStickX());
	printfDx("LStickY : %f \n", input->GetLeftStickY());

}


void Debug::DrawCapsule(const Character* character)
{
	DrawCapsule3D(VGet(character->GetPosition().x, character->GetPosition().y + character->GetHitRadius(), character->GetPosition().z)
		, VGet(character->GetPosition().x, character->GetPosition().y + character->GetHitHeight(), character->GetPosition().z)
			, character->GetHitRadius(), 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
}