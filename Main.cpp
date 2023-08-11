#include "GameData.h"
#include "Main.h"

int SelectDifficulty = 0;

void viewStageTitle(int i)
{
	if (StageTitleFadeTime < 500) StageTitleFadeTime++;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 450 - StageTitleFadeTime);
	DrawRotaGraph(300, 250 + (StageTitleFadeTime / 8), 1, 0, StageTitle_img[i], TRUE);//画像表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Update(void) //毎フレーム処理
{
	ChangeScene();//fadeを用いたシーンチェンジ　ChangeSceneActive -> trueで実行

	if (GameScene == Title_Scene) Title();
	if (GameScene == MusicRoom_Scene) MusicRoom();
	if (GameScene == Setting_Scene) Setting();
	if (GameScene == DifficultyLvSelect_Scene) DifficultyLvSelect();
	if (GameScene == Stage1_Scene)
	{
		PlayBGM(BGM[1 + BossBGM]);
		GameProcess();
		viewStageTitle(0);
		StageUpdater(Stage2_Scene);//引数に次のステージ
	}
	if (GameScene == Stage2_Scene)
	{
		PlayBGM(BGM[3 + BossBGM]);
		GameProcess();
		viewStageTitle(1);
		StageUpdater(Stage3_Scene);//引数に次のステージ
	}
	if (GameScene == Stage3_Scene)
	{
		PlayBGM(BGM[5 + BossBGM]);
		GameProcess();
		viewStageTitle(2);
		StageUpdater(Stage4_Scene);
	}
	if (GameScene == Stage4_Scene)
	{
		PlayBGM(BGM[7 + BossBGM]);
		GameProcess();
		viewStageTitle(3);
		StageUpdater(Stage5_Scene);
	}
	if (GameScene == Stage5_Scene)
	{
		PlayBGM(BGM[9 + BossBGM]);
		GameProcess();
		viewStageTitle(4);
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