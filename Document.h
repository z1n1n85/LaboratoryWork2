#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <iostream>
#include <compare>
#include <memory>

#include "Errors.h"
#include "validInput.h"

using std::string;
using std::cout;
using std::endl;

class Document {
private:
    string title;
    string author;
    int department_number;
    string content;
public:
    Document(string title, string author, int department_number, string content){
        if (department_number > 0 && !IsEmptyString(title) &&
            !IsEmptyString(author) && !IsEmptyString(content)) {
            this->title = title;
            this->author = author;
            this->department_number = department_number;
            this->content = content;
        }
        else {
            throw IncorrectDocumentException("Incorrect data!");
        }
    }
    string GetTitle(void) const { return title; }
    string GetAuthor(void) const { return author; }
    int GetDepartmentNumber(void) const { return department_number; }
    string GetContent(void) const { return content; }
    virtual void Print(void) const {
        cout << "Document" << endl
            << "Title: " << GetTitle() << endl
            << "Author: " << GetAuthor() << endl
            << "Department #" << GetDepartmentNumber() << endl
            << GetContent() << endl;
    }
    virtual string GetExportString(void) const {
        string export_string =
            "DOCUMENT\n" +
            GetTitle() + "\n" +
            GetAuthor() + "\n" +
            std::to_string(GetDepartmentNumber()) + "\n" +
            GetContent() + "\n";
        return export_string;
    }
};

#endif