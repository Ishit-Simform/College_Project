import cv2
from flask import Flask, render_template, Response
import numpy as np
import requests

app = Flask(__name__)

URL = "http://192.168.186.203"
cap = cv2.VideoCapture("http://192.168.186.203:81/stream")

def generate_frames():
    requests.get(URL + "/control?var=framesize&val=5")
    while True:        
        frame = cap.read()
        ret, buffer = cv2.imencode('.jpg', frame)
        frame = buffer.tobytes()

        yield (b'--frame\r\n'b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

        key = cv2.waitKey(1) & 0xFF

        if key == ord('q'):
            break

    cv2.destroyAllWindows()
    cap.release()


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/video')
def video():
    return Response(generate_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == "__main__":
    app.run(debug=False)
