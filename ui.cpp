#include "UI.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "DocumentData.h"
#include "Document.h"
#include "Mail.h"
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
    cout << "Author: Zinin Ilya Nikolaevich" << endl
        << "Group 4306" << endl
        << "Option 13" << endl
        << "Test work #2" << endl
        << endl
        << "Task text:" << endl
        << "The base class is an enterprise document. The derived class is mail" << endl
        << endl;
}
void PrintMainMenu(void) {
    cout << endl
        << "/=================================\\" << endl
        << "What do you want to do?" << endl
        << "1. Add a list of documents manually" << endl
        << "2. Add a list of documents from the file" << endl
        << "3. Print a list of documents" << endl
        << "4. Save the source data to a file" << endl
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
void ManualInput(DocumentData& document_data) {
    enum MenuManualInput {
        ADD_NEW_ITEM = 0,
        FINISH = 1,
        MAIL = 0,
        DOCUMENT = 1,
    };
    int is_addition_complete = 0;
    int type_document = 0;
    document_data.ClearList();
    do {
        std::string title;
        std::string author;
        int department_number = 0;
        std::string content;
        std::string addresse;
        int project_number = 0;
        cout << "(0 - add mail / 1 - add another document)" << endl << ">";
        type_document = SelectMenuItem(MAIL, DOCUMENT);
        cout << endl;
        cout << "Enter the document's author" << endl << ">";
        author = InputNotEmptyString();
        cout << "Enter the document's title" << endl << ">";
        title = InputNotEmptyString();
        cout << "Enter the document's department number" << endl << ">";
        department_number = InputPositiveInt();
        if (type_document == MAIL) {
            cout << "Enter the document's addresse" << endl << ">";
            addresse = InputNotEmptyString();
            cout << "Enter the document's project number (0 if the mail does not relate to the project)" << endl << ">";
            project_number = InputNaturalInt();
        }
        cout << "Enter the document's content" << endl << ">";
        content = InputNotEmptyString();
        try {
            if (type_document == DOCUMENT) {
                document_data.AddDocument(std::make_unique<Document>(title, author,
                    department_number, content));
            }
            else {
                document_data.AddDocument(std::make_unique<Mail>(title, author,
                    department_number, content, addresse, project_number));
            }
        }
        catch (const IncorrectDocumentException& ex) {
            cerr << "Data entry error, the document has not been added." << ex.message << endl;
        }
        cout << endl
            << "(0 - add document / 1 - finish adding document)" << endl
            << ">";
        is_addition_complete = SelectMenuItem(ADD_NEW_ITEM, FINISH);
    } while (is_addition_complete != FINISH);
}
void ReadFile(DocumentData &document_data) {
    cout << endl
        << "Enter the address of the file from which you want to download the data" << endl
        << "> ";
    string file_address = GetValidFileName();
    try {
        ReadOriginalListFromFile(file_address, document_data);
        document_data.PrintNameDocuments();
    }
    catch (const IncorrectDocumentException& ex) {
        cerr << "The data in the file is stored incorrectly, it cannot be downloaded. "
            << ex.message << endl;
    }
    catch (const IncorrectAccessFile& ex) {
        cerr << ex.message << endl;
    }
}
void SaveFile(DocumentData& document_data) {
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
                    SaveListToFile(file_address, document_data.GetExportData());
                    cout << "File saved successfully!" << endl;
                    is_finish_save = true;
                }
            }
            else {
                SaveListToFile(file_address, document_data.GetExportData());
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
        PRINT_DOCUMENTS,
        SAVE_DOCUMENTS,
        EXIT,
    };
    PrintIntro();
    if (InitTests()) {
        int user_variant = 0;
        DocumentData document_data;
        cout << "[All tests were successful!]" << endl;
        do {
            PrintMainMenu();
            user_variant = SelectMenuItem(MANUAL_INPUT, EXIT);
            switch (user_variant) {
            case MANUAL_INPUT: {
                ManualInput(document_data);
                break;
            }
            case READ_FILE: {
                ReadFile(document_data);
                break;
            }
            case PRINT_DOCUMENTS: {
                if (!document_data.IsListEmpty()) {
                    document_data.PrintFullDocuments();
                }
                else { cerr << "Source data is missing!" << endl; }
                break;
            }
            case SAVE_DOCUMENTS: {
                if (!document_data.IsListEmpty()) {
                    SaveFile(document_data);
                }
                else { cerr << "Source data is missing!" << endl; }
                break;
            }
            }
        } while (user_variant != EXIT);
    }
    else {
        cerr << "[Errors were found as a result of the tests.the main "
            << "functionality of the program is not available]" << endl;
    }
}