#include <WiFiS3.h>
#include <ArduinoHttpClient.h>

char ssid[] = "BPstudent";
char password[] = "studentuse";
int status = WL_IDLE_STATUS;
char serverAddress[] = "http://10.30.1.3:5000";

WiFiClient client;
HttpClient httpClient = HttpClient(client, serverAddress, 80);

// int HTTP_PORT = 80;
// String HTTP_METHOD = "POST";
// char HOST_NAME[] = "http://10.30.1.3:5000";
// String PATH_NAME = "/info";
// String queryString = "?value1=26&value2=70";

int sensor = 1; // the pin that the sensor is atteched to
int state = HIGH; // by default, no motion detected
int val = 0; // variable to store the sensor status (value)
int reed = 2;
int redLED = 3;
int greenLED = 5;
int blueLED = 6;

WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }

void setup() {
  Serial.begin(9600); // initialize serial
  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    // don't do anything else:
    while(true);
  }

    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(serverAddress, 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /search?q=arduino HTTP/1.0");
      client.println();
  }


  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   Serial.println(ssid);                   // print the network name (SSID);
  //   status = WiFi.begin(ssid, password);
  //   printWifiStatus();
  //   delay(500);
  // }

  //   if (client.connect(server, 80)) {
  //     Serial.println("connected");
  //     // Make a HTTP request:
  //     client.println("GET /search?q=arduino HTTP/1.0");
  //     client.println();
  //   }

  // if (client.connect(HOST_NAME, HTTP_PORT)) {
  //   // if connected:
  //   Serial.println("Connected to server");
  //   // make a HTTPHttp request:
  //   // send HTTP header
  //   client.println(HTTP_METHOD + " " + PATH_NAME + " HTTP/1.1");
  //   client.println("Host: " + String(HOST_NAME));
  //   client.println("Connection: close");
  //   client.println();  // end HTTP header

  //   // send HTTP body
  //   client.println(queryString);

  //   while (client.connected()) {

  //   }
  // }

  pinMode(sensor, INPUT); // initialize sensor as an input
  pinMode(reed, INPUT_PULLUP);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  int httpCode = httpClient.responseStatusCode();
  Serial.print("HTTP response code: ");
  Serial.println(httpCode);

  if (httpCode > 0) {
    String responseBody = httpClient.responseBody();
    Serial.println("Response body:");
    Serial.println(responseBody);
  }
}

void loop(){
  httpClient.get("/getData");
  if (client.available()) {
    // read an incoming byte from the server and print it to serial monitor:
    char c = client.read();
    Serial.print(c);
  } 

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