#ifndef TEST_DATA_H
#define TEST_DATA_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "DocumentData.h"
#include "Document.h"
#include "Mail.h"
#include "Errors.h"
#include "fileManager.h"

using std::cerr;
using std::string;
using std::vector;

class TestData {
private:
	bool is_test_success = true;
	DocumentData test_document_data;
	DocumentData file_document_data;
public:
	TestData(string source_data_address, vector<std::unique_ptr<Document>> list) {
		test_document_data.SetDocumentList(std::move(list));
		try {
			ReadOriginalListFromFile(source_data_address, file_document_data);
		}
		catch (const IncorrectDocumentException& ex) {
			cerr << "Error reading test data from files. It is impossible to conduct tests." << ex.message << endl;
			is_test_success = false;
		}
		catch (const IncorrectAccessFile& ex) {
			cerr << "It is not possible to open files for tests. It is impossible to conduct tests." << ex.message << endl;
			is_test_success = false;
		}
	};
	bool InitTest(void) {
		if (is_test_success == true) {
			is_test_success = 
				(test_document_data.GetExportData() == file_document_data.GetExportData());
			if (is_test_success == false) {
				cerr << "Expected data:" << endl;
				test_document_data.PrintFullDocuments();
				cerr << "Resulted data:" << endl;
				file_document_data.PrintFullDocuments();
			}
		}
		return is_test_success;
	}
};

#endif