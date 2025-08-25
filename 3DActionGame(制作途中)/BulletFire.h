#pragma once
class Character;

class BulletFire
{
public:
	BulletFire(const std::shared_ptr<Character>& characterPtr);

	void Init();
	void Update();

	// �S�����ɒe�𔭎�
	void FireAllDirection(const VECTOR& pos,int bulletNum, float angleHOffset, float angleVOffset);

	// ���������ɉ�]����e���𔭎�
	void FireHorizontalBarrage(const VECTOR& firePos);

	// �E�F�[�u��̒e���𔭎�
	void FireWaveBarrage(const VECTOR& firePos);

	// �e���𔭎˒����̃t���O���Z�b�g
	void SetIsActiveHorizontalBarrage(bool isActive) { isActiveHorizontalBarrage = isActive; }	// �i�����j
	void SetIsActiveWaveBarrage(bool isActive) { isActiveWaveBarrage = isActive; }		// �i�E�F�[�u��j
		
	float GetBarrageAngleV() { return barrageFireAngleV; }
private:
	// �萔
	// ��x�ɔ��Ԃ���e�̐�
	static constexpr int BULLET_NUM = 6;
	// �S�����ɒe�𔭎˂���ہA��x�ɔ��˂���e�̐�
	static constexpr int BULLET_FIRE_ALL_DIRECTION_NUM = 6;
	// ��x�̒e���ŌJ��Ԃ����ˉ�
	static constexpr int BARRAGE_FIRE_LOOP_NUM = 30;
	static constexpr int WAVE_BARRAGE_FIRE_LOOP_NUM = 60;
	// �e�����˂��Ƃɂ��炷�p�x�i���������j
	static constexpr float BARRAGE_ANGLE_H_OFFSET = 0.15f;
	static constexpr float WAVE_BARRAGE_ANGLE_H_OFFSET = 0.15f;
	// �e�����˂��Ƃɂ��炷�p�x�i���������j
	static constexpr float BARRAGE_ANGLE_V_OFFSET = 0.01;
	// �g�̒e���ł̏�����̊p�x���
	static constexpr float WAVE_MAX_ANGLE_V = 0.7f;
	// �e�����g�ł���
	static constexpr float WAVE_SPEED = 0.03f;

	// �ϐ�
	int barrageFireLoopCount = 0;		// �e�����[�v�񐔂̃J�E���g
	int barrageFrameCount = 0.0f;		// �e���𔭎˂���t���[���̃J�E���g

	bool isActiveHorizontalBarrage = false;		// �e�����˒����i�����j
	bool isActiveWaveBarrage = false;			// �e�����˒����i�E�F�[�u�j

	float barrageFireAngleH = 0.0f;		// �e�����ˊp�x�̊�l�i�����j
	float barrageFireAngleV = 0.0f;		// �e�����ˊp�x�̊�l�i�����j
	float fireAngleH = 0.0f;			// ���ˊp�x�i�����j
	float fireAngleV = 0.0f;			// ���ˊp�x�i�����j
	float barrageFireAngleVOffset = 0.05f;		// 

	VECTOR RotateFireHorizontal(const VECTOR& dir,float angleH);	// ���������ɉ�]
	VECTOR RotateFireVertical(const VECTOR& dir, float angleV);	// ���������ɉ�]
	std::shared_ptr<Character> character = nullptr;
};