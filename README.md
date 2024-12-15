# Auto Intensity Street Light Controller Using Arduino, RTC, and LDR

This project implements an automatic street light controller using Arduino, LDR (Light Dependent Resistor), and RTC (Real-Time Clock). The system adjusts the brightness of the street lights based on ambient light conditions and time of the day.

## Working Video
https://github.com/user-attachments/assets/57bdfad2-569e-40a5-90ad-686326f8b0cf


## How It Works

- **LDR Sensor**: Detects the surrounding light and adjusts the brightness of the street lights accordingly.
- **RTC Module**: Tracks the time to turn on and off the street lights between preset hours (e.g., 6 PM to 6 AM).
- **PWM Control**: The brightness is controlled through PWM signals based on the LDR sensor input.

### Features
- Energy-efficient lighting.
- Automatic light intensity adjustment.
- Low-cost and simple to implement.



## Components Used
- Arduino Uno
- RTC DS3231
- LDR Sensor
- Relay for controlling lights
- LED or any suitable light source

