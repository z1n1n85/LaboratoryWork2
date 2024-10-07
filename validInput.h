#ifndef VALIDINPUT_H
#define VALIDINPUT_H

#include  <string>

template <typename T> T InputNumber(void);
double InputDouble(void);
int InputPositiveInt(void);
int InputNaturalInt(void);
std::string InputFullString(void);
bool IsEmptyString(std::string value);
std::string InputNotEmptyString(void);

#endif
