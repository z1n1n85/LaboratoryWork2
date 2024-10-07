#include "sorting.h"

#include <vector>

using namespace std;

// Функция для слияния двух подпоследовательностей
void BitonicMerge(vector<double>& arr, int start_index, int count_elem_sorting, bool order) {
    //Если количество сортируемых элементов не больше 1,то массив отсортирован, функция завершает выполнение
    if (count_elem_sorting > 1) {
        // Индекс середины последовательности, то есть индекс конца последовательности
        int middle_arr = count_elem_sorting / 2;
        // Итерация по элементам первой подпоследовательности
        for (int i = start_index; i < start_index + middle_arr; i++) {
            // Итерация по элементам второй подпоследовательности
            for (int j = i + middle_arr; j < start_index + count_elem_sorting; j++) {
                // Если требуется сортировка в порядке возрастания
                if (order) {
                    if (arr[i] > arr[j]) {
                        swap(arr[i], arr[j]);
                    }
                }
                // Если требуется сортировка в порядке убывания
                else {
                    if (arr[i] < arr[j]) {
                        swap(arr[i], arr[j]);
                    }
                }
            }
        }
        BitonicMerge(arr, start_index, middle_arr, order);  // Рекурсивно сливаем левую подпоследовательность
        BitonicMerge(arr, start_index + middle_arr, count_elem_sorting - middle_arr, order);  // Рекурсивно сливаем правую подпоследовательность
    }
}

// Функция для сортировки массива методом битонной сортировки
void BitonicSort(vector<double>& arr, int start_index, int count_elem_sorting, bool order) {
    //Если количество сортируемых элементов не больше 1,то массив отсортирован, функция завершает выполнение
    if (count_elem_sorting > 1) {
        // Индекс середины последовательности, то есть индекс конца последовательности
        int middle_arr = count_elem_sorting / 2;
        // Рекурсивно сортируем левую подпоследовательность в порядке возрастания
        BitonicSort(arr, start_index, middle_arr, true);
        // Рекурсивно сортируем правую подпоследовательность в порядке убывания
        BitonicSort(arr, start_index + middle_arr, count_elem_sorting - middle_arr, false);
        // Сливаем две отсортированные подпоследовательности
        BitonicMerge(arr, start_index, count_elem_sorting, order);
    }
}