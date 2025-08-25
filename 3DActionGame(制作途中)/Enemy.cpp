#include "stdafx.h"
#include "Enemy.h"
#include "StageCollision.h"
#include "Animation.h"
#include "BulletFire.h"

Enemy::Enemy(std::shared_ptr<StageCollision>& stageCollPtr)
{
	name = "Enemy";
	pos = VGet(0.0f, 0.0f, 0.0f);
	scale = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	modelHandle = -1;

	stageColl = stageCollPtr;
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	pos = INIT_POS;
	scale = VGet(0.1f, 0.1f, 0.1f);
	currentState = State::Stand;
	isJumping = false;
	currentJumpPower = 0.0f;

	animation = std::make_shared<Animation>();
	bulletFire = std::make_shared<BulletFire>(this);
}

//void Enemy::Load()
//{
//	modelHandle = MV1LoadModel("data/model/character/robot.mv1");
//	MV1SetScale(modelHandle, scale);
//	anim.LoadAnimation(modelHandle);
//	//anim.Play(static_cast<int>(AnimKind::Idle));
//
//}

void Enemy::Load(const char* FilePath)
{
	modelHandle = MV1LoadModel(FilePath);
	//MV1SetScale(modelHandle, scale);
	MV1SetScale(modelHandle, VGet(0.2f,0.2f,0.2f));
	MV1SetPosition(modelHandle, pos);
}

void Enemy::Update()
{
	// ���[�g�t���[���̂y�������̈ړ��p�����[�^�𖳌��ɂ���
	DisableRootFrameZMove();

	// �G�̏�Ԃ��X�V
	State prevState = currentState;
	UpdateState();

	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// �G���Ƃ̍U������
	// ����F1�L�[�Œe���𔭎˂���i�����j
	if (CheckHitKey(KEY_INPUT_F1))
	{
		if (!pushF1)
		{
			bulletFire->SetIsActiveHorizontalBarrage(true);
			pushF1 = true;
		}
	}
	else
	{
		pushF1 = false;
	}

	// ����F2�L�[�Œe���𔭎˂���i�E�F�[�u��j
	if (CheckHitKey(KEY_INPUT_F2))
	{
		if (!pushF2)
		{
			bulletFire->SetIsActiveWaveBarrage(true);
			pushF2 = true;
		}
	}
	else
	{
		pushF2 = false;
	}

	// BulletFire�̍X�V
	bulletFire->Update();

	// �X�e�[�W���l�����Ĉړ�
	Move(moveVec);

	// �A�j���̍X�V

	animation->Update();

	MV1SetPosition(modelHandle, pos);
}

void Enemy::Draw()
{
	MV1DrawModel(modelHandle);
}

void Enemy::Move(VECTOR& moveVec)
{
	// HACK: �ړ�������0.01�����Ŕ����Ɉړ����Ă����ꍇ�͂�����ړ����ăo�O��
// x����y�������� 0.01f �ȏ�ړ������ꍇ�́u�ړ������v�t���O���P�ɂ���
	if (fabs(moveVec.x) > 0.01f || fabs(moveVec.z) > 0.01f)
	{
		isMove = true;
	}
	else
	{
		isMove = false;
	}

	if (isJumping)
	{
		// �W�����v���͏d�͂����Z
		currentJumpPower -= GRAVITY;

		// �W�����v�͂��O�ȉ����Ɨ�����
		if (currentJumpPower < 0.0f)
		{
			isFalling = true;
		}
		else
		{
			isFalling = false;
		}
	}

	// �ړ��x�N�g���̂x�������x�������̑��x�ɂ���
	moveVec.y = currentJumpPower;


	// �����蔻������āA�V�������W��ۑ�����
	pos = stageColl->CheckCollision(*this, moveVec);

	//Y���W��-100�ȉ��ɂȂ�������W������������
	if (pos.y < -100.0f || pos.y>500)
	{
		pos = INIT_POS;
	}


	// �v���C���[�̃��f���̍��W���X�V����
	MV1SetPosition(modelHandle, pos);


}

/// <summary>
/// �V��ɓ���������
/// </summary>
void Enemy::OnHitRoof()
{
	// �x�������̑��x�͔��]
	currentJumpPower = -currentJumpPower;
}


