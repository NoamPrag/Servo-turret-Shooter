#include <LED/LED.h>

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

void LED::turnOff()
{
    analogWrite(pin, 0);

    prevBrightness = brightness;
    brightness = 0;
};

void LED::blink(const unsigned int onTime, const unsigned int offTime, const unsigned int brightness)
{
    const unsigned long currentTime = millis();

    if (this->brightness <= 0)
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

void LED::fade(const unsigned int start, const unsigned int end, const int fadeAmount)
{
    if (abs(brightness - prevBrightness) != abs(fadeAmount))
        setBrightness(start);

    else if (abs(end - brightness) <= abs(fadeAmount) && abs(end - prevBrightness) <= abs(2 * fadeAmount))
        setBrightness(end);

    else
    {
        const int signedFadeAmount = abs(fadeAmount) * signbit(end - start) == 1 ? -1 : 1;
        setBrightness(brightness + signedFadeAmount);
    }
};