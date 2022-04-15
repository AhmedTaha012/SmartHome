# Smart Home 
Can you imagine your home when connected to internet and
you can know happens your home it’s temperature , lights on
or off ,air conditional and fans control ,password and
fingerprint for your entrance and when any one goes in you can
know him so we define all of this as smart home , everything is
smart in your home, so we implement some sensors like
(temperature, flame, rfid , finger print , light detective
resistance ) and some motors and relays to can control the
devices in your home like (fans , air conditioner).
# MAIN IDEA
Our project is small smart home which can show you some
content of any smart it’s just proof of concept of smart home,
So we use some sensor inside home like flame , temperature to
know if there is fire in your home then sends the state to
ubidots site which we use to can control the home and takes
the reading from the sensor inside the home by using our main
chip the nodemcu esp8266 which is the main part in our home
The section which include the door is contains a lot of privacy
features like keypad to insert password and RFID to check your
id then finger print sensor
The section which include the parking is consist of IR sensor to
detect the car.

# HOME SECTIONS
INSIDE HOME: include all sensors in home and relays to
control device
 OUTSIDE HOME
• PARKING : include sensor to open door when car enters
• Door: include RFID sensor, lcd to enter password from keypad
• Control unit : include Nodemcu esp8226 and voltage source to control all the sensors and outputs
connected to it

## INSIDE HOME SECTION
Inside our home we use many sensors and actuators which
includes:
Flame sensor : Flame sensor is the sensor which use to detect
there is flame or not it’s contains Vcc pin which we connected it
to 3.3v from nodemcu and Ground pin which we connected
ground of nodemcu then takes its outputs our flame sensor is
can work digital or analog we used the digital one which gives
one when there is aflame and zero when not ,The opposite
figure shows the flame sensor module .


Temperature sensor:
Inside our home we used lm35 is Temperature sensor, whose
output voltage varies, based on the temperature around it. It is
a small and cheap IC which can be used to measure
temperature anywhere between -55°C to 150°C. So we use it to
know the temperature inside home and sends it to our
dashboard in ubidots , the lm35 is consists of 3 pins one Vcc to
Nodemcu and another one to ground and the third one is
analog pins which takes the reading. The opposite figure shows
the lm35.

Relays: inside our home we use relay to can control an AC
device like fan our phone charger we use relay since we can’t
drive 220v AC from Nodemcu so we connect switch to the AC
source and open when the relay takes high input the AC source
is open so our device will operate when the relay takes low the
Switch off .there two figure which shows the relay module and
what is inside the module

We connect two lamps to relay and AC sources which connect
to relay we connect from dashboard of ubidots sites .
3.2 OUTSIDE HOME SECTION
Door section: we used lcd to view want wants from you to
enters the door the first asks you to put your finger print so we
used finger print sensor then asks to pass the ID so we used and
RFID sensor to check if your id is true or not the asks to enter
password so we used keypad to enters the password if the
password is wrong the Nodemcu send an email that’s wrong password is enter.


## Parking section:
we needs the parking door to open when the
car is enter so we used an servo motor which connected to the
IR sensor which check if there is something passes or not


## Control unit section:
In the control unit we used an nodemcu esp8622 which is
contains an wifi module and lots of communications protocols
like spi,i2c,uart and gpio put the pins is not enough so we used
shift register to can connect many digital pins and multiplexer
to can connect many analog pins .
The opposite figures shows
The nodemcu esp8266


# UBIDOTS
So now we need our system to be connected the internet and
sends the data to internet and sends mail when wrong
password is insert or when there is fire in home so we choose
an UBIDOTS site which shows our variables in dashboards and
can control the relay by put switch to on and off lamps and all ,
and we can makes an events to happened when any variables
change like if the temperature is high will send notification that
it’s hot inside your home .the figure shows you the dashboard
that views you the variables changes and switches .
