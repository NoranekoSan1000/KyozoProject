#include "GameData.h"
#include "Player.h"
#include "Enemy.h"
#include "Player_Bullet.h"

SceneManager GameScene = Title_Scene;
double FrameCount = 0;

//�L�[�擾�p�̔z��
char buf[256] = { 0 };
int KeyState[256] = { 0 };

void PlayerShotAction()
{
	if (KeyState[KEY_INPUT_Z] > 0)
	{
		if (P_ShotCoolTime > 0) return;
		PlayerShot(px, py - 8, 0);//�ˌ�
		PlayerShot(px, py - 4, 1);//�ˌ�
		PlayerShot(px, py - 4, 2);//�ˌ�
		PlayerShot(px + 8, py + 8, 5);//�ˌ�
		PlayerShot(px - 8, py + 8, 6);//�ˌ�
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
	DrawRotaGraph(300, 0 + intu, 1, 0, background_img, TRUE);
	if (intu >= 800) intu = 0;
}

bool FadeIn = false;
bool FadeOut = false;
int fadeALPHA = 256;
void ViewFadeWindow(void)
{
	if (FadeIn) {
		if (FadeOut) FadeOut = false;
		if (fadeALPHA <= 0)
		{
			fadeALPHA = 0;
			FadeIn = false;
		}
		else fadeALPHA -= 2;
	}
	if (FadeOut) {
		if (FadeIn) FadeIn = false;
		if (fadeALPHA >= 256)
		{
			fadeALPHA = 256;
			FadeOut = false;
		}
		else fadeALPHA += 2;
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeALPHA);
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
}

void GameProcess(void)
{
	ViewBackGround();

	if (P_ShotCoolTime >= 0) P_ShotCoolTime--;
	if (DamagedCoolTime >= 0) DamagedCoolTime--;

	if (KeyState[KEY_INPUT_A] == TRUE) EnemySpawn();
	EnemyAction();

	PlayerShotAction();
	PlayerBulletAction();

	PlayerMove(KeyState);//�v���C���[�̈ړ�
	ViewPlayer();//�v���C���[�\��

	ViewFadeWindow();
	ViewStatus();	
}

bool ChangeSceneActive = false;
SceneManager nextScene;
void ChangeScene(void)
{
	if (!ChangeSceneActive) return;
	FadeOut = true;
	if (fadeALPHA == 256)
	{
		GameScene = nextScene;
		FadeIn = true;
		ChangeSceneActive = false;
	}
}

void Update(void) //���t���[������
{
	ChangeScene();

	if (GameScene == Title_Scene)
	{
		PlayBGM(BGM[0]);
		DrawRotaGraph(450, 400, 1, 0, Title_img, TRUE);
		if (KeyState[KEY_INPUT_P] == TRUE)
		{		
			ChangeSceneActive = true;
			nextScene = Stage1_Scene;
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