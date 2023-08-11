#include "GameData.h"

int SelectSetting = 0;

void Setting()
{
	DrawRotaGraph(450, 400, 1, 0, Setting_img, TRUE);

	int Font;
	Font = CreateFontToHandle("メイリオ", 20, 9, DX_FONTTYPE_ANTIALIASING_EDGE);
	DrawStringToHandle(60, WINDOW_HEIGHT - 30, "Xキーを押して戻る", GetColor(255, 255, 255), Font);
	DeleteFontToHandle(Font);

	if (KeyState[KEY_INPUT_UP] == TRUE && SelectSetting > 0) SelectSetting--;
	else if (KeyState[KEY_INPUT_UP] == TRUE && SelectSetting == 0) SelectSetting = 1;
	if (KeyState[KEY_INPUT_DOWN] == TRUE && SelectSetting < 1) SelectSetting++;
	else if (KeyState[KEY_INPUT_DOWN] == TRUE && SelectSetting == 1) SelectSetting = 0;

	int y[2] = { 340,410 };

	DrawRotaGraph(50, y[SelectSetting], 1, 0, select_icon, TRUE);//画像表示
	if (SelectSetting == 0)
	{
		if (KeyState[KEY_INPUT_LEFT] == TRUE && BGMCurrentVolume > 0) BGMCurrentVolume--;
		if (KeyState[KEY_INPUT_RIGHT] == TRUE && BGMCurrentVolume < 9) BGMCurrentVolume++;
		volumeSetBGM();//音量再設定
	}
	else if (SelectSetting == 1)
	{
		if (KeyState[KEY_INPUT_LEFT] == TRUE && SECurrentVolume > 0) SECurrentVolume--;
		if (KeyState[KEY_INPUT_RIGHT] == TRUE && SECurrentVolume < 9) SECurrentVolume++;
	}

	for (int i = 0; i < 10; i++)
	{
		int alpha = 80;
		if (BGMCurrentVolume == i) alpha = 255;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRotaGraph(60 * (i + 1) + 150, 340, 0.8, 0, NumberText_img[i], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}

	for (int i = 0; i < 10; i++)
	{
		int alpha = 80;
		if (SECurrentVolume == i) alpha = 255;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRotaGraph(60 * (i + 1) + 150, 410, 0.8, 0, NumberText_img[i], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}

	if (KeyState[KEY_INPUT_X] == TRUE)
	{
		ChangeSceneActive = true;
		nextScene = Title_Scene;//シーン遷移用。この２つはセット
	}
}
