# LEDFlights

## Introduction

LEDFlights is my first C++ project, created during my month-long winter break from Macquarie University. The goal of this project was to get hands-on experience with C++ by building something practical and fun, and to build a gift for my partner who loves planes. LEDFlights connects to the OpenSky Network API, retrieves live flight data, and displays it on an LED matrix panel. Throughout the development process, I learned about C++ syntax, object-oriented programming, and working with hardware interfaces on the ESP32 platform. This project represents my journey into C++ and embedded systems, combining software and hardware in a real-world application.

## Software

LEDFlights starts by connecting to wifi or starting an access point to be configured if it cannot find a saved network. Then it syncs with a time server to get the local time, as when it is not displaying plane information, it acts as a simple clock. It will ping the OpenSky API to retrieve any flights within a specified latitude and longitude. These settings can be configured by accessing a web server hosted on the ESP32, or at `ledflights.local`. The configuration is saved and persists across reboots.

### Improvements

Given my limited knowledge of C++ and time constraints, I recognise that many improvements could be made to the software (and hardware for that matter). For example, the validation of an updated configuration only checks data types and only checks bounds for numeric parameters.

As the complexity of my code increased, I feel some of the classes should be refactored, for example, `NetworkManager` also handles some of the configuration logic, which seems like poor design.

My excessive use of converting strings from `std::string` to C-style strings may introduce unnecessary overhead and/or stability issues.

If I had more time and could start again, I would create my own web server and store preferences in a JSON file on the ESP32's non-volitile memory, as this would provide me greater flexibility to have the configuration portal look how I want, as well as make validation easier, as currently `WiFiManager` returns all custom parameters as a string.

Using a JSON file would also enable me to store previous flight information, allowing me to display older flights in addition to the most recent result from the API. I could also add preferences to let the user decide what plane information is shown on each line of the display, instead of hard coding it.

## Hardware

I purchased most of the hardware used in this project from Amazon, including the [Waveshare RGB matrix](https://www.waveshare.com/wiki/RGB-Matrix-P3-64x32) and the [Freenove ESP32-S3-WROOM](https://www.amazon.com.au/Freenove-ESP32-S3-WROOM-Dual-core-Microcontroller-Wireless/dp/B0DHJZ1V81).

I 3D printed a [case](https://www.thingiverse.com/thing:4009726/files) for the display and remixed this [mounting bracket](https://www.thingiverse.com/thing:4818439) and [ESP32 case](https://www.thingiverse.com/thing:4685532/files) on Tinkercad to create a case that mounts to the rear of the display, while still allowing easy access to the USB-C ports. My remixed STL can be found in the `stl` folder. I also bought a piece of transparent grey acrylic to cover the front of the display.

## Images

### Final Plane Display

![](img/Final%20Front%20Plane.jpg)

### Final Time Display

![](img/Final%20Front%20Time.jpg)

### Final ESP32 Mount

![](img/Final%20Back.jpg)

### Front With Case

![](img/Front%20with%20Case.jpg)

### Prototype Plane Display

![](img/Prototype%20Plane%20Display.jpg)

### Prototype Time Display

![](img/Prototype%20Time%20Display.jpg)

### Prototype ESP32 Mount

![](img/Prototype%20ESP%20Holder.jpg)

### First Display Test

![](img/Text%20Display.jpg)