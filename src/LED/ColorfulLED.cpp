#include <LED/ColorfulLED.h>

// TODO: make class "Color"?

ColorfulLED::ColorfulLED(const int redPin, const int greenPin, const int bluePin)
    : redLED(redPin),
      greenLED(greenPin),
      blueLED(bluePin){};

void ColorfulLED::setColor(const int red, const int green, const int blue)
{
    redLED.setBrightness(red);
    greenLED.setBrightness(green);
    blueLED.setBrightness(blue);
};

void ColorfulLED::blink(
    const int red,
    const int green,
    const int blue,
    const int onTime,
    const int offTime)
{
    redLED.blink(onTime, offTime, red);
    greenLED.blink(onTime, offTime, green);
    blueLED.blink(onTime, offTime, blue);
};

void ColorfulLED::fade(
    const int startRed,
    const int startGreen,
    const int startBlue,
    const int endRed,
    const int endGreen,
    const int endBlue,
    const int time)
{
    redLED.fade(startRed, endRed, time);
    greenLED.fade(startGreen, endGreen, time);
    blueLED.fade(startBlue, endBlue, time);
};