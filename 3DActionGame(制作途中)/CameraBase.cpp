#include "stdafx.h"
#include "CameraBase.h"

void CameraBase::Init()
{
	pos = VGet(0.0f, 0.0f, 0.0f);
	currentTarget = VGet(0.0f, 0.0f, 0.1f);
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
}


void CameraBase::Update()
{
	// ƒJƒƒ‰‚Ì•ûŒü‚ğ•Û‘¶
	forward = VSub(pos, currentTarget);
	forward = VNorm(forward);

	// ˆÊ’u‚Æ’‹“_‚Ìİ’è
	SetCameraPositionAndTarget_UpVecY(pos, currentTarget);
}

void CameraBase::SetCameraPositionAndTarget(const VECTOR& newPos, const VECTOR& newTarget)
{
	pos = newPos;
	currentTarget = newTarget;
}
