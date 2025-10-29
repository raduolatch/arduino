#include <Servo.h>

// Pin definisi
#define TRIG_PIN 9
#define ECHO_PIN 8
#define SERVO_PIN 10

Servo myServo;

// Konstanta
const int DISTANCE_THRESHOLD = 20; // cm
const int SERVO_STOP = 90;         // servo berhenti
const int SERVO_FORWARD = 0;       // arah putar maju
const int SERVO_BACKWARD = 180;    // arah putar mundur

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(SERVO_STOP); // pastikan servo berhenti di awal

  Serial.begin(9600);
}

void loop() {
  int distance = getDistance();

  if (distance > 0 && distance < DISTANCE_THRESHOLD) {
    // Jika objek dekat, servo berputar maju
    Serial.println("Objek terdeteksi. Servo berputar.");
    myServo.write(SERVO_FORWARD);
  } else {
    // Jika tidak ada objek, servo berhenti
    Serial.println("Tidak ada objek. Servo berhenti.");
    myServo.write(SERVO_STOP);
  }

  // for(int i = 0; i<=180; i++){
  //   myServo.write(i);
  //   delay(20);
  // }
  // for (int i=180; i>=0;i--){
  //    myServo.write(i);
  //    delay(20);
  // }
  delay(100);
}

// Fungsi membaca jarak HC-SR04
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}
