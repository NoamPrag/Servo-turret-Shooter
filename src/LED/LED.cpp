#include <LED/LED.h>

LED::LED(const unsigned int pin) : pin(pin)
{
    pinMode(pin, OUTPUT);
};

void LED::setBrightness(const unsigned int value)
{
    analogWrite(pin, value);
    brightness = value;
}

void LED::turnOff()
{
    analogWrite(pin, 0);
    brightness = 0;
}

void LED::blink(const unsigned int onTime, const unsigned int offTime, const unsigned int brightness)
{
    const unsigned long currentTime = millis();

    if (this->brightness <= 0)
    {
        if (currentTime - this->changeTime >= offTime)
        {
            setBrightness(brightness);
            changeTime = currentTime;
        }
    }
    else if (currentTime - this->changeTime >= onTime)
    {
        turnOff();
        changeTime = currentTime;
    }
}

void LED::fade(const unsigned int start, const unsigned int end, const unsigned long time)
{
    const unsigned long currentTime = millis();
    const float brightPerTime = (start - end) / time;

    // checking if brightness is not in range
    if ((this->brightness > start && this->brightness > end) || (this->brightness < start && this->brightness < end))
    {
        setBrightness(start);
        changeTime = currentTime;
    }
    else
    {
        const int brightness = this->brightness + ceil((currentTime - changeTime) * brightPerTime);
        if (this->brightness <= end + brightPerTime && this->brightness >= end - brightPerTime)
        {
            setBrightness(end);
            changeTime = currentTime;
            return;
        }
        setBrightness(brightness);
    }
}