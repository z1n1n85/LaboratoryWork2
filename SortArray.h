#ifndef SORT_ARRAY_H
#define SORT_ARRAY_H

#include <iostream>
#include <string>
#include <vector>

#include "sorting.h"

using std::move;
using std::vector;
using std::string;
using std::to_string;
using std::cout;
using std::endl;

class SortArray {
private:
	vector<double> list;
public:
	SortArray(void) = default;
	void Clear(void) { list.clear(); }
	bool IsEmpty(void) { return list.size() == 0; }
	void Set(vector<double> new_list) {
		list = new_list;
	}
	void Add(double item) {
		list.push_back(item);
	}
	void Print(void) const {
		for (int i = 0; i < list.size(); i++) {
			cout << to_string(i + 1) << ") " << list[i] << endl;
		}
	}
	void Sorting(void) {
		BitonicSort(list, 0, list.size(), true);
	}
	string GetExportData(void) const {
		string save_list;
		for (int i = 0; i < list.size(); i++) {
			save_list.append(to_string(list[i]) + "\n");
		}
		return save_list;
	}
};

#endif