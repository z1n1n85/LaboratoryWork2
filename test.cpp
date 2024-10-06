#include "test.h"

#include <vector>
#include <memory>
#include <string>

#include "DocumentData.h"
#include "Document.h"
#include "Mail.h"
#include "TestData.h"
#include "ui.h"

using std::vector;

bool InitTests(void) {
	vector<std::unique_ptr<double>> test_list_1;
	test_list_1.push_back(std::make_unique<double>(1.0));
	test_list_1.push_back(std::make_unique<double>(1.2));
	test_list_1.push_back(std::make_unique<double>(3.4));
	TestData test_data_1("TestData\\1.txt", std::move(test_list_1));

	vector<std::unique_ptr<double>> test_list_2;
	test_list_1.push_back(std::make_unique<double>(1.0));
	test_list_1.push_back(std::make_unique<double>(1.2));
	test_list_1.push_back(std::make_unique<double>(3.4));
	TestData test_data_2("TestData\\2.txt", std::move(test_list_2));

	vector<std::unique_ptr<double>> test_list_3;
	test_list_1.push_back(std::make_unique<double>(1.0));
	test_list_1.push_back(std::make_unique<double>(1.2));
	test_list_1.push_back(std::make_unique<double>(3.4));
	TestData test_data_3("TestData\\3.txt", std::move(test_list_3));

	vector<std::unique_ptr<double>> test_list_4;
	test_list_1.push_back(std::make_unique<double>(1.0));
	test_list_1.push_back(std::make_unique<double>(1.2));
	test_list_1.push_back(std::make_unique<double>(3.4));
	TestData test_data_4("TestData\\4.txt", std::move(test_list_4));

	vector<std::unique_ptr<double>> test_list_5;
	test_list_1.push_back(std::make_unique<double>(1.0));
	test_list_1.push_back(std::make_unique<double>(1.2));
	test_list_1.push_back(std::make_unique<double>(3.4));
	TestData test_data_5("TestData\\5.txt", std::move(test_list_5));

	return test_data_1.InitTest() &&
		test_data_2.InitTest() &&
		test_data_3.InitTest() &&
		test_data_4.InitTest() &&
		test_data_5.InitTest();
}