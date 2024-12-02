import sqlite3
import json

class DatabaseManager:
    # Инициализации класса, получаем ссылку на текущий экземпляр обьекта и путь к файлу бд
    def __init__(self, path):
        self.conn = sqlite3.connect(path) #устанавливаем соединение с бд(открытие, создание по указанному пути). Результат соединения сохраняется в self.conn.
        self.conn.execute('PRAGMA foreign_keys = ON') #включаем поддержку внешниx ключей
        self.cur = self.conn.cursor() #создаем обьект курсора(команды SELECT, INSERT, UPDATE...)
        self.create_tables() #вызываем создание таблицы


    # Выполнениe запроса: получаем текущий экземпляр класса, строку SQL запрос, параметр для значений который могут быть переданы доп
    def query(self, sql, params=()):
        cursor = self.conn.cursor()
        cursor.execute(sql, params)
        self.conn.commit()
        return cursor


    # Создание таблицы для хранения массивов
    def create_tables(self):
        self.query('''
                    CREATE TABLE IF NOT EXISTS Arrays (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        array_data TEXT NOT NULL,
                        is_sorted BOOLEAN NOT NULL
                    )
                ''')


    # Добавление массива в бд: получаем текущий экземпляр класса, данные массива и флаг сортировки
    def add_array(self, array_data,is_sorted):
        json_data = json.dumps(array_data)  # cериализация в JSON

        print(f"Добавляем массив: {json_data}, отсортирован: {is_sorted}")  # Отладочный вывод

        self.query('INSERT INTO Arrays (array_data, is_sorted) VALUES (?, ?)', (json_data, is_sorted))


    # Получение всех массивов из бд
    def get_all_arrays(self):
        self.query('SELECT * FROM Arrays')
        rows = self.cur.fetchall()

        return [(row[0], json.loads(row[1]), row[2]) for row in rows]  # десериализация JSON


    # Получение массива по ID
    def get_array_by_id(self, array_id):
        self.query('SELECT * FROM Arrays WHERE id = ?', (array_id,))
        row = self.cur.fetchone()

        return (row[0], json.loads(row[1]), row[2]) if row else None  # десериализация JSON


    # Обновление массива по ID
    def update_array(self, array_id, new_array_data, is_sorted):
        json_data = json.dumps(new_array_data)  # сериализация в JSON
        self.query('UPDATE Arrays SET array_data = ?, is_sorted = ? WHERE id = ?',
                   (json_data, is_sorted, array_id))


    # Удаление массива по ID
    def delete_array(self, array_id):
        self.query('DELETE FROM Arrays WHERE id = ?', (array_id,))

    def close(self):
        self.conn.close()

