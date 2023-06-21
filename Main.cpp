#include <stdio.h>
#include <DxLib.h>
#include <math.h>
#include "Player.h"
#include "Image.h"
#include "Audio.h"
#include "Enemy.h"
#include "Player_Bullet.h"
#define PI 3.141592654
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

double FrameCount = 0;

//キー取得用の配列
char buf[256] = { 0 };
int KeyState[256] = { 0 };

void ViewStatus(void)
{
	//枠
	DrawBox(0, 0, 100, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawRotaGraph(700, 300, 0.8, 0, gameFrame_img, TRUE);

	//テキスト
	DrawFormatString(WINDOW_WIDTH - 200, 30, GetColor(255, 255, 255), "Score : %d", Score);
	DrawFormatString(WINDOW_WIDTH - 200, 60, GetColor(255, 255, 255), "Life : %d", Life);
	DrawFormatString(WINDOW_WIDTH - 200, 120, GetColor(255, 255, 255), "sec %.2lf", FrameCount++ / 60);
}

void PlayerBulletAction(void)
{
	for (int i = 0; i < P_Bullet_Amount; i++)
	{
		if (P_Bullet_exist[i] == true) DrawCircle(P_Bullet_PosX[i], P_Bullet_PosY[i], P_Bullet_HitBoxSize[i], GetColor(0, 100, 100), 1);
		else continue;

		P_Bullet_PosY[i] -= 12;

		//画面外で消滅
		if (P_Bullet_PosY[i] < -20)
		{
			PlayerBulletDestroy(i);
			continue;
		}

		//敵に弾が当たる
		for (int j = 0; j < Enemy_Amount; j++)
		{
			//敵との座標チェック
			float dis = sqrt(pow((double)Enemy_X[j] - P_Bullet_PosX[i], 2) + pow((double)Enemy_Y[j] - P_Bullet_PosY[i], 2));
			if (dis <= Enemy_HitBoxSize[j] + P_Bullet_HitBoxSize[i])//被弾判定
			{
				EnemyDestroy(j);
				PlayerBulletDestroy(i);
				Score += 100;
				break;
			}
		}
	}
}

void EnemyAction(void)
{
	for (int i = 0; i < Enemy_Amount; i++)
	{
		//敵キャラ画像表示
		if (Enemy_exist[i] == true) DrawCircle(Enemy_X[i], Enemy_Y[i], Enemy_HitBoxSize[i], GetColor(255, 0, 0), 1);
		else continue;

		EnemyMove(i);

		//画面外で消滅
		if (Enemy_Y[i] > WINDOW_HEIGHT + 30)
		{
			EnemyDestroy(i);
			continue;
		}

		//敵との座標チェック
		float dis = sqrt(pow((double)Enemy_X[i] - px, 2) + pow((double)Enemy_Y[i] - py, 2));
		if (dis <= Enemy_HitBoxSize[i] + Player_HitBoxSize)
		{
			//被弾判定
			px = InitialPosX;
			py = InitialPosY;
			Life -= 1;
		}
	}
}

void EnemySpawn(void) 
{
	if (KeyState[KEY_INPUT_A] == TRUE) //単発入力
	{
		for (int i = 0; i < Enemy_Amount; i++)
		{
			if (Enemy_exist[i] == false)
			{
				EnemyGenerate(i, px, py - 600, 16, 3, 0);
				DrawFormatString(WINDOW_WIDTH - 100, 90, GetColor(255, 255, 255), "%d\n", i);
				break;
			}
		}
	}
}

void Update(void) //毎フレーム処理
{
	ViewStatus();

	if (P_ShotCoolTime >= 0) P_ShotCoolTime--;
	if (KeyState[KEY_INPUT_Z] > 0)
	{
		PlayerShotGenerate(px, py);//射撃
	}

	PlayerBulletAction();
	EnemyAction();
	EnemySpawn();

	PlayerMove(KeyState);//プレイヤーの移動
	DrawRotaGraph(px, py, 1.0, 0, player_img, TRUE); //画像の描画
	DrawCircle(px, py, Player_HitBoxSize, GetColor(255, 255, 80)); // プレイヤーの当たり判定

}

//キー入力状態を更新する関数
void KeyUpdate(void)
{
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++)
	{
		if (buf[i] == 1) KeyState[i]++;
		else KeyState[i] = 0;
	}
}

// プログラムは WinMain から始まる
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);//画面サイズ指定
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	SetMainWindowText("鏡像の歌姫 - Reflection of Diva -");
	SetBackgroundColor(0, 200, 200);

	if (DxLib_Init() == -1) { return -1; }		// ＤＸライブラリ初期化処理  エラーが起きたら直ちに終了

	ImageInit(); //画像の読み込み <- Image.cpp
	AudioInit(); //音声の読み込み <- Audio.cpp
	PlayBGM(ResonanceAtTwilight_audio);

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