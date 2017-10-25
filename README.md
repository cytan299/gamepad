# How to make BLUNO-Bee (BLE-Link) and DFRobot Wireless Gamepad v2 into Bluetooth low power (BLE, Bluetooth LE) HID Keyboard

It seems that there are not very good instructions on how to create a HID keyboard device from a BLUNO-BEE (BLE-LINK) and a DFRobot Wireless Gamepad V2. The instructions for doing this are in _instructions/instructions.pdf_

The Arduino program is _gamepad.ino_.

It is a *TERRIBLE* program that is only good for pedagogical purposesonly. It is totally unsuitable for playing games because it is pathetically slow! I'm sure hackers can get this code working at a faster clip, but my interest in it faded after I discovered that BLE keyboard devices are *not* supported in Raspbian, i.e. BLE keyboard devices are not supported in Raspberry PI 3 as of this writing (Oct 2017).

The gamepad.ino has been tested to work on a Mac, IPAD and IPhone. Once paired, you can open an editor or an input box, like the url input of Chrome, to see the gamepad in action. Pressing any buttons on the gamepad will generate a letter. The left joystick mimics the arrow keys on the keyboard.

I have conveniently included the required library _blehid_v2.zip_ that is necessary for compiling _gamepad.ino_. The file _DFBLE.cpp_ has replaced _Serial_ with _Serial1_ from the original distribution. This is because the _Leonardo_ in the Wireless Gamepad talks to the BLUNO-BEE using _Serial2_.

## Copyright

All the documentation and pictures that I have here is
copyright 2017 C.Y. Tan and released under Creative Commons
Attribution-ShareAlike 3.0 Unported License.

All software that is written by C.Y. Tan is released under GPLv3.
