#include <DxLib.h>

//�L�[�擾�p�̔z��
char buf[256] = { 0 };
int KeyState[256] = { 0 };

//�L�[���͏�Ԃ��X�V����֐�
void KeyUpdate(void)
{
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; i++)
	{
		if (buf[i] == 0)
		{
			if (KeyState[i] > 0) // ������Ă��Ȃ�
			{
				KeyState[i] = -1;		// ESC�L�[�����ꂽ�u��
			}
			else
			{
				KeyState[i] = 0;		// ESC�L�[������Ă�����
			}
		}
		else KeyState[i]++;// ������Ă���
	}
}