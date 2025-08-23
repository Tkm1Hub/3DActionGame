#include "stdafx.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Bullet.h"

CollisionManager::CollisionManager()
{}

CollisionManager::~CollisionManager(){}

void CollisionManager::Update(Player& player, const std::vector<std::shared_ptr<Bullet>>& bullets)
{
	// �L��������Ă�����Փ˔���
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			// �����v���C���[�ƒe���Փ˂�����
			if (CapsuleSphereCollision(player.GetCapsuleA(), player.GetCapsuleB(), player.GetHitRadius(),
				bullet->GetPos(), bullet->GetRadius()))
			{
				bullet->HitPlayer();
			}
		}
	}
}

// �J�v�Z���Ƌ��̓����蔻��
bool CollisionManager::CapsuleSphereCollision(VECTOR capsuleAPos, VECTOR capsuleBPos, float capsuleR, const VECTOR& spherePos, float sphereR)
{
	float dist = DistancePointSegment(capsuleAPos, capsuleBPos, spherePos);
	return dist <= (capsuleR + sphereR);
}

// ����AB�Ɠ_P�̍ŒZ���������߂�
float CollisionManager::DistancePointSegment(VECTOR A, VECTOR B, VECTOR P)
{
	VECTOR AB = VSub(B, A);
	VECTOR AP = VSub(P, A);

	float ab2 = VDot(AB, AB);		// |AB|^2
	float ap_ab = VDot(AP, AB);		// AP��AB�̓���

	float t = ap_ab / ab2;			// �ˉe�W��

	// �����͈͂�Clamp(�O�`�P)
	std::clamp(t, 0.0f, 1.0f);

	// �ŒZ�ړ_ = A + t * AB
	VECTOR closest = VAdd(A, VScale(AB, t));

	// �_P�ƍŒZ�ړ_�̋���
	return VSize(VSub(P, closest));
}