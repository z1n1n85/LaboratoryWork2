#include "test.h"

#include <vector>
#include <memory>

#include "DocumentData.h"
#include "Document.h"
#include "Mail.h"
#include "TestData.h"
#include "ui.h"

using std::vector;

bool InitTests(void) {
	vector<std::unique_ptr<Document>> test_list_1;
	test_list_1.push_back(std::make_unique<Document>("a", "a", 1, "a"));
	test_list_1.push_back(std::make_unique<Document>("b", "b", 2, "b"));
	test_list_1.push_back(std::make_unique<Document>("c", "c", 3, "c"));
	TestData test_data_1("TestData\\1.txt", std::move(test_list_1));

	vector<std::unique_ptr<Document>> test_list_2;
	test_list_2.push_back(std::make_unique<Mail>("d", "d", 4, "d", "d", 0));
	test_list_2.push_back(std::make_unique<Document>("e", "e", 5, "e e e e e"));
	test_list_2.push_back(std::make_unique<Mail>("f", "f", 6, "f", "f", 100));
	TestData test_data_2("TestData\\2.txt", std::move(test_list_2));

	vector<std::unique_ptr<Document>> test_list_3;
	test_list_3.push_back(std::make_unique<Document>("g", "g", 7, "g"));
	test_list_3.push_back(std::make_unique<Mail>("h h", "h", 8, "h", "h", 10));
	test_list_3.push_back(std::make_unique<Document>("i", "i", 9, "i"));
	TestData test_data_3("TestData\\3.txt", std::move(test_list_3));

	vector<std::unique_ptr<Document>> test_list_4;
	test_list_4.push_back(std::make_unique<Mail>("j", "j", 10, "j", "j", 9));
	test_list_4.push_back(std::make_unique<Mail>("k", "k", 11, "k", "k", 9));
	test_list_4.push_back(std::make_unique<Mail>("l", "l", 12, "l", "l", 9));
	TestData test_data_4("TestData\\4.txt", std::move(test_list_4));

	vector<std::unique_ptr<Document>> test_list_5;
	test_list_5.push_back(std::make_unique<Mail>("m", "m", 13, "m", "m", 1));
	test_list_5.push_back(std::make_unique<Document>("n", "n", 14, "n"));
	test_list_5.push_back(std::make_unique<Document>("o", "o", 15, "o"));
	TestData test_data_5("TestData\\5.txt", std::move(test_list_5));

	return test_data_1.InitTest() &&
		test_data_2.InitTest() &&
		test_data_3.InitTest() &&
		test_data_4.InitTest() &&
		test_data_5.InitTest();
}