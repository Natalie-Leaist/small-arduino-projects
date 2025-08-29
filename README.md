# small-arduino-projects

This repo contains some small arduino projects I have worked on.

## Simon Game
As a final project for my Introduction to C Programming Course (APSC 160), I was tasked with making a replication of The Simon Game using Arduino. Here’s how the Simon Game works:
- The game device has four coloured buttons: red, green, blue, yellow
- At the start, the game plays a single tone while lighting up one button
- The player must then press that same button
- On the next round, the game repeats the first light and sound, then adds a new one to the sequence
- The player now has to press both buttons in the right order
- Each round, the sequence is lengthened by one step
- If the player successfully repeats a sequence of length five, then they win!

The code handles the full game loop, including sequence generation, LED flashing, button input detection, and sequence comparison. A complementary set of helper functions manage pin setup, button-to-LED mapping, LED flashing, and input checking.

You can also view the project on TinkerCad [here.](https://www.tinkercad.com/things/jeuRpwNNCBP-simongame?sharecode=AK7lE3eDWVR4nnuOETv-xQTbmmfy_daz_ArlXevUN18)

## Semi-autonomous Claw
As a project in my Introduction to Engineering Course (APSC 100), we were tasked with working in groups of 4 to create a semi-autonoumous robotic claw to locate, grasp and transport small objects. I worked on both the software and mechanical design. On the software side, I programmed the arduino to sense the ground (using an ultrasonic sensor) and open/close the claw by controlling a servo motor. 
