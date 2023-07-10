#include "GameData.h"
#include "Item.h"
#include "Player.h"
#include "Enemy.h"
#include "Player_Bullet.h"
#include "Enemy_Bullet.h"
#include <string>

string SpawnPattern[4][50] = //[stage][NowStageMode]
{
	{"W180",1,1,1,"W60",3,"W120",2,2,2,0,3,"W120",1,1,1,0,3,0,0,2,2,2,0,3,0,0,1,1,1,0,3,"W180","F"},//Stage1
	{0,0,0,1,0,2,0,1,0,2,0,1,0,0,0,-1},
	{0,0,0,1,0,2,0,1,0,2,0,1,0,0,0,-1},
	{0,0,0,1,0,2,0,1,0,2,0,1,0,0,0,-1},
};

int SelectDifficulty = 0;

float StageModeUpdateTime = 120;
int NowStageMode = 0;

void ViewStatus(void)
{
	//�g
	DrawBox(0, 0, 25, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawBox(0, 0, WINDOW_WIDTH, 25, GetColor(0, 0, 0), 1);
	DrawBox(0, WINDOW_HEIGHT-25, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawRotaGraph(750, 400, 1, 0, gameFrame_img, TRUE);

	//�e�L�X�g
	DrawRotaGraph(WINDOW_WIDTH - 160, 40, 0.8, 0, DifficultyText_img[SelectDifficulty], TRUE);
	DrawRotaGraph(WINDOW_WIDTH - 240, 107, 0.8, 0, score_img, TRUE);
	for (int i = 0; i < 6; i++) 
	{
		DrawRotaGraph(WINDOW_WIDTH - 160 + (25 * i), 110, 0.8, 0, NumberText_img[(Score / (int)pow(10, 5 - i)) % 10], TRUE);
	}

	DrawRotaGraph(WINDOW_WIDTH - 240, 190, 0.7, 0, LifeText_img, TRUE);
	for (int i = 0; i < Life; i++)
	{
		DrawRotaGraph(WINDOW_WIDTH - 170 + (32 * i), 190, 0.95, 0, Life_img, TRUE);
	}
	DrawRotaGraph(WINDOW_WIDTH - 240, 240, 0.7, 0, BombText_img, TRUE);
	for (int i = 0; i < Bomb; i++)
	{
		DrawRotaGraph(WINDOW_WIDTH - 170 + (32 * i), 240, 0.95, 0, Bomb_img, TRUE);
	}

	DrawRotaGraph(WINDOW_WIDTH - 220, 310, 0.8, 0, LevelText_img, TRUE);
	DrawRotaGraph(WINDOW_WIDTH - 120, 313, 0.8, 0, NumberText_img[Level], TRUE);

	DrawRotaGraph(WINDOW_WIDTH - 220, 350, 0.8, 0, PowerText_img, TRUE);
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(WINDOW_WIDTH - 230 + (25 * i), 390, 0.8, 0, NumberText_img[(Power / (int)pow(10, 2 - i)) % 10], TRUE);
		DrawRotaGraph(WINDOW_WIDTH - 110 + (25 * i), 390, 0.8, 0, NumberText_img[(NextPower[Level] / (int)pow(10, 2 - i)) % 10], TRUE);
	}
	DrawRotaGraph(WINDOW_WIDTH - 140, 390, 0.8, 0, slash_img, TRUE);

	DrawFormatString(WINDOW_WIDTH - 250, 400, GetColor(255, 255, 255), "sec %d ",NowStageMode);
}

int intu;
void ViewBackGround(void)//�w�i���[�v
{
	intu += 1;
	if (GameScene == Stage1_Scene)
	{
	DrawRotaGraph(300, 0 + intu, 1, 0, background_img[0], TRUE);//��O
	}
	else if (GameScene == Stage2_Scene)
	{
		DrawRotaGraph(300, 0 + intu, 1, 0, background_img[1], TRUE);//��
		DrawRotaGraph(300, 0 + intu, 1, 0, background_img[2], TRUE);//��O
	}
	else if (GameScene == Stage3_Scene)
	{
		DrawRotaGraph(300, 0 + intu, 1, 0, background_img[3], TRUE);//��O
	}
	else if (GameScene == Stage4_Scene)
	{
		DrawRotaGraph(300, 0 + intu, 1, 0, background_img[4], TRUE);//��O
	}
	
	if (intu >= 800) intu = 0;
}

void viewStageTitle(int i)
{
	if (StageTitleFadeTime < 500) StageTitleFadeTime++;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 450 - StageTitleFadeTime);
	DrawRotaGraph(300, 250 + (StageTitleFadeTime / 8), 1, 0, StageTitle_img[i], TRUE);//�摜�\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
}

