#include "GameData.h"
#include "Item.h"
#include "Player.h"
#include "Player_Bullet.h"
#include "Enemy_Bullet.h"
#include "Talk.h"
#include "Enemy.h"

float StageModeUpdateTime = 120;
int NowStageMode = 0;

bool BossBGM = false;

EnemyController enemyController;
void ViewStatus(void)
{
	//枠
	DrawBox(0, 0, 25, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawBox(0, 0, WINDOW_WIDTH, 25, GetColor(0, 0, 0), 1);
	DrawBox(0, WINDOW_HEIGHT - 25, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
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

	DrawFormatString(WINDOW_WIDTH - 250, 400, GetColor(255, 255, 255), "sec %d ", NowStageMode);
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



void viewBossHpBar(void)
{
	DrawBox(25, 20, 600, 36, GetColor(0, 0, 0), 1);
	DrawBox(25, 16, ((555 * enemyController.GetBossCurrentHP()) / enemyController.GetBossMaxHP()) + 25, 32, GetColor(0, 255, 0), 1);//Enemy.cpp

	int Font;
	Font = CreateFontToHandle("メイリオ", 20, 9, DX_FONTTYPE_ANTIALIASING_EDGE);
	DrawFormatStringToHandle(590, 14, GetColor(0, 255, 0), Font, "%d", BossStock);
	DeleteFontToHandle(Font);
}

void GameProcess(void)
{
	if (KeyState[KEY_INPUT_P] == TRUE) NowStageMode++;//デバッグ用

	ViewBackGround(); //Fade用黒背景 ViewBackGroundが挿入されていないシーンではフェードは反映されない

	ItemMovement();

	enemyController.EnemyAction();

	EnemyBulletAction();//敵の弾の処理

	PlayerMovement();

	PlayerBulletAction(); //レイヤーの弾の処理

	ViewFadeWindow();

	ViewStatus();

	if (BossActive) viewBossHpBar();
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
void spawn(int enemy, int amt, int interval, MoveList move, int posX, int posY)
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

	if (PlayerTalk == 0) SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
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
