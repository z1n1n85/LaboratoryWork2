from flask import Flask, request, redirect, url_for, render_template, flash, jsonify
from db import Database
from sorting import sort_bitonic
import json

app = Flask(__name__)  # Создаем экземпляр приложения Flask
app.secret_key = 'keyyyyyyyyyyyyyyyyyyy'  # Устанавливаем секретный ключ для использования сессий и flash-сообщений

# Создаем экземпляр БД для пользовательских данных
db = Database()
# Создаем экземпляр БД для тестовых данных
db_test = Database('test_db.db')


# Главная страница
@app.route('/')
def main_page():
    arrays = db.get_all_arrays()
    return render_template('mainPage.html', arrays=arrays)


# Страница добавления
@app.route('/add', methods=['GET', 'POST'])
def add_array():

    # Обрабатываем запрос POST
    if request.method == 'POST':
        array_data = request.form['array']  # Получаем данные массива из формы

        # Сохраняем массив, обрабатываем ошибки
        try:
            number_array = list(map(int, array_data.split()))  # Преобразуем строку в список целых чисел
            db.add_array(number_array)
            flash('Массив успешно добавлен!', 'success')

        except ValueError:
            flash('Ошибка: убедитесь, что вы ввели только числа, разделенные пробелами.', 'error')

        return redirect(url_for('main_page'))

    # Выполянем запрос GET
    return render_template('addArray.html')


# Редактирование
@app.route('/edit/<int:index>', methods=['GET', 'POST'])
def edit_array(index):
    current_array = db.get_array_by_id(index)  # Получаем текущий массив по его индексу

    # Проверяем, существует ли массив
    if not current_array:
        flash('Массив не найден!', 'error')
        return redirect(url_for('main_page'))

    # Обрабатываем POST-запрос
    if request.method == 'POST':

        # Удаление массива
        if 'delete' in request.form:
            db.delete_array(index)
            flash('Массив успешно удален!', 'success')
            return redirect(url_for('main_page'))

        # Сортировка массива
        if 'sort' in request.form:
            array_data = request.form['array']  # Получаем введенные данные

            try:
                # Пробуем преобразовать строку в список целых чисел
                number_array = list(map(int, array_data.split()))
                sorted_array = sort_bitonic(number_array)  # Сортируем массив с помощью битонной сортировки
                db.update_array(index, sorted_array)  # Обновляем данные
                flash('Массив успешно отсортирован!', 'success')
                return redirect(url_for('edit_array', index=index))

            except ValueError:
                flash('Ошибка: убедитесь, что вы ввели только числа, разделенные пробелами.', 'error')
                # Возвращаем пользователя на страницу редактирования с введёнными данными
                return render_template('editArray.html', index=index, current_array=array_data)

        # Получаем новые данные массива из формы
        new_data = request.form['array']

        # Сохраняем массив, обрабатываем ошибки
        try:
            number_array = list(map(int, new_data.split()))  # Преобразуем строку в список целых чисел
            db.update_array(index, number_array)
            flash('Массив успешно обновлен!', 'success')
        except ValueError:
            flash('Ошибка: убедитесь, что вы ввели только числа, разделенные пробелами.', 'error')

        return redirect(url_for('main_page'))

    # Преобразуем массив в строку для отображения в форме
    array_string = ' '.join(map(str, current_array.array_data))

    # GET запрос, текущий массив на шаблон редактирования отправляем
    return render_template('editArray.html', current_array=array_string)


# Добавление записей в тесте
@app.route('/test-add', methods=['POST'])
def test_add_array():

    array_data = request.json  # Получаем данные массива из формы
    # Сохраняем массив, обрабатываем ошибки
    try:
        db_test.add_array(array_data)
        return jsonify({"status": "success"}), 201

    except ValueError:
        return jsonify({"status": "error"}), 400


# Удаление всех записей из тестовой БД
@app.route('/test-delete-all', methods=['POST'])
def test_delete_all():
    arrays = db_test.get_all_arrays()

    for array in arrays:
        db_test.delete_array(array.id)

    return jsonify({"status": "success"}), 201


# Сортировка всех записей из тестовой БД
@app.route('/test-sort-all', methods=['POST'])
def test_sort_all():
    arrays = db_test.get_all_arrays()

    for array in arrays:
        sorted_array = sort_bitonic(array.array_data)  # Сортируем массив с помощью битонной сортировки
        db_test.update_array(array.id, sorted_array)  # Обновляем данные

    return jsonify({"status": "success"}), 201

if __name__ == '__main__':
    app.run(debug=True)