void GameProcess(void)
{
	ViewBackGround(); //Fade�p���w�i ViewBackGround���}������Ă��Ȃ��V�[���ł̓t�F�[�h�͔��f����Ȃ�

	if (P_ShotCoolTime >= 0) P_ShotCoolTime--;
	if (DamagedCoolTime >= 0) DamagedCoolTime--;

	ItemAction();

	EnemyAction();

	EnemyBulletAction();//�G�̒e�̏���

	PlayerUseBomb();
	PlayerShotAction();
	PlayerBulletAction(); //���C���[�̒e�̏���

	LevelUp();
	ViewPlayer();//�v���C���[�\��

	ViewFadeWindow();
	ViewStatus();	
}

void StageUpdater(SceneManager Next)
{
	string spw = SpawnPattern[0][NowStageMode];

	if (StageModeUpdateTime >= 0) StageModeUpdateTime--;
	if (StageModeUpdateTime < 0)//120�t���[�����Ɏ��s
	{
		NowStageMode++;
		if (spw[0] == 'F')//�X�e�[�W�I��
		{
			ChangeSceneActive = true;
			nextScene = Next;
			NowStageMode = 0;
		}
		else if (spw[0] == 'W')//wait
		{
			float tmp;
			if (spw[2] == '\0') tmp = (float)spw[1];
			else if (spw[3] == '\0') tmp = (float)spw[1] * 10 + (float)spw[2];
			else if (spw[4] == '\0') tmp = (float)spw[1] * 100 + (float)spw[2] * 10 + (float)spw[3];

			StageModeUpdateTime = tmp;
		}
		else if (SpawnPattern[0][NowStageMode] == 1)
		{
			EnemySpawn(SpawnPattern[0][NowStageMode]);//�G�o��
			StageModeUpdateTime = 40;
		}
		else if (SpawnPattern[0][NowStageMode] == 2)
		{
			EnemySpawn(SpawnPattern[0][NowStageMode]);//�G�o��
			StageModeUpdateTime = 40;
		}
		else if (SpawnPattern[0][NowStageMode] == 3)
		{
			EnemySpawn(SpawnPattern[0][NowStageMode]);//�G�o��
			StageModeUpdateTime = 30;
		}
	}
}

void Update(void) //���t���[������
{
	ChangeScene();//fade��p�����V�[���`�F���W�@ChangeSceneActive -> true�Ŏ��s

	if (GameScene == Title_Scene)
	{
		PlayBGM(BGM[0]);
		DrawRotaGraph(450, 400, 1, 0, Title_img, TRUE);
		if (KeyState[KEY_INPUT_Z] == TRUE)
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
		if (KeyState[KEY_INPUT_Z] == TRUE)
		{
			ChangeSceneActive = true;
			nextScene = Stage1_Scene;//�V�[���J�ڗp�B���̂Q�̓Z�b�g
		}
		if (KeyState[KEY_INPUT_X] == TRUE)
		{
			ChangeSceneActive = true;
			nextScene = Title_Scene;//�V�[���J�ڗp�B���̂Q�̓Z�b�g
		}
	}
	if (GameScene == Stage1_Scene)
	{
		PlayBGM(BGM[1]);
		GameProcess();
		viewStageTitle(0);
		StageUpdater(Stage2_Scene);//�����Ɏ��̃X�e�[�W
	}
	if (GameScene == Stage2_Scene)
	{
		PlayBGM(BGM[3]);
		GameProcess();
		viewStageTitle(1);
		StageUpdater(Stage3_Scene);//�����Ɏ��̃X�e�[�W
	}
	if (GameScene == Stage3_Scene)
	{
		PlayBGM(BGM[5]);
		GameProcess();
		viewStageTitle(2);
		StageUpdater(Stage4_Scene);
	}
	if (GameScene == Stage4_Scene)
	{
		PlayBGM(BGM[7]);
		GameProcess();
		viewStageTitle(3);
		StageUpdater(Title_Scene);
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
		KeyUpdate();//�L�[���͏�Ԃ��X�V���� <- KeyManager.cpp
		Update();//���t���[������
		ScreenFlip();//����ʂ�\��ʂɃR�s�[
	}

	DxLib_End();			// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I�� 
}