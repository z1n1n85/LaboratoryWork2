#ifndef ERROR_H
#define ERROR_H

#include <string>

using std::string;

// Error handling for creating a SortArray
class IncorrectSortArrayException {
public:
	string message = "";
	IncorrectSortArrayException(void) = default;
	IncorrectSortArrayException(string message) {
		this->message = message;
	};
};
class IncorrectAccessFile {
public:
	string message = "";
	IncorrectAccessFile(void) = default;
	IncorrectAccessFile(string message) {
		this->message = message;
	};
};

#endif
