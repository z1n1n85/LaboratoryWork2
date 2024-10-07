#include "test.h"

#include <vector>
#include <string>

#include "TestData.h"
#include "ui.h"

using std::vector;

bool InitTests(void) {
	vector<double> test_list_1;
	test_list_1.push_back(1.0);
	test_list_1.push_back(1.2);
	test_list_1.push_back(1.3);
	test_list_1.push_back(1.8);
	TestData test_data_1("TestData\\1.txt", test_list_1);

	vector<double> test_list_2;
	test_list_2.push_back(3);
	test_list_2.push_back(4);
	test_list_2.push_back(5);
	TestData test_data_2("TestData\\2.txt", test_list_2);

	vector<double> test_list_3;
	test_list_3.push_back(1.2);
	test_list_3.push_back(1.3);
	test_list_3.push_back(10.0);
	TestData test_data_3("TestData\\3.txt", test_list_3);

	return test_data_1.InitTest() &&
		test_data_2.InitTest() &&
		test_data_3.InitTest();
}