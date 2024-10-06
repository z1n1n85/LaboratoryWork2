#include "UI.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "SortArray.h"
#include "Errors.h"
#include "validInput.h"
#include "fileManager.h"
#include "test.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

void PrintIntro(void) {
    cout << "Authors: Kazak-Tyasto Kristina & Zinin Ilya" << endl
        << "Group 433" << endl
        << "Laboratory work #2" << endl
        << "Option 4" << endl
        << endl
        << "Sorting algorithm: Bitonic sort" << endl
        << endl;
}
void PrintMainMenu(void) {
    cout << endl
        << "/=================================\\" << endl
        << "What do you want to do?" << endl
        << "1. Add a array manually" << endl
        << "2. Add a array from the file" << endl
        << "3. Print a array" << endl
        << "4. Save the array to a file" << endl
        << "5. Exit the program" << endl
        << "> ";
}
int SelectMenuItem(int start, int end) {
    int user_variant = 0;
    user_variant = InputNumber<int>();
    while (user_variant < start || user_variant > end) {
        cout << "Choose one of the available options" << endl
            << "> ";
        user_variant = InputNumber<int>();
    }
    return user_variant;
}
void ManualInput(SortArray& sort_array) {
    enum MenuManualInput {
        ADD_NEW_ITEM = 0,
        FINISH = 1,
    };
    int is_addition_complete = 0;
    sort_array.Clear();
    do {
        double number = 0;
        cout << "Enter the number" << endl << ">";
        number = InputNumber<double>();
        try {
                sort_array.Add(std::make_unique<double>(number));
        }
        catch (const IncorrectSortArrayException& ex) {
            cerr << "Data entry error, the number has not been added." << ex.message << endl;
        }
        cout << endl
            << "(0 - add number / 1 - finish adding number)" << endl
            << ">";
        is_addition_complete = SelectMenuItem(ADD_NEW_ITEM, FINISH);
    } while (is_addition_complete != FINISH);
}
void ReadFile(SortArray& sort_array) {
    cout << endl
        << "Enter the address of the file from which you want to download the data" << endl
        << "> ";
    string file_address = GetValidFileName();
    try {
        ReadOriginalListFromFile(file_address, sort_array);
        sort_array.Print();
    }
    catch (const IncorrectSortArrayException& ex) {
        cerr << "The data in the file is stored incorrectly, it cannot be downloaded. "
            << ex.message << endl;
    }
    catch (const IncorrectAccessFile& ex) {
        cerr << ex.message << endl;
    }
}
void SaveFile(SortArray& sort_array) {
    bool is_finish_save = false;
    string file_address = "";
    while (!is_finish_save) {
        try {
            cout << endl
                << "Enter the address of the file to which you want to save the file" << endl
                << "> ";
            file_address = GetValidFileName();
            if (FileExists(file_address)) {
                cout << "A file with that name already exists!" << endl;
                cout << "(0 - choose a different address / 1 - overwrite the file)"
                    << endl << ">";
                if (static_cast<bool>(SelectMenuItem(0, 1))) {
                    SaveListToFile(file_address, sort_array.GetExportData());
                    cout << "File saved successfully!" << endl;
                    is_finish_save = true;
                }
            }
            else {
                SaveListToFile(file_address, sort_array.GetExportData());
                cout << "The file has been successfully overwritten!" << endl;
                is_finish_save = true;
            }
        }
        catch (const IncorrectAccessFile& ex) {
            cerr << "The file could not be saved." << ex.message << endl;
        }
    }
}
void CreateUI(void) {
    enum MenuVariant {
        MANUAL_INPUT = 1,
        READ_FILE,
        SORTING,
        SAVE,
        EXIT,
    };
    PrintIntro();
    if (!InitTests()) {
        cerr << "[Errors were found as a result of the tests.the main "
            << "functionality of the program is not available]" << endl;
    }
    else {
        int user_variant = 0;
        SortArray sort_array;
        cout << "[All tests were successful!]" << endl;
        do {
            PrintMainMenu();
            user_variant = SelectMenuItem(MANUAL_INPUT, EXIT);
            switch (user_variant) {
            case MANUAL_INPUT: {
                ManualInput(sort_array);
                break;
            }
            case READ_FILE: {
                ReadFile(sort_array);
                break;
            }
            case SORTING: {
                if (sort_array.IsEmpty()) {
                    cerr << "Source data is missing!" << endl;
                }
                else {
                    sort_array.Print();
                }
                break;
            }
            case SAVE: {
                if (sort_array.IsEmpty()) {
                    cerr << "Source data is missing!" << endl;
                }
                else {
                    SaveFile(sort_array);
                }
                break;
            }
            }
        } while (user_variant != EXIT);
    }
}