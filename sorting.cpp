#include "sorting.h"

#include <vector>

using namespace std;

// ������� ��� ������� ���� ����������������������
void BitonicMerge(vector<double>& arr, int start_index, int count_elem_sorting, bool order) {
    //���� ���������� ����������� ��������� �� ������ 1,�� ������ ������������, ������� ��������� ����������
    if (count_elem_sorting > 1) {
        // ������ �������� ������������������, �� ���� ������ ����� ������������������
        int middle_arr = count_elem_sorting / 2;
        // �������� �� ��������� ������ ���������������������
        for (int i = start_index; i < start_index + middle_arr; i++) {
            // �������� �� ��������� ������ ���������������������
            for (int j = i + middle_arr; j < start_index + count_elem_sorting; j++) {
                // ���� ��������� ���������� � ������� �����������
                if (order) {
                    if (arr[i] > arr[j]) {
                        swap(arr[i], arr[j]);
                    }
                }
                // ���� ��������� ���������� � ������� ��������
                else {
                    if (arr[i] < arr[j]) {
                        swap(arr[i], arr[j]);
                    }
                }
            }
        }
        BitonicMerge(arr, start_index, middle_arr, order);  // ���������� ������� ����� ���������������������
        BitonicMerge(arr, start_index + middle_arr, count_elem_sorting - middle_arr, order);  // ���������� ������� ������ ���������������������
    }
}

// ������� ��� ���������� ������� ������� �������� ����������
void BitonicSort(vector<double>& arr, int start_index, int count_elem_sorting, bool order) {
    //���� ���������� ����������� ��������� �� ������ 1,�� ������ ������������, ������� ��������� ����������
    if (count_elem_sorting > 1) {
        // ������ �������� ������������������, �� ���� ������ ����� ������������������
        int middle_arr = count_elem_sorting / 2;
        // ���������� ��������� ����� ��������������������� � ������� �����������
        BitonicSort(arr, start_index, middle_arr, true);
        // ���������� ��������� ������ ��������������������� � ������� ��������
        BitonicSort(arr, start_index + middle_arr, count_elem_sorting - middle_arr, false);
        // ������� ��� ��������������� ���������������������
        BitonicMerge(arr, start_index, count_elem_sorting, order);
    }
}