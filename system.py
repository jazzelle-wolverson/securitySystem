from flask import Flask
from flask import render_template
import serial

app = Flask(__name__)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

@app.route('/')
def index():
    return 'index'

@app.route('/info', methods = ["POST"])
def info():
    data = request.json
    print(data)
    return data

@app.route('/hello/')

@app.route('/hello/<name>')
def hello(name="test"):
    return render_template('/hello/', person=name)