#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>

#include "SortArray.h"

bool IsFileNameValid(const std::string &file_name);
std::string GetValidFileName(void);
bool FileExists(const std::string &file_name);
void SaveListToFile(const string& file_address, std::string export_string);
void ReadOriginalListFromFile(const string& file_address, SortArray& sort_array);

#endif