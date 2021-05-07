#include <LED.h>
#include <Color.h>

class ColorfulLED
{
private:
    LED redLED;
    LED greenLED;
    LED blueLED;

public:
    ColorfulLED(
        const unsigned int redPin,
        const unsigned int greenPin,
        const unsigned int bluePin);

    void setColor(const Color color);

    const Color getColor();

    void turnOff();

    void blink(
        const Color color,
        const unsigned int onTime,
        const unsigned int offTime);

    void fade(
        const Color startColor,
        const Color endColor,
        const unsigned int time);

    void blinkFade(
        const Color startColor,
        const Color endColor,
        const unsigned int time);
};