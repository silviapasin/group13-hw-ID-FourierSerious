# group13-hw-ID-FourierSerious
Group 13 repository for the ID homework of CMLS 2022

# Group FourierSerious - Components:
- Manuel Alejandro Jaramillo Rodríguez
- Marcello Grati
- Maria Gracia Fernandez
- Silvia Pasin
- Natasa Popovic

# POSTACCIO INVADERS
![GUI1](https://github.com/polimi-cmls-22/group13-hw-ID-FourierSerious/blob/main/GUI1.png?raw=true)

# Project description:
POSTACCIO INVADERS is a multiplayer music video game with an interface consisting of a piano at the top, a small selection screen at the bottom and in the center the spaceship's movement space. The goal is that the player, driving the spaceship, must dodge the "bullets" launched by the keyboard, which is controlled by another player from a midi keyboard and without seeing the interface. In order to dodge the bullets, the ship will move through the interface changing the parameters that appear at the bottom, and he can also change some types of parameters through the conductivity switch sensor, making the notes played by the opposing player sound differently based on the position of the ship at each moment. The game ends the moment a bullet hits the ship.

# Instructions:
In order to try Postaccio Invaders, you need to:
1. download the code
2. run in Bela the code "Main.cpp" that you can find in the folder "FourierSerious"
3. run the JUCE plugin SubSynthHW3 that you can find in the folder "SubSynthHW3"
4. run the Processing file "HW3Processsing.pde" that you can find in the folder "Processing"
5. connect a MIDI keyboard or use a virtual MIDI instrument to play a melody
6. enjoy the game!


# Controls and Interface:

![GUI](https://github.com/polimi-cmls-22/group13-hw-ID-FourierSerious/blob/main/GUI.png?raw=true) 

The spaceship can move freely through the interface to escape from the bullets thrown by the piano. Its movement will be done through the joystick both in its X and Y axis; however, performing these actions not only moves the ship, but also allows the user to play with other parameters of the system. When he moves on the X axis (analogX) he will control the cutoff frequency of the filter he has at that moment. Meanwhile, with the Y axis (analogY) he can change the type of filter so that, when the spaceship goes up it will correspond to a high pass filter, in the middle it will be a band pass filter and, if it is the farthest away from the piano, it will be a low pass filter. It should be noted that the frequency that is controlled with the analogX is mapped logarithmically. That is, the relationship between the range of joystick values (from 0 to 1) and the filter cutoff frequency range (from 65Hz to 523Hz), will be logarithmic in order to obtain a higher resolution in the low frequencies.
      On the other hand, through the conductivity switch sensor the user will be able to vary the oscillator waveform. He can choose between sine, saw, square, triangle and white noise while continuing to control the ship, so that he can look for a better sonority while continuing to dodge bullets, giving rise to another challenge for the player.
      The score obtained is based on the number of bullets dodged, and is recorded and displayed to the player in the lower left corner of the screen along with the rest of the parameters mentioned above.
