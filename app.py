from flask import Flask, request, redirect, url_for, render_template, g
import sqlite3
from db import DatabaseManager
import json

app = Flask(__name__)

DATABASE = 'my_db.db'

def get_db():
    if 'db_manager' not in g:
        g.db_manager = DatabaseManager(DATABASE)  # Создаем новый экземпляр DatabaseManager
    return g.db_manager

@app.route('/')
def main_page():
    db_manager = get_db()  # Получаем экземпляр DatabaseManager
    arrays = db_manager.get_all_arrays()  # Получаем все массивы
    return render_template('mainPage.html', arrays=arrays)

@app.route('/add', methods=['GET', 'POST'])
def add_array():
    db_manager = get_db()  # Получаем экземпляр DatabaseManager
    if request.method == 'POST':
        try:
            new_array = json.loads(request.form['array'])  # Десериализация JSON из формы

            print(f"Получен массив: {new_array}")  # Отладочный вывод

            # Проверка на то, что новый массив действительно является списком
            if not isinstance(new_array, list):
                raise ValueError("Введенный массив должен быть списком.")

            is_sorted = request.form.get('is_sorted') == 'true'  # Получаем флаг сортировки из формы

            print(f"Флаг сортировки: {is_sorted}")  # Отладочный вывод

            # Сохраняем массив в базе данных
            db_manager.add_array(new_array, is_sorted)
            return redirect(url_for('main_page'))

        except (json.JSONDecodeError, ValueError) as e:
            return render_template('addArray.html', error=str(e))  # Отображаем ошибку пользователю

    return render_template('addArray.html')

@app.route('/edit/<int:index>', methods=['GET', 'POST'])
def edit_array(index):
    db_manager = get_db()  # Получаем экземпляр DatabaseManager
    current_array = db_manager.get_array_by_id(index)  # Получаем текущий массив из базы данных

    if current_array is None:
        return "Массив не найден", 404  # Обработка случая, если массив не найден

    # Получаем текущее состояние сортировки
    is_sorted = db_manager.is_array_sorted(index)  # Предполагается, что у вас есть метод для получения этого значения

    if request.method == 'POST':
        try:
            array_data = json.loads(request.form['array'])  # Десериализация JSON из формы
            is_sorted = request.form.get('is_sorted', 'false') == 'true'  # Получаем флаг сортировки из формы

            # Сохраняем новый массив в базу данных
            db_manager.update_array(index, array_data, is_sorted)  # Используем метод из DatabaseManager
            return redirect(url_for('main_page'))

        except json.JSONDecodeError:
            return render_template('editArray.html', current_array=current_array, is_sorted=is_sorted, error="Неверный формат массива. Пожалуйста, введите корректный JSON.")

    return render_template('editArray.html', current_array=current_array, is_sorted=is_sorted)  # Передаем текущий массив и флаг сортировки в шаблон

@app.teardown_appcontext
def close_db(exception):
    db_manager = g.pop('db_manager', None)  # Удаляем db_manager из контекста приложения
    if db_manager is not None:
        db_manager.close()  # Закрываем соединение с базой данных

if __name__ == '__main__':
    app.run(debug=True)