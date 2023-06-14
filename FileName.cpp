#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	if (DxLib_Init() == -1) { return -1; }		
	// ＤＸライブラリ初期化処理
	// エラーが起きたら直ちに終了

	DrawPixel(320, 240, GetColor(255, 255, 255));	// 点を打つ
	DrawPixel(320, 200, GetColor(255, 255, 255));	// 点を打つ
	DrawPixel(320, 280, GetColor(255, 255, 255));	// 点を打つ

	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}