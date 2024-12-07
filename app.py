from flask import Flask, request, redirect, url_for, render_template, flash
from db import Database
import json

app = Flask(__name__)
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

        # Преобразуем строку в массив целых чисел
        try:
            number_array = list(map(int, array_data.split()))
            db.add_array(number_array)  # Добавляем массив в базу данных

            flash('Массив успешно добавлен!', 'success')  # Уведомление об успешном добавлении
        except ValueError:
            flash('Ошибка: убедитесь, что вы ввели только числа, разделенные пробелами.', 'error')

        return redirect(url_for('main_page'))  # Перенаправляем на главную страницу

    return render_template('addArray.html')

@app.route('/edit/<int:index>', methods=['GET', 'POST'])
def edit_array(index):
    current_array = db.get_array_by_id(index)  #Получаем массив по индексу

    if not current_array:
        flash('Массив не найден!', 'error')  # Уведомление об ошибке
        return redirect(url_for('main_page'))

    if request.method == 'POST':
        new_data = request.form['array']
        try:
            number_array = list(map(int, new_data.split()))
            db.update_array(index, number_array)

            flash('Массив успешно обновлен!', 'success')  # Уведомление об успешном обновлении
        except ValueError:
            flash('Ошибка: убедитесь, что вы ввели только числа, разделенные пробелами.', 'error')

        return redirect(url_for('main_page'))

    # Преобразуем массив в строку для отображения в окне
    array_string = ' '.join(map(str, current_array.array_data))
    return render_template('editArray.html', current_array=array_string)

if __name__ == '__main__':  # Исправлено: __name__ вместо name
    app.run(debug=True)
