import requests
import random
import time
import unittest

BASE_URL = "http://127.0.0.1:5000"

def generate_random_array():
    size = random.randint(1, 100)  # Генерируем случайный размер массива
    return [random.randint(1, 1000) for _ in range(size)]  # Генерируем случайные числа

def add_multiple_arrays(self, num_arrays):
    start_time = time.time()
    success_count = 0
    failure_count = 0

    for _ in range(num_arrays):
        array_data = generate_random_array()
        response = requests.post(BASE_URL + '/test-add', json=array_data)
        if response.status_code == 201:
            success_count += 1
        else:
            failure_count += 1

    end_time = time.time()
    elapsed_time = end_time - start_time

    print(f"Успешно добавлено массивов: {success_count}")
    print(f"Неудачных попыток: {failure_count}")
    print(f"Время выполнения: {elapsed_time:.2f} секунд")

    # Проверка успешного выполнения
    self.assertEqual(failure_count, 0, "Не все массивы были успешно добавлены.")

def sort_all_arrays(num_arrays):
    start_time = time.time()
    response = requests.post(BASE_URL + '/test-sort-all')
    end_time = time.time()
    elapsed_time = end_time - start_time
    if response.status_code == 201:
        print(f"Добавленные массивы успешно отсортированы за {elapsed_time:.2f} секунд")
        print(f"Среднее время: {elapsed_time/num_arrays:.2f} секунд")
    else:
        print(f"Добавленные массивы не удалось отсортирвоать за {elapsed_time:.2f} секунд")

def delete_all_arrays():
    start_time = time.time()
    response = requests.post(BASE_URL + '/test-delete-all')
    end_time = time.time()
    elapsed_time = end_time - start_time
    if response.status_code == 201:
        print(f"Тестовая БД успешно очищена от тестовых данных за {elapsed_time:.2f} секунд")
    else:
        print(f"Не удалось очистить тестовую БД за {elapsed_time:.2f} секунд")

class Test100(unittest.TestCase):
    def test_1_add(self):
        add_multiple_arrays(self, 100)

    def test_2_sort(self):
        sort_all_arrays(100)

    def test_3_delete(self):
        delete_all_arrays()


class Test1000(unittest.TestCase):
    def test_1_add(self):
        add_multiple_arrays(self, 1000)

    def test_2_sort(self):
        sort_all_arrays(1000)

    def test_3_delete(self):
        delete_all_arrays()


# class Test10000(unittest.TestCase):
#     def test_1_add(self):
#         add_multiple_arrays(self, 10000)
#
#     def test_2_sort(self):
#         sort_all_arrays(10000)
#
#     def test_3_delete(self):
#         delete_all_arrays()

if __name__ == "__main__":
    unittest.main()
