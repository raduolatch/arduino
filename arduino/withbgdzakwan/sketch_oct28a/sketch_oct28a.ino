#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID   "TMPL62SVH9opD" // Template ID Blynk
#define BLYNK_TEMPLATE_NAME "tch tzy"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = "joA2xnw6Z5phgWUAfBA5R7C7k9KBg11U"; //Auth Token Bluynk
char ssid[] = "A14 ror"; // SSID Wifi
char pass[] = "LMAOKIDZZZ12"; // Password Wifi

DHT dht(25, DHT11); 
BlynkTimer timer;

float h = 0;
float t = 0;

int led1 = 12;
int led2 = 14;

int maxTemp = 40; // default

void sendSensor() {
  h = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(300);
    return;
  }

  // Tampilkan di Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  // Kirim ke Blynk
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}

// Fungsi kontrol LED 1 dari aplikasi Blynk (V2)
BLYNK_WRITE(V2) {
  int ledState = param.asInt(); // Baca nilai dari tombol (0 atau 1)

  if (ledState == 1) {
    Serial.println("LED 1 ON");
    digitalWrite(led1, HIGH);
  } else {
    Serial.println("LED 1 OFF");
    digitalWrite(led1, LOW);
  }
}


void cekSuhu(){
  if (t > maxTemp) {
    Serial.println("Suhu Tidak Normal");
    digitalWrite(led1, HIGH);  
    digitalWrite(led2, LOW);  
  } else {
    Serial.println("Suhu Normal");
    digitalWrite(led1, LOW);  
    digitalWrite(led2, HIGH);   
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  dht.begin();
  
  // Hubungkan ke WiFi + Blynk Cloud
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  // Loop kirim data sensor setiap 3 detik
  timer.setInterval(3000L, sendSensor);
  Serial.println("System Started...");
}

void loop() {
  Blynk.run();
  timer.run();
  cekSuhu();
  delay(500);
}


