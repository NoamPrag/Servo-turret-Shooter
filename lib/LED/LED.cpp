#include <LED.h>

LED::LED(const unsigned int pin) : pin(pin)
{
    pinMode(pin, OUTPUT);
};

void LED::setBrightness(const unsigned int value)
{
    analogWrite(pin, value);

    prevBrightness = brightness;
    brightness = value;
};

const unsigned int LED::getBrightness()
{
    return this->brightness;
};

void LED::turnOff()
{
    setBrightness(0);
};

void LED::blink(
    const unsigned int onTime,
    const unsigned int offTime,
    const unsigned int brightness)
{
    const unsigned long currentTime = millis();

    if (this->brightness == 0)
    {
        if (currentTime - changeTime >= offTime)
        {
            setBrightness(brightness);
            changeTime = currentTime;
        }
    }
    else if (currentTime - changeTime >= onTime)
    {
        turnOff();
        changeTime = currentTime;
    }
};

void LED::fade(
    const unsigned int start,
    const unsigned int end,
    const unsigned long time)
{
    if (brightness == end && abs(brightness - prevBrightness) == 1)
    {
        return;
    }

    const long timeToChange = start == end ? INFINITY : time / abs(start - end);
    const unsigned long currentTime = millis();

    if (currentTime - changeTime >= timeToChange)
    {
        setBrightness(brightness + 1 * (signbit(end - start) == 1 ? -1 : 1));
        changeTime = currentTime;
    }
};