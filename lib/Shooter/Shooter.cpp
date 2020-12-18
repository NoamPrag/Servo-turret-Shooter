#include <Shooter.h>

static const int realeaseAngle = 60;
static const int shootAngle = 110;

Shooter::Shooter(const unsigned int pin)
    : releaseAngle(releaseAngle),
      shootAngle(shootAngle),
      servoPin(pin){};

void Shooter::shoot()
{
    this->write(shootAngle); // Pull the trigger.

    delay(500); // Wait half a second.

    this->write(releaseAngle); // Turn back to the default angle.

    delay(500); // Wait another half a second.

    Serial.print("SHOOT!! :)");
};

void Shooter::reset()
{
    this->attach(this->servoPin); // Attach the servo to its pin.

    write(releaseAngle); // Set the servo to its released angle.

    delay(1000); // Wait a second.

    Serial.println("Shooter Reset. :)"); // Print that shooter has been reset.
};