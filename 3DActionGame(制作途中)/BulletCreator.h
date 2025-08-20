#pragma once

class Bullet;
class Enemy;
class Player;
class BulletCreator
{
private:
	// コンストラクタを非公開にする
	BulletCreator(){}

	// コピーコンストラクタと代入演算子を削除
	BulletCreator(const BulletCreator&) = delete;
	BulletCreator& operator=(const BulletCreator&) = delete;

	// プライベートデストラクタ
	~BulletCreator(){}

public:
	// インスタンスを取得するためのメソッド
	static BulletCreator& GetBulletCreator()
	{
		static BulletCreator instance;	// 静的変数としてインスタンスを定義
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