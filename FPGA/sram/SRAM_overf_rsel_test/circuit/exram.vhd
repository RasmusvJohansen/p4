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
    Port ( D : inout  STD_LOGIC_VECTOR (7 downto 0); -- Databus imellem, FSM og SRAM
			  Di: in std_logic_vector(7 downto 0); -- Input Data
			  DATA_out: out std_logic_vector(7 downto 0); -- Output til LED'er til at vise output data
           led : out  STD_LOGIC_VECTOR (7 downto 0); -- Bliver ikke brugt i denne kode
           ADR : out  STD_LOGIC_VECTOR (18 downto 0); -- ADR signal til SRAM
			  ADRI : out STD_LOGIC_VECTOR(1 downto 0); -- midlertidigt output der bruges til fejlfinding
           CS : out  STD_LOGIC; -- Chip select signal til SRAM
           WE : inout  STD_LOGIC; -- Write enable signal til SRAM
           OE : inout  STD_LOGIC; -- output enable signal til SRAM
           a : out  STD_LOGIC; -- bliver ikke brugt
           b: out  STD_LOGIC; --bliver ikke brugt
           clk : in  STD_LOGIC; --klok signal
			  rw : in std_logic; -- rw signal fra arduino
			  mem : in std_logic -- memory operation fra arduino
			  );
end exram;
 
architecture Behavioral of exram is
signal sclk: STD_LOGIC;
signal cnt: STD_LOGIC_VECTOR (30 downto 0); -- bruges til en clk-divider
signal DO: STD_LOGIC_VECTOR (7 downto 0) := "00000001"; -- signal der bruges til at overføre input signalet til D
--signal data: std_logic_vector(7 downto 0) := "00000000"; -- sæter input data til 0
signal state_reg: STD_LOGIC_VECTOR (1 downto 0) :="00"; -- state for testing
signal state_next: STD_LOGIC_VECTOR (1 downto 0); 
signal WEint: STD_LOGIC := '1'; -- internal state for WE initially 1 (read)
--signal counter: std_logic_vector(18 downto 0):="0000000000000000000";
begin
ADR <= "0000000000000000001"; --address no 1
--ADR(1 downto 0) <= ADRI(1 downto 0);
--LED(7 downto 0) <= ADR(7 downto 0);
OE <= not WE; -- OE må ikke være det samme som WE, og tændes og slukkes i to forskelliges states
--CS <= '0'; -- chip always selected
sclk <= cnt(5); -- slow clk
--led(6 downto 0) <= Data_out(6 downto 0);
--led(7) <= WE; --check whether D is tristated - tristated for WE=1
WE <= WEint;
--data <= D; --opdaterer data med hvad der ligger på D
--b <= WE; --oscilloscope output
--a <= D(0); --oscilloscope output
--a <= adr(0); 
-- tristate output gate of D when reading OE='0', WE='1'
--with OE select D <= 
--			DO when '0', -- open output gate of D when writing OE='1', WE='0'
--			data  when '1',
--			(others => 'Z') when others; -- tristate output gate of D when reading OE='0', WE='1'

process ( CLK) -- Denne process har til formål at skrive dataen til SRAM'en eller læse og sætte det på output pins
		begin
			if rising_edge(clk) then
				case (oe) is 
					when '0' => -- OE er 0, og vi skriver til SRAM ved at sætte DO på D som går til SRAM
						D <= Di;
					when '1' => --OE er 1, data tager det der ligger på D og sætte ud på LED, der sider på DATA_OUT
						data_out <= D;
					when others =>
						D <= (others => 'Z');
				end case;
			end if;
end process;



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
	case (mem) is  -- mem sikrer at vi ønsket en memory operation. Derved kan rw kun ændres hvis mem = 1
	when '1' =>
		if (rw = '1') then
			state_next <= "10";  -- rw er sat til 1 og vi læser derfor fra SRAM
		elsif (rw = '0') then
			state_next <= "01"; -- rw er sat til 0 og vi skriver derfor til SRAM
		end if;
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
      when "00" => -- IDLE case
         --state <= "01"; -- next state in next slow xlk state
			state_reg <= state_next;
			ADRI(0) <= '1';
			ADRI(1) <= '0';
			CS <= '1';
		when "01" => -- Skrive Case
         WEint <= '1'; --weint styrer både OE og WE, OE er WE negeret
         --state <= "10"; -- next state in next slow xlk state
			state_reg <= state_next;
			--counter <= counter + "0000000000000000001";
			--adr <= adr + 1;
			CS <= '0';
			ADRI(1) <= '0';
			ADRI(0) <= '0';
			--DO <= Di; 
      when "10" => -- læse case 
         WEint <= '0'; -- weint styrer både OE og WE, OE er WE negeret
			
			ADRI(1) <= '1';
			ADRI(0) <= '0';
			--DO <= DO+1; 
			state_reg <=state_next;
			CS <= '0';
       when others =>
         state_reg <= "00";
   end case;
     
   end if;
end process;
 
end Behavioral;



