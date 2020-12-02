#include <ColorfulLED.h>

ColorfulLED::ColorfulLED(const int redPin, const int greenPin, const int bluePin)
    : redLED(redPin),
      greenLED(greenPin),
      blueLED(bluePin){};

void ColorfulLED::setColor(const Color color)
{
    redLED.setBrightness(color.red);
    greenLED.setBrightness(color.green);
    blueLED.setBrightness(color.blue);
};

void ColorfulLED::blink(
    const Color color,
    const int onTime,
    const int offTime)
{
    redLED.blink(onTime, offTime, color.red);
    greenLED.blink(onTime, offTime, color.green);
    blueLED.blink(onTime, offTime, color.blue);
};

void ColorfulLED::fade(
    const Color startColor,
    const Color endColor,
    const int time)
{
    redLED.fade(startColor.red, endColor.red, time);
    greenLED.fade(startColor.green, endColor.green, time);
    blueLED.fade(startColor.blue, endColor.blue, time);
};