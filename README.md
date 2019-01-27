# off-on-disconnect



//README is still work in progress

## Starting point

In an energy-saving-spree, I noticed my internet-modem was drawing 10 watts of energy. No matter the settings of it, it's always 10 watts, even with WiFi off. Removing its WiFi cards lead to a 3 watts reduction, but also to a modem stuck in a bootloop. The only way I saw to save energy on the thing, was switching it off when I'm sure I don't use it: during bedtime. That's what this project is about.



> Automatically switching off my internet-modem during bedtime, that's what this project is about.



I already set my router to switch off WiFi at scheduled times and found my modem should do the same. 

### My personal requirements

I wanted this project to be:

- Energy-saving

- Automonous, so I don't need to look at it once installed. It should switch off my modem automatically when WiFi is off

- Offline, so not being connected to the internet or WiFi

  

## Requirements

Besides wires and soldering stuff and skills you will need:

- A router with WiFi, which availability is scheduled

- A device you want to switch off whenever WiFi is switched off

- A ESP-8266 based development board (I used a Wemos D1 mini)

- Power-supply for the development board, preferably the same as for your device

- A 220V relais



## Future improvements

- Make use of the ESP-8266 ability to go in deep-sleep in between its checks
