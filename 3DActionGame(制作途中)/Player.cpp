#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "FreeCamera.h"
#include "StageCollision.h"
#include "Animation.h"

Player::Player(const std::shared_ptr<CameraBase>& cameraPtr,std::shared_ptr<StageCollision>& stageCollPtr)
{
	name = "Player";
	pos = VGet(0.0f, 0.0f, 0.0f);
	scale = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	modelHandle = -1;

	camera = cameraPtr;
	stageColl = stageCollPtr;
}

Player::~Player()
{
}

void Player::Init()
{
	std::ifstream ifs("Player.Json");
	nlohmann::json j;
	ifs >> j;

	std::string path = j["ModelPath"];
	pos = INIT_POS;
	scale = VGet(j["Scale"]["x"], j["Scale"]["y"], j["Scale"]["z"]);
	currentState = State::Stand;
	currentAnimState = PlayerAnim::Idle;
	currentPlayAnim = 1;
	prevPlayAnim = 1;

	animation = std::make_shared<Animation>();
}

void Player::Load(const char* FilePath)
{
	std::ifstream ifs("Player.Json");
	nlohmann::json j;
	ifs >> j;

	std::string path = j["ModelPath"];
	modelHandle = MV1LoadModel(path.c_str());
	// ���f���X�P�[���̐ݒ�
	MV1SetScale(modelHandle, scale);

	// �A�j���[�V�����̃��[�h
	animation->LoadAnimation(modelHandle);
	animation->Play(static_cast<int>(PlayerAnim::Idle));
}

void Player::Update()
{
	// ���[�g�t���[���̂y�������̈ړ��p�����[�^�𖳌��ɂ���
	DisableRootFrameZMove();

	// �p�b�h���͂ɂ���Ĉړ��p�����[�^��ݒ肷��
	UpdateMoveParameterWithPad(camera->GetForward());
	// �v���C���[�̏�Ԃ��X�V
	State prevState = currentState;
	UpdateState();

	// ���f���̈ʒu���X�V
	Move(moveVec);
	
	// ���f���̉�]
	UpdateAngle();


	// �A�j���ԍ��̍X�V
	UpdateAnimState(prevState);

	// �A�j���[�V�����̍X�V
	animation->Update();
	//UpdateAnimation();


}

void Player::UpdateMoveParameterWithPad(const VECTOR& cameraForward)
{
	// ���X�e�B�b�N�̐��l���擾
	float stickX = Input::GetInput().GetLeftStickX();
	float stickY = Input::GetInput().GetLeftStickY();

	bool isMoveStick = Input::GetInput().GetIsMoveLStick();

	// ���̃t���[���ł̈ړ��x�N�g����������
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// �ړ��������ǂ����̃t���O��������Ԃł́u�ړ����Ă��Ȃ��v��\��FALSE�ɂ���
	isMove = false;

	// �X�e�B�b�N���X���Ă�����ړ���
	if (isMoveStick)
	{
		// �J�����̑O�����x�N�g�����擾
		VECTOR camForward = cameraForward;
		camForward.y = 0.0f;
		camForward = VNorm(camForward);

		// �J�����̉������x�N�g�����擾�i�O�����Ə�����̊O�ρj
		VECTOR camRight = VCross(camForward, VGet(0.0f, 1.0f, 0.0f));
		camRight = VNorm(camRight);

		// �X�e�B�b�N���͂��J�����̌����ɕϊ������ړ��x�N�g�����쐬
		moveVec = VAdd(VScale(camRight, stickX), VScale(camForward, stickY));

		isMove = true;
	}

	// A�{�^���ŃW�����v
	if (currentState != State::Jump && (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_A))
	{
		// �x�������̑��x���Z�b�g
		currentJumpPower = JUMP_POWER;
	
		isJumping = true;
	}

	// B�{�^���ő���
	if (currentState != State::Run && (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_B))
	{
		// ���x�����Z
		//currentMoveSpeed = RUN_SPEED;
		isRunning = true;
	}

	// �ړ��x�N�g���𐳋K���������̂��v���C���[�������ׂ������Ƃ��ĕۑ�
	// 0�ȊO�̏ꍇ�̂ݐ��K��
	if (VSize(moveVec) != 0.0f)
	{
		targetMoveDirection = VNorm(moveVec);
	}
}

