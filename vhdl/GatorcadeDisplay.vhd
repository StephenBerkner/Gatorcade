library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use work.LEDMatrixDataTypes.all;


entity GatorcadeDisplay is

    --display driver for interfacing directly with Adafruit 32x32 LED matrix
    --a Cyclone III FPGA will be used to interface with the LED Matrix
    Port (
    	clk 		: in  	std_logic;
	    matrixClk 	: out  	std_logic;
        r1 			: out  	std_logic;
        g1 			: out  	std_logic;
        b1 			: out  	std_logic;
        r2 			: out  	std_logic;
        g2 			: out  	std_logic;
        b2 			: out  	std_logic;
        oe 			: out  	std_logic;
        latch 		: out  	std_logic;
        addr_out 	: out  	std_logic_vector (3 downto 0);
        data 		: in 	RGBLEDMatrix;
		rst 		: in 	std_logic
	);
end GatorcadeDisplay;

architecture BHV of GatorcadeDisplay is

	--5 states for stepping, reading data, shifting data in, latching data, and showing data
	type State is (Step, ReadData, Shift, LatchData, Show);

	signal currentState: State;
	signal nextState: State;
	
	signal lineStep: std_logic;
	signal pixelStep: std_logic;
	signal lineLoad: std_logic;
	signal lineShow: std_logic;
	
	signal addr_out_i : std_logic_vector(3 downto 0);
	signal addr_out_plus : std_logic_vector(4 downto 0);
	signal shift_counter : unsigned(4 downto 0);
	signal show_counter : unsigned(13 downto 0);
	signal pwm_count: unsigned(7 downto 0);
	
	signal R1Values : LEDRow;
	signal G1Values : LEDRow;
	signal B1Values : LEDRow;
	
	signal R2Values : LEDRow;
	signal G2Values : LEDRow;
	signal B2Values : LEDRow;
	
begin

	--concurrent statements
	addr_out_plus(4) <= '1';
	addr_out_plus(3 downto 0) <= addr_out_i;
	
	addr_out <= addr_out_i;

	--oe <= '0' when state = Show else '1';
	oe <= lineStep;
	
	--clock when clock is needed (for shifting and latching)
	matrixClk <= clk when ((currentState = Shift) or (currentState = LatchData)) else '0';
	

	
	process (clk) begin
		if rising_edge(clk) then

			if (rst = '1') then
		

				addr_out_i <= (others => '0');
				
				--set current state back to Step
				currentState <= Step;

				--set shift 
				shift_counter <= (others => '0');
				show_counter <= (others => '0');
				pwm_count <= (others => '0');
			else
				--advance state
				currentState <= nextState;
				
				--Load data in
				if lineLoad = '1' then
					
					--red data
					R1Values <= data(0)(to_integer(unsigned(addr_out_i)));
					R2Values <= data(0)(to_integer(unsigned(addr_out_plus)));
					
					--green data
					G1Values <= data(1)(to_integer(unsigned(addr_out_i)));
					G2Values <= data(1)(to_integer(unsigned(addr_out_plus)));
					
					--blue data
					B1Values <= data(2)(to_integer(unsigned(addr_out_i)));
					B2Values <= data(2)(to_integer(unsigned(addr_out_plus)));
					
					pwm_count <= pwm_count + 1;
				end if;
				
				--if we need to step a line
				if lineStep = '1' then
					--add one to output address
					addr_out_i <= std_logic_vector(unsigned(addr_out_i)+1);
				end if;
				
				--if we need to step a pixel
				if pixelStep = '1' then
					--add one to pixel counter
					shift_counter <= shift_counter+1;
				end if;
				
				--count up to 16384, this is the delay for ligting one row
				if lineStep = '0' then
					show_counter <= show_counter+1;
				else
					show_counter <= (others => '0');
				end if;
				
			end if;
		end if;
	end process;
	

	process (currentState, shift_counter, show_counter)
	begin
	
		--default values
		lineStep <= '0';
		lineLoad <= '0';
		pixelStep <= '0';
		latch <= '0';
		lineShow <= '0';

		case currentState is
	
			when Step =>
				lineStep <='1';
				nextState <= ReadData;
	
			when ReadData =>
				lineLoad <='1';
				nextState <= Shift;
	
			when Shift =>
				pixelStep <='1';
	
				if shift_counter = "11110" then
					nextState <= LatchData;
				else
					nextState <= Shift;
				end if;
	
			when LatchData =>
				latch <= '1';
				nextState <= Show;
	
			when Show =>
				lineShow <= '1';

				if show_counter(5 downto 0) = "111111" then
					if show_counter(13 downto 6) = "11111111" then
						nextState <= Step;
					else
						nextState <= ReadData;
					end if;
				else
					nextState <= Show;
				end if;
			
		end case;
	end process;




	--determine value of r1, r2, g1, g2, b1, b2 outputs
	process(pwm_count)
	begin

		--r1 
		if (R1Values(to_integer(shift_counter)) > pwm_count) then
			r1 <= '1';
		else
			r1 <= '0';
		end if;

		--r2
		if (R2Values(to_integer(shift_counter)) > pwm_count) then
			r2 <= '1';
		else
			r2 <= '0';
		end if;

		--g1
		if (G1Values(to_integer(shift_counter)) > pwm_count) then
			g1 <= '1';
		else
			g1 <= '0';
		end if;


		--g2
		if (G2Values(to_integer(shift_counter)) > pwm_count) then
			g2 <= '1';
		else
			g2 <= '0';
		end if;

		--b1
		if (B1Values(to_integer(shift_counter)) > pwm_count) then
			b1 <= '1';
		else 
			b1 <= '0';
		end if;

		--b2
		if (B2Values(to_integer(shift_counter)) > pwm_count) then
			b2 <= '1';
		else
			b2 <= '0';
		end if;




	end process;

end BHV;

