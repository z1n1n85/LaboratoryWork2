#include "fileManager.h"

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>
#include <errno.h>
#include <stdexcept>
#include <memory>

#include "SortArray.h"
#include "Errors.h"
#include "consts.h"
#include "validInput.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::regex;

bool IsFileNameValid(const string& file_address) {
	string lower_cased_address = file_address;
	for (auto& x : lower_cased_address) {
		x = (char)tolower(x);
	}
	std::size_t pos = lower_cased_address.find_last_of("\\");
	string file_path = "";
	string file_name = "";
	if (pos != string::npos)
	{
		file_name = lower_cased_address.substr(pos + 1);
	}
	else { file_name = lower_cased_address; }
	regex FileNameRegex("[^/:*?\"<>|]+.txt");
	regex FileNameReservedNames("(con|prn|aux|nul|com[1-9]|lpt[1-9]).txt");
	if (!regex_match(file_name, FileNameRegex)) {
		cerr << "Error validating the file address: Invalid file name." << endl;
		return false;
	}
	if (regex_match(file_name, FileNameReservedNames)) {
		cerr << "Error validating the file address: Invalid file name. Using reserved filenames is prohibited!" << endl;
		return false;
	}
	return true;
}
string GetValidFileName(void) {
	string file_address = "";
	cin >> file_address;
	while (!IsFileNameValid(file_address)) {
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cerr << "Try again" << endl << "> ";
		cin >> file_address;
	}
	return file_address;
}
bool FileExists(const string& file_address) {
	std::ifstream file(file_address);
	return file.is_open();
}
void SaveListToFile(const string& file_address, std::string export_string) {
	std::ofstream write_file;
	write_file.open(file_address, std::ios::out);
	if (write_file.is_open()) {
		write_file << export_string;
		write_file.close();
	}
	else if (write_file.bad()) {
		throw IncorrectAccessFile("Unknown error");
	}
	else if (write_file.fail()) {
		char errmsg[ERR_STR_LEN];
		strerror_s(errmsg, ERR_STR_LEN, errno);
		throw IncorrectAccessFile(errmsg);
	}
}
void ReadOriginalListFromFile(const string &file_address, SortArray &sort_array) {
	string line;
	std::ifstream read_file;
	read_file.open(file_address);
	if (read_file.is_open()) {
		sort_array.Clear();
		double number = 0.0;
		while (std::getline(read_file, line)) {
			try {
				number = std::stod(line);
				sort_array.Add(number);
			}
			catch (std::invalid_argument const& ex) {
				throw IncorrectSortArrayException(ex.what());
			}
			catch (std::out_of_range const& ex) {
				throw IncorrectSortArrayException(ex.what());
			}
		}
		read_file.close();
	}
	else {
		throw IncorrectAccessFile("The file could not be opened!");
	}
}