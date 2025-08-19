#pragma once

class Bullet;
class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void Init();
	void Update();
	void Create(const VECTOR& pos, const VECTOR& moveVec);
	void Draw();

private:
	std::vector<std::shared_ptr<Bullet>> bullets;
};