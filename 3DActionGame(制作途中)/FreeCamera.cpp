#include "stdafx.h"
#include "FreeCamera.h"
#include "Player.h"
#include "Input.h"

FreeCamera::FreeCamera()
{
	name = "FreeCamera";
	pos = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	currentTarget = VGet(0.0f, 0.0f, 0.0f);
	angleH = 0.0f;	// 180�x
	angleV = 0.0f;
	currentAngleSpeed = 0.0f;
	isMoveAngle = false;
}

FreeCamera::~FreeCamera(){}

void FreeCamera::Init()
{
	pos = VGet(0.0f, 0.0f, -20.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	currentTarget = VGet(0.0f, 0.0f, 1.0f);

	// ���s0.1�`300�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(0.1f, 1000.0f);
}

void FreeCamera::Update(const Input& input,const Player& player)
{
	// �J�����̐��񑬓x���v�Z
	currentAngleSpeed = CalcAngleSpeed(input);

	CalcCameraAngle(input);

	//�J�����̒����_�̓v���C���[���W����K��l���������W
	nextTarget = VAdd(player.GetPosition(), VGet(0.0f, LOOK_OFFSET_Y, 0.0f));

	// �J�����̍��W��␳����
	FixCameraPosition();

	// �J�������X���[�Y�Ɉړ�
	//moveSmoothing();

	// �J�����̕�����ۑ�
	// �J�����̕����x�N�g���̓J�������W���璍���_���W�������Đ��K��
	forward = VSub(nextPosition, currentTarget);
	forward = VNorm(forward);

	// �J�����̏������C�u�����̃J�����ɔ��f������
	//SetCameraPositionAndTarget_UpVecY(currentPosition, currentTarget);
}

void FreeCamera::Draw()
{

}

void FreeCamera::CalcCameraAngle(const Input& input)
{
	// X��
	if (0.0f > input.GetRightStickX())
	{
		angleH -= currentAngleSpeed;
		// �P�W�O�x�ȏ�ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
		if (angleH > DX_PI_F)
		{
			angleH += DX_TWO_PI_F;
		}
	}
	else if(input.GetRightStickX() > 0.0f)
	{
		angleH += currentAngleSpeed;
		// �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x������
		if (angleH < -DX_PI_F)
		{
			angleH -= DX_TWO_PI_F;
		}
	}

	// Y��
	if (0.0f > input.GetRightStickY())
	{
		angleV += currentAngleSpeed;
		// ������p�x�ȉ��ɂ͂Ȃ�Ȃ��悤�ɂ���
		if (angleV > DX_PI_F * 0.5f - 0.6f)
		{
			angleV = DX_PI_F * 0.5f - 0.6f;
		}
	}
	else if (input.GetRightStickY() > 0.0f)
	{
		angleV -= currentAngleSpeed;
		// ������p�x�ȏ�ɂ͂Ȃ�Ȃ��悤�ɂ���
		if (angleV < -DX_PI_F * 0.5f + 0.6f)
		{
			angleV = -DX_PI_F * 0.5f + 0.6f;
		}
	}
}

float FreeCamera::CalcAngleSpeed(const Input&input)
{
	float stickAngle = input.GetRStickAngle();
	float stickPower = abs(stickAngle) / 1000.0f;

	// �X���ɉ������ő呬�x���v�Z
	float maxSpeed = MAX_ANGLE_SPEED * stickPower;

	// ���� or ����
	if (input.GetIsMoveRStick())
	{
		currentAngleSpeed += ACCEL; // ������
		currentAngleSpeed = min(currentAngleSpeed, maxSpeed); // maxSpeed�Ő���
	}
	else
	{
		currentAngleSpeed -= DECEL; // �����͌Œ�
		currentAngleSpeed = max(currentAngleSpeed, 0.0f); // �}�C�i�X�ɂȂ�Ȃ��悤��
	}

	// �t���O
	isMoveAngle = (currentAngleSpeed > 0.0f);

	return currentAngleSpeed;
}

void FreeCamera::FixCameraPosition()
{
	// ���������̉�]�͂x����]
	auto rotY = MGetRotY(angleH);

	// ���������̉�]�͂y����] )
	auto rotZ = MGetRotZ(angleV);

	// �J��������v���C���[�܂ł̏����������Z�b�g
	float cameraPlayerLength = DISTANCE_OFFSET;

	// �J�����̍��W���Z�o
	// �w���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����
	// ����������]( �y����] )���������Ɛ���������]( �x����] )���čX��
	// �����_�̍��W�𑫂������̂��J�����̍��W
	nextPosition = VAdd(VTransform(VTransform(VGet(-cameraPlayerLength, 0.0f, 0.0f), rotZ), rotY), nextTarget);

}


void FreeCamera::moveSmoothing()
{
	// �ڕW�n�_�ƌ��݈ʒu�̍����擾
	VECTOR diff = VSub(nextPosition, currentPosition);
	VECTOR targetDiff = VSub(nextTarget, currentTarget);

	// ���ɃX���[�W���O��������
	diff = VScale(diff, SMOOTHING);
	targetDiff = VScale(targetDiff, SMOOTHING);

	// ���݈ʒu�ɉ��Z
	currentPosition = VAdd(currentPosition, diff);
	currentTarget = VAdd(currentTarget, targetDiff);
}