#include "stdafx.h"
#include "FocusCamera.h"

FocusCamera::FocusCamera(){}

void FocusCamera::Init()
{
	pos = VGet(30.0f, 30.0f, 0.0f);
	nextPosition = VGet(30.0f, 30.0f, 0.0f);
	currentTarget = VGet(0.0f, 0.0f, 0.0f);
	nextTarget = VGet(0.0f, 0.0f, 0.0f);
}

void FocusCamera::Update()
{
	pos = VGet(30.0f, 25.0f, 0.0f);
	nextPosition = VGet(00.0f, 30.0f, -100.0f);
	nextTarget = VGet(0.0f, 5.0f, 0.0f);

}