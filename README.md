# ESP-Weather-Station
In this I have Used ESP8266 NodeMcu v1.0 to detect temperature, barrometric pressure, humidity, altitude.
Compile and Uload The Sketch
I also created a localhost (server) on that NodeMcu and created a webpage which will be accessed by the IP address to that specific NodeMcu.
Then I created an simple Web Browser (client) Application Using Android Studio which oppens and only connects to that localhost IP address.
After that connected the NodeMcu and the android phone in same network and "voila..." everything works as planned. 

N.B:: all the library which are used in the NodeMcu programme are from adafruit and you can get those on Manage Library(Ctrl+Shift+I) 
option on Arduino IDE. There search or DHT11, BMP180, Adafruit Unified Sensor. Download all those library.
