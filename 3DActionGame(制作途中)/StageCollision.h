#pragma once
#include "Character.h"
class StageCollision
{
public:
	StageCollision(int modelHandle);

	VECTOR CheckCollision(Character& object, const VECTOR& moveVec);

private:
	static const int MaxHitColl = 2048;		// ��������R���W�����|���S���̍ő吔	
	static constexpr int HitTryNum = 16;	// �ǉ����o�������̍ő厎�s��
	static constexpr float HitSlideLength = 0.05f;	// ��x�̕ǉ����o�������ŃX���C�h�����鋗��
	static constexpr float DefaultSize = 100.0f;	// ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y

	// ���o���ꂽ�|���S�����ǃ|���S��( �w�y���ʂɐ����ȃ|���S�� )�����|���S��( �w�y���ʂɐ����ł͂Ȃ��|���S�� )���𔻒f���A�ۑ�����
	void AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition);

	// �ǃ|���S���Ƃ̓�������`�F�b�N���A�␳���ׂ��ړ��x�N�g����Ԃ�
	VECTOR CheckHitWithWall(Character& object, const VECTOR& checkPosition);

	// ���|���S���Ƃ̓�������`�F�b�N���A�␳���ׂ��ړ��x�N�g����Ԃ�
	VECTOR CheckHitWithFloor(Character& object, const VECTOR& checkPosition);

	// HACK: �ǂ�XZ���ʂɐ����ł���O��Ő��藧���Ă���B����ȊO��u���ƃo�O��
	int		wallNum = 0;		// �ǃ|���S���Ɣ��f���ꂽ�|���S���̐�
	int		floorNum = 0;		// ���|���S���Ɣ��f���ꂽ�|���S���̐�

	MV1_COLL_RESULT_POLY* wall[MaxHitColl] = {};		// �ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* floor[MaxHitColl] = {};		// ���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��

	int modelHandle = -1;	// ���f���n���h��

};