import sqlite3  # Импортируем библиотеку для работы с SQLite
import json  # Импортируем библиотеку для работы с JSON

class Array:
    def __init__(self, id, array_data):
        self.id = id  # Уникальный идентификатор массива
        self.array_data = array_data  # Данные массива


class Database:
    # Инициализация объекта и установка имени базы данны
    def __init__(self, db_name='my_db.db'):
        self.database = db_name
        self.init_db()

    # Метод для получения соединения с базой данных
    def get_connection(self):
        conn = sqlite3.connect(self.database)  # Устанавливаем соединение с базой данных
        conn.row_factory = sqlite3.Row  # Устанавливаем фабрику строк для получения данных в виде словаря, чтобы обращаться по именам столбцов

        return conn  # Возвращаем соединение

    # Метод, который выполняет конкретную задачу по созданию таблицы в базе данных.
    def init_db(self):
        conn = self.get_connection()  # Получаем соединение

        # Создаем таблицу, если она не существует
        conn.execute('''
            CREATE TABLE IF NOT EXISTS arrays (
                id INTEGER PRIMARY KEY AUTOINCREMENT,  
                array_data TEXT NOT NULL  
            )
        ''')
        conn.commit()
        conn.close()

    # Метод для добавления нового массива в базу данных
    def add_array(self, array_data):
        json_data = json.dumps(array_data)  # Сохраняем массив как JSON
        conn = self.get_connection()  # Получаем соединение

        # Вставляем данные в таблицу
        conn.execute('INSERT INTO arrays (array_data) VALUES (?)', (json_data,))

        conn.commit()
        conn.close()

    # Метод для получения всех массивов из базы данных
    def get_all_arrays(self):
        conn = self.get_connection()

        arrays = conn.execute('SELECT * FROM arrays').fetchall()  # Получаем все массивы
        conn.close()

        # Создаем объекты Array из полученных данных и возвращаем их
        return [Array(array['id'], json.loads(array['array_data'])) for array in arrays]

    # Метод для получения массива по его идентификатору
    def get_array_by_id(self, array_id):
        conn = self.get_connection()
        array = conn.execute('SELECT * FROM arrays WHERE id = ?', (array_id,)).fetchone()  # Получаем массив по ID
        conn.close()

        # Возвращаем объект Array, если массив найден, иначе возвращаем None
        return Array(array['id'], json.loads(array['array_data'])) if array else None

    # Метод для обновления массива по его идентификатору
    def update_array(self, array_id, array_data):
        json_data = json.dumps(array_data)  # Сохраняем массив как JSON
        conn = self.get_connection()

        # Обновляем данные в таблице по ID
        conn.execute('UPDATE arrays SET array_data = ? WHERE id = ?', (json_data, array_id))
        conn.commit()
        conn.close()

    # Метод для удаления массива по его идентификатору
    def delete_array(self, array_id):
        conn = self.get_connection()

        # Удаляем массив из таблицы по ID
        conn.execute('DELETE FROM arrays WHERE id = ?', (array_id,))
        conn.commit()
        conn.close()
