#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include "DHT.h"

// ================= WIFI =================
const char* ssid = "Guik guik piyaw piyaw";
const char* password = "12345678";

// ================= TELEGRAM =================
#define BOT_TOKEN "8308292051:AAFX-OlQLEFtsbZUJ3eZo8Fon-U7euHJs3M"

// ================= PIN (ESP32-C3 SAFE) =================
#define LED_A 4
#define LED_B 6
#define LED_UTAMA 5

#define DHTPIN 2
#define DHTTYPE DHT11

#define MQ_PIN 0      // Analog (ADC)

// ================= OBJECT =================
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
DHT dht(DHTPIN, DHTTYPE);

// ================= IDENTITAS =================
String anggotaA = "1973810352";
String anggotaB = "1353775639";
String groupID  = "-1003764982429";

// ================= VARIABLE =================
unsigned long lastTimeBotRan;
unsigned long lastGasAlert = 0;

int botRequestDelay = 1000;
int gasThreshold = 3100;

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_UTAMA, OUTPUT);

  dht.begin();

  WiFi.begin(ssid, password);
  client.setInsecure();

  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
}

// ================= HANDLE TELEGRAM =================
void handleNewMessages(int numNewMessages) {

  for (int i = 0; i < numNewMessages; i++) {

    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    String user_id = String(bot.messages[i].from_id);

    Serial.print("Text: ");
    Serial.println(text);
    Serial.print("User ID: ");
    Serial.println(user_id);

    // ===== START =====
    if (text.startsWith("/start")) {
      bot.sendMessage(chat_id,
      "Smart House Bot\n\n"
      "/ledA_on\n/ledA_off\n"
      "/ledB_on\n/ledB_off\n"
      "/led_utama_on\n/led_utama_off\n"
      "/cek_suhu\n/cek_gas", "");
    }

    // ===== LED A =====
    if (text.startsWith("/ledA_on")) {
      if (user_id == anggotaA) {
        digitalWrite(LED_A, HIGH);
        bot.sendMessage(chat_id, "Lampu Kamar Vashih Nyala", "");
      } else {
        bot.sendMessage(chat_id, "AKSES DITOLAK!", "");
      }
    }

    if (text.startsWith("/ledA_off")) {
      if (user_id == anggotaA) {
        digitalWrite(LED_A, LOW);
        bot.sendMessage(chat_id, "Lampu Kamar Vashih Mati", "");
      } else {
        bot.sendMessage(chat_id, "AKSES DITOLAK!", "");
      }
    }

    // ===== LED B =====
    if (text.startsWith("/ledB_on")) {
      if (user_id == anggotaB) {
        digitalWrite(LED_B, HIGH);
        bot.sendMessage(chat_id, "Lampu Kamar Rafif Nyala", "");
      } else {
        bot.sendMessage(chat_id, "AKSES DITOLAK!", "");
      }
    }

    if (text.startsWith("/ledB_off")) {
      if (user_id == anggotaB) {
        digitalWrite(LED_B, LOW);
        bot.sendMessage(chat_id, "Lampu Kamar Rafif Mati", "");
      } else {
        bot.sendMessage(chat_id, "AKSES DITOLAK!", "");
      }
    }

    // ===== LED UTAMA (bebas semua) =====
    if (text.startsWith("/led_utama_on")) {
      digitalWrite(LED_UTAMA, HIGH);
      bot.sendMessage(chat_id, "Lampu ruang tamu NYALA", "");
    }

    if (text.startsWith("/led_utama_off")) {
      digitalWrite(LED_UTAMA, LOW);
      bot.sendMessage(chat_id, "Lampu ruang tamu MATI", "");
    }

    // ===== CEK SUHU =====
    if (text.startsWith("/cek_suhu")) {

      delay(2000);

      float suhu = dht.readTemperature();
      float hum = dht.readHumidity();

      if (isnan(suhu) || isnan(hum)) {
        bot.sendMessage(chat_id, "Gagal baca sensor DHT!", "");
        return;
      }

      String msg = "Suhu: " + String(suhu) + " C\n";
      msg += "Kelembapan: " + String(hum) + " %";

      bot.sendMessage(chat_id, msg, "");
    }

    // ===== CEK GAS =====
    if (text.startsWith("/cek_gas")) {
      int gasValue = analogRead(MQ_PIN);

      String msg = "Sensor Gas\nNilai: " + String(gasValue);
      bot.sendMessage(chat_id, msg, "");
    }
  }
}

// ================= LOOP =================
void loop() {

    // ===== AUTO GAS ALERT =====
  int gasValue = analogRead(MQ_PIN);

  Serial.print("Gas: ");
  Serial.println(gasValue);

  if (gasValue > gasThreshold && millis() - lastGasAlert > 10000) {

    String msg = "⚠️ WARNING GAS TERDETEKSI!\n";
    msg += "Nilai: " + String(gasValue);

    bot.sendMessage(groupID, msg, "");

    lastGasAlert = millis();
  }

  // TELEGRAM LOOP
  if (millis() - lastTimeBotRan > botRequestDelay) {

    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    lastTimeBotRan = millis();
  }
}