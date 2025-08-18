#include "stdafx.h"
#include "CameraManager.h"
#include "FreeCamera.h"
#include "FocusCamera.h"
#include "Player.h"
#include "Input.h"

CameraManager::CameraManager(){}

CameraManager::~CameraManager()
{

}

void CameraManager::Init()
{
	currentMode = CameraMode::Free;

	//camera = new CameraBase;
	//freeCamera = new FreeCamera;
	//focusCamera = new FocusCamera;

	camera->Init();
	freeCamera->Init();
	focusCamera->Init();
}


/// <summary>
///  �X�V����
/// </summary>
/// <param name="input"></param>
void CameraManager::Update(const std::shared_ptr<Input>& input,const std::shared_ptr<Player>& player)
{
	// L2�{�^���Ń��[�h�ؑ�
	if (input->GetNowFrameNewInput() & PAD_INPUT_5)
	{
		SwitchMode();
	}

	//���[�h���ƂɍX�V����
	if (currentMode == CameraMode::Free)
	{
		freeCamera->Update(input,player);
		nextPosition = freeCamera->GetNextPosition();
		nextTarget = freeCamera->GetNextTarget();
	}
	else if (currentMode == CameraMode::Focus)
	{
		focusCamera->Update();
		nextPosition = focusCamera->GetNextPosition();
		nextTarget = focusCamera->GetNextTarget();
	}

	// ���W���X���[�Y�Ɉړ�
	moveSmoothing();

	// �J�����Ɉʒu�ƒ����_��ݒ�
	camera->SetCameraPositionAndTarget(currentPosition, currentTarget);

	// �J�����̍X�V
	camera->Update();

}

/// <summary>
/// �J�����̐؂�ւ�
/// </summary>
void CameraManager::SwitchMode()
{
	if (currentMode == CameraMode::Free)
	{
		currentMode = CameraMode::Focus;
	}
	else if(currentMode == CameraMode::Focus)
	{
		currentMode = CameraMode::Free;
	}
}

/// <summary>
/// �X���[�Y�Ɉړ�
/// </summary>
void CameraManager::moveSmoothing()
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