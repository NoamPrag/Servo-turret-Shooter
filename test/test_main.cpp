#include <Arduino.h>
#include <unity.h>
#include <LED.h>

UnityTestFunction testLEDBlink(
    LED *testLED,
    const unsigned int seconds,
    const unsigned int onTime,
    const unsigned int offTime,
    const unsigned int brightness)
{
    return []() {
        const unsigned long startTime = millis();
        unsigned long currentTime = startTime;
        while (currentTime - startTime < 5 * 1000) // Five Seconds Test.
        {
            currentTime = millis();
            // led->blink(100, 500, 200);
        }
    };
};

UnityTestFunction f(int x)
{
    UnityTestFunction x = []() -> void { return; };
    // return x;
    return []() -> void { return; };
}

void loop()
{
    RUN_TEST(testLEDBlink(&LED(9), 1, 1, 1, 1));
};