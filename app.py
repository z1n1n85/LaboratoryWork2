from flask import Flask, render_template

app = Flask(__name__)


@app.route("/")
def mainPage():
    return render_template('mainPage.html')


@app.route("/addArr")
def addArr():
    return render_template('addArray.html')


@app.route("/editArr")
def editArr():
    return render_template('editArray.html')

if __name__ == '__main__':
    app.run(debug=True)



