#include <stdio.h>
#include <DxLib.h>
#include <math.h>
#include "Player.h"
#include "Image.h"
#include "Audio.h"
#define PI 3.141592654
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

double FrameCount = 0;

//�L�[�擾�p�̔z��
char buf[256] = { 0 };
int KeyState[256] = { 0 };

struct PlayerBullet
{
	bool exist;
	int posX;
	int posY;
	int HitBoxSize;
};
const int PLAYER_BULLET_AMOUNT = 50;
float ShotCoolTime = 0;
struct PlayerBullet p_bullet[PLAYER_BULLET_AMOUNT];

void PlayerBulletGenerate(int num ,int x, int y,int hitboxsize)
{
	p_bullet[num].exist = true;
	p_bullet[num].posX = x;
	p_bullet[num].posY = y;
	p_bullet[num].HitBoxSize = hitboxsize;
}

void PlayerBulletDestroy(int num)
{
	p_bullet[num].exist = false;
	p_bullet[num].posX = NULL;
	p_bullet[num].posY = NULL;
}

//�G
struct Enemy
{
	bool exist;
	int enX;
	int enY;
	int enHitBoxSize;
	int moveSpeed;
};
const int ENEMY_AMOUNT = 20;
Enemy enemy[ENEMY_AMOUNT];

void EnemyGenerate(int num,int x, int y, int hitboxsize,int movespeed) 
{
	enemy[num].exist = true;
	enemy[num].enX = x;
	enemy[num].enY = y;
	enemy[num].enHitBoxSize = hitboxsize;
	enemy[num].moveSpeed = movespeed;
}

void EnemyDestroy(int num)
{
	enemy[num].exist = false;
	enemy[num].enX = NULL;
	enemy[num].enY = NULL;
	enemy[num].enHitBoxSize = NULL;
	enemy[num].moveSpeed = NULL;
}

void PlayerShot(void) 
{
	if (KeyState[KEY_INPUT_Z] > 0)
	{
		if (ShotCoolTime > 0) return;
		for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++)
		{
			if (p_bullet[i].exist == false)//�V���b�g�ݒ�i�[�ꏊ�̋󂫂��m�F
			{
				PlayerBulletGenerate(i, px, py, 6);
				ShotCoolTime = 10;//�t���[���Őݒ�
				break;
			}
		}
	}
}

void Update(void) //���t���[������
{
	DrawRotaGraph(10, 10, 1.0, 0, shot_img, TRUE); //�摜�̕`��

	DrawBox(0, 0, 100, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawRotaGraph(700, 300, 0.8, 0, gameFrame_img, TRUE); //�摜�̕`��

	DrawFormatString(WINDOW_WIDTH - 200, 30, GetColor(255, 255, 255), "Score : %d", Score);
	DrawFormatString(WINDOW_WIDTH - 200, 60, GetColor(255, 255, 255), "Life : %d", Life);
	DrawFormatString(WINDOW_WIDTH - 200, 120, GetColor(255, 255, 255), "sec %.2lf", FrameCount++ / 60);

	if(ShotCoolTime >= 0) ShotCoolTime--;
	PlayerShot();

	for (int i = 0; i < PLAYER_BULLET_AMOUNT; i++)
	{
		if (p_bullet[i].exist == true) DrawCircle(p_bullet[i].posX, p_bullet[i].posY, p_bullet[i].HitBoxSize, GetColor(0, 100, 100), 1);
		else continue;

		p_bullet[i].posY -= 12;

		//��ʊO�ŏ���
		if (p_bullet[i].posY < -20)
		{
			PlayerBulletDestroy(i);
			continue;
		}

		//�G�ɓ�����
		for (int j = 0; j < ENEMY_AMOUNT; j++) 
		{
			//�G�Ƃ̍��W�`�F�b�N
			float dis = sqrt(pow((double)enemy[j].enX - p_bullet[i].posX, 2) + pow((double)enemy[j].enY - p_bullet[i].posY, 2));
			if (dis <= enemy[j].enHitBoxSize + p_bullet[i].HitBoxSize)//��e����
			{		
				EnemyDestroy(j);
				PlayerBulletDestroy(i);
				Score += 100;
				break;
			}
		}
	}

	if (KeyState[KEY_INPUT_A] == TRUE) //�P������
	{
		for (int i = 0; i < ENEMY_AMOUNT; i++) 
		{
			if (enemy[i].exist == false) 
			{
				EnemyGenerate(i,px,py-600,16,3);
				DrawFormatString(WINDOW_WIDTH - 100, 90, GetColor(255, 255, 255), "%d\n", i);
				break;
			}
		}
	}

	for (int i = 0; i < ENEMY_AMOUNT; i++)
	{
		if (enemy[i].exist == true) DrawCircle(enemy[i].enX, enemy[i].enY, enemy[i].enHitBoxSize, GetColor(255, 0, 0), 1);
		else continue;

		enemy[i].enY += enemy[i].moveSpeed;

		//��ʊO�ŏ���
		if (enemy[i].enY > WINDOW_HEIGHT + 30)
		{
			EnemyDestroy(i);
			continue;
		}

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