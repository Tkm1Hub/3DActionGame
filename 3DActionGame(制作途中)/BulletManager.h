#pragma once

class Bullet;
class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void Init();
	void Update();
	void Create(VECTOR pos,VECTOR moveVec);

private:
	std::vector<std::shared_ptr<Bullet>> bullets;
};