#include <Arduino.h> // Arduino çekirdek kütüphanesi / Arduino core library
#include <U8g2lib.h> // OLED ekran kütüphanesi / OLED display library
#include <Wire.h>    // I2C haberleşme kütüphanesi / I2C communication library

// OLED ekran nesnesini tanımla (SSD1306, 128x64 çözünürlük)
// Initialize the OLED display object (SSD1306, 128x64 resolution)
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// LED pin dizisi / Array of LED pins
const int ledPins[] = {8, 9, 10, 11};
// Kalp boyutunu tutan değişken / Variable to hold heart size
int kalpBoyutu = 7;

// Kalp çizen fonksiyon / Function to draw a heart
void drawHeart(int x, int y, int scale) {
  u8g2.drawDisc(x - scale, y, scale); // Sol daire / Left circle
  u8g2.drawDisc(x + scale, y, scale); // Sağ daire / Right circle
  // Kalbin alt üçgen kısmı / Bottom triangle part of the heart
  u8g2.drawTriangle(x - scale * 2, y + scale/2, x + scale * 2, y + scale/2, x, y + scale * 3);
}

void setup() {
  u8g2.begin(); // Ekranı başlat / Start the display
  u8g2.setContrast(255); // Ekran parlaklığını maksimum yap / Set display brightness to maximum
  
  // LED'leri hazırla ve test et / Prepare and test LEDs
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], HIGH); // Başlangıçta tüm LED'leri yak / Turn on all LEDs initially
  }
  delay(1000); // 1 saniye bekle / Wait for 1 second
  for (int i = 0; i < 4; i++) digitalWrite(ledPins[i], LOW); // LED'leri söndür / Turn off LEDs
}

void loop() {
  // LED Efekti / LED Effect
  digitalWrite(8, HIGH); digitalWrite(10, HIGH); delay(200);
  digitalWrite(8, LOW); digitalWrite(10, LOW);
  digitalWrite(9, HIGH); digitalWrite(11, HIGH); delay(200);
  digitalWrite(9, LOW); digitalWrite(11, LOW);

  // Kalp Animasyonu mantığı / Heart animation logic
  if (kalpBoyutu == 7) kalpBoyutu = 9; else kalpBoyutu = 7;
  
  // OLED ekran güncelleme döngüsü / OLED display update loop
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_logisoso28_tf); // Yazı tipini ayarla / Set font
    u8g2.drawStr(10, 45, "1K!");           // Metni yazdır / Draw text
    
    // Kalbi belirtilen koordinatlarda çiz / Draw heart at specified coordinates
    drawHeart(85, 25, kalpBoyutu); 
  } while (u8g2.nextPage());
}
