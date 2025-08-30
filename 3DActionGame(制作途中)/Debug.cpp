#include "stdafx.h"
#include "Debug.h"
#include "Input.h"
#include "ObjectManager.h"
#include "CameraBase.h"
#include "Player.h"
#include "Enemy.h"

void Debug::SetObjectManager(const std::shared_ptr<ObjectManager>& objectMgrPtr)
{
	objMgr = objectMgrPtr;
}

void Debug::Draw()
{
	// 前フレームの文字を消去
	clsDx();

	// オブジェクトがなければ早期リターン
	if (!objMgr) return;

	for (auto obj : objMgr->GetObjects())
	{
		auto pos = obj->GetPosition();
		auto name = obj->GetName();

		printfDx("%s : Pos[%f, %f, %f] \n", name.c_str(), pos.x, pos.y, pos.z);

		if (name == "Player")
		{
			std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(obj);
			if (player)
			{
				printfDx("AnimBlendRate : %f\n", player->GetBrendRate());
				printfDx("currentAnimCount : %f\n", player->GetCurrentAnim());
				printfDx("prevAnimCount : %f\n", player->GetPrevAnim());
				printfDx("runFramwCount : %f\n", player->GetRunFrameCount());

				DrawCapsule(player);
				// プレイヤーの頂点の球を描画
				DrawSphere3D(player->GetCapsuleA(), player->GetHitRadius(), 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
				// プレイヤーの足元の球を描画
				DrawSphere3D(player->GetCapsuleB(), player->GetHitRadius(), 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

			}
		}

		if (name == "Enemy")
		{
			std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(obj);
			if (enemy)
			{
				DrawCapsule(enemy);
			}
		}
	}


	printfDx("RStickX : %f \n", Input::GetInput().GetRightStickX());
	printfDx("RStickY : %f \n", Input::GetInput().GetRightStickY());
	printfDx("LStickX : %f \n", Input::GetInput().GetLeftStickX());
	printfDx("LStickY : %f \n", Input::GetInput().GetLeftStickY());

}


void Debug::DrawCapsule(const std::shared_ptr<Character>& character)
{
	DrawCapsule3D(VGet(character->GetPosition().x, character->GetPosition().y + character->GetHitRadius(), character->GetPosition().z)
		, VGet(character->GetPosition().x, character->GetPosition().y + character->GetHitHeight(), character->GetPosition().z)
			, character->GetHitRadius(), 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
}