#ifndef DOCUMENT_DATA_H
#define DOCUMENT_DATA_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Document.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

class DocumentData {
private:
	vector<std::unique_ptr<Document>> list;
public:
	DocumentData(void) = default;
	void ClearList(void) { list.clear(); }
	bool IsListEmpty(void) { return list.size() == 0; }
	void SetDocumentList(vector<std::unique_ptr<Document>> new_list) {
		list = std::move(new_list);
	}
	void AddDocument(std::unique_ptr<Document> item) {
		list.push_back(std::move(item));
	}
	void PrintNameDocuments(void) const {
		for (int i = 0; i < list.size(); i++) {
			cout << std::to_string(i+1) << ". " << list[i]->GetTitle() << endl;
		}
	}
	void PrintFullDocuments(void) const {
		for (int i = 0; i < list.size(); i++) {
			list[i]->Print();
			cout << endl;
		}
	}
	string GetExportData(void) const {
		string save_list;
		for (int i = 0; i < list.size(); i++) {
			save_list.append(list[i]->GetExportString() + "\n");
		}
		return save_list;
	}
};

#endif