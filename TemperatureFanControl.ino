// Connect the PWM pin of the fan to this Arduino pin
#define FAN_PIN 9

// Connect the thermistor to this pin and ground, and the 10K resistor from this pin to 5V.
#define SENSOR_PIN A0

#define VCC 5.0 // 5 volts reference voltage (Feel free to add a more accurate voltage reference)
#define R2 10000.0 // 10k resistor ohms (set this to the resistance of your 10K resistor)

// Values for a 10k thermistor for use in the Steinhart-Hart equation (You may need to adjust these to calibrate)
#define A 0.001125308852122
#define B 0.000234711863267
#define C 0.000000085663516

// Set the minimum and maximum temperature range for the fan speed (Degrees Celcius)
#define MIN_TEMP 30
#define MAX_TEMP 35

// Set the minimum and maximum fan speed for the given temp range (0-255)
#define FAN_SLOW 0
#define FAN_FAST 255

void setup() {
  Serial.begin(115200);

  // pause Zero, Leonardo, etc until serial console opens
  while (!Serial)
    delay(10);     

  pinMode(FAN_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
}


float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void loop() {
  // Calculate the voltage of the sensor pin
  double voltage = (analogRead(SENSOR_PIN) / 1024.0) * VCC;
  Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");

  // Calculate the resistance of the thermistor based on the known resistor value
  double thermistor_resistance = (voltage * R2)/(VCC - voltage);
  Serial.print("Thermistor: "); Serial.print(thermistor_resistance); Serial.println("Ω");

  // Calculate the temperature using the Steinhart-Hart equation
  double temperature = pow(A + B * log(thermistor_resistance) + pow(C * log(thermistor_resistance), 3), -1) - 273.15;
  Serial.print("Temperature: "); Serial.print(temperature); Serial.println("°C");

  // Calculate the correct fan speed given the inputs. If the temperature is out of range, clamp the output to 0-255 range.
  double fan_speed = constrain(mapfloat(temperature, MIN_TEMP, MAX_TEMP, FAN_SLOW, FAN_FAST), FAN_SLOW, FAN_FAST);

  Serial.print("Fan Speed: "); Serial.print(fan_speed); Serial.println("/255.0");
  analogWrite(FAN_PIN, fan_speed);

  delay(250);
}