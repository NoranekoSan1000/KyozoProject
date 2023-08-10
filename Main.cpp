#include "GameData.h"
#include "Item.h"
#include "Player.h"
#include "Player_Bullet.h"
#include "Enemy_Bullet.h"
#include "Talk.h"
#include "Enemy.h"

int SelectTitleAction = 0;
int SelectDifficulty = 0;
int SelectMusic = 0;
int PlayingMusic = 0;
int SelectSetting = 0;

float StageModeUpdateTime = 120;
int NowStageMode = 0;

bool BossBGM = false;

EnemyController enemyController;
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
		DrawRotaGraph(300, 0 + intu, 1, 0, background_img[4], TRUE);//手前
	}
	else if (GameScene == Stage4_Scene)
	{
		DrawRotaGraph(300, 0 + intu, 1, 0, background_img[5], TRUE);//手前
	}
	else if (GameScene == Stage4_Scene)
	{
		DrawRotaGraph(300, 0, 1, 0, background_img[6], TRUE);//手前
	}
	
	if (intu >= 800) intu = 0;
}

void viewStageTitle(int i)
{
	if (StageTitleFadeTime < 500) StageTitleFadeTime++;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 450 - StageTitleFadeTime);
	DrawRotaGraph(300, 250 + (StageTitleFadeTime / 8), 1, 0, StageTitle_img[i], TRUE);//画像表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void viewBossHpBar(void)
{	
	DrawBox(25, 20, 600, 36, GetColor(0, 0, 0), 1);
	DrawBox(25, 16, ((555 * enemyController.GetBossCurrentHP()) / enemyController.GetBossMaxHP())+25, 32, GetColor(0, 255, 0), 1);//Enemy.cpp

	int Font;
	Font = CreateFontToHandle("メイリオ", 20, 9, DX_FONTTYPE_ANTIALIASING_EDGE);
	DrawFormatStringToHandle(590, 14, GetColor(0, 255, 0), Font, "%d", BossStock);
	DeleteFontToHandle(Font);
}

void GameProcess(void)
{
	ViewBackGround(); //Fade用黒背景 ViewBackGroundが挿入されていないシーンではフェードは反映されない

	if (P_ShotCoolTime >= 0) P_ShotCoolTime--;
	if (DamagedCoolTime >= 0) DamagedCoolTime--;

	ItemMovement();

	enemyController.EnemyAction();

	EnemyBulletAction();//敵の弾の処理

	PlayerUseBomb();
	PlayerShotAction();
	PlayerBulletAction(); //レイヤーの弾の処理

	LevelUp();
	ViewPlayer();//プレイヤー表示

	ViewFadeWindow();
	ViewStatus();	

	if(BossActive) viewBossHpBar();
}

int amount = 0;
void wait(int time)
{
	StageModeUpdateTime = time;
	NowStageMode++;
}
void bosswait()
{
	if (BossActive) StageModeUpdateTime = 0;
	else NowStageMode++;
}
void end(SceneManager Next)
{
	ChangeSceneActive = true;
	nextScene = Next;
	NowStageMode = -1;
}
void spawn(int enemy,int amt, int interval,MoveList move,int posX, int posY)
{
	if (amount == 0) amount = amt;
	else
	{
		enemyController.EnemySpawn(enemy, move, posX, posY);
		amount--;
		if (amount == 0) NowStageMode++;
		else StageModeUpdateTime = interval;
	}
}
void talk()
{
	TalkActive = true;

	if(PlayerTalk == 0) SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	else if (PlayerTalk == 1) SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	else if (PlayerTalk == 2)SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawRotaGraph(515, 575, 1, 0, CharaTalk_img[0], TRUE);//画像表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	if (BossTalk == 0) SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	else if (BossTalk == 1) SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	else if (BossTalk == 2)SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	if (GameScene == Stage1_Scene) DrawRotaGraph(115, 575, 1, 0, CharaTalk_img[1], TRUE);//画像表示
	else if (GameScene == Stage2_Scene) DrawRotaGraph(115, 575, 1, 0, CharaTalk_img[2], TRUE);//画像表示
	else if (GameScene == Stage3_Scene) DrawRotaGraph(115, 575, 1, 0, CharaTalk_img[3], TRUE);//画像表示
	else if (GameScene == Stage4_Scene) DrawRotaGraph(115, 575, 1, 0, CharaTalk_img[4], TRUE);//画像表示
	else if (GameScene == Stage5_Scene) DrawRotaGraph(115, 575, 1, 0, CharaTalk_img[5], TRUE);//画像表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DrawRotaGraph(315, 675, 1, 0, talkwindow_img, TRUE);//画像表示
	TalkProcess();

	if (KeyState[KEY_INPUT_Z] == TRUE)
	{
		TalkStep++;
	}

	if (!TalkActive)
	{
		BossBGM = true;
		NowStageMode++; //会話終了を検知
		TalkStep = 0;
		TalkScene++;
	}
}

