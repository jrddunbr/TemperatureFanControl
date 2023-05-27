# TemperatureFanControl

A simple program for reading a 10kΩ NTC temperature sensor and controlling a fan from it

## Wiring

I connected a 4 pin 12V PWM fan (commonly found in computers on the CPU cooler) to the Arduino

* Gnd to Gnd on the Arduino and the Battery
* 12V to a 12V battery I have
* PWM to Arduino Pin 9

[Here's an example for Noctua Fan pinouts](https://faqs.noctua.at/support/solutions/articles/101000081757-what-pin-configuration-do-noctua-fans-use-)

I also connected a cheap 10kΩ thermistor and a 10kΩ resistor to the arduino:
* One end of the NTC to Gnd
* One end of the NTC to Analog 0 on the Arduino
* One end of the 10kΩ resistor to Analog 0
* One end of the 10kΩ resistor to 5V

## Configuration

At the top of the file, you can specify the fan speeds and the temperature range for activation.

You will need to calibrate the NTC thermistor against a known temperature source. You could do this in many ways,
but this is left as an exercise to the user. I've provided sensible values for a 10kΩ thermistor, but it was off by about 5 degrees C.
The A, B, and C defines at the top let you control these constants.

You may also want to put a more accurate resistance for your 10kΩ resistor if you have a decent ohmmeter. This will also improve accuracy,
as this number is used to calculate the (unknown) resistance of the thermistor using a voltage divider calculation.

The temperature range is the minimum and maximum temperature. Beyond these temperatures, the fan will camp
to the slow and fast speeds in the other variables. In the current configuration, the fan is slow or off
(depending on your ambient temperature in celcius, mine was 23.5) and when you hold the sensor it quickly raises beyond
28 degrees and that results in the fan spinning up to full speed with the default values.

The temperature sensor deals in celcius.

The fan uses the standard 0-255 for PWM values in code, so 0 is 0%, 255 is 100% speed.

You can use a value other than zero for FAN_SLOW to have the fan always run a minimum amount.