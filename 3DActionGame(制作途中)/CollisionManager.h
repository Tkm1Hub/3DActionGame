#pragma once

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	bool CapsuleSphereCollision(VECTOR capsuleAPos, VECTOR capsuleBPos, float capsuleR, VECTOR spherePos, float sphereR);
	float DistancePointSegment(VECTOR A, VECTOR B, VECTOR P);

private:


};