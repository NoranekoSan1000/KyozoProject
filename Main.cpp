#include "GameData.h"
#include "Enemy_Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Player_Bullet.h"

double FrameCount = 0;

//�L�[�擾�p�̔z��
char buf[256] = { 0 };
int KeyState[256] = { 0 };

void PlayerShotAction()
{
	if (KeyState[KEY_INPUT_Z] > 0)
	{
		if (P_ShotCoolTime > 0) return;
		if (Level >= 0)
		{
			PlayerShot(px, py - 8, 0);//�ˌ�
		}
		if (Level >= 1 && Level < 3)//�_��Lv1
		{
			PlayerShot(px, py + 20, 7);//�ˌ�
		}
		if (Level >= 2)
		{
			PlayerShot(px, py - 4, 1);//�ˌ�
			PlayerShot(px, py - 4, 2);//�ˌ�
		}
		if (Level >= 3)//�_��Lv2
		{
			PlayerShot(px + 8, py + 8, 5);//�ˌ�
			PlayerShot(px - 8, py + 8, 6);//�ˌ�
		}
		P_ShotCoolTime = 8;//�t���[���Őݒ�
	}
}

void ViewStatus(void)
{

	//�g
	DrawBox(0, 0, 25, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawBox(0, 0, WINDOW_WIDTH, 25, GetColor(0, 0, 0), 1);
	DrawBox(0, WINDOW_HEIGHT-25, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawRotaGraph(750, 400, 1, 0, gameFrame_img, TRUE);

	//�e�L�X�g
	DrawFormatString(WINDOW_WIDTH - 200, 30, GetColor(255, 255, 255), "Score : %d", Score);
	DrawFormatString(WINDOW_WIDTH - 200, 60, GetColor(255, 255, 255), "Life : %d", Life);
	DrawFormatString(WINDOW_WIDTH - 200, 120, GetColor(255, 255, 255), "sec %.2lf", FrameCount++ / 60);
}

int intu;
void ViewBackGround(void)//�w�i���[�v
{
	intu += 2;
	DrawRotaGraph(300, 0 + intu, 1, 0, backgroundBack_img, TRUE);
	DrawRotaGraph(300, 0 + intu, 1, 0, backgroundFront_img, TRUE);
	if (intu >= 800) intu = 0;
}

void GameProcess(void)
{
	ViewBackGround(); //Fade�p���w�i

	if (P_ShotCoolTime >= 0) P_ShotCoolTime--;
	if (DamagedCoolTime >= 0) DamagedCoolTime--;

	if (KeyState[KEY_INPUT_A] == TRUE) EnemySpawn();
	EnemyAction();

	EnemyBulletAction();//�G�̒e�̏���

	PlayerShotAction();
	PlayerBulletAction(); //���C���[�̒e�̏���

	PlayerMove(KeyState);//�v���C���[�̈ړ�
	ViewPlayer();//�v���C���[�\��

	ViewFadeWindow();
	ViewStatus();	
}

void Update(void) //���t���[������
{
	ChangeScene();//fade��p�����V�[���`�F���W�@ChangeSceneActive -> true�Ŏ��s

	if (GameScene == Title_Scene)
	{
		PlayBGM(BGM[0]);
		DrawRotaGraph(450, 400, 1, 0, Title_img, TRUE);
		if (KeyState[KEY_INPUT_S] == TRUE)
		{		
			ChangeSceneActive = true;
			nextScene = DifficultyLvSelect_Scene;//�V�[���J�ڗp�B���̂Q�̓Z�b�g
		}
	}
	if (GameScene == DifficultyLvSelect_Scene)
	{
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
		DrawRotaGraph(450, 140, 1, 0, DifficultyLv_img[0], TRUE);
		DrawRotaGraph(450, 310, 1, 0, DifficultyLv_img[1], TRUE);
		DrawRotaGraph(450, 480, 1, 0, DifficultyLv_img[2], TRUE);
		DrawRotaGraph(450, 650, 1, 0, DifficultyLv_img[3], TRUE);
		if (KeyState[KEY_INPUT_P] == TRUE)
		{
			ChangeSceneActive = true;
			nextScene = Stage1_Scene;//�V�[���J�ڗp�B���̂Q�̓Z�b�g
		}
	}
	if (GameScene == Stage1_Scene)
	{
		PlayBGM(BGM[1]);
		GameProcess();
		if (KeyState[KEY_INPUT_P] == TRUE)
		{	
			ChangeSceneActive = true;
			nextScene = Stage2_Scene;
		}
	}
	if (GameScene == Stage2_Scene)
	{
		PlayBGM(BGM[3]);
		GameProcess();
		if (KeyState[KEY_INPUT_P] == TRUE)
		{
			ChangeSceneActive = true;
			nextScene = Stage3_Scene;
		}
	}
	if (GameScene == Stage3_Scene)
	{
		PlayBGM(BGM[5]);
		GameProcess();
		if (KeyState[KEY_INPUT_P] == TRUE)
		{
			ChangeSceneActive = true;
			nextScene = Stage4_Scene;
		}
	}
	if (GameScene == Stage4_Scene)
	{
		PlayBGM(BGM[7]);
		GameProcess();
		if (KeyState[KEY_INPUT_P] == TRUE)
		{
			ChangeSceneActive = true;
			nextScene = Title_Scene;
		}
	}
}

//�L�[���͏�Ԃ��X�V����֐�
void KeyUpdate(void)
{
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++)
	{
		if (buf[i] == 0)
		{		
			if (KeyState[i] > 0) // ������Ă��Ȃ�
			{
				KeyState[i] = -1;		// ESC�L�[�����ꂽ�u��
			}
			else
			{
				KeyState[i] = 0;		// ESC�L�[������Ă�����
			}		
		}
		else KeyState[i]++;// ������Ă���
	}
}

// �v���O������ WinMain ����n�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);//��S��ʂɃZ�b�g
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);//��ʃT�C�Y�w��
	SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�
	SetMainWindowText("�����̉̕P - Reflection of Diva -");
	SetBackgroundColor(100, 100, 100);

	if (DxLib_Init() == -1) { return -1; }		// �c�w���C�u��������������  �G���[���N�����璼���ɏI��

	ImageInit(); //�摜�̓ǂݍ��� <- Image.cpp
	AudioInit(); //�����̓ǂݍ��� <- Audio.cpp
	PlayBGM(BGM[0]);

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