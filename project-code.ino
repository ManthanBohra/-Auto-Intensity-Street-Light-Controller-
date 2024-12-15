#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ldrPin = A0; // Analog pin connected to the LDR
const int ledPin = 9; // PWM-capable pin connected to the LED
const int potPin = A1; // Analog pin connected to the potentiometer
const int buttonPin = 8; // Digital pin connected to the push button

bool manualOverride = false;

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP); // Enable internal pull-up resistor
    lcd.init();
    lcd.clear();
    lcd.backlight();
    
    if (!rtc.begin()) {
        lcd.print("Couldn't find RTC");
        while (1);
    }

    if (rtc.lostPower()) {
        lcd.print("RTC lost power!");
        rtc.adjust(DateTime(F(_DATE), F(TIME_))); // Set RTC to compile time
    }

    Serial.begin(9600);
}

void loop() {
    DateTime now = rtc.now();
    
    // Display current time on LCD
    lcd.setCursor(0, 0);
    lcd.print(now.hour());
    lcd.print(":");
    lcd.print(now.minute());
    lcd.print(":");
    lcd.print(now.second());
    
    // Read LDR value
    int ldrValue = analogRead(ldrPin);
    
    // Read potentiometer value
    int potValue = analogRead(potPin);
    
    // Read button state
    int buttonState = digitalRead(buttonPin);
    
    // Manual override logic
    if (buttonState == LOW) {
        manualOverride = !manualOverride;
        delay(200); // Debounce delay
    }

    // Determine LED brightness
    int ledBrightness;
    if (manualOverride) {
        // Manual control with potentiometer
        ledBrightness = map(potValue, 0, 1023, 0, 255);
        lcd.setCursor(0, 1);
        lcd.print("Manual Bright: ");
        lcd.print(ledBrightness);
    } else {
        // Auto control based on LDR value
        //ledBrightness = map(ldrValue, 0, 1023, 255, 0);
        if(ldrValue <300){
          ledBrightness=255;
        }
        else  if(ldrValue >300 && ldrValue<700){
          ledBrightness=15;
        }

        else ledBrightness =0;
        lcd.setCursor(0, 1);
        lcd.print("Auto Bright: ");
        lcd.print(ledBrightness);
    }

    // Set LED brightness
    analogWrite(ledPin, ledBrightness);
    
    // Print values to Serial Monitor for debugging
    Serial.print("LDR Value: ");
    Serial.print(ldrValue);
    Serial.print(" | Pot Value: ");
    Serial.print(potValue);
    Serial.print(" | LED Brightness: ");
    Serial.println(ledBrightness);
    
    delay(1000); // Wait for a second before repeating the loop
}