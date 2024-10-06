#ifndef MAIL_H
#define MAIL_H

#include <iostream>
#include <regex>
#include <string>
#include <memory>

#include "Document.h"
#include "Errors.h"
#include "validInput.h"

using std::string;

class Mail : public Document {
private:
    string addressee;
    int project_number;
public:
    Mail(string title, string author, int department_number, string content, string addressee, int project_number) :
        Document(title, author, department_number, content) {
        if (!IsEmptyString(addressee) && project_number >= 0) {
            this->addressee = addressee;
            this->project_number = project_number;
        }
        else {
            throw IncorrectDocumentException("Incorrect data!");
        }
    }
    string GetAddressee(void) const { return addressee; }
    int GetProjectNumber(void) const { return project_number; }
    void Print(void) const override {
        cout << "Mail" << endl
            << "Title: " << GetTitle() << endl
            << "Author: " << GetAuthor() << endl
            << "Department #" << GetDepartmentNumber() << endl
            << "Addressee: " << GetAddressee() << endl;
        if (GetProjectNumber() != 0) {
            cout << "The mail of the project #" << GetProjectNumber() << endl;
        }
        else {
            cout << "The mail does not apply to any project" << endl;
        }
        cout << GetContent() << endl;
    }
    string GetExportString(void) const override {
        string export_string =
            "MAIL\n" +
            GetTitle() + "\n" +
            GetAuthor() + "\n" +
            std::to_string(GetDepartmentNumber()) + "\n" +
            GetContent() + "\n" +
            GetAddressee() + "\n" +
            std::to_string(GetProjectNumber()) + "\n";
        return export_string;
    }
};

#endif