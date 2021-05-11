library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;
 
use ieee.std_logic_unsigned.all;
 
-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;
 
entity exram is
    Port ( D : inout  STD_LOGIC_VECTOR (7 downto 0);
				--Di: in std_logic_vector(7 downto 0);
           led : out  STD_LOGIC_VECTOR (7 downto 0);
           ADR : out  STD_LOGIC_VECTOR (18 downto 0);
			  ADRI : out STD_LOGIC_VECTOR(1 downto 0);
           CS : out  STD_LOGIC;
           WE : inout  STD_LOGIC;
           OE : inout  STD_LOGIC;
           a : out  STD_LOGIC; --to oscilloscope
           b: out  STD_LOGIC; --to oscilloscope
           clk : in  STD_LOGIC;
			  rw : in std_logic;
			  mem : in std_logic
			  );
end exram;
 
architecture Behavioral of exram is
signal sclk: STD_LOGIC;
signal cnt: STD_LOGIC_VECTOR (30 downto 0);
signal DO: STD_LOGIC_VECTOR (7 downto 0) := "00111000";
signal state_reg: STD_LOGIC_VECTOR (1 downto 0) :="00"; -- state for testing
signal state_next: STD_LOGIC_VECTOR (1 downto 0);
signal WEint: STD_LOGIC := '1'; -- internal state for WE initially 1 (read)
--signal counter: std_logic_vector(18 downto 0):="0000000000000000000";
begin
ADR <= "0000000000000000001"; --address no 1
--ADR(1 downto 0) <= ADRI(1 downto 0);
--LED(7 downto 0) <= ADR(7 downto 0);
OE <= not WE; -- never read and write simultaneously
CS <= '0'; -- chip always selected
sclk <= cnt(25); -- slow clk
led(6 downto 0) <= D(6 downto 0);
led(7) <= WE; --check whether D is tristated - tristated for WE=1
WE <= WEint;
--b <= WE; --oscilloscope output
--a <= D(0); --oscilloscope output
--a <= adr(0); 
-- tristate output gate of D when reading OE='0', WE='1'
with OE select
      D <= DO when '1', -- open output gate of D when writing OE='1', WE='0'
      (others=>'Z') when others; -- tristate output gate of D when reading OE='0', WE='1'
 
process (clk) --clk process, der driver sclk (slowclk)
begin 
   if (clk'event and clk = '1') then
      cnt <= cnt + 1;
   end if;
end process;
-- next state logic
process(clk,state_next)
	begin
	if (clk'event and clk = '1')then
	case (mem) is
	when '1' =>
		if (rw = '1') then
			state_next <= "10";
		elsif (rw = '0') then
			state_next <= "01";
		end if;
	when '0' =>
		state_next <= "00";
	when others =>
		state_next <= "00";
	end case;
	end if;
end process;



-- FSM
process (sclk)
begin 
   if (sclk'event and sclk = '1') then
             
      case (state_reg) is
      when "00" =>
         --state <= "01"; -- next state in next slow xlk state
			state_reg <= state_next;
			ADRI(0) <= '1';
			ADRI(1) <= '0';
		when "01" => 
         WEint <= '0'; --negative edge on WE - start write
         --state <= "10"; -- next state in next slow xlk state
			state_reg <= state_next;
			--counter <= counter + "0000000000000000001";
			--adr <= adr + 1;
			
			ADRI(1) <= '0';
			ADRI(0) <= '0';
      when "10" =>
         WEint <= '1'; --stop writing - enable output
         DO <= DO+1;
			ADRI(1) <= '1';
			ADRI(0) <= '0';
			--DO <= D; 
			state_reg <=state_next;
       when others =>
         state_reg <= "00";
   end case;
     
   end if;
end process;
 
end Behavioral;

