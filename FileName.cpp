#include <stdio.h>
#include <DxLib.h>

//変数宣言エリア
const int Window_Width = 800;
const int Window_Height = 600;

void Update(void) //毎フレーム処理
{
	DrawPixel(Window_Width / 2, Window_Height / 2 - 20, GetColor(255, 255, 255));	// 点を打つ
	DrawPixel(Window_Width / 2, Window_Height / 2, GetColor(255, 255, 255));	// 点を打つ
	DrawPixel(Window_Width / 2, Window_Height / 2 + 20, GetColor(255, 255, 255));	// 点を打つ
}

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(Window_Width, Window_Height, 32);//画面サイズ指定
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定

	if (DxLib_Init() == -1) { return -1; }		// ＤＸライブラリ初期化処理  エラーが起きたら直ちに終了

	//画像・音の読み込み

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す
		SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に
		Update();//毎フレーム処理
		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}