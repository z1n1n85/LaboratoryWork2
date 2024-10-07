#include "ValidInput.h"

#include <iostream>
#include <string>
#include <regex>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::regex;
using std::string;

template <typename T>
T InputNumber(void) {
    T result;
    cin >> result;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cerr << "Incorrect input. Try again" << endl
            << "> ";
        cin >> result;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return result;
}
double InputDouble(void) {
    return InputNumber<double>();
}
int InputPositiveInt(void) {
    int result = InputNumber<int>();
    while (result <= 0) {
        cerr << "The input value should not be negative or zero. Try again" << endl
            << "> ";
        result = InputNumber<int>();
    }
    return result;
}
int InputNaturalInt(void) {
    int result = InputNumber<int>();
    while (result < 0) {
        cerr << "The input value should not be negative. Try again" << endl
            << "> ";
        result = InputNumber<int>();
    }
    return result;
}
string InputFullString(void) {
    string result;
    std::getline(cin, result, '\n');
    return result;
}
bool IsEmptyString(string value) {
    regex EmptyString("\\s*");
    return regex_match(value, EmptyString);
}
string InputNotEmptyString(void) {
    string result = InputFullString();
    while (IsEmptyString(result)) {
        cerr << "The string must contain characters other than  space, tab character. Try again" << endl
            << "> ";
        result = InputFullString();
    }
    return result;
}