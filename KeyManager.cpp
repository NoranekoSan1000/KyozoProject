#include <DxLib.h>

//キー取得用の配列
char buf[256] = { 0 };
int KeyState[256] = { 0 };

//キー入力状態を更新する関数
void KeyUpdate(void)
{
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++)
	{
		if (buf[i] == 0)
		{
			if (KeyState[i] > 0) // 押されていない
			{
				KeyState[i] = -1;		// ESCキーが離れた瞬間
			}
			else
			{
				KeyState[i] = 0;		// ESCキーが離れている状態
			}
		}
		else KeyState[i]++;// 押されている
	}
}