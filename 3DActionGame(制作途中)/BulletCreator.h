#pragma once

class Bullet;
class Enemy;
class Player;
class BulletCreator
{
private:
	// �R���X�g���N�^�����J�ɂ���
	BulletCreator(){}

	// �R�s�[�R���X�g���N�^�Ƒ�����Z�q���폜
	BulletCreator(const BulletCreator&) = delete;
	BulletCreator& operator=(const BulletCreator&) = delete;

	// �v���C�x�[�g�f�X�g���N�^
	~BulletCreator(){}

public:
	// �C���X�^���X���擾���邽�߂̃��\�b�h
	static BulletCreator& GetBulletCreator()
	{
		static BulletCreator instance;	// �ÓI�ϐ��Ƃ��ăC���X�^���X���`
		return instance;
	}



	void Init();
	void Update(const Enemy& enemy,const Player& player);
	void Create(const VECTOR& pos, const VECTOR& moveVec);
	void Draw();

	const std::vector<std::shared_ptr<Bullet>>& GetBullets() { return bullets; }

private:
	std::vector<std::shared_ptr<Bullet>> bullets;
};