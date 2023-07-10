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
	//枠
	DrawBox(0, 0, 25, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawBox(0, 0, WINDOW_WIDTH, 25, GetColor(0, 0, 0), 1);
	DrawBox(0, WINDOW_HEIGHT-25, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawRotaGraph(750, 400, 1, 0, gameFrame_img, TRUE);

	//テキスト
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
void ViewBackGround(void)//背景ループ
{
	intu += 1;
	if (GameScene == Stage1_Scene)
	{
	DrawRotaGraph(300, 0 + intu, 1, 0, background_img[0], TRUE);//手前
	}
	else if (GameScene == Stage2_Scene)
	{
		DrawRotaGraph(300, 0 + intu, 1, 0, background_img[1], TRUE);//奥
		DrawRotaGraph(300, 0 + intu, 1, 0, background_img[2], TRUE);//手前
	}
	else if (GameScene == Stage3_Scene)
	{
		DrawRotaGraph(300, 0 + intu, 1, 0, background_img[3], TRUE);//手前
	}
	else if (GameScene == Stage4_Scene)
	{
		DrawRotaGraph(300, 0 + intu, 1, 0, background_img[4], TRUE);//手前
	}
	
	if (intu >= 800) intu = 0;
}

void viewStageTitle(int i)
{
	if (StageTitleFadeTime < 500) StageTitleFadeTime++;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 450 - StageTitleFadeTime);
	DrawRotaGraph(300, 250 + (StageTitleFadeTime / 8), 1, 0, StageTitle_img[i], TRUE);//画像表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
}

void GameProcess(void)
{
	ViewBackGround(); //Fade用黒背景 ViewBackGroundが挿入されていないシーンではフェードは反映されない

	if (P_ShotCoolTime >= 0) P_ShotCoolTime--;
	if (DamagedCoolTime >= 0) DamagedCoolTime--;

	ItemAction();

	EnemyAction();

	EnemyBulletAction();//敵の弾の処理

	PlayerUseBomb();
	PlayerShotAction();
	PlayerBulletAction(); //レイヤーの弾の処理

	LevelUp();
	ViewPlayer();//プレイヤー表示

	ViewFadeWindow();
	ViewStatus();	
}

void StageUpdater(SceneManager Next)
{
	string spw = SpawnPattern[0][NowStageMode];

	if (StageModeUpdateTime >= 0) StageModeUpdateTime--;
	if (StageModeUpdateTime < 0)//120フレーム毎に実行
	{
		NowStageMode++;
		if (spw[0] == 'F')//ステージ終了
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
			EnemySpawn(SpawnPattern[0][NowStageMode]);//敵登場
			StageModeUpdateTime = 40;
		}
		else if (SpawnPattern[0][NowStageMode] == 2)
		{
			EnemySpawn(SpawnPattern[0][NowStageMode]);//敵登場
			StageModeUpdateTime = 40;
		}
		else if (SpawnPattern[0][NowStageMode] == 3)
		{
			EnemySpawn(SpawnPattern[0][NowStageMode]);//敵登場
			StageModeUpdateTime = 30;
		}
	}
}

void Update(void) //毎フレーム処理
{
	ChangeScene();//fadeを用いたシーンチェンジ　ChangeSceneActive -> trueで実行

	if (GameScene == Title_Scene)
	{
		PlayBGM(BGM[0]);
		DrawRotaGraph(450, 400, 1, 0, Title_img, TRUE);
		if (KeyState[KEY_INPUT_Z] == TRUE)
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
		if (KeyState[KEY_INPUT_Z] == TRUE)
		{
			ChangeSceneActive = true;
			nextScene = Stage1_Scene;//シーン遷移用。この２つはセット
		}
		if (KeyState[KEY_INPUT_X] == TRUE)
		{
			ChangeSceneActive = true;
			nextScene = Title_Scene;//シーン遷移用。この２つはセット
		}
	}
	if (GameScene == Stage1_Scene)
	{
		PlayBGM(BGM[1]);
		GameProcess();
		viewStageTitle(0);
		StageUpdater(Stage2_Scene);//引数に次のステージ
	}
	if (GameScene == Stage2_Scene)
	{
		PlayBGM(BGM[3]);
		GameProcess();
		viewStageTitle(1);
		StageUpdater(Stage3_Scene);//引数に次のステージ
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
		KeyUpdate();//キー入力状態を更新する <- KeyManager.cpp
		Update();//毎フレーム処理
		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}