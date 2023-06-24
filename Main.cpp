#include "GameData.h"
#include "Player.h"
#include "Enemy.h"
#include "Player_Bullet.h"

SceneManager GameScene = Title_Scene;
double FrameCount = 0;

//キー取得用の配列
char buf[256] = { 0 };
int KeyState[256] = { 0 };

void ViewStatus(void)
{
	//枠
	DrawBox(0, 0, 25, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawBox(0, 0, WINDOW_WIDTH, 25, GetColor(0, 0, 0), 1);
	DrawBox(0, WINDOW_HEIGHT-25, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	DrawRotaGraph(750, 400, 1, 0, gameFrame_img, TRUE);

	//テキスト
	DrawFormatString(WINDOW_WIDTH - 200, 30, GetColor(255, 255, 255), "Score : %d", Score);
	DrawFormatString(WINDOW_WIDTH - 200, 60, GetColor(255, 255, 255), "Life : %d", Life);
	DrawFormatString(WINDOW_WIDTH - 200, 120, GetColor(255, 255, 255), "sec %.2lf", FrameCount++ / 60);
}

void PlayerShotAction()
{
	if (KeyState[KEY_INPUT_Z] > 0)
	{
		if (P_ShotCoolTime > 0) return;
		PlayerShot(px, py-8, 0);//射撃
		PlayerShot(px, py-4, 1);//射撃
		PlayerShot(px, py-4, 2);//射撃
		PlayerShot(px+8, py+8, 5);//射撃
		PlayerShot(px-8, py+8, 6);//射撃
		P_ShotCoolTime = 8;//フレームで設定
	}
}

void Update(void) //毎フレーム処理
{
	if (GameScene == Title_Scene)
	{
		DrawRotaGraph(450, 400, 1, 0, Title_img, TRUE);
		if (KeyState[KEY_INPUT_A] == TRUE) GameScene = Stage1_Scene;
	}
	if (GameScene == Stage1_Scene)
	{
		if (P_ShotCoolTime >= 0) P_ShotCoolTime--;
		if (DamagedCoolTime >= 0) DamagedCoolTime--;

		if (KeyState[KEY_INPUT_A] == TRUE) EnemySpawn();
		EnemyAction();

		PlayerShotAction();
		PlayerBulletAction();

		PlayerMove(KeyState);//プレイヤーの移動
		ViewPlayer();//プレイヤー表示

		ViewStatus();
	}

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
	SetBackgroundColor(100, 100, 100);

	if (DxLib_Init() == -1) { return -1; }		// ＤＸライブラリ初期化処理  エラーが起きたら直ちに終了

	ImageInit(); //画像の読み込み <- Image.cpp
	AudioInit(); //音声の読み込み <- Audio.cpp
	PlayBGM(BGM[0]);

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