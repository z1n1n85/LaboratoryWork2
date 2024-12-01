from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

arrays = []

@app.route('/')
def main_page():
    return render_template('mainPage.html', arrays=arrays)

@app.route('/add', methods=['GET', 'POST'])
def add_array():
    if request.method == 'POST': #проверка метода
        array_data = request.form['array'] #получаем массив

        # Преобразуем строку в список чисел и добавляем в общий список
        array_numbers = [int(num) for num in array_data.split(',')]
        arrays.append(array_numbers)

        return redirect(url_for('main_page')) #перенаправляем на главную
    return render_template('addArray.html')

@app.route('/edit/<int:index>', methods=['GET', 'POST'])
def edit_array(index):
    if request.method == 'POST':
        array_data = request.form['array']
        array_numbers = [int(num) for num in array_data.split(',')]

        arrays[index] = array_numbers  # Обновляем массив по индексу
        return redirect(url_for('main_page'))

    current_array = arrays[index]
    return render_template('editArray.html', current_array=current_array, index=index)

if __name__ == '__main__':
    app.run(debug=True)