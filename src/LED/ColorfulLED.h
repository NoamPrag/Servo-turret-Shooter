#include <LED/LED.h>

class ColorfulLED
{
private:
    LED redLED;
    LED greenLED;
    LED blueLED;

public:
    ColorfulLED(const int redPin, const int greenPin, const int bluePin);

    void setColor(
        const int red,
        const int green,
        const int blue);

    void blink(
        const int red,
        const int green,
        const int blue,
        const int onTime,
        const int offTime);

    void fade(
        const int startRed,
        const int startGreen,
        const int startBlue,
        const int endRed,
        const int endGreen,
        const int endBlue,
        const int time);
};