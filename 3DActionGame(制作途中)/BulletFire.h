#pragma once

class BulletFire
{
public:
	BulletFire();

	void Init();
	void Update();
	void FireAllDirection(const VECTOR& pos,int bulletNum, float angleOffset);
	void FireHorizontalBarrage(const VECTOR& pos, bool& isFireBarrage);
		
private:
	// �萔
	static constexpr int BULLET_NUM = 6;	// ��x�ɔ��Ԃ���e�̐�
	// �S�����ɒe�𔭎˂���ہA��x�ɔ��˂���e�̐�
	static constexpr int BULLET_FIRE_ALL_DIRECTION_NUM = 6;
	// ��x�̒e���ŌJ��Ԃ����ˉ�
	static constexpr int BARRAGE_FIRE_LOOP_NUM = 30;
	// �e�����˂��Ƃɂ��炷�p�x
	static constexpr float BARRAGE_ANGLE_OFFSET = 0.15f;

	// �ϐ�
	float burrageFireAngle = 0.0f; // �e�����ˊp�x�̊�l
	int barrageFireLoopCount = 0;        // �e�����[�v�񐔂̃J�E���g
	float BarrageFrameCount = 0.0f;  // �e���𔭎˂���t���[���̃J�E���g

	float shotAngle = 0.0f;					// ���ˊp�x
	
	VECTOR RotateXZ(const VECTOR& dir,float angle);	// ���������ɉ�]
};