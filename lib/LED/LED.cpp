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
    const int start,
    const int end,
    const unsigned long time)
{
    if (abs(brightness - prevBrightness) == 1)
    {
        if (brightness == end)
            return;
    }
    else if (brightness != start)
    {
        setBrightness(start);
        return;
    }

    const unsigned long timeToChange = start == end ? INFINITY : time / abs(end - start);
    const unsigned long currentTime = millis();

    if (currentTime - changeTime >= timeToChange)
    {
        setBrightness(this->brightness + ((end - start) > 0 ? 1 : -1));
        changeTime = currentTime;
    }
};

void LED::blinkFade(const int start, const int end, const unsigned long time)
{
    const int dBrightness = brightness - prevBrightness; // How much has changed.

    if (abs(dBrightness) != 1) // first and second call.
    {
        fade(start, end, time);
        return;
    }

    /*
    * Checking for the current direction of the fade.
    * When reaches the edge, flip the direction,
    * and proceed until reaching the other one.
    */
    if (dBrightness > 0 == (end - start) > 0) // xnor gate

        if (brightness == end)
            fade(end, start, time);
        else
            fade(start, end, time);

    else if (brightness == start)
        fade(start, end, time);
    else
        fade(end, start, time);
};