#include "stdafx.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Bullet.h"

CollisionManager::CollisionManager()
{}

CollisionManager::~CollisionManager(){}

void CollisionManager::Update(Player& player, std::shared_ptr<Bullet>& bullet)
{
	// ‚à‚µƒvƒŒƒCƒ„[‚Æ’e‚ªÕ“Ë‚µ‚½‚ç
	if (CapsuleSphereCollision(player.GetCapsuleA(), player.GetCapsuleB(), player.GetHitRadius(),
		bullet->GetPos(), bullet->GetRadius()))
	{
		bullet->HitPlayer();
	}

}

// ƒJƒvƒZƒ‹‚Æ‹…‚Ì“–‚½‚è”»’è
bool CollisionManager::CapsuleSphereCollision(VECTOR capsuleAPos, VECTOR capsuleBPos, float capsuleR, const VECTOR& spherePos, float sphereR)
{
	float dist = DistancePointSegment(capsuleAPos, capsuleBPos, spherePos);
	return dist <= (capsuleR + sphereR);
}


// ü•ªAB‚Æ“_P‚ÌÅ’Z‹——£‚ğ‹‚ß‚é
float CollisionManager::DistancePointSegment(VECTOR A, VECTOR B, VECTOR P)
{
	VECTOR AB = VSub(B, A);
	VECTOR AP = VSub(A, P);

	float ab2 = VDot(AB, AB);		// |AB|^2
	float ap_ab = VDot(AP, AB);		// AP‚ÆAB‚Ì“àÏ

	float t = ap_ab / ab2;			// Ë‰eŒW”

	// ü•ª”ÍˆÍ‚ÉClamp(‚O`‚P)
	if (t < 0.0f)t = 0.0f;
	if (t > 1.0f)t = 1.0f;

	// Å’ZÚ“_ = A + t * AB
	VECTOR closest = VAdd(A, VScale(AB, t));

	// “_P‚ÆÅ’ZÚ“_‚Ì‹——£
	return VSize(VSub(P, closest));
}