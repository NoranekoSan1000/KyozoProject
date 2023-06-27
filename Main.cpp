#include "GameData.h"
#include "Enemy_Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Player_Bullet.h"

double FrameCount = 0;
int SelectDifficulty = 0;

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
	DrawRotaGraph(WINDOW_WIDTH - 160, 40, 0.8, 0, DifficultyText_img[SelectDifficulty], TRUE);
	DrawRotaGraph(WINDOW_WIDTH - 240, 77, 0.8, 0, score_img, TRUE);
	for (int i = 0; i < 6; i++) 
	{
		DrawRotaGraph(WINDOW_WIDTH - 160 + (25 * i), 80, 0.8, 0, NumberText_img[(Score / (int)pow(10, 5 - i)) % 10], TRUE);
	}

	
	DrawFormatString(WINDOW_WIDTH - 250, 110, GetColor(255, 255, 255), "Life : %d", Life);
	DrawFormatString(WINDOW_WIDTH - 250, 150, GetColor(255, 255, 255), "ShotLevel : %d", Level);
	DrawFormatString(WINDOW_WIDTH - 250, 180, GetColor(255, 255, 255), "Power : %d", Power);
	DrawFormatString(WINDOW_WIDTH - 250, 300, GetColor(255, 255, 255), "sec %.2lf", FrameCount++ / 60);
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
		if (KeyState[KEY_INPUT_UP] == TRUE && SelectDifficulty > 0) SelectDifficulty--;
		else if (KeyState[KEY_INPUT_UP] == TRUE && SelectDifficulty == 0) SelectDifficulty = 3;
		if (KeyState[KEY_INPUT_DOWN] == TRUE && SelectDifficulty < 3) SelectDifficulty++;
		else if (KeyState[KEY_INPUT_DOWN] == TRUE && SelectDifficulty == 3) SelectDifficulty = 0;
		
		
		for (int i = 0; i < 4; i++)
		{
			if(SelectDifficulty == i) DrawRotaGraph(450, 140 + (i * 170), 1, 0, DifficultyLv_img[i], TRUE);//�摜�\��
			else 
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
				DrawRotaGraph(450, 140 + (i * 170), 1, 0, DifficultyLv_img[i], TRUE);//�摜�\��
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
			}
			
		}
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