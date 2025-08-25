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
	// モデルスケールの設定
	MV1SetScale(modelHandle, scale);

	// アニメーションのロード
	animation->LoadAnimation(modelHandle);
	animation->Play(static_cast<int>(PlayerAnim::Idle));
}

void Player::Update()
{
	// ルートフレームのＺ軸方向の移動パラメータを無効にする
	DisableRootFrameZMove();

	// パッド入力によって移動パラメータを設定する
	UpdateMoveParameterWithPad(camera->GetForward());
	// プレイヤーの状態を更新
	State prevState = currentState;
	UpdateState();

	// モデルの位置を更新
	Move(moveVec);
	
	// モデルの回転
	UpdateAngle();


	// アニメ番号の更新
	UpdateAnimState(prevState);

	// アニメーションの更新
	animation->Update();
	//UpdateAnimation();


}

void Player::UpdateMoveParameterWithPad(const VECTOR& cameraForward)
{
	// 左スティックの数値を取得
	float stickX = Input::GetInput().GetLeftStickX();
	float stickY = Input::GetInput().GetLeftStickY();

	bool isMoveStick = Input::GetInput().GetIsMoveLStick();

	// このフレームでの移動ベクトルを初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// 移動したかどうかのフラグを初期状態では「移動していない」を表すFALSEにする
	isMove = false;

	// スティックが傾いていたら移動中
	if (isMoveStick)
	{
		// カメラの前方向ベクトルを取得
		VECTOR camForward = cameraForward;
		camForward.y = 0.0f;
		camForward = VNorm(camForward);

		// カメラの横方向ベクトルを取得（前方向と上方向の外積）
		VECTOR camRight = VCross(camForward, VGet(0.0f, 1.0f, 0.0f));
		camRight = VNorm(camRight);

		// スティック入力をカメラの向きに変換した移動ベクトルを作成
		moveVec = VAdd(VScale(camRight, stickX), VScale(camForward, stickY));

		isMove = true;
	}

	// Aボタンでジャンプ
	if (currentState != State::Jump && (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_A))
	{
		// Ｙ軸方向の速度をセット
		currentJumpPower = JUMP_POWER;
	
		isJumping = true;
	}

	// Bボタンで走る
	if (currentState != State::Run && (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_B))
	{
		// 速度を加算
		//currentMoveSpeed = RUN_SPEED;
		isRunning = true;
	}

	// 移動ベクトルを正規化したものをプレイヤーが向くべき方向として保存
	// 0以外の場合のみ正規化
	if (VSize(moveVec) != 0.0f)
	{
		targetMoveDirection = VNorm(moveVec);
	}
}

/// <summary>
/// 移動処理
/// </summary>
void Player::Move(const VECTOR& MoveVector)
{

	// HACK: 移動距離が0.01未満で微妙に移動していた場合はじんわり移動してバグる
	// x軸かy軸方向に 0.01f 以上移動した場合は「移動した」フラグを１にする
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

	//移動速度を計算
	CulcMoveSpeed();
	moveVec = VScale(targetMoveDirection, currentMoveSpeed);

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
	pos = stageColl->CheckCollision(*this, MoveVector);

	//Y座標が-100以下になったら座標を初期化する
	if (pos.y < -100.0f || pos.y>500)
	{
		pos = INIT_POS;
	}

	// プレイヤーのモデルの座標を更新する
	MV1SetPosition(modelHandle, pos);
}


/// <summary>
/// 状態の変更
/// </summary>
/// <param name="newState"></param>
void Player::ChangeState(int newState)
{
	currentState = static_cast<State>(newState);
}

/// <summary>
/// 状態の更新
/// </summary>
void Player::UpdateState()
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
/// アニメ番号の変更
/// </summary>
/// <param name="animKind"></param>
void Player::ChangeAnimState(int animKind)
{
	currentAnimState = static_cast<PlayerAnim>(animKind);
}

/// <summary>
/// アニメ番号の更新
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

	// 立ち止まり→歩き
	if (prevState == State::Stand && currentState == State::Walk)
	{
		// 歩きモーションを再生
		animation->Play(static_cast<int>(PlayerAnim::Walk));
	}
	// 歩き→立ち止まり
	else if (prevState == State::Walk && currentState == State::Stand)
	{
		animation->Play(static_cast<int>(PlayerAnim::Idle));
	}
	// 走り→立ち止まり
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
			// 現在走りアニメーションじゃない場合、走りアニメに切り替え
			if (MV1GetAttachAnim(modelHandle, currentPlayAnim) != static_cast<int>(PlayerAnim::RunPose))
			{
				animation->Play(static_cast<int>(PlayerAnim::RunPose));
			}
		}
		else
		{
			// 現在走りアニメーションじゃない場合、走りアニメに切り替え
			if (MV1GetAttachAnim(modelHandle, currentPlayAnim) != static_cast<int>(PlayerAnim::Run))
			{
				animation->Play(static_cast<int>(PlayerAnim::Run));
			}
		}
	}

	// ジャンプ中
	else if (currentState == State::Jump)
	{
		// 現在が落下中かどうか
		if (isFalling)
		{
			// 現在のアニメーションがジャンプ用なら、落下アニメに切り替え
			if (MV1GetAttachAnim(modelHandle, currentPlayAnim) == static_cast<int>(PlayerAnim::Jump))
			{
				animation->Play(static_cast<int>(PlayerAnim::Fall));
			}
		}
		else
		{
			// 現在ジャンプアニメでない場合、ジャンプアニメに切り替え
			if (MV1GetAttachAnim(modelHandle, currentPlayAnim) != static_cast<int>(PlayerAnim::Jump))
			{
				animation->Play(static_cast<int>(PlayerAnim::Jump));
				// ジャンプ初めはブレンドを行わない
				//animBlendRate = 1.0f;
			}
		}
	}
}

