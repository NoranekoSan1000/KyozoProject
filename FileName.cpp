#include <stdio.h>
#include <DxLib.h>
#define PI 3.141592654

//変数宣言エリア
const int Window_Width = 800;
const int Window_Height = 600;

int mouseX = 0;//マウス座標
int mouseY = 0;//マウス座標

//キー取得用の配列
char buf[256] = { 0 };
int keyState[256] = { 0 };

int count = 0;

int shot_img;

//キー入力状態を更新する関数
void KeyUpdate(void)
{
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++)
	{
		if (buf[i] == 1) {
			keyState[i]++;
		}
		else {
			keyState[i] = 0;
		}
	}
}

int x = 100;

void Update(void) //毎フレーム処理
{
	DrawRotaGraph(300, 100, 5.0, PI/4, shot_img, TRUE); //画像の描画
	DrawPixel(Window_Width / 2, Window_Height / 2, GetColor(255, 255, 255));	// 点を打つ
	DrawCircle(100, 100, 30, GetColor(255, 0, 0), 0);
	DrawCircle(200, 100, 30, GetColor(0, 255, 0), 1);
	DrawBox(50, 200, 100, 300, GetColor(0, 0, 255), 1);
	DrawLine(200, 200, 300, 330, GetColor(255, 255, 255), 1);
	
	count++;
	DrawFormatString(Window_Width-100, 100, GetColor(255, 255, 255), "frame %d", count);
	DrawFormatString(Window_Width-100, 120, GetColor(255, 255, 255), "sec %d", count / 60);

	GetMousePoint(&mouseX, &mouseY); //マウス座標更新
	DrawFormatString(20, 50, GetColor(255, 255, 255), "MX:%3d MY:%3d", mouseX, mouseY); //左上に文字（マウスの座標）を描画

	DrawFormatString(100, 100, GetColor(255, 255, 255), "Z KEY %d", keyState[KEY_INPUT_Z]);
	DrawFormatString(100, 120, GetColor(255, 255, 255), "X KEY %d", keyState[KEY_INPUT_X]);

	if (keyState[KEY_INPUT_Z] > 0) //継続入力
	{
		x += 1;
	}
	if (keyState[KEY_INPUT_X] == TRUE) //単発入力
	{
		x += 30;
	}
	DrawCircle(x, 200, 32, GetColor(255, 255, 0));
}

void ImgInit(void)
{
	shot_img = LoadGraph("shot.png");
}

// プログラムは WinMain から始まる
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(Window_Width, Window_Height, 32);//画面サイズ指定
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定

	if (DxLib_Init() == -1) { return -1; }		// ＤＸライブラリ初期化処理  エラーが起きたら直ちに終了

	ImgInit(); //画像・音の読み込み

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