#pragma once

class Bullet;
class Player;
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Update(Player& player,std::shared_ptr<Bullet>& bullet);

	bool CapsuleSphereCollision(VECTOR capsuleAPos, VECTOR capsuleBPos, float capsuleR, VECTOR spherePos, float sphereR);
	float DistancePointSegment(VECTOR A, VECTOR B, VECTOR P);

private:

	Player* player;
	std::shared_ptr<Bullet>bullet;

};