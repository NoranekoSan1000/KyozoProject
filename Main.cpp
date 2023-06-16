#include <stdio.h>
#include <DxLib.h>
#include <math.h>
#include "PlayerAction.h"
#include "Image.h"
#include "Audio.h"
#define PI 3.141592654
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//�}�E�X���W
int mouseX = 0;
int mouseY = 0;

//�L�[�擾�p�̔z��
char buf[256] = { 0 };
int KeyState[256] = { 0 };

//�v���C���[
const int InitialPosX = 350;
const int InitialPosY = 550;
const int Player_HitBoxSize = 4;
int px = InitialPosX;
int py = InitialPosY;

//�G
class Enemy{
public:
	int enX;
	int enY;
	int enHitBoxSize;
	Enemy(int x, int y, int size)
	{
		enX = x;
		enY = y;
		enHitBoxSize = size;
	};
};

Enemy enemy[3]{ {120,80,20},{220,20,20},{320,220,20} };

int FrameCount = 0;

int Life = 10;

void Update(void) //���t���[������
{
	DrawRotaGraph(10, 10, 1.0, 0, shot_img, TRUE); //�摜�̕`��

	DrawBox(0, 0, 100, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawRotaGraph(700, 300, 0.8, 0, status_img, TRUE); //�摜�̕`��

	DrawFormatString(WINDOW_WIDTH - 100, 120, GetColor(255, 255, 255), "sec %d", FrameCount++ / 60);

	if (KeyState[KEY_INPUT_X] == TRUE) //�P������
	{
		PlayBGM(ResonanceAtTwilight_audio);
	}

	for (int i = 0; i < 3; i++) 
	{
		DrawCircle(enemy[i].enX, enemy[i].enY, enemy[i].enHitBoxSize, GetColor(255, 0, 0), 1);

		//�G�Ƃ̍��W�`�F�b�N
		float dis = sqrt(pow((double)enemy[i].enX - px, 2) + pow((double)enemy[i].enY - py, 2));
		if (dis <= enemy[i].enHitBoxSize + Player_HitBoxSize)
		{
			//��e����
			px = InitialPosX;
			py = InitialPosY;
			Life -= 1;
		}
	}

	DrawFormatString(WINDOW_WIDTH - 100, 6, GetColor(255, 255, 255), "Life : %d", Life);

	PlayerMove(KeyState, &px, &py);//�v���C���[�̈ړ�
	DrawRotaGraph(px, py, 1.0, 0, player_img, TRUE); //�摜�̕`��
	DrawCircle(px, py, Player_HitBoxSize, GetColor(255, 255, 80)); // �v���C���[�̓����蔻��

}

//�L�[���͏�Ԃ��X�V����֐�
void KeyUpdate(void)
{
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++)
	{
		if (buf[i] == 1) KeyState[i]++;
		else KeyState[i] = 0;
	}
}

// �v���O������ WinMain ����n�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(FALSE);//��S��ʂɃZ�b�g
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);//��ʃT�C�Y�w��
	SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�
	SetMainWindowText("�����̉̕P - Reflection of Diva -");
	SetBackgroundColor(0, 255, 0);

	if (DxLib_Init() == -1) { return -1; }		// �c�w���C�u��������������  �G���[���N�����璼���ɏI��

	ImageInit(); //�摜�̓ǂݍ��� <- Image.cpp
	AudioInit(); //�����̓ǂݍ��� <- Audio.cpp

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