#pragma once
class Character;

class BulletFire
{
public:
	BulletFire(){}

	void Init();
	void Update();

	void SetCharacter(Character* characterPtr);

	// �S�����ɒe�𔭎�
	void FireAllDirection(const VECTOR& pos,int bulletNum, float angleHOffset, float angleVOffset);

	// ���������ɉ�]����e���𔭎�
	void FireHorizontalBarrage(const VECTOR& firePos);

	// �E�F�[�u��̒e���𔭎�
	void FireWaveBarrage(const VECTOR& firePos);

	// �e���𔭎˒����̃t���O���Z�b�g
	void SetIsActiveHorizontalBarrage(bool isActive) { isActiveHorizontalBarrage = isActive; }	// �i�����j
	void SetIsActiveWaveBarrage(bool isActive) { isActiveWaveBarrage = isActive; }		// �i�E�F�[�u��j
		
private:
	// �萔
	// ��x�ɔ��Ԃ���e�̐�
	static constexpr int BULLET_NUM = 6;
	// �S�����ɒe�𔭎˂���ہA��x�ɔ��˂���e�̐�
	static constexpr int BULLET_FIRE_ALL_DIRECTION_NUM = 6;
	// ��x�̒e���ŌJ��Ԃ����ˉ�
	static constexpr int BARRAGE_FIRE_LOOP_NUM = 30;
	// �e�����˂��Ƃɂ��炷�p�x�i���������j
	static constexpr float BARRAGE_ANGLE_H_OFFSET = 0.15f;
	// �e�����˂��Ƃɂ��炷�p�x�i���������j
	static constexpr float BARRAGE_ANGLE_V_OFFSET = 0.1;

	// �ϐ�
	int barrageFireLoopCount = 0;		// �e�����[�v�񐔂̃J�E���g

	bool isActiveHorizontalBarrage = false;		// �e�����˒����i�����j
	bool isActiveWaveBarrage = false;			// �e�����˒����i�E�F�[�u�j

	float barrageFireAngleH = 0.0f;		// �e�����ˊp�x�̊�l�i�����j
	float barrageFireAngleV = 0.0f;		// �e�����ˊp�x�̊�l�i�����j
	float BarrageFrameCount = 0.0f;		// �e���𔭎˂���t���[���̃J�E���g
	float fireAngleH = 0.0f;			// ���ˊp�x�i�����j
	float fireAngleV = 0.0f;			// ���ˊp�x�i�����j
	float barrageFireAngleVOffset = 0.0f;		// 

	VECTOR RotateFireHorizontal(const VECTOR& dir,float angleH);	// ���������ɉ�]
	VECTOR RotateFireVertical(const VECTOR& dir, float angleV);	// ���������ɉ�]

	Character* character = nullptr;
};