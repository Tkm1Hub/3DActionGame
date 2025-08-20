#pragma once

class BulletFire
{
public:
	BulletFire();

	void Init();
	void Update();
	void FireAllDirection(const VECTOR& pos,int bulletNum);
		
private:
	static constexpr int BULLET_NUM = 6;	// ��x�ɔ��Ԃ���e�̐�
	
	float shotAngle = 0.0f;					// ���ˊp�x
	
	VECTOR RotateXZ(const VECTOR& dir,float angle);	// ���������ɉ�]

};