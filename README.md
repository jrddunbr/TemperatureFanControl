# TemperatureFanControl

A simple program for reading a SHT4x temperature sensor and controlling a fan from it

## Wiring

I connected a 4 pin 12V PWM fan (commonly found in computers on the CPU cooler) to the Arduino

* Gnd to Gnd on the Arduino and the Battery
* 12V to a 12V battery I have
* PWM to Arduino Pin 9

[Here's an example for Noctua Fan pinouts](https://faqs.noctua.at/support/solutions/articles/101000081757-what-pin-configuration-do-noctua-fans-use-)

I also connected the [Adafruit SHT45 breakout](https://www.adafruit.com/product/5665) to the Arduino.
This can be done with their SemmaQt connector breakout wire:
* Yellow to SCL
* Blue to SCK
* Red to 5V
* Black to Gnd

## Configuration

At the top of the file, you can specify the fan speeds and the temperature range for activation.

The temperature range is the minimum and maximum temperature. Beyond these temperatures, the fan will camp
to the slow and fast speeds in the other variables. In the current configuration, the fan is slow or off
(depending on your ambient temperature in celcius, mine was 23.5) and when you hold the sensor it quickly raises beyond
28 degrees and that results in the fan spinning up to full speed with the default values.

The temperature sensor deals in celcius.

The fan uses the standard 0-255 for PWM values in code, so 0 is 0%, 255 is 100% speed.

You can use a value other than zero for FAN_SLOW to have the fan always run a minimum amount.