/// <summary>
/// 新たなアニメーションを再生する
/// </summary>
/// <param name="animKind"></param>
void Player::PlayAnim(PlayerAnim animKind)
{
	// HACK: 指定した番号のアニメーションをアタッチし、直前に再生していたアニメーションの情報をprevに移行している
	// 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
	if (prevPlayAnim != -1)
	{
		MV1DetachAnim(modelHandle, prevPlayAnim);
		prevPlayAnim = -1;
	}

	// 今まで再生中のモーションだったものの情報をPrevに移動する
	prevPlayAnim = currentPlayAnim;
	prevAnimCount = currentAnimCount;

	// 新たに指定のモーションをモデルにアタッチして、アタッチ番号を保存する
	currentPlayAnim = MV1AttachAnim(modelHandle, static_cast<int>(animKind));
	currentAnimCount = 0.0f;

	// ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
	animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;

}


/// <summary>
/// アニメーションの更新
/// </summary>
void Player::UpdateAnimation()
{
	float animTotalTime;		// 再生しているアニメーションの総時間

	// ブレンド率が１以下の場合は１に近づける
	if (animBlendRate < 1.0f)
	{
		animBlendRate += ANIM_BLEND_SPEED;
		if (animBlendRate > 1.0f)
		{
			animBlendRate = 1.0f;
		}
	}

	// 再生しているアニメーション１の処理
	if (currentPlayAnim != -1)
	{
		// アニメーションの総時間を取得
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, currentPlayAnim);

		// 再生時間を進める
		currentAnimCount += ANIM_PLAY_SPEED;

		// ジャンプアニメーションのときだけ、ループさせない
		if (MV1GetAttachAnim(modelHandle, currentPlayAnim) == static_cast<int>(PlayerAnim::Jump))
		{
			if (currentAnimCount >= animTotalTime)
			{
				currentAnimCount = animTotalTime - 0.001f; // 最後のフレームで止める
			}
		}
		else
		{
			// 通常はループさせる
			if (currentAnimCount >= animTotalTime)
			{
				currentAnimCount = static_cast<float>(fmod(currentAnimCount, animTotalTime));
			}
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(modelHandle, currentPlayAnim, currentAnimCount);

		// アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(modelHandle, currentPlayAnim, animBlendRate);
	}

	// 再生しているアニメーション２の処理
	if (prevPlayAnim != -1)
	{
		// アニメーションの総時間を取得
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, prevPlayAnim);

		// 再生時間を進める
		prevAnimCount += ANIM_PLAY_SPEED;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (prevAnimCount > animTotalTime)
		{
			prevAnimCount = static_cast<float>(fmod(prevAnimCount, animTotalTime));
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(modelHandle, prevPlayAnim, prevAnimCount);

		// アニメーション２のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(modelHandle, prevPlayAnim, 1.0f - animBlendRate);
	}
}


/// <summary>
/// 天井に当たった時
/// </summary>
void Player::OnHitRoof()
{
	// Ｙ軸方向の速度は反転
	currentJumpPower = -currentJumpPower;
}

/// <summary>
/// 床に当たった時
/// </summary>
void Player::OnHitFloor()
{
	// Ｙ軸方向の移動速度は０に
	currentJumpPower = 0.0f;

	// もしジャンプ中だった場合は着地状態にする
	if (currentState == State::Jump)
	{
		// 移動していたかどうかで着地後の状態と再生するアニメーションを分岐する
		if (isMove)
		{
			if (isRunning)
			{
				// 移動している場合は走り状態に
				animation->Play(static_cast<int>(PlayerAnim::Run));
				currentState = State::Run;
			}
			else
			{
				// 移動している場合は走り状態に
				animation->Play(static_cast<int>(PlayerAnim::Walk));
				currentState = State::Walk;
			}
		}
		else
		{
			// 移動していない場合は立ち止り状態に
			animation->Play(static_cast<int>(PlayerAnim::Idle));
			currentState = State::Stand;
		}

		// 着地時はアニメーションのブレンドは行わない
		animation->SetBlendRate(1.0f);
		isJumping = false;
	}
}

/// <summary>
/// 落下が確定したとき
/// </summary>
void Player::OnFall()
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
		PlayAnim(PlayerAnim::Jump);
	}
}

/// <summary>
/// 移動速度の計算
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

	// 限界値を超えたら修正
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
/// モデルの角度を更新
/// </summary>
void Player::UpdateAngle()
{
	// プレイヤーの移動方向にモデルの方向を近づける
	float targetAngle;			// 目標角度
	float difference;			// 目標角度と現在の角度との差
	float speed = ANGLE_SPEED;	// 角度変更速度

	// 目標の方向ベクトルから角度値を算出する
	targetAngle = static_cast<float>(atan2(targetMoveDirection.x, targetMoveDirection.z));

	// 目標の角度と現在の角度との差を割り出す
	// 最初は単純に引き算
	difference = targetAngle - angle;

	// ある方向からある方向の差が１８０度以上になることは無いので
	// 差の値が１８０度以上になっていたら修正する
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}


	// 角度の差が０に近づける
	if (difference > 0.0f)
	{
		// 差がプラスの場合は引く
		difference -= speed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else
	{
		// 差がマイナスの場合は足す
		difference += speed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	// モデルの角度を更新
	angle = targetAngle - difference;

	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

/// <summary>
/// ルートフレームのＺ軸方向の移動パラメータを無効にする
/// </summary>
void Player::DisableRootFrameZMove()
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

/// <summary>
/// 描画処理
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