#include "GameData.h"

int SelectMusic = 0;
int PlayingMusic = 0;

void MusicRoom()
{
	DrawRotaGraph(450, 400, 1, 0, MusicRoom_img, TRUE);

	int Font;
	Font = CreateFontToHandle("メイリオ", 20, 9, DX_FONTTYPE_ANTIALIASING_EDGE);
	DrawStringToHandle(60, WINDOW_HEIGHT - 30, "Xキーを押して戻る", GetColor(255, 255, 255), Font);

	int i = 70, j = 30;

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

	int x[2] = { i + j - 60 , WINDOW_WIDTH / 2 + j - 60 };

	int sel = 0, ply = 0;
	if (SelectMusic < 6) sel = 0;
	else sel = 1;
	if (PlayingMusic < 6) ply = 0;
	else ply = 1;
	DrawRotaGraph(x[sel] + 25, (SelectMusic % 6 + 2) * i + 10, 1, 0, select_icon, TRUE);//画像表示

	DrawBox(x[ply] + 55, (PlayingMusic % 6 + 2) * i + 10 - 20, x[ply] + 350, (PlayingMusic % 6 + 2) * i + 10 + 20, GetColor(0, 50, 100), 1);

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