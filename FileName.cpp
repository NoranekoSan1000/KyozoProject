#include <stdio.h>
#include <DxLib.h>
#include "PlayerAction.h"
#define PI 3.141592654

//�ϐ��錾�G���A
const static int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

//�}�E�X���W
int mouseX = 0;
int mouseY = 0;

//�L�[�擾�p�̔z��
char buf[256] = { 0 };
int KeyState[256] = { 0 };

int FrameCount = 0;

//�v���C���[�̍��W
int px = 320;
int py = 320;

int shot_img;
int player_img;
int status_img;
int ResonanceAtTwilight_audio;


void Update(void) //���t���[������
{
	DrawRotaGraph(10, 10, 1.0, 0, shot_img, TRUE); //�摜�̕`��
	
	DrawCircle(100, 100, 30, GetColor(255, 0, 0), 0);
	DrawCircle(200, 100, 30, GetColor(0, 255, 0), 1);

	DrawBox(0, 0, 100, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawRotaGraph(WINDOW_WIDTH - 100, 300, 0.75, 0, status_img, TRUE); //�摜�̕`��

	FrameCount++;
	DrawFormatString(WINDOW_WIDTH - 100, 100, GetColor(255, 255, 255), "frame %d", FrameCount);
	DrawFormatString(WINDOW_WIDTH - 100, 120, GetColor(255, 255, 255), "sec %d", FrameCount / 60);

	GetMousePoint(&mouseX, &mouseY); //�}�E�X���W�X�V
	DrawFormatString(20, 50, GetColor(255, 255, 255), "MX:%3d MY:%3d", mouseX, mouseY); //����ɕ����i�}�E�X�̍��W�j��`��

	DrawFormatString(100, 100, GetColor(255, 255, 255), "Z KEY %d", KeyState[KEY_INPUT_Z]);
	DrawFormatString(100, 120, GetColor(255, 255, 255), "X KEY %d", KeyState[KEY_INPUT_X]);

	if (KeyState[KEY_INPUT_X] == TRUE) //�P������
	{
		StopSoundMem(ResonanceAtTwilight_audio);
		ChangeVolumeSoundMem(100, ResonanceAtTwilight_audio);
		PlaySoundMem(ResonanceAtTwilight_audio, DX_PLAYTYPE_BACK);
	}

	PlayerMove(KeyState, &px, &py);//�v���C���[�̈ړ�
	DrawRotaGraph(px, py, 1.0, 0, player_img, TRUE); //�摜�̕`��
	DrawCircle(px, py, 8, GetColor(100, 180, 255)); // �v���C���[

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