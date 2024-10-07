#ifndef TEST_DATA_H
#define TEST_DATA_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "SortArray.h"
#include "Errors.h"
#include "fileManager.h"

using std::cerr;
using std::string;
using std::vector;

class TestData {
private:
	bool is_test_success = true;
	SortArray test_sort_array;
	SortArray file_sort_array;
public:
	TestData(string source_data_address, vector<double> list) {
		test_sort_array.Set(list);
		try {
			ReadOriginalListFromFile(source_data_address, file_sort_array);
		}
		catch (const IncorrectSortArrayException& ex) {
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
			file_sort_array.Sorting();
			is_test_success = 
				(test_sort_array.GetExportData() == file_sort_array.GetExportData());
			if (is_test_success == false) {
				cerr << "Expected data:" << endl;
				test_sort_array.Print();
				cerr << "Resulted data:" << endl;
				file_sort_array.Print();
			}
		}
		return is_test_success;
	}
};

#endif