void StageUpdater(SceneManager Next)
{
	if (StageModeUpdateTime >= 0) StageModeUpdateTime--;
	if (StageModeUpdateTime < 0)//120フレーム毎に実行
	{	
		switch (NowStageMode)
		{
			//spawn(敵タイプ,出現数,出現間隔,移動パターン,X座標,Y座標)
			case -1: wait(180); break;
			case  0: wait(180); break;
			case  1: spawn(0, 3, 40, MOVE_A, 175, 0); break;
			case  2: wait(180); break;
			case  3: spawn(0, 3, 40, MOVE_A, 450, 0); break;
			case  4: wait(60); break;
			case  5: spawn(1, 1, 40, MOVE_B, 325, 0); break;
			case  6: wait(180); break;
			case  7: spawn(0, 3, 40, MOVE_A, 175, 0); break;
			case  8: wait(180); break;
			case  9: spawn(0, 3, 40, MOVE_A, 450, 0); break;
			case 10: wait(60); break;
			case 11: spawn(1, 1, 40, MOVE_B, 325, 0); break;
			case 12: wait(180); break;
			case 13: spawn(2, 1, 40, MOVE_BOSS, 325, 0); break;//中ボス
			case 14: bosswait(); break;//中ボス死亡時、次へ
			case 15: wait(180); break;
			case 16: spawn(0, 3, 40, MOVE_A, 175, 0); break;
			case 17: wait(180); break;
			case 18: spawn(0, 3, 40, MOVE_A, 450, 0); break;
			case 19: wait(60); break;
			case 20: spawn(1, 1, 40, MOVE_B, 325, 0); break;
			case 21: wait(180); break;
			case 22: spawn(0, 3, 40, MOVE_A, 175, 0); break;
			case 23: wait(180); break;
			case 24: spawn(0, 3, 40, MOVE_A, 450, 0); break;
			case 25: wait(60); break;
			case 26: spawn(1, 1, 40, MOVE_B, 325, 0); break;
			case 27: wait(120); break;
			case 28: talk(); break;
			case 29: spawn(2, 1, 40, MOVE_BOSS, 325, 0); break;//ボス
			case 30: bosswait(); break;//ボス死亡時、次へ
			case 31: end(Next); break;
			default: break;
		};
	}
}

