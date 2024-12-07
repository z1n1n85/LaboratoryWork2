import sqlite3
import json

class Array:
    def __init__(self, id, array_data):
        self.id = id
        self.array_data = array_data

class Database:
    def __init__(self, db_name='my_db.db'):
        self.database = db_name
        self.init_db()

    def get_connection(self):
        conn = sqlite3.connect(self.database)
        conn.row_factory = sqlite3.Row
        return conn

    def init_db(self):
        conn = self.get_connection()
        conn.execute('''
            CREATE TABLE IF NOT EXISTS arrays (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                array_data TEXT NOT NULL
            )
        ''')
        conn.commit()
        conn.close()

    def add_array(self, array_data):
        json_data = json.dumps(array_data)  # Сохраняем массив как JSON
        conn = self.get_connection()
        conn.execute('INSERT INTO arrays (array_data) VALUES (?)', (json_data,))
        conn.commit()
        conn.close()

    def get_all_arrays(self):
        conn = self.get_connection()
        arrays = conn.execute('SELECT * FROM arrays').fetchall()
        conn.close()
        return [Array(array['id'], json.loads(array['array_data'])) for array in arrays]  # Создание объектов Array

    def get_array_by_id(self, array_id):
        conn = self.get_connection()
        array = conn.execute('SELECT * FROM arrays WHERE id = ?', (array_id,)).fetchone()
        conn.close()
        return Array(array['id'], json.loads(array['array_data'])) if array else None  # Возвращаем объект Array

    def update_array(self, array_id, array_data):
        json_data = json.dumps(array_data)  # Сохраняем массив как JSON
        conn = self.get_connection()
        conn.execute('UPDATE arrays SET array_data = ? WHERE id = ?', (json_data, array_id))
        conn.commit()
        conn.close()

    def delete_array(self, array_id):
        conn = self.get_connection()
        conn.execute('DELETE FROM arrays WHERE id = ?', (array_id,))
        conn.commit()
        conn.close()
