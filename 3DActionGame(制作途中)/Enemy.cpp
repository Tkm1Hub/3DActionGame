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
	// ルートフレームのＺ軸方向の移動パラメータを無効にする
	DisableRootFrameZMove();

	// 敵の状態を更新
	State prevState = currentState;
	UpdateState();

	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// 敵ごとの攻撃処理
	// 仮にF1キーで弾幕を発射する（水平）
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

	// 仮にF2キーで弾幕を発射する（ウェーブ状）
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

	// BulletFireの更新
	bulletFire->Update();

	// ステージを考慮して移動
	Move(moveVec);

	// アニメの更新

	animation->Update();

	MV1SetPosition(modelHandle, pos);
}

void Enemy::Draw()
{
	MV1DrawModel(modelHandle);
}

void Enemy::Move(VECTOR& moveVec)
{
	// HACK: 移動距離が0.01未満で微妙に移動していた場合はじんわり移動してバグる
// x軸かy軸方向に 0.01f 以上移動した場合は「移動した」フラグを１にする
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
		// ジャンプ中は重力を加算
		currentJumpPower -= GRAVITY;

		// ジャンプ力が０以下だと落下中
		if (currentJumpPower < 0.0f)
		{
			isFalling = true;
		}
		else
		{
			isFalling = false;
		}
	}

	// 移動ベクトルのＹ成分をＹ軸方向の速度にする
	moveVec.y = currentJumpPower;


	// 当たり判定をして、新しい座標を保存する
	pos = stageColl->CheckCollision(*this, moveVec);

	//Y座標が-100以下になったら座標を初期化する
	if (pos.y < -100.0f || pos.y>500)
	{
		pos = INIT_POS;
	}


	// プレイヤーのモデルの座標を更新する
	MV1SetPosition(modelHandle, pos);


}

/// <summary>
/// 天井に当たった時
/// </summary>
void Enemy::OnHitRoof()
{
	// Ｙ軸方向の速度は反転
	currentJumpPower = -currentJumpPower;
}


/// <summary>
/// 床に当たった時
/// </summary>
void Enemy::OnHitFloor()
{
	// Ｙ軸方向の移動速度は０に
	currentJumpPower = 0.0f;

	// もしジャンプ中だった場合は着地状態にする
	if (currentState == State::Jump)
	{
		// 移動していたかどうかで着地後の状態と再生するアニメーションを分岐する
		if (isMove)
		{
			// 移動している場合は走り状態に
			animation->Play(static_cast<int>(AnimKind::Idle));
			currentState = State::Run;
		}
		else
		{
			// 移動していない場合は立ち止り状態に
			animation->Play(static_cast<int>(AnimKind::Idle));
			currentState = State::Stand;
		}

		// 着地時はアニメーションのブレンドは行わない
		animation->SetBlendRate(1.0f);
	}
}

/// <summary>
/// 落下が確定したとき
/// </summary>
void Enemy::OnFall()
{
	if (currentState != State::Jump)
	{
		// ジャンプ中(落下中）にする
		currentState = State::Jump;
		isJumping = true;
		isFalling = true;

		// ちょっとだけジャンプする
		currentJumpPower = FallUpPower;

		// アニメーションは落下中のものにする
		animation->Play(static_cast<int>(AnimKind::Idle));
	}
}


/// <summary>
/// 状態の更新
/// </summary>
void Enemy::UpdateState()
{
	// 移動中の場合
	if (isMove)
	{
		// 走っているかどうか
		if (isRunning)
		{
			currentState = State::Run;
		}
		else
		{
			// 今まで立ち止まり状態だったら移動状態にする
			if (currentState == State::Stand)
			{
				currentState = State::Walk;
			}
		}
	}
	else
	{
		// 今まで移動状態だったら立ち止まりにする
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
/// ルートフレームのＺ軸方向の移動パラメータを無効にする
/// </summary>
void Enemy::DisableRootFrameZMove()
{
	// HACK:
	// ・DXライブラリのモデルファイル内には、複数のメッシュ（ポリゴンの集合）やカメラ、ライトを入れることができる
	// ・置いた複数のファイルは、親子関係をつけたり、Unityのヒエラルキーみたいに、階層構造が作れる
	// ・この階層それぞれには名前が付けられる Root-Meshes-Model1
	//											         |-Model2
	// ・この名前の付いた階層のことをDXライブラリではフレームという
	// ・一番親の階層を「ルートフレーム」と呼ぶ。ルートフレームは一つ
	// 
	// HACK: 何のために？モデルの一番親フレーム（親階層）のZ軸方向の移動パラメータをゼロにしている

	MATRIX localMatrix;

	// ユーザー行列を解除する
	MV1ResetFrameUserLocalMatrix(modelHandle, 2);

	// 現在のルートフレームの行列を取得する
	localMatrix = MV1GetFrameLocalMatrix(modelHandle, 2);

	// Ｚ軸方向の平行移動成分を無効にする
	localMatrix.m[3][2] = 0.0f;

	// ユーザー行列として平行移動成分を無効にした行列をルートフレームにセットする
	MV1SetFrameUserLocalMatrix(modelHandle, 2, localMatrix);
}
