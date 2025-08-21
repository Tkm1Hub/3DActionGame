#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	Init();
}

Bullet::~Bullet(){}

// ������
void Bullet::Init()
{
	name = "Bullet";
	pos = VGet(0.0f, 0.0f, 0.0f);
	scale = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	modelHandle = -1;

	active = false;
	moveVec = VGet(0.0f, 0.0f, 0.0f);
}

void Bullet::Load(){}

// �X�V����
void Bullet::Update()
{
	// �����Ȃ瑁�����^�[��
	if (!active) return;
	Move();

	lifeCount--;

	if (lifeCount <= 0)
	{
		Reset();
	}
}

// �`�揈��
void Bullet::Draw()
{
	// �����Ȃ瑁�����^�[��
	if (!active) return;
	DrawSphere3D(pos, RADIUS, DIVNUM, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
}

// �e�̈ړ�
void Bullet::Move()
{
	moveVec = VNorm(moveVec);
	moveVec = VScale(moveVec, speed);
	pos = VAdd(pos, moveVec);
}

// �v���C���[�ɓ��������ۂ̏���
void Bullet::HitPlayer()
{
	// �v���C���[�ɓ����������\��
	active = false;
	pos = VGet(0.0f, 0.0f, 0.0f);
}

// �L����
void Bullet::Activate()
{
	active = true;
	lifeCount = LIFETIME;
}

// ������
void Bullet::Reset()
{
	active = false;
	pos = VGet(0.0f, 0.0f, 0.0f);
}