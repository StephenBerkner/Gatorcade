library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

package LED_matrix_type_package is

	--data type for brightness of the red, green, or blue LED in each coordinate of the matrix
	subtype SingleColorLED is unsigned(7 downto 0);

	--data type for the row of LEDs
	type LEDRow is array (0 to 31) of SingleColorLED;


	--data type for the LED matrix containing 32x32 LEDs of a single color
	type SingleColorLEDMatrix is array (0 to 31) of LEDRow;
	
	--data type for the LED matrix containing 32x32 RGB LEDs
	type RGBLEDMatrix is array (0 to 2) of SingleColorLEDMatrix;
	
	
	--this needs to be changed to 27 for a base of 5
	--array of frames for player 1 paddle
	type P1_Values is array (0 to 27) of RGBLEDMatrix; 

	--array of frames for player 2 paddle
	type P2_Values is array (0 to 27) of RGBLEDMatrix;

	--array of frames for ball
	type Ball_Values is array (0 to 503) of RGBLEDMatrix; 

	



end LED_matrix_type_package;

package body LED_matrix_type_package is

end LED_matrix_type_package;
