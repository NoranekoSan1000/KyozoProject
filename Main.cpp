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
			PlayerShot(px, py - 8, 0);//射撃
		}
		if (Level >= 1 && Level < 3)//狙いLv1
		{
			PlayerShot(px, py + 20, 7);//射撃
		}
		if (Level >= 2)
		{
			PlayerShot(px, py - 4, 1);//射撃
			PlayerShot(px, py - 4, 2);//射撃
		}
		if (Level >= 3)//狙いLv2
		{
			PlayerShot(px + 8, py + 8, 5);//射撃
			PlayerShot(px - 8, py + 8, 6);//射撃
		}
		P_ShotCoolTime = 8;//フレームで設定
	}
}

void ViewStatus(void)
{
	//枠
	DrawBox(0, 0, 25, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawBox(0, 0, WINDOW_WIDTH, 25, GetColor(0, 0, 0), 1);
	DrawBox(0, WINDOW_HEIGHT-25, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawRotaGraph(750, 400, 1, 0, gameFrame_img, TRUE);

	//テキスト
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
void ViewBackGround(void)//背景ループ
{
	intu += 2;
	DrawRotaGraph(300, 0 + intu, 1, 0, backgroundBack_img, TRUE);
	DrawRotaGraph(300, 0 + intu, 1, 0, backgroundFront_img, TRUE);
	if (intu >= 800) intu = 0;
}

void GameProcess(void)
{
	ViewBackGround(); //Fade用黒背景

	if (P_ShotCoolTime >= 0) P_ShotCoolTime--;
	if (DamagedCoolTime >= 0) DamagedCoolTime--;

	if (KeyState[KEY_INPUT_A] == TRUE) EnemySpawn();
	EnemyAction();

	EnemyBulletAction();//敵の弾の処理

	PlayerShotAction();
	PlayerBulletAction(); //レイヤーの弾の処理

	ViewPlayer();//プレイヤー表示

	ViewFadeWindow();
	ViewStatus();	
}

void Update(void) //毎フレーム処理
{
	ChangeScene();//fadeを用いたシーンチェンジ　ChangeSceneActive -> trueで実行

	if (GameScene == Title_Scene)
	{
		PlayBGM(BGM[0]);
		DrawRotaGraph(450, 400, 1, 0, Title_img, TRUE);
		if (KeyState[KEY_INPUT_S] == TRUE)
		{		
			ChangeSceneActive = true;
			nextScene = DifficultyLvSelect_Scene;//シーン遷移用。この２つはセット
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
			if(SelectDifficulty == i) DrawRotaGraph(450, 140 + (i * 170), 1, 0, DifficultyLv_img[i], TRUE);//画像表示
			else 
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
				DrawRotaGraph(450, 140 + (i * 170), 1, 0, DifficultyLv_img[i], TRUE);//画像表示
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
			}
			
		}
		if (KeyState[KEY_INPUT_P] == TRUE)
		{
			ChangeSceneActive = true;
			nextScene = Stage1_Scene;//シーン遷移用。この２つはセット
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

// プログラムは WinMain から始まる
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);//画面サイズ指定
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	SetMainWindowText("鏡像の歌姫 - Reflection of Diva -");
	SetBackgroundColor(100, 100, 100);

	if (DxLib_Init() == -1) { return -1; }		// ＤＸライブラリ初期化処理  エラーが起きたら直ちに終了

	ImageInit(); //画像の読み込み <- Image.cpp
	AudioInit(); //音声の読み込み <- Audio.cpp
	PlayBGM(BGM[0]);

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す
		SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に
		KeyUpdate();//キー入力状態を更新する（自作関数）
		Update();//毎フレーム処理
		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}