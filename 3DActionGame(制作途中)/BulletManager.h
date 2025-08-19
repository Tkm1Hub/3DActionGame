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

	const std::vector<std::shared_ptr<Bullet>>& GetBullets() { return bullets; }

private:
	std::vector<std::shared_ptr<Bullet>> bullets;
};