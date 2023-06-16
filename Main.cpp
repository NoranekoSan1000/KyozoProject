#include <stdio.h>
#include <DxLib.h>
#include <math.h>
#include "PlayerAction.h"
#include "Image.h"
#include "Audio.h"
#define PI 3.141592654
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//マウス座標
int mouseX = 0;
int mouseY = 0;

//キー取得用の配列
char buf[256] = { 0 };
int KeyState[256] = { 0 };

//プレイヤー
const int InitialPosX = 350;
const int InitialPosY = 550;
const int Player_HitBoxSize = 4;
int px = InitialPosX;
int py = InitialPosY;

//敵
class Enemy{
public:
	int enX;
	int enY;
	int enHitBoxSize;
	Enemy(int x, int y, int size)
	{
		enX = x;
		enY = y;
		enHitBoxSize = size;
	};
};

Enemy enemy[3]{ {120,80,20},{220,20,20},{320,220,20} };

int FrameCount = 0;

int Life = 10;

void Update(void) //毎フレーム処理
{
	DrawRotaGraph(10, 10, 1.0, 0, shot_img, TRUE); //画像の描画

	DrawBox(0, 0, 100, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawRotaGraph(700, 300, 0.8, 0, status_img, TRUE); //画像の描画

	DrawFormatString(WINDOW_WIDTH - 100, 120, GetColor(255, 255, 255), "sec %d", FrameCount++ / 60);

	if (KeyState[KEY_INPUT_X] == TRUE) //単発入力
	{
		PlayBGM(ResonanceAtTwilight_audio);
	}

	for (int i = 0; i < 3; i++) 
	{
		DrawCircle(enemy[i].enX, enemy[i].enY, enemy[i].enHitBoxSize, GetColor(255, 0, 0), 1);

		//敵との座標チェック
		float dis = sqrt(pow((double)enemy[i].enX - px, 2) + pow((double)enemy[i].enY - py, 2));
		if (dis <= enemy[i].enHitBoxSize + Player_HitBoxSize)
		{
			//被弾判定
			px = InitialPosX;
			py = InitialPosY;
			Life -= 1;
		}
	}

	DrawFormatString(WINDOW_WIDTH - 100, 6, GetColor(255, 255, 255), "Life : %d", Life);

	PlayerMove(KeyState, &px, &py);//プレイヤーの移動
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
	ChangeWindowMode(FALSE);//非全画面にセット
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);//画面サイズ指定
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	SetMainWindowText("鏡像の歌姫 - Reflection of Diva -");
	SetBackgroundColor(0, 255, 0);

	if (DxLib_Init() == -1) { return -1; }		// ＤＸライブラリ初期化処理  エラーが起きたら直ちに終了

	ImageInit(); //画像の読み込み <- Image.cpp
	AudioInit(); //音声の読み込み <- Audio.cpp

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