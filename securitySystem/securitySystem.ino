int sensor = 1; // the pin that the sensor is atteched to
int state = HIGH; // by default, no motion detected
int val = 0; // variable to store the sensor status (value)
int reed = 2;
int redLED = 3;
int greenLED = 5;
int blueLED = 6;

void setup() {
  pinMode(sensor, INPUT); // initialize sensor as an input
  pinMode(reed, INPUT_PULLUP);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  Serial.begin(9600); // initialize serial
}

void loop(){
  val = digitalRead(sensor); // read sensor value
  if (val == HIGH) { // check if the sensor is HIGH
    // setColor(255, 255, 255);
    // delay(100); // delay 100 milliseconds
    while (state == LOW) {
      setColor(0, 0, 255);
      Serial.println("Motion detected!");
      state = HIGH; // update variable state to HIGH
      delay(1500);
    }
  }
  else {
    delay(200); // delay 200 milliseconds
    while (state == HIGH){
     setColor(255, 255, 255);
     Serial.println("Motion stopped!");
      state = LOW; // update variable state to LOW
    }
  }
  if (digitalRead(reed) == LOW) {
   setColor(255, 255, 255);
   Serial.println("door closed");
  } else {
    setColor(255, 0, 0);
    Serial.println("door open");
      delay(500);
  }
}

void setColor(int redVal, int greenVal, int blueVal) {
  analogWrite(redLED, redVal);
  analogWrite(greenLED, greenVal);
  analogWrite(blueLED, blueVal);
}