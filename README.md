# ABPlayer Mini - AudioBook Player
This is the code for ABPlayer Mini, an audiobook player based on the DFPlayer Mini Module.

More details about the hardware project [on Hackaday.io](https://hackaday.io/project/168330-abplayer-mini-audiobook-player).

Still under heavy development.

## Details
  * The code runs on an ATTiny85 microcontroller
  * Uses the [DFMiniMp3 library](https://github.com/Makuna/DFMiniMp3) by Makuna
  * The ATTiny85 communicates with the DFPlayer Mini module using SoftwareSerial
  * The SSD1306 LCD Display is used mostly for debugging 
  * The hardware has 4 buttons each has a short and long press inputs:
	* Button 1 (short) - Play previous track
	* Button 1 (long) - Decrease volume
	* Button 2 (short) - Play/Pause
	* Button 2 (long) - Low power mode
	* Button 3 (short) - Play next track
	* Button 3 (long) - Increase volume
	* Button 4 (short) - Wake up
	* Button 4 (long) - Sleep
  * Powered by an 18650 battery

