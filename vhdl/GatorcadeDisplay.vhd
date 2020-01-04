library ieee;
use ieee.numeric_std.all;
use ieee.std_logic_1164.all;
use work.LEDMatrixDataTypes.all;


entity GatorcadeDisplay is

    --display driver for interfacing directly with Adafruit 32x32 LED matrix
    --a Cyclone III FPGA will be used to interface with the LED Matrix
    Port (
    	clk 					: in  	std_logic;
	    data 					: in 	RGBLEDMatrix;
		rst 					: in 	std_logic;
	    matrixClk 				: out  	std_logic;
        r1 						: out  	std_logic;
        g1 						: out  	std_logic;
        b1 						: out  	std_logic;
        r2 						: out  	std_logic;
        g2 						: out  	std_logic;
        b2 						: out  	std_logic;
        outputEnable 			: out  	std_logic;
        latch 					: out  	std_logic;
        matrixAddressLines 		: out  	std_logic_vector (3 downto 0)
        
	);
end GatorcadeDisplay;

architecture BHV of GatorcadeDisplay is

	--5 states for stepping, reading data, shifting data in, latching data, and showing data
	type State is (StepData, ReadData, ShiftData, LatchData, ShowData);

	--state data
	signal currentState			: State;
	signal nextState			: State;
	
	--line and step 
	signal lineStep				: std_logic;
	signal pixelStep			: std_logic;
	signal lineLoad				: std_logic;
	signal lineShow				: std_logic;
	
	--address data
	signal current_address 		: std_logic_vector(3 downto 0);
	signal next_address 		: std_logic_vector(4 downto 0);
	signal indexShift 			: unsigned(4 downto 0);
	signal indexShow 			: unsigned(13 downto 0);
	signal indexPWM				: unsigned(7 downto 0);
	
	--R1, G1, B1 LED Row Data
	signal R1Values 			: LEDRow;
	signal G1Values 			: LEDRow;
	signal B1Values 			: LEDRow;
	
	--R2, G2, B2 LED Row Data
	signal R2Values 			: LEDRow;
	signal G2Values 			: LEDRow;
	signal B2Values 			: LEDRow;
	
begin

	--concurrent statements

	--address concurent statements
	next_address(4) <= '1';
	next_address(3 downto 0) <= current_address;
	matrixAddressLines <= current_address;

	--enable output when appropriate
	outputEnable <= lineStep;
	

	
	process (clk) begin
		if rising_edge(clk) then

			if (rst = '1') then
				
				--reset current address to all 0s
				current_address <= (others => '0');
				
				--set current state back to Step
				currentState <= StepData;

				--reset all counters
				indexShift <= (others => '0');
				indexShow <= (others => '0');
				indexPWM <= (others => '0');

			else
				--advance state
				currentState <= nextState;
				
				--Load data in
				if lineLoad = '1' then
					
					--red data
					R1Values <= data(0)(to_integer(unsigned(current_address)));
					R2Values <= data(0)(to_integer(unsigned(next_address)));
					
					--green data
					G1Values <= data(1)(to_integer(unsigned(current_address)));
					G2Values <= data(1)(to_integer(unsigned(next_address)));
					
					--blue data
					B1Values <= data(2)(to_integer(unsigned(current_address)));
					B2Values <= data(2)(to_integer(unsigned(next_address)));
					
					--increment PWM index
					indexPWM <= indexPWM + 1;

				end if;
				
				--if we need to step a line
				if lineStep = '1' then
					--incremenet output address
					--add one to output address
					current_address <= std_logic_vector(unsigned(current_address)+1);
				end if;
				
				--if we need to step a pixel
				if pixelStep = '1' then
					--add one to pixel counter
					-- go to next pixel
					indexShift <= indexShift+1;
				end if;
				
				--check if we need to step to the next line
				if lineStep = '0' then
					indexShow <= indexShow + 1;
				else
					--reset to 0
					indexShow <= (others => '0');
				end if;
				
			end if;
		end if;
	end process;
	

	process (currentState, indexShift, indexShow)
	begin
		--default values
		--to prevent latches
		matrixClk <= '0';
		lineStep <= '0';
		lineLoad <= '0';
		pixelStep <= '0';
		latch <= '0';
		lineShow <= '0';

		case currentState is
	
			when StepData =>
				lineStep <='1';
				nextState <= ReadData;
	
			when ReadData =>
				lineLoad <='1';
				nextState <= ShiftData;
	
			when ShiftData =>
				pixelStep <='1';
	
				--latch data after all data has been shifted in
				--otherwise continue shifting in data 
				if indexShift = "11110" then
					nextState <= LatchData;
				else
					nextState <= ShiftData;
				end if;

				matrixClk <= clk;
	
			when LatchData =>
				--data must be latched before showing it on the matrix 
				latch <= '1';
				nextState <= ShowData;
				matrixClk <= clk;
			when ShowData =>

				lineShow <= '1';

				if indexShow(5 downto 0) = "111111" then
					
					if indexShow(13 downto 6) = "11111111" then
						nextState <= StepData;
					else
						nextState <= ReadData;
					end if;
				
				else

					nextState <= ShowData;
				
				end if;
			
		end case;
	end process;




	--determine value of r1, r2, g1, g2, b1, b2 outputs
	--determines duty cycles of PWM to determine pixel colors
	process(indexPWM)
	begin

		--r1 
		if (R1Values(to_integer(indexShift)) > indexPWM) then
			r1 <= '1';
		else
			r1 <= '0';
		end if;

		--r2
		if (R2Values(to_integer(indexShift)) > indexPWM) then
			r2 <= '1';
		else
			r2 <= '0';
		end if;

		--g1
		if (G1Values(to_integer(indexShift)) > indexPWM) then
			g1 <= '1';
		else
			g1 <= '0';
		end if;


		--g2
		if (G2Values(to_integer(indexShift)) > indexPWM) then
			g2 <= '1';
		else
			g2 <= '0';
		end if;

		--b1
		if (B1Values(to_integer(indexShift)) > indexPWM) then
			b1 <= '1';
		else 
			b1 <= '0';
		end if;

		--b2
		if (B2Values(to_integer(indexShift)) > indexPWM) then
			b2 <= '1';
		else
			b2 <= '0';
		end if;




	end process;

end BHV;

