#include <stdio.h>
#include <DxLib.h>
#include <math.h>
#include "PlayerAction.h"
#define PI 3.141592654
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//�}�E�X���W
int mouseX = 0;
int mouseY = 0;

//�L�[�擾�p�̔z��
char buf[256] = { 0 };
int KeyState[256] = { 0 };

//�摜�A���y
int shot_img;
int player_img;
int status_img;
int ResonanceAtTwilight_audio;

//�v���C���[�̍��W
int px = 320;
int py = 320;

//�G�̍��W
int enX[3];
int enY[3];
int enHitBoxSize[3];

int FrameCount = 0;

const int Player_HitBoxSize = 4;

void Update(void) //���t���[������
{
	DrawRotaGraph(10, 10, 1.0, 0, shot_img, TRUE); //�摜�̕`��

	DrawBox(0, 0, 100, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawRotaGraph(700, 300, 0.8, 0, status_img, TRUE); //�摜�̕`��

	FrameCount++;
	DrawFormatString(WINDOW_WIDTH - 100, 100, GetColor(255, 255, 255), "frame %d", FrameCount);
	DrawFormatString(WINDOW_WIDTH - 100, 120, GetColor(255, 255, 255), "sec %d", FrameCount / 60);
	GetMousePoint(&mouseX, &mouseY); //�}�E�X���W�X�V
	DrawFormatString(20, 50, GetColor(255, 255, 255), "MX:%3d MY:%3d", mouseX, mouseY); //����ɕ����i�}�E�X�̍��W�j��`��

	if (KeyState[KEY_INPUT_X] == TRUE) //�P������
	{
		StopSoundMem(ResonanceAtTwilight_audio);
		ChangeVolumeSoundMem(100, ResonanceAtTwilight_audio);
		PlaySoundMem(ResonanceAtTwilight_audio, DX_PLAYTYPE_BACK);
	}

	enX[0] = 200;
	enY[0] = 200;
	enHitBoxSize[0] = 30;

	DrawCircle(enX[0], enY[0], enHitBoxSize[0], GetColor(255, 0, 0), 1);

	//�G�Ƃ̍��W�`�F�b�N
	float dis = sqrt(pow((double)enX[0] -px, 2) + pow((double)enY[0] - py, 2));
	DrawFormatString(WINDOW_WIDTH - 100, 300, GetColor(255, 255, 255), "%f" , dis);
	if (dis <= 30 + Player_HitBoxSize) DrawFormatString(WINDOW_WIDTH - 100, 350, GetColor(255, 255, 255), "Hit");

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

void ImgInit(void)
{
	shot_img = LoadGraph("shot.png");
	player_img = LoadGraph("player.png");
	status_img = LoadGraph("status.png");
}
void AudioInit(void)
{
	ResonanceAtTwilight_audio = LoadSoundMem("ResonanceAtTwilight.mp3");
}

// �v���O������ WinMain ����n�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);//��S��ʂɃZ�b�g
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);//��ʃT�C�Y�w��
	SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�
	SetMainWindowText("�����̉̕P - Reflection of Diva -");
	SetBackgroundColor(0, 255, 0);

	if (DxLib_Init() == -1) { return -1; }		// �c�w���C�u��������������  �G���[���N�����璼���ɏI��

	ImgInit(); //�摜�E���̓ǂݍ���
	AudioInit();

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