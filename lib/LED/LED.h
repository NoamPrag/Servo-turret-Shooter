#include <Arduino.h>

class LED
{
private:
    const unsigned int pin;
    int brightness = 0, prevBrightness = 0;
    unsigned long changeTime = 0;

public:
    explicit LED(const unsigned int pin);

    void setBrightness(const unsigned int brightness);

    const unsigned int getBrightness();

    void turnOff();

    void blink(const unsigned int onTime, const unsigned int offTime, const unsigned int brightness);

    void fade(const int start, const int end, const unsigned long time);

    void blinkFade(const int start, const int end, const unsigned long time);
};