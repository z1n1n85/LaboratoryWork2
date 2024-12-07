def bitonic_merge(arr, start_index, count_elem_sorting, order):
    if count_elem_sorting > 1:
        middle_arr = count_elem_sorting // 2
        for i in range(start_index, start_index + middle_arr):
            for j in range(i + middle_arr, start_index + count_elem_sorting):
                if (order and arr[i] > arr[j]) or (not order and arr[i] < arr[j]):
                    arr[i], arr[j] = arr[j], arr[i]

        bitonic_merge(arr, start_index, middle_arr, order)  # Рекурсивно сливаем левую подпоследовательность
        bitonic_merge(arr, start_index + middle_arr, count_elem_sorting - middle_arr,order)  # Рекурсивно сливаем правую подпоследовательность


def bitonic_sort(arr, start_index, count_elem_sorting, order):
    if count_elem_sorting > 1:
        middle_arr = count_elem_sorting // 2

        bitonic_sort(arr, start_index, middle_arr, True)  # Сортируем левую подпоследовательность в порядке возрастания
        bitonic_sort(arr, start_index + middle_arr, count_elem_sorting - middle_arr,False)  # Сортируем правую подпоследовательность в порядке убывания

        bitonic_merge(arr, start_index, count_elem_sorting, order)  # Сливаем две отсортированные подпоследовательности


def sort_bitonic(arr):
    bitonic_sort(arr, 0, len(arr), True)  # Сортируем весь массив в порядке возрастания
    return arr
