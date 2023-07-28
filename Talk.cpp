#include "GameData.h"



int TalkScene = 0;

bool TalkActive = false;
int PlayerTalk = 0;
int BossTalk = 0;

int TalkStep = 0;
string str = "";

int Font = CreateFontToHandle("ＭＳ ゴシック", 50, 9, DX_FONTTYPE_ANTIALIASING);

struct TalkList
{
	char Conversation[70];
	int p; //0 <-Disable 1<-stand-by 2<-Enable
	int b;
};

TalkList talklist_0[] = 
{ 
	{"そこのお前！とまれ！！！\0",0,0},
	{"お前、確か指名手配されていた女だな！\0",1,2},
	{"あれは私じゃないわ。別人よ。\0",2,1},
	{"どうしてそんな見え透いた嘘をつく？\0",1,2},
	{"少しは他の可能性も考えないわけ？\0",2,1},
	{"とりあえず爆破させれば分かることだ！\0",1,2},
	{"思考停止ってことね・・・。\0",2,1},
	{"\0",0,0}//終了
};
TalkList talklist_1[] =
{
	{"どうやら厄介な魔女の縄張りに入ってしまったみたいね。\0",2,0},
	{"人を厄介者扱いしないでくれる？今はあなたがいる方が\n困るんだけど。\0",1,2},
	{"確かにね。早いとこ先に進ませてもらうわ。\0",2,1},
	{"待ちなさい。あなたが行くべき方向はそっちじゃ\nないわよ。\0",1,2},
	{"どういうこと？\0",2,1},
	{"これから自首しに行くんじゃないの？もしかして\n私の案内が必要？\0",1,2},
	{"余計なお世話よ。\0",2,1},
	{"\0",0,0}//終了
};
TalkList talklist_2[] =
{
	{"どうやら厄介な魔女の縄張りに入ってしまったみたいね。\0",2,0},
	{"人を厄介者扱いしないでくれる？今はあなたがいる方が\n困るんだけど。\0",1,2},
	{"確かにね。早いとこ先に進ませてもらうわ。\0",2,1},
	{"待ちなさい。あなたが行くべき方向はそっちじゃ\nないわよ。\0",1,2},
	{"どういうこと？\0",2,1},
	{"これから自首しに行くんじゃないの？もしかして\n私の案内が必要？\0",1,2},
	{"余計なお世話よ。\0",2,1},
	{"\0",0,0}//終了
};
TalkList talklist_3[] =
{
	{"どうやら厄介な魔女の縄張りに入ってしまったみたいね。\0",2,0},
	{"人を厄介者扱いしないでくれる？今はあなたがいる方が\n困るんだけど。\0",1,2},
	{"確かにね。早いとこ先に進ませてもらうわ。\0",2,1},
	{"待ちなさい。あなたが行くべき方向はそっちじゃ\nないわよ。\0",1,2},
	{"どういうこと？\0",2,1},
	{"これから自首しに行くんじゃないの？もしかして\n私の案内が必要？\0",1,2},
	{"余計なお世話よ。\0",2,1},
	{"\0",0,0}//終了
};
TalkList talklist_4[] =
{
	{"どうやら厄介な魔女の縄張りに入ってしまったみたいね。\0",2,0},
	{"人を厄介者扱いしないでくれる？今はあなたがいる方が\n困るんだけど。\0",1,2},
	{"確かにね。早いとこ先に進ませてもらうわ。\0",2,1},
	{"待ちなさい。あなたが行くべき方向はそっちじゃ\nないわよ。\0",1,2},
	{"どういうこと？\0",2,1},
	{"これから自首しに行くんじゃないの？もしかして\n私の案内が必要？\0",1,2},
	{"余計なお世話よ。\0",2,1},
	{"\0",0,0}//終了
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