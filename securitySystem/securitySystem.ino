#include <WiFiS3.h>
#include <ArduinoHttpClient.h>

char ssid[] = "BPstudent";
char password[] = "studentuse";
int status = WL_IDLE_STATUS;
char serverAddress[] = "172.17.20.210";

WiFiClient client;
HttpClient httpClient = HttpClient(client, serverAddress, 5000);

int sensor = 1; // the pin that the sensor is atteched to
int state = HIGH; // by default, no motion detected
int val = 0; // variable to store the sensor status (value)
int reed = 2;
int redLED = 3;
int greenLED = 5;
int blueLED = 6;

void setup() {
  Serial.begin(9600); // initialize serial

  pinMode(sensor, INPUT); // initialize sensor as an input
  pinMode(reed, INPUT_PULLUP);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    delay(1000);
  }
    Serial.println("WiFi connected!");
    Serial.print("Arduino IP: ");
    Serial.println(WiFi.localIP());
}

void loop(){
  val = digitalRead(sensor); // read sensor value
  if (val == HIGH && state == LOW) { // check if the sensor is HIGH
    setColor(0, 0, 255);
    Serial.println("Motion detected!");
    delay(1500);
      httpClient.stop();

    if (digitalRead(reed) == LOW) {
      setColor(255, 255, 255);
      Serial.println("door closed");
      httpClient.get("/info?getData=Door%20Closedandmotiondetected");
      // int statusCode = httpClient.responseStatusCode();
      // Serial.print("HTTP status: ");
      // Serial.println(statusCode);    
      httpClient.stop();
    } else {
      setColor(255, 0, 0);
      Serial.println("door open");
      httpClient.get("/info?getData=Door%20Openandmotiondetected");
      httpClient.stop();
    }
    state = HIGH; // update variable state to HIGH
  }

  else if (val == LOW && state == HIGH) {
    delay(200); // delay 200 milliseconds
    setColor(255, 255, 255);
       httpClient.stop();
   Serial.println("Motion stopped!");
    if (digitalRead(reed) == LOW) {
      setColor(255, 255, 255);
      Serial.println("door closed");
      // httpClient.get("/info?getData=Door%20ClosedandmotionNOTdetected");
      // int statusCode = httpClient.responseStatusCode();
      // Serial.print("HTTP status: ");
      // Serial.println(statusCode);
      httpClient.stop();
    } else {
      setColor(255, 0, 0);
      Serial.println("door open");
      // httpClient.get("/info?getData=Door%20OpenandmotionNOTdetected");
      httpClient.stop();
    }
    state = LOW; // update variable state to LOW    
  }
}

void setColor(int redVal, int greenVal, int blueVal) {
  analogWrite(redLED, redVal);
  analogWrite(greenLED, greenVal);
  analogWrite(blueLED, blueVal);
}