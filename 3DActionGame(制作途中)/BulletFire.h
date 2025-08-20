#pragma once

class BulletFire
{
public:
	BulletFire();

	void Init();
	void Update();
	void FireAllDirection(const VECTOR& pos,int bulletNum);
		
private:
	static constexpr int BULLET_NUM = 6;	// ˆê“x‚É”­Ô‚·‚é’e‚Ì”
	
	float shotAngle = 0.0f;					// ”­ËŠp“x
	
	VECTOR RotateXZ(const VECTOR& dir,float angle);	// …•½•ûŒü‚É‰ñ“]

};