#include "stdafx.h"
#include "SceneManager.h"
#include "GameScene.h"

// ��ʐݒ�
int constexpr SCREEN_WIDTH = 1600;
int constexpr SCREEN_HEIGHT = 900;
int constexpr SCREEN_COLOR = 32;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // �E�B���h�E���[�h�ɂ���
    ChangeWindowMode(TRUE);


    // DX���C�u�����̏������i���s���͏I���j
    if (DxLib_Init() == -1) return -1;

    // ��ʂ̃T�C�Y�ƐF�[�x�̐ݒ�
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR);

    // DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
    // Effekseer���g�p����ɂ͕K���ݒ肷��B
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    // Effekseer������������B
    // �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
    if (Effekseer_Init(8000) == -1)
    {
        DxLib_End();
        return -1;
    }

    // �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
    // Effekseer���g�p����ꍇ�͕K���ݒ肷��B
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
    // �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
    // �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    // �y�o�b�t�@��L���ɂ���
    SetUseZBuffer3D(TRUE);

    // �y�o�b�t�@�ւ̏������݂�L���ɂ���
    SetWriteZBuffer3D(TRUE);

    // ����ʂɕ`��
    SetDrawScreen(DX_SCREEN_BACK);

    SceneManager* sceneManager = new SceneManager();

    sceneManager->Add<GameScene>("Game");

    // ���C���Q�[�����[�v�iESC�L�[ or �E�B���h�E���� �܂ő����j
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
        Effekseer_Sync3DSetting();

        auto prevTime = GetNowHiPerformanceCount();  // �t���[���J�n����


        // �X�V����
        sceneManager->Update();

        // ��ʂ̏�����
        ClearDrawScreen();

        // �`�揈��
        sceneManager->Draw();
        
        ScreenFlip();      // �\��ʂɔ��f�i�_�u���o�b�t�@�����O�j

        // �ȈՓI��FPS�Œ�i60fps = ��16667�}�C�N���b�j
        auto afterTime = GetNowHiPerformanceCount();
        while (afterTime - prevTime < 16667)
        {
            afterTime = GetNowHiPerformanceCount();
        }
    }




    // Effekseer���I������B
    Effkseer_End();

    // DX���C�u�����̏I������
    DxLib_End();

    return 0; // ����I��
}
