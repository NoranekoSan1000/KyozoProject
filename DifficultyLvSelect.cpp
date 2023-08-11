#include "GameData.h"

void DifficultyLvSelect()
{
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	if (KeyState[KEY_INPUT_UP] == TRUE && SelectDifficulty > 0) SelectDifficulty--;
	else if (KeyState[KEY_INPUT_UP] == TRUE && SelectDifficulty == 0) SelectDifficulty = 3;
	if (KeyState[KEY_INPUT_DOWN] == TRUE && SelectDifficulty < 3) SelectDifficulty++;
	else if (KeyState[KEY_INPUT_DOWN] == TRUE && SelectDifficulty == 3) SelectDifficulty = 0;

	for (int i = 0; i < 4; i++)
	{
		if (SelectDifficulty == i) DrawRotaGraph(450, 140 + (i * 170), 1, 0, DifficultyLv_img[i], TRUE);//画像表示
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
			DrawRotaGraph(450, 140 + (i * 170), 1, 0, DifficultyLv_img[i], TRUE);//画像表示
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}

	}
	if (KeyState[KEY_INPUT_Z] == TRUE)
	{
		ChangeSceneActive = true;
		nextScene = Stage1_Scene;//シーン遷移用。この２つはセット
	}
	if (KeyState[KEY_INPUT_X] == TRUE)
	{
		ChangeSceneActive = true;
		nextScene = Title_Scene;//シーン遷移用。この２つはセット
	}
}