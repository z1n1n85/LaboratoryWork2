from flask import Flask, request, redirect, url_for, render_template, flash
import json
from db import Database
from sorting import sort_bitonic

app = Flask(__name__)  # Исправлено на __name__
app.secret_key = 'keyyyyyyyyyyyyyyyyyyy'

# Создаем экземпляр базы данных
db = Database()

@app.route('/')
def main_page():
    arrays = db.get_all_arrays()  # Получаем все массивы из базы данных
    return render_template('mainPage.html', arrays=arrays)

@app.route('/add', methods=['GET', 'POST'])
def add_array():
    if request.method == 'POST':
        array_data = request.form['array']
        try:
            number_array = list(map(int, array_data.split()))
            db.add_array(number_array)  # Просто добавляем массив в базу данных
            flash('Массив успешно добавлен!', 'success')
        except ValueError:
            flash('Ошибка: убедитесь, что вы ввели только числа, разделенные пробелами.', 'error')
        return redirect(url_for('main_page'))
    return render_template('addArray.html')

@app.route('/edit/<int:index>', methods=['GET', 'POST'])
def edit_array(index):
    current_array = db.get_array_by_id(index)

    if not current_array:
        flash('Массив не найден!', 'error')
        return redirect(url_for('main_page'))

    if request.method == 'POST':
        if 'delete' in request.form:
            db.delete_array(index)  # Удаляем массив из базы данных
            flash('Массив успешно удален!', 'success')
            return redirect(url_for('main_page'))  # Перенаправляем на главную страницу

        if 'sort' in request.form:
            sorted_array = sort_bitonic(current_array.array_data)  # Используем битонную сортировку
            db.update_array(index, sorted_array)  # Сохраняем отсортированный массив в базе данных
            flash('Массив успешно отсортирован!', 'success')
            return redirect(url_for('edit_array', index=index))  # Перенаправляем на ту же страницу

        new_data = request.form['array']
        try:
            number_array = list(map(int, new_data.split()))
            db.update_array(index, number_array)
            flash('Массив успешно обновлен!', 'success')
        except ValueError:
            flash('Ошибка: убедитесь, что вы ввели только числа, разделенные пробелами.', 'error')

        return redirect(url_for('main_page'))

    array_string = ' '.join(map(str, current_array.array_data))
    return render_template('editArray.html', current_array=array_string)

@app.route('/sort/<int:index>', methods=['POST'])
def sort_array(index):
    current_array = db.get_array_by_id(index)

    if not current_array:
        flash('Массив не найден!', 'error')
        return redirect(url_for('main_page'))

    sorted_array = sort_bitonic(current_array.array_data)  # Используем битонную сортировку

    db.update_array(index, sorted_array)  # Сохраняем отсортированный массив в базе данных
    flash('Массив успешно отсортирован!', 'success')
    return redirect(url_for('main_page'))

if __name__ == '__main__':  # Исправлено на __name__
    app.run(debug=True)
