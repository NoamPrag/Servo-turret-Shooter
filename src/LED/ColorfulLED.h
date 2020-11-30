#include <LED/LED.h>
#include <LED/Color.h>

class ColorfulLED
{
private:
    LED redLED;
    LED greenLED;
    LED blueLED;

public:
    ColorfulLED(
        const int redPin,
        const int greenPin,
        const int bluePin);

    void setColor(const Color color);

    void blink(
        const Color color,
        const int onTime,
        const int offTime);

    void fade(
        const Color startColor,
        const Color endColor,
        const int time);
};