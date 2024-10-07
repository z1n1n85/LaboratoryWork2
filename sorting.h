#ifndef SORTING_H
#define SORTING_H

#include <vector>

void BitonicMerge(std::vector<double>& arr, int start_index, int count_elem_sorting, bool order);
void BitonicSort(std::vector<double>& arr, int start_index, int count_elem_sorting, bool order);

#endif