/// <summary>
/// �ړ�����
/// </summary>
void Player::Move(const VECTOR& MoveVector)
{

	// HACK: �ړ�������0.01�����Ŕ����Ɉړ����Ă����ꍇ�͂�����ړ����ăo�O��
	// x����y�������� 0.01f �ȏ�ړ������ꍇ�́u�ړ������v�t���O���P�ɂ���
	if (fabs(MoveVector.x) > 0.01f || fabs(MoveVector.z) > 0.01f)
	{
		isMove = true;
	}
	else
	{
		isMove = false;
		isRunning = false;
	}


	if (isRunning)
	{
		runFrameCount += 1.0f;
	}
	else
	{
		runFrameCount = 0;
	}

	if (runFrameCount == 24)
	{
		currentMoveSpeed = RUN_SPEED;
	}

	//�ړ����x���v�Z
	CulcMoveSpeed();
	moveVec = VScale(targetMoveDirection, currentMoveSpeed);

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
	pos = stageColl->CheckCollision(*this, MoveVector);

	//Y���W��-100�ȉ��ɂȂ�������W������������
	if (pos.y < -100.0f || pos.y>500)
	{
		pos = INIT_POS;
	}

	// �v���C���[�̃��f���̍��W���X�V����
	MV1SetPosition(modelHandle, pos);
}


/// <summary>
/// ��Ԃ̕ύX
/// </summary>
/// <param name="newState"></param>
void Player::ChangeState(int newState)
{
	currentState = static_cast<State>(newState);
}

/// <summary>
/// ��Ԃ̍X�V
/// </summary>
void Player::UpdateState()
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
/// �A�j���ԍ��̕ύX
/// </summary>
/// <param name="animKind"></param>
void Player::ChangeAnimState(int animKind)
{
	currentAnimState = static_cast<PlayerAnim>(animKind);
}

/// <summary>
/// �A�j���ԍ��̍X�V
/// </summary>
void Player::UpdateAnimState(State prevState)
{
	if (isPlayingStopAnim)
	{
		stopAnimCount++;

		if (stopAnimCount >= STOP_ANIM_DURATION)
		{
			animation->Play(static_cast<int>(PlayerAnim::Idle));
			isPlayingStopAnim = false;
		}

		return;
	}

	// �����~�܂聨����
	if (prevState == State::Stand && currentState == State::Walk)
	{
		// �������[�V�������Đ�
		animation->Play(static_cast<int>(PlayerAnim::Walk));
	}
	// �����������~�܂�
	else if (prevState == State::Walk && currentState == State::Stand)
	{
		animation->Play(static_cast<int>(PlayerAnim::Idle));
	}
	// ���聨�����~�܂�
	else if (prevState == State::Run && currentState == State::Stand)
	{
		animation->Play(static_cast<int>(PlayerAnim::RunStop));
		isPlayingStopAnim = true;
		stopAnimCount = 0;
	}
	else if (currentState == State::Run)
	{
		if (runFrameCount < 30)
		{
			// ���ݑ���A�j���[�V��������Ȃ��ꍇ�A����A�j���ɐ؂�ւ�
			if (MV1GetAttachAnim(modelHandle, currentPlayAnim) != static_cast<int>(PlayerAnim::RunPose))
			{
				animation->Play(static_cast<int>(PlayerAnim::RunPose));
			}
		}
		else
		{
			// ���ݑ���A�j���[�V��������Ȃ��ꍇ�A����A�j���ɐ؂�ւ�
			if (MV1GetAttachAnim(modelHandle, currentPlayAnim) != static_cast<int>(PlayerAnim::Run))
			{
				animation->Play(static_cast<int>(PlayerAnim::Run));
			}
		}
	}

	// �W�����v��
	else if (currentState == State::Jump)
	{
		// ���݂����������ǂ���
		if (isFalling)
		{
			// ���݂̃A�j���[�V�������W�����v�p�Ȃ�A�����A�j���ɐ؂�ւ�
			if (MV1GetAttachAnim(modelHandle, currentPlayAnim) == static_cast<int>(PlayerAnim::Jump))
			{
				animation->Play(static_cast<int>(PlayerAnim::Fall));
			}
		}
		else
		{
			// ���݃W�����v�A�j���łȂ��ꍇ�A�W�����v�A�j���ɐ؂�ւ�
			if (MV1GetAttachAnim(modelHandle, currentPlayAnim) != static_cast<int>(PlayerAnim::Jump))
			{
				animation->Play(static_cast<int>(PlayerAnim::Jump));
				// �W�����v���߂̓u�����h���s��Ȃ�
				//animBlendRate = 1.0f;
			}
		}
	}
}