void Update(void) //毎フレーム処理
{
	if (KeyState[KEY_INPUT_P] == TRUE)//デバッグ用
	{
		NowStageMode++;
	}

	ChangeScene();//fadeを用いたシーンチェンジ　ChangeSceneActive -> trueで実行

	if (GameScene == Title_Scene)
	{
		PlayBGM(BGM[0]);
		DrawRotaGraph(450, 400, 1, 0, Title_img, TRUE);

		if (KeyState[KEY_INPUT_UP] == TRUE && SelectTitleAction > 0) SelectTitleAction--;
		else if (KeyState[KEY_INPUT_UP] == TRUE && SelectTitleAction == 0) SelectTitleAction = 3;
		if (KeyState[KEY_INPUT_DOWN] == TRUE && SelectTitleAction < 3) SelectTitleAction++;
		else if (KeyState[KEY_INPUT_DOWN] == TRUE && SelectTitleAction == 3) SelectTitleAction = 0;

		int y[4] = {500 ,570 ,650 ,710};
		DrawRotaGraph(560 + (10 * SelectTitleAction), y[SelectTitleAction], 1, 0, select_icon, TRUE);//画像表示
		DrawRotaGraph(860, y[0], 1, 0, gamestart_text, TRUE);//画像表示
		DrawRotaGraph(870, y[1], 1, 0, musicroom_text, TRUE);//画像表示
		DrawRotaGraph(880, y[2], 1, 0, setting_text, TRUE);//画像表示
		DrawRotaGraph(890, y[3], 1, 0, exit_text, TRUE);//画像表示

		if (KeyState[KEY_INPUT_Z] == TRUE)
		{		
			ChangeSceneActive = true;
			if (SelectTitleAction == 0) nextScene = DifficultyLvSelect_Scene;//シーン遷移用。この２つはセット
			else if (SelectTitleAction == 1) nextScene = MusicRoom_Scene;
			else if (SelectTitleAction == 2) nextScene = Setting_Scene;
			else if (SelectTitleAction == 3) DxLib_End();
		}
	}
	if (GameScene == MusicRoom_Scene)
	{
		DrawRotaGraph(450, 400, 1, 0, MusicRoom_img, TRUE);

		int Font;
		Font = CreateFontToHandle("メイリオ", 20, 9, DX_FONTTYPE_ANTIALIASING_EDGE);
		DrawStringToHandle(60, WINDOW_HEIGHT - 30, "Xキーを押して戻る", GetColor(255, 255, 255), Font);

		int i = 70,j = 30;

		//カーソル移動
		if (KeyState[KEY_INPUT_UP] == TRUE && SelectMusic > 0) SelectMusic--;
		else if (KeyState[KEY_INPUT_UP] == TRUE && SelectMusic == 0) SelectMusic = 0;
		if (KeyState[KEY_INPUT_DOWN] == TRUE && SelectMusic < 11) SelectMusic++;
		else if (KeyState[KEY_INPUT_DOWN] == TRUE && SelectMusic == 11) SelectMusic = 11;
		if (KeyState[KEY_INPUT_LEFT] == TRUE && SelectMusic >= 6) SelectMusic -= 6;
		if (KeyState[KEY_INPUT_RIGHT] == TRUE && SelectMusic < 6) SelectMusic += 6;

		//再生
		if (KeyState[KEY_INPUT_Z] == TRUE)
		{
			PlayBGM(BGM[SelectMusic]);
			PlayingMusic = SelectMusic;
		}

		int x[2] = { i + j -60 , WINDOW_WIDTH / 2 + j - 60};

		int sel = 0,ply = 0;
		if (SelectMusic < 6) sel = 0;
		else sel = 1;
		if (PlayingMusic < 6) ply = 0;
		else ply = 1;
		DrawRotaGraph(x[sel] +25, (SelectMusic % 6 + 2) * i + 10, 1, 0, select_icon, TRUE);//画像表示

		DrawBox(x[ply]+55, (PlayingMusic % 6 + 2) * i + 10 -20 , x[ply]+350, (PlayingMusic % 6 + 2) * i + 10 + 20,GetColor(0, 50, 100),1);

		DrawStringToHandle(i + j, i * 2, "MirrorImageDiva", GetColor(255, 255, 255), Font);
		DrawStringToHandle(i + j, i * 3, "Departure", GetColor(255, 255, 255), Font);
		DrawStringToHandle(i + j, i * 4, "Explosion", GetColor(255, 255, 255), Font);
		DrawStringToHandle(i + j, i * 5, "WitchPromenade", GetColor(255, 255, 255), Font);
		DrawStringToHandle(i + j, i * 6, "Jade-coloredWitch", GetColor(255, 255, 255), Font);
		DrawStringToHandle(i + j, i * 7, "KnightRoad", GetColor(255, 255, 255), Font);
		DrawStringToHandle(WINDOW_WIDTH / 2 + j, i * 2, "Ruthlessblade", GetColor(255, 255, 255), Font);
		DrawStringToHandle(WINDOW_WIDTH / 2 + j, i * 3, "ResonanceAtTwilight", GetColor(255, 255, 255), Font);
		DrawStringToHandle(WINDOW_WIDTH / 2 + j, i * 4, "null", GetColor(255, 255, 255), Font);
		DrawStringToHandle(WINDOW_WIDTH / 2 + j, i * 5, "HermitOfTheAbyss", GetColor(255, 255, 255), Font);
		DrawStringToHandle(WINDOW_WIDTH / 2 + j, i * 6, "null", GetColor(255, 255, 255), Font);
		DrawStringToHandle(WINDOW_WIDTH / 2 + j, i * 7, "EndofTheStory", GetColor(255, 255, 255), Font);
		DeleteFontToHandle(Font);

		if (KeyState[KEY_INPUT_X] == TRUE)
		{
			PlayingMusic = 0;
			SelectMusic = 0;
			ChangeSceneActive = true;
			nextScene = Title_Scene;//シーン遷移用。この２つはセット
		}
	}
	if (GameScene == Setting_Scene)
	{
		DrawRotaGraph(450, 400, 1, 0, Setting_img, TRUE);

		int Font;
		Font = CreateFontToHandle("メイリオ", 20, 9, DX_FONTTYPE_ANTIALIASING_EDGE);
		DrawStringToHandle(60, WINDOW_HEIGHT - 30, "Xキーを押して戻る", GetColor(255, 255, 255),Font);
		DeleteFontToHandle(Font);

		if (KeyState[KEY_INPUT_UP] == TRUE && SelectSetting > 0) SelectSetting--;
		else if (KeyState[KEY_INPUT_UP] == TRUE && SelectSetting == 0) SelectSetting = 1;
		if (KeyState[KEY_INPUT_DOWN] == TRUE && SelectSetting < 1) SelectSetting++;
		else if (KeyState[KEY_INPUT_DOWN] == TRUE && SelectSetting == 1) SelectSetting = 0;

		int y[2] = { 340,410 };

		DrawRotaGraph(50, y[SelectSetting], 1, 0, select_icon, TRUE);//画像表示
		if (SelectSetting == 0)
		{
			if (KeyState[KEY_INPUT_LEFT] == TRUE && BGMCurrentVolume > 0) BGMCurrentVolume--;
			if (KeyState[KEY_INPUT_RIGHT] == TRUE && BGMCurrentVolume < 9) BGMCurrentVolume++;
			volumeSetBGM();//音量再設定
		}
		else if (SelectSetting == 1)
		{
			if (KeyState[KEY_INPUT_LEFT] == TRUE && SECurrentVolume > 0) SECurrentVolume--;
			if (KeyState[KEY_INPUT_RIGHT] == TRUE && SECurrentVolume < 9) SECurrentVolume++;
		}

		for (int i = 0; i < 10; i++)
		{	
			int alpha = 80;
			if (BGMCurrentVolume == i) alpha = 255;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawRotaGraph(60 * (i + 1) + 150, 340, 0.8, 0, NumberText_img[i], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}

		for (int i = 0; i < 10; i++)
		{
			int alpha = 80;
			if (SECurrentVolume == i) alpha = 255;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawRotaGraph(60 * (i + 1) + 150, 410, 0.8, 0, NumberText_img[i], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		
		if (KeyState[KEY_INPUT_X] == TRUE)
		{
			ChangeSceneActive = true;
			nextScene = Title_Scene;//シーン遷移用。この２つはセット
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
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
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