#include <stdio.h>
#include <DxLib.h>
#include <math.h>
#include "Player.h"
#include "Image.h"
#include "Audio.h"
#include "Enemy.h"
#include "Player_Bullet.h"
#define PI 3.141592654
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

double FrameCount = 0;

//�L�[�擾�p�̔z��
char buf[256] = { 0 };
int KeyState[256] = { 0 };

void ViewStatus(void)
{
	//�g
	DrawBox(0, 0, 100, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawRotaGraph(700, 300, 0.8, 0, gameFrame_img, TRUE);

	//�e�L�X�g
	DrawFormatString(WINDOW_WIDTH - 200, 30, GetColor(255, 255, 255), "Score : %d", Score);
	DrawFormatString(WINDOW_WIDTH - 200, 60, GetColor(255, 255, 255), "Life : %d", Life);
	DrawFormatString(WINDOW_WIDTH - 200, 120, GetColor(255, 255, 255), "sec %.2lf", FrameCount++ / 60);
}

void PlayerBulletAction(void)
{
	for (int i = 0; i < P_Bullet_Amount; i++)
	{
		if (P_Bullet_exist[i] == true) DrawCircle(P_Bullet_PosX[i], P_Bullet_PosY[i], P_Bullet_HitBoxSize[i], GetColor(0, 100, 100), 1);
		else continue;

		P_Bullet_PosY[i] -= 12;

		//��ʊO�ŏ���
		if (P_Bullet_PosY[i] < -20)
		{
			PlayerBulletDestroy(i);
			continue;
		}

		//�G�ɒe��������
		for (int j = 0; j < Enemy_Amount; j++)
		{
			//�G�Ƃ̍��W�`�F�b�N
			float dis = sqrt(pow((double)Enemy_X[j] - P_Bullet_PosX[i], 2) + pow((double)Enemy_Y[j] - P_Bullet_PosY[i], 2));
			if (dis <= Enemy_HitBoxSize[j] + P_Bullet_HitBoxSize[i])//��e����
			{
				EnemyDestroy(j);
				PlayerBulletDestroy(i);
				Score += 100;
				break;
			}
		}
	}
}

void EnemyAction(void)
{
	for (int i = 0; i < Enemy_Amount; i++)
	{
		//�G�L�����摜�\��
		if (Enemy_exist[i] == true) DrawCircle(Enemy_X[i], Enemy_Y[i], Enemy_HitBoxSize[i], GetColor(255, 0, 0), 1);
		else continue;

		EnemyMove(i);

		//��ʊO�ŏ���
		if (Enemy_Y[i] > WINDOW_HEIGHT + 30)
		{
			EnemyDestroy(i);
			continue;
		}

		//�G�Ƃ̍��W�`�F�b�N
		float dis = sqrt(pow((double)Enemy_X[i] - px, 2) + pow((double)Enemy_Y[i] - py, 2));
		if (dis <= Enemy_HitBoxSize[i] + Player_HitBoxSize)
		{
			//��e����
			px = InitialPosX;
			py = InitialPosY;
			Life -= 1;
		}
	}
}

void EnemySpawn(void) 
{
	if (KeyState[KEY_INPUT_A] == TRUE) //�P������
	{
		for (int i = 0; i < Enemy_Amount; i++)
		{
			if (Enemy_exist[i] == false)
			{
				EnemyGenerate(i, px, py - 600, 16, 3, 0);
				DrawFormatString(WINDOW_WIDTH - 100, 90, GetColor(255, 255, 255), "%d\n", i);
				break;
			}
		}
	}
}

void Update(void) //���t���[������
{
	ViewStatus();

	if (P_ShotCoolTime >= 0) P_ShotCoolTime--;
	if (KeyState[KEY_INPUT_Z] > 0)
	{
		PlayerShotGenerate(px, py);//�ˌ�
	}

	PlayerBulletAction();
	EnemyAction();
	EnemySpawn();

	PlayerMove(KeyState);//�v���C���[�̈ړ�
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
	ChangeWindowMode(TRUE);//��S��ʂɃZ�b�g
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);//��ʃT�C�Y�w��
	SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�
	SetMainWindowText("�����̉̕P - Reflection of Diva -");
	SetBackgroundColor(0, 200, 200);

	if (DxLib_Init() == -1) { return -1; }		// �c�w���C�u��������������  �G���[���N�����璼���ɏI��

	ImageInit(); //�摜�̓ǂݍ��� <- Image.cpp
	AudioInit(); //�����̓ǂݍ��� <- Audio.cpp
	PlayBGM(ResonanceAtTwilight_audio);

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