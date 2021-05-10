#include <Arduino.h>

class LED
{
private:
    const unsigned int pin;
    byte brightness = 0, prevBrightness = 0;
    unsigned long changeTime = 0;

public:
    explicit LED(const unsigned int pin);

    void setBrightness(const byte brightness);

    const byte getBrightness();

    void turnOff();

    void blink(const unsigned int onTime, const unsigned int offTime, const byte brightness);

    void fade(const byte start, const byte end, const unsigned long time);

    void blinkFade(const byte start, const byte end, const unsigned long time);
};