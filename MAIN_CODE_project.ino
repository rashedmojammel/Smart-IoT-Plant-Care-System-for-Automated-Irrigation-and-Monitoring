

/* Connections
Relay. D3
Btn.   D7
Soil.  A0
PIR.   D5
SDA.   D2
SCL.   D1
Temp.  D4
Rain.  D6
LED    D0     // indicator
MOTION D8     // motion LED/buzzer output
*/
//Mercybro
// #define BLYNK_TEMPLATE_ID "TMPL62EHkrRxd"
// #define BLYNK_TEMPLATE_NAME "Smart Irrigation System"

//rashedmojammel0
#define BLYNK_TEMPLATE_ID "TMPL6CWV3XM5n"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation System"
// #define BLYNK_AUTH_TOKEN "0YsNF7dZ2kXeqDRCr4MR6w2-3Wy-GXha"

//rashedmojammel414
#define BLYNK_TEMPLATE_ID "TMPL6PHvZa0Vl"
#define BLYNK_TEMPLATE_NAME "Smart Plant Monitoring System"


#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- credentials (yours) ---
// char auth[] = "xBSl5XKNd2y5USWvnR59ywbuvHMVJqPs";
// char ssid[] = "Neel";
// char pass[] = "01755628215";

char auth[] = "yM7XtTvzN-hkdLFgN96YBNzQinW2HhKG";
char ssid[] = "Sameer";
char pass[] = "Password";

DHT dht(D4, DHT11);
BlynkTimer timer;

// ---- Pins ----
#define soil A0
#define PIR  D5
#define rainSensor D6
#define LED_PIN D0
#define MOTION_LED_PIN D8   // LED/Buzzer

#define RELAY_PIN_1   D3
#define PUSH_BUTTON_1 D7
#define VPIN_BUTTON_1 V12

// ---- Behavior switches ----
#define ALERT_ACTIVE_LOW 0  // if D8 device is active-LOW (LOW = ON). Use 0 if active-HIGH
#define RAIN_ACTIVE_HIGH 0   // if rain DO = HIGH means rain, set 1

inline void alertOn()  { digitalWrite(MOTION_LED_PIN, ALERT_ACTIVE_LOW ? LOW  : HIGH); }
inline void alertOff() { digitalWrite(MOTION_LED_PIN, ALERT_ACTIVE_LOW ? HIGH : LOW ); }

BlynkTimer pirTimer;
int PIR_ToggleValue = 1; // 1 = enabled
int relay1State = LOW;
int pushButton1State = HIGH;

// ----------------- Setup -----------------
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(PIR, INPUT);
  pinMode(rainSensor, INPUT);

  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_1, relay1State);

  pinMode(PUSH_BUTTON_1, INPUT_PULLUP);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  pinMode(MOTION_LED_PIN, OUTPUT);
  alertOff();

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
  dht.begin();

  lcd.setCursor(0, 0); lcd.print("  Initializing  ");
  for (int a = 5; a <= 10; a++) { lcd.setCursor(a, 1); lcd.print("..."); delay(300); }
  lcd.clear();
  lcd.setCursor(11, 1); lcd.print("W:OFF");

  timer.setInterval(2000L, soilMoistureSensor);
  timer.setInterval(3000L, DHT11sensor);
  timer.setInterval(100L,  checkPhysicalButton);
  timer.setInterval(1000L, checkRainSensor);

  pirTimer.setInterval(200L, PIRsensorTick);
}

// ----------------- Sensors -----------------
void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) { Serial.println("Failed to read DHT"); return; }

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  lcd.setCursor(0, 0); lcd.print("T:"); lcd.print(t);
  lcd.setCursor(8, 0);  lcd.print("H:"); lcd.print(h);
}

void soilMoistureSensor() {
  int raw = analogRead(soil);
  int value = map(raw, 0, 1024, 0, 100);
  value = (value - 100) * -1;
  Blynk.virtualWrite(V3, value);
  lcd.setCursor(0, 1); lcd.print("S:"); lcd.print(value); lcd.print(" ");
  if (value < 35 ) { // If soil moisture is below 30%, turn on the pump
    relay1State =   LOW;
    digitalWrite(RELAY_PIN_1, relay1State);
    Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);  // Update Blynk button state

    Blynk.logEvent("lowmoisture", "Soil moisture is low! Please water the plants.");
  } else { // If soil moisture is above 30%, turn off the pump
    relay1State = HIGH;
    digitalWrite(RELAY_PIN_1, relay1State);
    Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);  // Update Blynk button state
  }

}

// -------- PIR Tick --------
// void PIRsensorTick() {
//   static WidgetLED wled(V5);  // Blynk LED widget

//   if (PIR_ToggleValue != 1) {
//     // PIR disabled from app -> force OFF
//     alertOff();
//     wled.off();
//     return;
//   }

//   bool motion = digitalRead(PIR);

//   if (motion) {
//     // Motion detected
//     alertOn();
//     wled.on();
//     Serial.println("Motion detected");
//   } else {
//     // No motion
//     alertOff();
//     wled.off();
//     Serial.println("No motion");
//   }
// }
void PIRsensorTick() {
  static WidgetLED wled(V5);  // Blynk LED widget

  if (PIR_ToggleValue != 1) {
    // PIR disabled from app -> force OFF
    alertOff();
    wled.off();
    return;
  }

  bool motion = digitalRead(PIR);

  if (motion) {
    // Motion detected
    alertOn();
    wled.on();
    Serial.println("Motion detected");
    //Blynk.notify("Motion detected!");  // Send notification
    Blynk.logEvent("pirmotion", "Motion Detected");  // Log the PIR motion event
  } else {
    // No motion
    alertOff();
    wled.off();
    Serial.println("No motion");
  }
}


// ----------------- Rain sensor -----------------
void checkRainSensor() {
  int s = digitalRead(rainSensor);
  bool rainDetected = RAIN_ACTIVE_HIGH ? (s == HIGH) : (s == LOW);

  Blynk.virtualWrite(V7, rainDetected ? 1 : 0);
  if (rainDetected) {
    Blynk.logEvent("raindetected", "Rain Detected");
  }
}

// ----------------- Blynk handlers -----------------
BLYNK_WRITE(V6) {   // PIR toggle (enable/disable PIR logic)
  PIR_ToggleValue = param.asInt();
  if (PIR_ToggleValue != 1) {
    alertOff();
    WidgetLED wled(V5); wled.off();
  }
}

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V7);
  Blynk.syncVirtual(V0, V1, V3, V5, V6, V12);
}

BLYNK_WRITE(VPIN_BUTTON_1) {
  relay1State = param.asInt();
  digitalWrite(RELAY_PIN_1, relay1State);
}

// ----------------- Button & indicator -----------------
void checkPhysicalButton() {
  if (digitalRead(PUSH_BUTTON_1) == LOW) {
    if (pushButton1State != LOW) {
      relay1State = !relay1State;
      digitalWrite(RELAY_PIN_1, relay1State);
      Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);
    }
    pushButton1State = LOW;
  } else {
    pushButton1State = HIGH;
  }
}

void controlLED() {
  if (relay1State == HIGH) digitalWrite(LED_PIN, LOW);
  else                     digitalWrite(LED_PIN, HIGH);
}

// ----------------- Loop -----------------
void loop() {
  lcd.setCursor(5, 1); lcd.print(PIR_ToggleValue == 1 ? "M:ON " : "M:OFF");
  lcd.setCursor(11, 1); lcd.print(relay1State == HIGH ? "W:OFF" : "W:ON ");

  controlLED();
  Blynk.run();
  timer.run();
  pirTimer.run();
}
