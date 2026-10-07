from flask import Flask
from flask import render_template
from flask import request
import sqlite3

app = Flask(__name__)



@app.route('/')
def index():
    return 'index'

@app.route('/info', methods = ["GET", "POST"])
def info():
    connection = sqlite3.connect("arduinoData.db", check_same_thread=False)
    cursor = connection.cursor()    
    getData = request.args.get("getData", "(not provided)")
    event = request.args.get("getData")
    print("event: ", getData)

    # data2 = request.json
    # usingData = data2["val"]
    # print(getData)

    # return getData
    print("Arguments:", request.args)
    print("getData:", request.args.get("getData"))
    print(getData)
    if getData != None:
        arduinoData = getData
        print("updated:", arduinoData)

    cursor.execute(
        "INSERT INTO motion_detection (event) VALUES (?)",
        (event,)
    )
    connection.commit()

    connection.close()
    return render_template(
        'info.html',
        title="Info",
        arduinoData = arduinoData
        )

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
