#include <stdio.h>
#include <DxLib.h>
#define PI 3.141592654

//�ϐ��錾�G���A
const int Window_Width = 800;
const int Window_Height = 600;

int mouseX = 0;//�}�E�X���W
int mouseY = 0;//�}�E�X���W

//�L�[�擾�p�̔z��
char buf[256] = { 0 };
int keyState[256] = { 0 };

int count = 0;

int shot_img;

//�L�[���͏�Ԃ��X�V����֐�
void KeyUpdate(void)
{
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++)
	{
		if (buf[i] == 1) {
			keyState[i]++;
		}
		else {
			keyState[i] = 0;
		}
	}
}

int x = 100;

void Update(void) //���t���[������
{
	DrawRotaGraph(300, 100, 5.0, PI/4, shot_img, TRUE); //�摜�̕`��
	DrawPixel(Window_Width / 2, Window_Height / 2, GetColor(255, 255, 255));	// �_��ł�
	DrawCircle(100, 100, 30, GetColor(255, 0, 0), 0);
	DrawCircle(200, 100, 30, GetColor(0, 255, 0), 1);
	DrawBox(50, 200, 100, 300, GetColor(0, 0, 255), 1);
	DrawLine(200, 200, 300, 330, GetColor(255, 255, 255), 1);
	
	count++;
	DrawFormatString(Window_Width-100, 100, GetColor(255, 255, 255), "frame %d", count);
	DrawFormatString(Window_Width-100, 120, GetColor(255, 255, 255), "sec %d", count / 60);

	GetMousePoint(&mouseX, &mouseY); //�}�E�X���W�X�V
	DrawFormatString(20, 50, GetColor(255, 255, 255), "MX:%3d MY:%3d", mouseX, mouseY); //����ɕ����i�}�E�X�̍��W�j��`��

	DrawFormatString(100, 100, GetColor(255, 255, 255), "Z KEY %d", keyState[KEY_INPUT_Z]);
	DrawFormatString(100, 120, GetColor(255, 255, 255), "X KEY %d", keyState[KEY_INPUT_X]);

	if (keyState[KEY_INPUT_Z] > 0) //�p������
	{
		x += 1;
	}
	if (keyState[KEY_INPUT_X] == TRUE) //�P������
	{
		x += 30;
	}
	DrawCircle(x, 200, 32, GetColor(255, 255, 0));
}

void ImgInit(void)
{
	shot_img = LoadGraph("shot.png");
}

// �v���O������ WinMain ����n�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);//��S��ʂɃZ�b�g
	SetGraphMode(Window_Width, Window_Height, 32);//��ʃT�C�Y�w��
	SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�

	if (DxLib_Init() == -1) { return -1; }		// �c�w���C�u��������������  �G���[���N�����璼���ɏI��

	ImgInit(); //�摜�E���̓ǂݍ���

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//����ʏ���
		SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�
		KeyUpdate();//�L�[���͏�Ԃ��X�V����i����֐��j
		Update();//���t���[������
		ScreenFlip();//����ʂ�\��ʂɃR�s�[
	}

	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}