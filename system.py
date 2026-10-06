from flask import Flask
from flask import render_template
from flask import request

app = Flask(__name__)

@app.route('/')
def index():
    return 'index'

@app.route('/info', methods = ["GET", "POST"])
def info():
    info = request.args.get("/info", "(not provided)")
    # data2 = request.json
    # usingData = data2["val"]
    print(info)

    return info

@app.route('/hello/<name>')
def hello(name="test"):
    return render_template('/hello/', person=name)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
