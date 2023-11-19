# Women-Safety-Device

Hi! This "IOT Based Women Safety Device",meant to help the women whenever they're in dangerous situations
Basically this Device is Alerting device that is ,when the device is manually triggered,it would automatically make calls or messages to their parents or guardians


#######################
# Components Required #
#######################

1.Arduino Uno/Arduino Nano
2.GSM Module Sim 800L(works perfectly with SIM 900A ,However the code is optimized to work with other GSM Modules)
3.GPS Module NEO 6M
4.A Led(for debugging /notification )
5.A pushbutton(with pull down resistor )


...............
. Connections .
...............

GSM                |  ARDUINO
RX,TX              |  6,5
                   |
GPS                |  ARDUINO
RX,TX              |  3,4
                   |
PUSHBUTTON         |  ARDUINO
(pulldown out)     |  2
                   |
LED                |  ARDUINO
anode              |  7

also create a account in ThinkSpeak and Change your API 
Also Update the code with your Phone Numbers


------------------------------
| Working and Functionalites |
------------------------------

# For every One Minute the current location will be Updated on ThinkSpeak
# While Updation the LED will glow,at this time no other function will be engaged
# When the device is idle ,and the push button is pushed once, a text message with location details will be passed to the associated phone number
# While message pass the LED will Blink Twice and thinkSpeak updation will disengaged and will be ready to perform next operation
# After pressing the Button twice the LED with start to beat for 40 time on Series at 1 second of interval ,at this time continuous calls will be done to that associated number
# Press and hold the button just when the LED stops beating to disengaged from call functions
# When Disengaged the LED will be turned ON while updating the location in Thinkspeak
# If the button is pressed again it immediately jumps to calling function
# Repeat the previous step to disengage the function


Hope You Like it ! Thank You

