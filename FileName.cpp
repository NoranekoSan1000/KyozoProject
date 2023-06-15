#include <stdio.h>
#include <DxLib.h>
#define PI 3.141592654

//変数宣言エリア
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

//マウス座標
int mouseX = 0;
int mouseY = 0;

//キー取得用の配列
char buf[256] = { 0 };
int keyState[256] = { 0 };

int FrameCount = 0;

int shot_img;
int player_img;
int ResonanceAtTwilight_audio;

//プレイヤーの座標
int px = 320;
int py = 320;

void PlayerMove(void)
{
	const int MOVE_SPEED = 4;
	float slow = 1;
	const int PLAYER_SIZE_X = 10;
	const int PLAYER_SIZE_Y = 20;

	if (keyState[KEY_INPUT_LSHIFT] > 0) slow = 0.5;
	else slow = 1;

	if (keyState[KEY_INPUT_RIGHT] > 0 && px < WINDOW_WIDTH - PLAYER_SIZE_X) //継続入力
	{
		px += MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_LEFT] > 0 && px > 0 + PLAYER_SIZE_X) //継続入力
	{
		px -= MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_DOWN] > 0 && py < WINDOW_HEIGHT - PLAYER_SIZE_Y) //継続入力
	{
		py += MOVE_SPEED * slow;
	}
	if (keyState[KEY_INPUT_UP] > 0 && py > 0 + PLAYER_SIZE_Y) //継続入力
	{
		py -= MOVE_SPEED * slow;
	}
}

void Update(void) //毎フレーム処理
{
	DrawRotaGraph(300, 100, 5.0, PI/4, shot_img, TRUE); //画像の描画
	DrawPixel(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GetColor(255, 255, 255));	// 点を打つ
	DrawCircle(100, 100, 30, GetColor(255, 0, 0), 0);
	DrawCircle(200, 100, 30, GetColor(0, 255, 0), 1);
	DrawBox(WINDOW_WIDTH-250, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 255), 1);
	
	FrameCount++;
	DrawFormatString(WINDOW_WIDTH-100, 100, GetColor(255, 255, 255), "frame %d", FrameCount);
	DrawFormatString(WINDOW_WIDTH-100, 120, GetColor(255, 255, 255), "sec %d", FrameCount / 60);

	GetMousePoint(&mouseX, &mouseY); //マウス座標更新
	DrawFormatString(20, 50, GetColor(255, 255, 255), "MX:%3d MY:%3d", mouseX, mouseY); //左上に文字（マウスの座標）を描画

	DrawFormatString(100, 100, GetColor(255, 255, 255), "Z KEY %d", keyState[KEY_INPUT_Z]);
	DrawFormatString(100, 120, GetColor(255, 255, 255), "X KEY %d", keyState[KEY_INPUT_X]);

	if (keyState[KEY_INPUT_X] == TRUE) //単発入力
	{
		StopSoundMem(ResonanceAtTwilight_audio);
		ChangeVolumeSoundMem(100, ResonanceAtTwilight_audio);
		PlaySoundMem(ResonanceAtTwilight_audio, DX_PLAYTYPE_BACK);
	}

	PlayerMove();//プレイヤーの移動
	DrawRotaGraph(px, py, 1.0, 0, player_img, TRUE); //画像の描画
	DrawCircle(px, py, 8, GetColor(100, 180, 255)); // プレイヤー
	
}

//キー入力状態を更新する関数
void KeyUpdate(void)
{
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++)
	{
		if (buf[i] == 1) keyState[i]++;
		else keyState[i] = 0;
	}
}

void ImgInit(void)
{
	shot_img = LoadGraph("shot.png");
	player_img = LoadGraph("player.png");
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