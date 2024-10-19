#include <DHT.h>

// Define pin connections
#define DHTPIN 2          // Pin connected to DHT sensor (use GPIO 2)
#define DHTTYPE DHT11     // DHT 11 (for DHT22, use DHT22)
#define LED_PIN 4         // Pin connected to LED (use GPIO 4)
#define FAN_INA 5         // Motor driver control pin (INA) - GPIO 5
#define FAN_INB 18        // Motor driver control pin (INB) - GPIO 18

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial monitor
  Serial.begin(115200);
 
  // Initialize DHT sensor
  dht.begin();
 
  // Set up pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(FAN_INA, OUTPUT);
  pinMode(FAN_INB, OUTPUT);

  // Initial state
  digitalWrite(LED_PIN, LOW);  // Turn off LED
  stopFan();                   // Stop the fan
}

void loop() {
  // Read temperature and humidity from DHT sensor
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
 
  // Check if reading is successful
  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print readings to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C  Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Control LED based on temperature
  if (temp > 2.50) {
    digitalWrite(LED_PIN, HIGH);  // Turn on LED if temp > 2.50°C
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn off LED if temp <= 2.50°C
  }

  // Control fan based on temperature
  if (temp > 1.50) {
    startFan();  // Start the fan if temp > 1.50°C
  } else {
    stopFan();   // Stop the fan if temp <= 1.50°C
  }

  // Wait before next reading
  delay(2000);
}

void startFan() {
  digitalWrite(FAN_INA, HIGH);  // Set INA high
  digitalWrite(FAN_INB, LOW);   // Set INB low (to rotate motor)
}

void stopFan() {
  digitalWrite(FAN_INA, LOW);   // Set INA low
  digitalWrite(FAN_INB, LOW);   // Set INB low (stop motor)
}
