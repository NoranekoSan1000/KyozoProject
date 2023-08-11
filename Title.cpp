#include "GameData.h"

int SelectTitleAction = 0;

void Title()
{
	PlayBGM(BGM[0]);
	DrawRotaGraph(450, 400, 1, 0, Title_img, TRUE);

	if (KeyState[KEY_INPUT_UP] == TRUE && SelectTitleAction > 0) SelectTitleAction--;
	else if (KeyState[KEY_INPUT_UP] == TRUE && SelectTitleAction == 0) SelectTitleAction = 3;
	if (KeyState[KEY_INPUT_DOWN] == TRUE && SelectTitleAction < 3) SelectTitleAction++;
	else if (KeyState[KEY_INPUT_DOWN] == TRUE && SelectTitleAction == 3) SelectTitleAction = 0;

	int y[4] = { 500 ,570 ,650 ,710 };
	DrawRotaGraph(560 + (10 * SelectTitleAction), y[SelectTitleAction], 1, 0, select_icon, TRUE);//画像表示
	DrawRotaGraph(860, y[0], 1, 0, gamestart_text, TRUE);//画像表示
	DrawRotaGraph(870, y[1], 1, 0, musicroom_text, TRUE);//画像表示
	DrawRotaGraph(880, y[2], 1, 0, setting_text, TRUE);//画像表示
	DrawRotaGraph(890, y[3], 1, 0, exit_text, TRUE);//画像表示

	if (KeyState[KEY_INPUT_Z] == TRUE)
	{
		ChangeSceneActive = true;
		if (SelectTitleAction == 0) nextScene = DifficultyLvSelect_Scene;//シーン遷移用。この２つはセット
		else if (SelectTitleAction == 1) nextScene = MusicRoom_Scene;
		else if (SelectTitleAction == 2) nextScene = Setting_Scene;
		else if (SelectTitleAction == 3) DxLib_End();
	}
}