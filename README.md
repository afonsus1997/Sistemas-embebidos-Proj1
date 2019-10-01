# Sistemas embebidos-Proj1

### Multi-function Digital Clock 

##### Material

* EXP430G2 LaunchPad;

* TMP100 / TMP101 I2C temp. sensor,;

* Kingbright SA08-11EWA 7-seg. display.

  

**Challenge**: develop a digital clock capable of measuring the ambient temperature.



The system, using an MSP430-based small development board, should implement a digital clock where hours and minutes shall be shown in a display set, formed by 4 7-seg. displays. The 2 left most displays are reserved for the hour while the 2 right most displays will show the minutes; a decimal point in the lower right dot of the second hour display (the right one) will blink at a rate of 1 Hz (1 sec. on, 1 sec. off). Due to HW problems, it is possible that only 2 7-seg. displays will be used, being the minutes shown after the hours with a small interval between the two values.



Using the push buttons (one integrated in the LaunchPad and the other external) it shall implement two operation modes: Clock mode (hour:minute); Temp. mode (2 digit).

In the Clock mode, the system will show the time as previously described; the time can be set by the user through the activation of a combination of the push buttons.

In the Temp. mode, upon the activation of one of the push buttons, the displays should show the temperature measured by the temperature sensor in ºC.