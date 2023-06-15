#include <stdio.h>
#include <DxLib.h>
#define PI 3.141592654

//�ϐ��錾�G���A
const int Window_Width = 800;
const int Window_Height = 600;

int mouseX = 0;//�}�E�X���W
int mouseY = 0;//�}�E�X���W

int count = 0;

int shot_img;

void Update(void) //���t���[������
{
	DrawRotaGraph(300, 100, 5.0, PI/4, shot_img, TRUE); //�摜�̕`��
	DrawPixel(Window_Width / 2, Window_Height / 2, GetColor(255, 255, 255));	// �_��ł�
	DrawCircle(100, 100, 30, GetColor(255, 0, 0), 0);
	DrawCircle(200, 100, 30, GetColor(0, 255, 0), 1);
	DrawBox(50, 200, 100, 300, GetColor(0, 0, 255), 1);
	DrawLine(200, 200, 300, 330, GetColor(255, 255, 255), 1);
	
	count++;
	DrawFormatString(100, 100, GetColor(255, 255, 255), "frame %d", count);
	DrawFormatString(100, 120, GetColor(255, 255, 255), "sec %d", count / 60);
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);//��S��ʂɃZ�b�g
	SetGraphMode(Window_Width, Window_Height, 32);//��ʃT�C�Y�w��
	SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�

	if (DxLib_Init() == -1) { return -1; }		// �c�w���C�u��������������  �G���[���N�����璼���ɏI��

	//�摜�E���̓ǂݍ���
	shot_img = LoadGraph("shot.png");

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