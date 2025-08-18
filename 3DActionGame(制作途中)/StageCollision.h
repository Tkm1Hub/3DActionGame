#pragma once
#include "Character.h"
class StageCollision
{
public:
	StageCollision(int modelHandle);

	VECTOR CheckCollision(Character& object, const VECTOR& moveVec);

private:
	static const int MaxHitColl = 2048;		// 処理するコリジョンポリゴンの最大数	
	static constexpr int HitTryNum = 16;	// 壁押し出し処理の最大試行回数
	static constexpr float HitSlideLength = 0.05f;	// 一度の壁押し出し処理でスライドさせる距離
	static constexpr float DefaultSize = 100.0f;	// 周囲のポリゴン検出に使用する球の初期サイズ

	// 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断し、保存する
	void AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition);

	// 壁ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
	VECTOR CheckHitWithWall(Character& object, const VECTOR& checkPosition);

	// 床ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
	VECTOR CheckHitWithFloor(Character& object, const VECTOR& checkPosition);

	// HACK: 壁はXZ平面に垂直である前提で成り立っている。それ以外を置くとバグる
	int		wallNum = 0;		// 壁ポリゴンと判断されたポリゴンの数
	int		floorNum = 0;		// 床ポリゴンと判断されたポリゴンの数

	MV1_COLL_RESULT_POLY* wall[MaxHitColl] = {};		// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* floor[MaxHitColl] = {};		// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列

	int modelHandle = -1;	// モデルハンドル

};