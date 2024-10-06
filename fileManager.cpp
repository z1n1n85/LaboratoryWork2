#include "fileManager.h"

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>
#include <errno.h>
#include <stdexcept>
#include <memory>

#include "DocumentData.h"
#include "Document.h"
#include "Mail.h"
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
void ReadOriginalListFromFile(const string &file_address, DocumentData &document_data) {
	enum SettingOrder {
		TYPE = 0,
		TITLE,
		AUTHOR,
		DEPARTMENT_NUMBER,
		CONTENT,
		ADDRESSE,
		PROJECT_NUMBER,
		ADD_DOCUMENT,
	};
	string line;
	std::ifstream read_file;
	read_file.open(file_address);
	if (read_file.is_open()) {
		document_data.ClearList();
		int param_num = 0;
		string type;
		string title;
		string author;
		int department_number = 0;
		string content;
		string addresse;
		int project_number = 0;
		while (std::getline(read_file, line)) {
			try {
				switch (param_num++) {
				case TYPE: {
					type = line;
					if (type != "MAIL" && type != "DOCUMENT") {
						throw IncorrectDocumentException("The document type is incorrect or not specified!");
					}
					break;
				}
				case TITLE: { title = line; break; }
				case AUTHOR: { author = line; break; }
				case DEPARTMENT_NUMBER: { department_number = std::stoi(line); break; }
				case CONTENT: { content = line; break; }
				case ADDRESSE: {
					if (type == "MAIL") {
						addresse = line;
						break;
					}
					else { [[fallthrough]]; }
				}
				case PROJECT_NUMBER: {
					if (type == "MAIL") {
						project_number = std::stoi(line);
						break;
					}
					else { [[fallthrough]]; }
				}
				case ADD_DOCUMENT: {
					if (type == "MAIL") {
						document_data.AddDocument(std::make_unique<Mail>(title, author,
							department_number, content, addresse, project_number));
					}
					else {
						document_data.AddDocument(std::make_unique<Document>(title, author,
							department_number, content));
					}
					param_num = 0;
					break;
				}
				}
			}
			catch (std::invalid_argument const& ex) {
				throw IncorrectDocumentException(ex.what());
			}
			catch (std::out_of_range const& ex) {
				throw IncorrectDocumentException(ex.what());
			}
		}
		read_file.close();
	}
	else {
		throw IncorrectAccessFile("The file could not be opened!");
	}
}