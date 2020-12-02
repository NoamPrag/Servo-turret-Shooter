#include <Arduino.h>

class LED
{
private:
    const unsigned int pin;
    unsigned int brightness = 0, prevBrightness = 0;
    unsigned long changeTime = 0;

public:
    LED(const unsigned int pin);

    void setBrightness(const unsigned int brightness);

    void turnOff();

    void blink(const unsigned int onTime, const unsigned int offTime, const unsigned int brightness);

    void fade(const int start, const int end, const long time);
};