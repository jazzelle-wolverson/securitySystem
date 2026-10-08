from flask import Flask, render_template, request
import sqlite3
from datetime import datetime

app = Flask(__name__)

@app.route('/')
def index():
    return render_template(
        'index.html'
    )

@app.route('/dashboard')
def dashboard():
    return render_template(
        'dashboard.html'
    )

@app.route('/info', methods = ["GET", "POST"])
def info():
    connection = sqlite3.connect("arduinoData.db", check_same_thread=False)
    cursor = connection.cursor()    
    getData = request.args.get("getData", "(not provided)")
    motion = request.args.get("getData")
    timestamp = datetime.now().strftime("%d/%m/%Y, %H:%M:%S")

    # i need to create a list of motion and timestamps and then pass that varible
    # in through render_template to do my for each loop for my polling

    print("motion: ", getData)
    print("timestamp: ", timestamp)

    cursor.execute(
        "INSERT INTO motion_detection (motion, timestamp) VALUES (?, ?)",
        (motion, timestamp)
    )

    connection.commit()

    connection.close()
    return render_template(
        'info.html',
        title="Info",
        getData = getData,
        timestamp=timestamp,
        motion = motion
        )

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
