#pragma once
class Character;

class BulletFire
{
public:
	BulletFire(Character* obj) : character(obj){}

	void Init();
	void Update();
	void FireAllDirection(const VECTOR& pos,int bulletNum, float angleOffset);
	void FireHorizontalBarrage(const VECTOR& pos);

	void SetIsActiveBarrage(bool isActive) { isActiveBarrage = isActive; }
		
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
	int barrageFireLoopCount = 0;		// �e�����[�v�񐔂̃J�E���g

	bool isActiveBarrage = false;		// �e�����˒���

	float barrageFireAngle = 0.0f;		// �e�����ˊp�x�̊�l
	float BarrageFrameCount = 0.0f;		// �e���𔭎˂���t���[���̃J�E���g
	float shotAngle = 0.0f;				// ���ˊp�x

	VECTOR RotateXZ(const VECTOR& dir,float angle);	// ���������ɉ�]

	Character* character;
};