from flask import Flask
from flask import render_template
from flask import request

app = Flask(__name__)

@app.route('/')
def index():
    return 'index'

@app.route('/info', methods = ["GET"])
def info():
    getData = request.args.get("val")
    # data2 = request.json
    # usingData = data2["val"]
    # print(getData)

    # return getData
    return render_template(
        'info.html',
        title="Info",
        arduinoData = getData
        )

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
