#include <Servo.h> 
#include <NewPing.h>

const int servoPin = 9;
const int trigPin = 12;
const int echoPin = 11;
const int maxDist = 100;  // Max detection range in cm

NewPing sonar(trigPin, echoPin, maxDist);
Servo servo_test;

bool objectPicked = false;  // Tracks whether an object is being held

void setup() {
    Serial.begin(9600);
    servo_test.attach(servoPin);
    servo_test.write(0);  // Start with the claw open (0°)
}

void loop() {
    int dist = sonar.ping_cm();
    Serial.print("Distance: ");
    Serial.println(dist);

    // Close claw when object is detected
    if (!objectPicked && dist > 0 && dist <= 15) {
        delay(1000);
        servo_test.write(90);  // close claw
        delay(5000);  // time to grip object
        objectPicked = true;  // claw is now holding the object
    }

    // Wait until sensor detects the ground again
    if (objectPicked) {
        while (true) {
            int groundDist = sonar.ping_cm();

            if (groundDist > 0 && groundDist <= 10) {  // close to the ground
                servo_test.write(0);  // open claw (release object)
                delay(2000);  // wait to ensure object is released
                objectPicked = false;  // claw is now empty
                break;
            }

            delay(250);  
        }
    }

    delay(125);  // Short delay before next loop iteration
}
