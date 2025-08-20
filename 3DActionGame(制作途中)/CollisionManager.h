#pragma once

class Bullet;
class Player;
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Update(Player& player, const std::vector<std::shared_ptr<Bullet>>& bullets);

	bool CapsuleSphereCollision(VECTOR capsuleAPos, VECTOR capsuleBPos, float capsuleR, const VECTOR& spherePos, float sphereR);
	float DistancePointSegment(VECTOR A, VECTOR B, VECTOR P);


private:

	std::shared_ptr<Bullet>bullet;
	std::vector<std::shared_ptr<Bullet>>bullets;

};