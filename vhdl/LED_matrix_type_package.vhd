library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

package LED_matrix_type_package is

	subtype LED is unsigned(7 downto 0);

	type LED_line is array (0 to 31) of LED;

	type LED_array is array (0 to 31) of LED_line;
	
	type RGB_LED_array is array (0 to 2) of LED_array;
	
	
	--this needs to be changed to 27 for a base of 5
	type P1_Values is array (0 to 27) of RGB_LED_array; 

	type P2_Values is array (0 to 27) of RGB_LED_array;

	type Ball_Values is array (0 to 503) of RGB_LED_array; 

	



end LED_matrix_type_package;

package body LED_matrix_type_package is

end LED_matrix_type_package;