/// <summary>
/// �V���ȃA�j���[�V�������Đ�����
/// </summary>
/// <param name="animKind"></param>
void Player::PlayAnim(PlayerAnim animKind)
{
	// HACK: �w�肵���ԍ��̃A�j���[�V�������A�^�b�`���A���O�ɍĐ����Ă����A�j���[�V�����̏���prev�Ɉڍs���Ă���
	// ����ւ����s���̂ŁA�P�O�̃��[�V���������L����������f�^�b�`����
	if (prevPlayAnim != -1)
	{
		MV1DetachAnim(modelHandle, prevPlayAnim);
		prevPlayAnim = -1;
	}

	// ���܂ōĐ����̃��[�V�������������̂̏���Prev�Ɉړ�����
	prevPlayAnim = currentPlayAnim;
	prevAnimCount = currentAnimCount;

	// �V���Ɏw��̃��[�V���������f���ɃA�^�b�`���āA�A�^�b�`�ԍ���ۑ�����
	currentPlayAnim = MV1AttachAnim(modelHandle, static_cast<int>(animKind));
	currentAnimCount = 0.0f;

	// �u�����h����Prev���L���ł͂Ȃ��ꍇ�͂P�D�O��( ���݃��[�V�������P�O�O���̏�� )�ɂ���
	animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;

}


/// <summary>
/// �A�j���[�V�����̍X�V
/// </summary>
void Player::UpdateAnimation()
{
	float animTotalTime;		// �Đ����Ă���A�j���[�V�����̑�����

	// �u�����h�����P�ȉ��̏ꍇ�͂P�ɋ߂Â���
	if (animBlendRate < 1.0f)
	{
		animBlendRate += ANIM_BLEND_SPEED;
		if (animBlendRate > 1.0f)
		{
			animBlendRate = 1.0f;
		}
	}

	// �Đ����Ă���A�j���[�V�����P�̏���
	if (currentPlayAnim != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, currentPlayAnim);

		// �Đ����Ԃ�i�߂�
		currentAnimCount += ANIM_PLAY_SPEED;

		// �W�����v�A�j���[�V�����̂Ƃ������A���[�v�����Ȃ�
		if (MV1GetAttachAnim(modelHandle, currentPlayAnim) == static_cast<int>(PlayerAnim::Jump))
		{
			if (currentAnimCount >= animTotalTime)
			{
				currentAnimCount = animTotalTime - 0.001f; // �Ō�̃t���[���Ŏ~�߂�
			}
		}
		else
		{
			// �ʏ�̓��[�v������
			if (currentAnimCount >= animTotalTime)
			{
				currentAnimCount = static_cast<float>(fmod(currentAnimCount, animTotalTime));
			}
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(modelHandle, currentPlayAnim, currentAnimCount);

		// �A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(modelHandle, currentPlayAnim, animBlendRate);
	}

	// �Đ����Ă���A�j���[�V�����Q�̏���
	if (prevPlayAnim != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, prevPlayAnim);

		// �Đ����Ԃ�i�߂�
		prevAnimCount += ANIM_PLAY_SPEED;

		// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
		if (prevAnimCount > animTotalTime)
		{
			prevAnimCount = static_cast<float>(fmod(prevAnimCount, animTotalTime));
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(modelHandle, prevPlayAnim, prevAnimCount);

		// �A�j���[�V�����Q�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(modelHandle, prevPlayAnim, 1.0f - animBlendRate);
	}
}


