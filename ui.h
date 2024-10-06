#ifndef UI_H
#define UI_H

#include <vector>

#include "SortArray.h"

void PrintIntro(void);
void PrintMainMenu(void);
int SelectMenuItem(int start, int end);
void ManualInput(SortArray& sort_array);
void ReadFile(SortArray& sort_array);
void SaveFile(SortArray& sort_array);
void CreateUI(void);

#endif