#pragma once
#include "GameObject.h"

enum class State :int
{
	Stand = 0,      // �����~�܂�
	Walk = 1,       // ����
	Run = 2,        // ����
	Jump = 3,       // �W�����v
};


class Character:public GameObject
{
public:
	// ���f���̃��[�h
	virtual void Load(const char* FinePath) = 0;

	// ��Ԃ̕ύX
	virtual void ChangeState(int newState) = 0;
	virtual void ChangeAnimState(int animKind) = 0;

	// �Q�b�^�[
	virtual const enum class State GetState() const = 0;
	virtual const float GetJumpPower() const = 0;

	// �����蔻��
	virtual const float GetHitRadius() const = 0;
	virtual const float GetHitHeight() const = 0;

	virtual void OnFall() = 0;
	virtual void OnHitFloor() = 0;
	virtual void OnHitRoof() = 0;


protected:
	// �萔
	static constexpr float	FallUpPower = 0.05f;	// ���𓥂݊O�������̃W�����v��
	
	// �L�����N�^�[�p�ϐ�
	VECTOR moveVec;						// �ړ��x�N�g��
	VECTOR targetMoveDirection;			// ���f���������ׂ������̃x�N�g��
	float angle;						// ���f���̊p�x
	float currentMoveSpeed;				// ���݂̈ړ����x
	float currentJumpPower;				// Y�������̑��x

};