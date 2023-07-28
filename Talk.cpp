#include "GameData.h"



int TalkScene = 0;

bool TalkActive = false;
int PlayerTalk = 0;
int BossTalk = 0;

int TalkStep = 0;
string str = "";

int Font = CreateFontToHandle("�l�r �S�V�b�N", 50, 9, DX_FONTTYPE_ANTIALIASING);

struct TalkList
{
	char Conversation[70];
	int p; //0 <-Disable 1<-stand-by 2<-Enable
	int b;
};

TalkList talklist_0[] = 
{ 
	{"�����̂��O�I�Ƃ܂�I�I�I\0",0,0},
	{"���O�A�m���w����z����Ă��������ȁI\0",1,2},
	{"����͎�����Ȃ���B�ʐl��B\0",2,1},
	{"�ǂ����Ă���Ȍ����������R�����H\0",1,2},
	{"�����͑��̉\�����l���Ȃ��킯�H\0",2,1},
	{"�Ƃ肠�������j������Ε����邱�Ƃ��I\0",1,2},
	{"�v�l��~���Ă��ƂˁE�E�E�B\0",2,1},
	{"\0",0,0}//�I��
};
TalkList talklist_1[] =
{
	{"�ǂ������Ȗ����̓꒣��ɓ����Ă��܂����݂����ˁB\0",2,0},
	{"�l����҈������Ȃ��ł����H���͂��Ȃ����������\n����񂾂��ǁB\0",1,2},
	{"�m���ɂˁB�����Ƃ���ɐi�܂��Ă��炤��B\0",2,1},
	{"�҂��Ȃ����B���Ȃ����s���ׂ������͂���������\n�Ȃ����B\0",1,2},
	{"�ǂ��������ƁH\0",2,1},
	{"���ꂩ�玩�񂵂ɍs���񂶂�Ȃ��́H����������\n���̈ē����K�v�H\0",1,2},
	{"�]�v�Ȃ����b��B\0",2,1},
	{"\0",0,0}//�I��
};
TalkList talklist_2[] =
{
	{"�ǂ������Ȗ����̓꒣��ɓ����Ă��܂����݂����ˁB\0",2,0},
	{"�l����҈������Ȃ��ł����H���͂��Ȃ����������\n����񂾂��ǁB\0",1,2},
	{"�m���ɂˁB�����Ƃ���ɐi�܂��Ă��炤��B\0",2,1},
	{"�҂��Ȃ����B���Ȃ����s���ׂ������͂���������\n�Ȃ����B\0",1,2},
	{"�ǂ��������ƁH\0",2,1},
	{"���ꂩ�玩�񂵂ɍs���񂶂�Ȃ��́H����������\n���̈ē����K�v�H\0",1,2},
	{"�]�v�Ȃ����b��B\0",2,1},
	{"\0",0,0}//�I��
};
TalkList talklist_3[] =
{
	{"�ǂ������Ȗ����̓꒣��ɓ����Ă��܂����݂����ˁB\0",2,0},
	{"�l����҈������Ȃ��ł����H���͂��Ȃ����������\n����񂾂��ǁB\0",1,2},
	{"�m���ɂˁB�����Ƃ���ɐi�܂��Ă��炤��B\0",2,1},
	{"�҂��Ȃ����B���Ȃ����s���ׂ������͂���������\n�Ȃ����B\0",1,2},
	{"�ǂ��������ƁH\0",2,1},
	{"���ꂩ�玩�񂵂ɍs���񂶂�Ȃ��́H����������\n���̈ē����K�v�H\0",1,2},
	{"�]�v�Ȃ����b��B\0",2,1},
	{"\0",0,0}//�I��
};
TalkList talklist_4[] =
{
	{"�ǂ������Ȗ����̓꒣��ɓ����Ă��܂����݂����ˁB\0",2,0},
	{"�l����҈������Ȃ��ł����H���͂��Ȃ����������\n����񂾂��ǁB\0",1,2},
	{"�m���ɂˁB�����Ƃ���ɐi�܂��Ă��炤��B\0",2,1},
	{"�҂��Ȃ����B���Ȃ����s���ׂ������͂���������\n�Ȃ����B\0",1,2},
	{"�ǂ��������ƁH\0",2,1},
	{"���ꂩ�玩�񂵂ɍs���񂶂�Ȃ��́H����������\n���̈ē����K�v�H\0",1,2},
	{"�]�v�Ȃ����b��B\0",2,1},
	{"\0",0,0}//�I��
};

void TalkProcess(void)
{
	int x = 115;
	int y = 630;
	if (TalkScene == 0)
	{
		if (talklist_0[TalkStep].Conversation[0] == '\0') TalkActive = false;
		DrawFormatStringToHandle(x, y, GetColor(255, 255, 255), Font00, "%s",talklist_0[TalkStep].Conversation);
		//DrawFormatString(x, y, GetColor(255, 255, 255), "%s",talklist_0[TalkStep].Conversation);
		PlayerTalk = talklist_0[TalkStep].p;
		BossTalk = talklist_0[TalkStep].b;
	}
	if (TalkScene == 1)
	{
		if (talklist_1[TalkStep].Conversation[0] == '\0') TalkActive = false;
		DrawFormatString(x, y, GetColor(255, 255, 255), "%s", talklist_1[TalkStep].Conversation);
		PlayerTalk = talklist_1[TalkStep].p;
		BossTalk = talklist_1[TalkStep].b;
	}
	if (TalkScene == 2)
	{
		if (talklist_2[TalkStep].Conversation[0] == '\0') TalkActive = false;
		DrawFormatString(x, y, GetColor(255, 255, 255), "%s", talklist_2[TalkStep].Conversation);
		PlayerTalk = talklist_2[TalkStep].p;
		BossTalk = talklist_2[TalkStep].b;
	}
	if (TalkScene == 3)
	{
		if (talklist_3[TalkStep].Conversation[0] == '\0') TalkActive = false;
		DrawFormatString(x, y, GetColor(255, 255, 255), "%s", talklist_3[TalkStep].Conversation);
		PlayerTalk = talklist_3[TalkStep].p;
		BossTalk = talklist_3[TalkStep].b;
	}
	if (TalkScene == 4)
	{
		if (talklist_4[TalkStep].Conversation[0] == '\0') TalkActive = false;
		DrawFormatString(x, y, GetColor(255, 255, 255), "%s", talklist_4[TalkStep].Conversation);
		PlayerTalk = talklist_4[TalkStep].p;
		BossTalk = talklist_4[TalkStep].b;
	}
}