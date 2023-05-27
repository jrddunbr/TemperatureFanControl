// Connect the PWM pin of the fan to this Arduino pin
#define FAN_PIN 9

// Set the minimum and maximum temperature range for the fan speed (Degrees Celcius)
#define MIN_TEMP 23
#define MAX_TEMP 28

// Set the minimum and maximum fan speed for the given temp range (0-255)
#define FAN_SLOW 0
#define FAN_FAST 255

// Connect the SHT4x to the SCL and SDA pins
#include "Adafruit_SHT4x.h"
Adafruit_SHT4x sht4 = Adafruit_SHT4x();

void setup() {
  Serial.begin(115200);

  // pause Zero, Leonardo, etc until serial console opens
  while (!Serial)
    delay(10);     

  pinMode(FAN_PIN, OUTPUT);

  if (! sht4.begin()) {
    Serial.println("Couldn't find SHT4x");
    while (1) delay(1);
  }

  sht4.setPrecision(SHT4X_HIGH_PRECISION);
  sht4.setHeater(SHT4X_NO_HEATER);
}


float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void loop() {
  sensors_event_t humidity, temp;
  sht4.getEvent(&humidity, &temp);
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");

  // Calculate the correct fan speed given the inputs. If the temperature is out of range, clamp the output to 0-255 range.
  double fan_speed = constrain(mapfloat(temp.temperature, MIN_TEMP, MAX_TEMP, FAN_SLOW, FAN_FAST), FAN_SLOW, FAN_FAST);

  Serial.print("Fan Speed: "); Serial.print(fan_speed); Serial.println("/255.0");
  analogWrite(FAN_PIN, fan_speed);

  delay(250);
}