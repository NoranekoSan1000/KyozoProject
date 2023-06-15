#include <stdio.h>
#include <DxLib.h>

//�ϐ��錾�G���A
const int Window_Width = 800;
const int Window_Height = 600;

void Update(void) //���t���[������
{
	DrawPixel(Window_Width / 2, Window_Height / 2 - 20, GetColor(255, 255, 255));	// �_��ł�
	DrawPixel(Window_Width / 2, Window_Height / 2, GetColor(255, 255, 255));	// �_��ł�
	DrawPixel(Window_Width / 2, Window_Height / 2 + 20, GetColor(255, 255, 255));	// �_��ł�
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);//��S��ʂɃZ�b�g
	SetGraphMode(Window_Width, Window_Height, 32);//��ʃT�C�Y�w��
	SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�

	if (DxLib_Init() == -1) { return -1; }		// �c�w���C�u��������������  �G���[���N�����璼���ɏI��

	//�摜�E���̓ǂݍ���

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//����ʏ���
		SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�
		Update();//���t���[������
		ScreenFlip();//����ʂ�\��ʂɃR�s�[
	}

	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}