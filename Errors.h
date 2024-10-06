#ifndef ERROR_H
#define ERROR_H

#include <string>

using std::string;

// Error handling for creating a Document object
class IncorrectDocumentException {
public:
	string message = "";
	IncorrectDocumentException(void) = default;
	IncorrectDocumentException(string message) {
		this->message = message;
	};
};
// Error handling when working with files
class IncorrectAccessFile {
public:
	string message = "";
	IncorrectAccessFile(void) = default;
	IncorrectAccessFile(string message) {
		this->message = message;
	};
};

#endif
