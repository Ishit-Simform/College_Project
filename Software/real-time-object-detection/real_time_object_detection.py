from flask import Flask,render_template,Response
from imutils.video import VideoStream
from imutils.video import FPS
import numpy as np
import argparse
import imutils
import time
import cv2

app=Flask(__name__)
CLASSES = ["background", "aeroplane", "bicycle", "bird", "boat",
	"bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
	"dog", "horse", "motorbike", "person", "pottedplant", "sheep",
	"sofa", "train", "tvmonitor"]
COLORS = np.random.uniform(0, 255, size=(len(CLASSES), 3))

print("[INFO] loading model...")
net = cv2.dnn.readNetFromCaffe('MobileNetSSD_deploy.prototxt.txt', 'MobileNetSSD_deploy.caffemodel')
print("[INFO] starting video stream...")

#vs = VideoStream(src=0).start()
vs = VideoStream(src="http://192.168.39.203:81/stream").start()
#vs = cv2.VideoCapture("http://192.168.186.203:81/stream")
time.sleep(5.0)
fps = FPS().start()

def generate_frames():
	while True:		
		frame = vs.read()
		frame = cv2.flip(frame, 0)
		frame = imutils.resize(frame, width=400)
		
		(h, w) = frame.shape[:2]
		blob = cv2.dnn.blobFromImage(cv2.resize(frame, (300, 300)),
			0.007843, (300, 300), 127.5)

		net.setInput(blob)
		detections = net.forward()
		
		for i in np.arange(0, detections.shape[2]):
			confidence = detections[0, 0, i, 2]

			if confidence > 0.2:
				idx = int(detections[0, 0, i, 1])

				if(CLASSES[idx]=="person"):
					box = detections[0, 0, i, 3:7] * np.array([w, h, w, h])
					(startX, startY, endX, endY) = box.astype("int")
					
					label = "{}: {:.2f}%".format(CLASSES[idx],
						confidence * 100)
					cv2.rectangle(frame, (startX, startY), (endX, endY),
						COLORS[idx], 2)
					y = startY - 15 if startY - 15 > 15 else startY + 15
					cv2.putText(frame, label, (startX, y),
						cv2.FONT_HERSHEY_SIMPLEX, 0.5, COLORS[idx], 2)
		
		ret,buffer=cv2.imencode('.jpg',frame)
		frame=buffer.tobytes()
		
		yield(b'--frame\r\n'b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')
		
		key = cv2.waitKey(1) & 0xFF
		
		if key == ord("q"):
			break
		
		fps.update()
	
	fps.stop()
	print("[INFO] elapsed time: {:.2f}".format(fps.elapsed()))
	print("[INFO] approx. FPS: {:.2f}".format(fps.fps()))
	
	cv2.destroyAllWindows()
	vs.stop()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/video')
def video():
    return Response(generate_frames(),mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__=="__main__":
    app.run(host='192.168.39.182', port=5000)
    app.run(debug=False)