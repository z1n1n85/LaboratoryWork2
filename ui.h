#ifndef UI_H
#define UI_H

#include <vector>

#include "DocumentData.h"

void PrintIntro(void);
void PrintMainMenu(void);
int SelectMenuItem(int start, int end);
void ManualInput(DocumentData& document_data);
void ReadFile(DocumentData& document_data);
void SaveFile(DocumentData& document_data);
void CreateUI(void);

#endif