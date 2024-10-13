#include <DHT.h>
#include <BlynkSimpleEsp8266.h>

// Define the DHT11 pin and type
#define DHTPIN 19    // D2 pin on NodeMCU
#define DHTTYPE DHT11  // DHT11 sensor

DHT dht(DHTPIN, DHTTYPE);

// Blynk Authentication Token
char auth[] = "Your_Blynk_Auth_Token";

// Setup Wi-Fi credentials
char ssid[] = "WiFi_SSID";   // Your WiFi SSID
char pass[] = "WiFi_Password"; //  WiFi Password i.e YOUR CONNECTED

void setup() {
  // Start serial communication
  Serial.begin(115200);
  Serial.println("DHT11 sensor interfacing with NodeMCU");

  // Initialize the DHT sensor
  dht.begin();

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // Run Blynk
  Blynk.run();

  // Wait a few seconds between measurements
  delay(2000);

  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();
  // Read humidity
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the results to the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Send data to Blynk
  Blynk.virtualWrite(V0, temperature); // Send temperature to virtual pin V0
  Blynk.virtualWrite(V1, humidity);    // Send humidity to virtual pin V1
}
