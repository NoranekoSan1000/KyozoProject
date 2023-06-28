#pragma once

extern bool Item_exist[];
extern int Item_X[];
extern int Item_Y[];
extern int Item_HitBoxSize[];

void ItemGenerate(int num, int x, int y, int hitboxsize);
void ItemDestroy(int num);
void ItemSpawn(int en_x, int en_y);
void ItemMove(int num);
void ItemAction(void);
void ItemClear(void);