/// <summary>
/// �V��ɓ���������
/// </summary>
void Player::OnHitRoof()
{
	// �x�������̑��x�͔��]
	currentJumpPower = -currentJumpPower;
}

/// <summary>
/// ���ɓ���������
/// </summary>
void Player::OnHitFloor()
{
	// �x�������̈ړ����x�͂O��
	currentJumpPower = 0.0f;

	// �����W�����v���������ꍇ�͒��n��Ԃɂ���
	if (currentState == State::Jump)
	{
		// �ړ����Ă������ǂ����Œ��n��̏�ԂƍĐ�����A�j���[�V�����𕪊򂷂�
		if (isMove)
		{
			if (isRunning)
			{
				// �ړ����Ă���ꍇ�͑����Ԃ�
				animation->Play(static_cast<int>(PlayerAnim::Run));
				currentState = State::Run;
			}
			else
			{
				// �ړ����Ă���ꍇ�͑����Ԃ�
				animation->Play(static_cast<int>(PlayerAnim::Walk));
				currentState = State::Walk;
			}
		}
		else
		{
			// �ړ����Ă��Ȃ��ꍇ�͗����~���Ԃ�
			animation->Play(static_cast<int>(PlayerAnim::Idle));
			currentState = State::Stand;
		}

		// ���n���̓A�j���[�V�����̃u�����h�͍s��Ȃ�
		animation->SetBlendRate(1.0f);
		isJumping = false;
	}
}

/// <summary>
/// �������m�肵���Ƃ�
/// </summary>
void Player::OnFall()
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
		PlayAnim(PlayerAnim::Jump);
	}
}

/// <summary>
/// �ړ����x�̌v�Z
/// </summary>
void Player::CulcMoveSpeed()
{
	if (isMove)
	{
		currentMoveSpeed += ACCEL;
	}
	else
	{
		currentMoveSpeed -= DECEL;
	}

	// ���E�l�𒴂�����C��
	if (isRunning)
	{
		currentMoveSpeed = std::clamp(currentMoveSpeed, 0.0f, RUN_SPEED);
	}
	else
	{
		currentMoveSpeed = std::clamp(currentMoveSpeed, 0.0f, WALK_SPEED);
	}
}

/// <summary>
/// ���f���̊p�x���X�V
/// </summary>
void Player::UpdateAngle()
{
	// �v���C���[�̈ړ������Ƀ��f���̕������߂Â���
	float targetAngle;			// �ڕW�p�x
	float difference;			// �ڕW�p�x�ƌ��݂̊p�x�Ƃ̍�
	float speed = ANGLE_SPEED;	// �p�x�ύX���x

	// �ڕW�̕����x�N�g������p�x�l���Z�o����
	targetAngle = static_cast<float>(atan2(targetMoveDirection.x, targetMoveDirection.z));

	// �ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
	// �ŏ��͒P���Ɉ����Z
	difference = targetAngle - angle;

	// ����������炠������̍����P�W�O�x�ȏ�ɂȂ邱�Ƃ͖����̂�
	// ���̒l���P�W�O�x�ȏ�ɂȂ��Ă�����C������
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}


	// �p�x�̍����O�ɋ߂Â���
	if (difference > 0.0f)
	{
		// �����v���X�̏ꍇ�͈���
		difference -= speed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else
	{
		// �����}�C�i�X�̏ꍇ�͑���
		difference += speed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	// ���f���̊p�x���X�V
	angle = targetAngle - difference;

	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

/// <summary>
/// ���[�g�t���[���̂y�������̈ړ��p�����[�^�𖳌��ɂ���
/// </summary>
void Player::DisableRootFrameZMove()
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

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw()
{
	if (modelHandle != -1)
	{
		MV1DrawModel(modelHandle);
	}
}

const VECTOR Player::GetCapsuleA()
{
	VECTOR CapsuleA = VGet(pos.x, pos.y + HIT_HEIGHT, pos.z);
	return CapsuleA;
}

const VECTOR Player::GetCapsuleB()
{
	VECTOR CapsuleB = VGet(pos.x, pos.y + HIT_RADIUS, pos.z);
	return CapsuleB;
}