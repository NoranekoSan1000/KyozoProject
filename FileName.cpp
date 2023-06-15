#include <stdio.h>
#include <DxLib.h>
#include <math.h>
#include "PlayerAction.h"
#define PI 3.141592654
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//マウス座標
int mouseX = 0;
int mouseY = 0;

//キー取得用の配列
char buf[256] = { 0 };
int KeyState[256] = { 0 };

//画像、音楽
int shot_img;
int player_img;
int status_img;
int ResonanceAtTwilight_audio;

//プレイヤーの座標
int px = 320;
int py = 320;

//敵の座標
int enX[3];
int enY[3];
int enHitBoxSize[3];

int FrameCount = 0;

const int Player_HitBoxSize = 4;

void Update(void) //毎フレーム処理
{
	DrawRotaGraph(10, 10, 1.0, 0, shot_img, TRUE); //画像の描画

	DrawBox(0, 0, 100, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawRotaGraph(700, 300, 0.8, 0, status_img, TRUE); //画像の描画

	FrameCount++;
	DrawFormatString(WINDOW_WIDTH - 100, 100, GetColor(255, 255, 255), "frame %d", FrameCount);
	DrawFormatString(WINDOW_WIDTH - 100, 120, GetColor(255, 255, 255), "sec %d", FrameCount / 60);
	GetMousePoint(&mouseX, &mouseY); //マウス座標更新
	DrawFormatString(20, 50, GetColor(255, 255, 255), "MX:%3d MY:%3d", mouseX, mouseY); //左上に文字（マウスの座標）を描画

	if (KeyState[KEY_INPUT_X] == TRUE) //単発入力
	{
		StopSoundMem(ResonanceAtTwilight_audio);
		ChangeVolumeSoundMem(100, ResonanceAtTwilight_audio);
		PlaySoundMem(ResonanceAtTwilight_audio, DX_PLAYTYPE_BACK);
	}

	enX[0] = 200;
	enY[0] = 200;
	enHitBoxSize[0] = 30;

	DrawCircle(enX[0], enY[0], enHitBoxSize[0], GetColor(255, 0, 0), 1);

	//敵との座標チェック
	float dis = sqrt(pow((double)enX[0] -px, 2) + pow((double)enY[0] - py, 2));
	DrawFormatString(WINDOW_WIDTH - 100, 300, GetColor(255, 255, 255), "%f" , dis);
	if (dis <= 30 + Player_HitBoxSize) DrawFormatString(WINDOW_WIDTH - 100, 350, GetColor(255, 255, 255), "Hit");

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

void ImgInit(void)
{
	shot_img = LoadGraph("shot.png");
	player_img = LoadGraph("player.png");
	status_img = LoadGraph("status.png");
}
void AudioInit(void)
{
	ResonanceAtTwilight_audio = LoadSoundMem("ResonanceAtTwilight.mp3");
}

// プログラムは WinMain から始まる
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);//画面サイズ指定
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	SetMainWindowText("鏡像の歌姫 - Reflection of Diva -");
	SetBackgroundColor(0, 255, 0);

	if (DxLib_Init() == -1) { return -1; }		// ＤＸライブラリ初期化処理  エラーが起きたら直ちに終了

	ImgInit(); //画像・音の読み込み
	AudioInit();

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