/// <summary>
/// ���ɓ���������
/// </summary>
void Enemy::OnHitFloor()
{
	// �x�������̈ړ����x�͂O��
	currentJumpPower = 0.0f;

	// �����W�����v���������ꍇ�͒��n��Ԃɂ���
	if (currentState == State::Jump)
	{
		// �ړ����Ă������ǂ����Œ��n��̏�ԂƍĐ�����A�j���[�V�����𕪊򂷂�
		if (isMove)
		{
			// �ړ����Ă���ꍇ�͑����Ԃ�
			animation->Play(static_cast<int>(AnimKind::Idle));
			currentState = State::Run;
		}
		else
		{
			// �ړ����Ă��Ȃ��ꍇ�͗����~���Ԃ�
			animation->Play(static_cast<int>(AnimKind::Idle));
			currentState = State::Stand;
		}

		// ���n���̓A�j���[�V�����̃u�����h�͍s��Ȃ�
		animation->SetBlendRate(1.0f);
	}
}

/// <summary>
/// �������m�肵���Ƃ�
/// </summary>
void Enemy::OnFall()
{
	if (currentState != State::Jump)
	{
		// �W�����v��(�������j�ɂ���
		currentState = State::Jump;
		isJumping = true;
		isFalling = true;

		// ������Ƃ����W�����v����
		currentJumpPower = FallUpPower;

		// �A�j���[�V�����͗������̂��̂ɂ���
		animation->Play(static_cast<int>(AnimKind::Idle));
	}
}


/// <summary>
/// ��Ԃ̍X�V
/// </summary>
void Enemy::UpdateState()
{
	// �ړ����̏ꍇ
	if (isMove)
	{
		// �����Ă��邩�ǂ���
		if (isRunning)
		{
			currentState = State::Run;
		}
		else
		{
			// ���܂ŗ����~�܂��Ԃ�������ړ���Ԃɂ���
			if (currentState == State::Stand)
			{
				currentState = State::Walk;
			}
		}
	}
	else
	{
		// ���܂ňړ���Ԃ������痧���~�܂�ɂ���
		if (currentState == State::Walk)
		{
			currentState = State::Stand;
		}
		else if (currentState == State::Run)
		{
			currentState = State::Stand;
		}
	}

	if (isJumping)
	{
		currentState = State::Jump;
	}
}

/// <summary>
/// ���[�g�t���[���̂y�������̈ړ��p�����[�^�𖳌��ɂ���
/// </summary>
void Enemy::DisableRootFrameZMove()
{
	// HACK:
	// �EDX���C�u�����̃��f���t�@�C�����ɂ́A�����̃��b�V���i�|���S���̏W���j��J�����A���C�g�����邱�Ƃ��ł���
	// �E�u���������̃t�@�C���́A�e�q�֌W��������AUnity�̃q�G�����L�[�݂����ɁA�K�w�\��������
	// �E���̊K�w���ꂼ��ɂ͖��O���t������ Root-Meshes-Model1
	//											         |-Model2
	// �E���̖��O�̕t�����K�w�̂��Ƃ�DX���C�u�����ł̓t���[���Ƃ���
	// �E��Ԑe�̊K�w���u���[�g�t���[���v�ƌĂԁB���[�g�t���[���͈��
	// 
	// HACK: ���̂��߂ɁH���f���̈�Ԑe�t���[���i�e�K�w�j��Z�������̈ړ��p�����[�^���[���ɂ��Ă���

	MATRIX localMatrix;

	// ���[�U�[�s�����������
	MV1ResetFrameUserLocalMatrix(modelHandle, 2);

	// ���݂̃��[�g�t���[���̍s����擾����
	localMatrix = MV1GetFrameLocalMatrix(modelHandle, 2);

	// �y�������̕��s�ړ������𖳌��ɂ���
	localMatrix.m[3][2] = 0.0f;

	// ���[�U�[�s��Ƃ��ĕ��s�ړ������𖳌��ɂ����s������[�g�t���[���ɃZ�b�g����
	MV1SetFrameUserLocalMatrix(modelHandle, 2, localMatrix);
}
