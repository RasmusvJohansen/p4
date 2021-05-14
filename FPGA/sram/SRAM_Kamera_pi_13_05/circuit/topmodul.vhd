----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    09:28:03 05/07/2021 
-- Design Name: 
-- Module Name:    topmodul - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity topmodul is
    Port ( sram_data			: inout  STD_LOGIC_VECTOR (7 downto 0); 		-- Databus imellem, FSM og SRAM
			  Di2					: in std_logic_vector(7 downto 0); 				-- Input Data
			  --DATA_out	: out std_logic_vector(7 downto 0); 			-- Output til LED'er til at vise output data
           led2 				: out  STD_LOGIC_VECTOR (7 downto 0); 			-- Bliver ikke brugt i denne kode
           sram_addr 		: inout  STD_LOGIC_VECTOR (19 downto 0); 		-- ADR signal til SRAM
			  RWMEMLED2 		: out STD_LOGIC_VECTOR(1 downto 0); 			-- midlertidigt output der bruges til fejlfinding
           sram_Ce 			: inout  STD_LOGIC; 									-- Chip select signal til SRAM
           sram_WE 			: inout  STD_LOGIC; 									-- Write enable signal til SRAM
           sram_OE 			: inout  STD_LOGIC; 									-- output enable signal til SRAM
           clk 				: in  STD_LOGIC; 										-- klok signal
			  rw2 				: inout std_logic; 										-- rw signal fra arduino
			  mem2 				: in std_logic; 										-- memory operation fra arduino
			  rpi					: in std_logic;
			  rpi_clk			: in std_logic;
			  vsync				: in std_logic;
			  href				: in std_logic;
			  pclk				: in std_logic;
			  TX					: out std_logic;
			  RX					: IN std_logic;
			  reset				: IN std_logic;
			  checkSignal		: OUT std_logic;
			  x19					: out std_logic;
			  test2				: out std_logic
			  );
end topmodul;

architecture Behavioral of topmodul is
component exram is
    Port ( sram_data			: inout  STD_LOGIC_VECTOR (7 downto 0); 		-- Databus imellem, FSM og SRAM
			  Di					: in std_logic_vector(7 downto 0); 				-- Input Data
			  --DATA_out	: out std_logic_vector(7 downto 0); 			-- Output til LED'er til at vise output data
			  --AD					: in std_logic_vector(7 downto 0);
           led 				: out  STD_LOGIC_VECTOR (7 downto 0); 			-- Bliver ikke brugt i denne kode
           --sram_addr 		: inout  STD_LOGIC_VECTOR (7 downto 0); 		-- ADR signal til SRAM
			  RWMEMLED 			: out STD_LOGIC_VECTOR(1 downto 0); 			-- midlertidigt output der bruges til fejlfinding
           sram_Ce 			: inout  STD_LOGIC; 									-- Chip select signal til SRAM
           sram_WE 			: inout  STD_LOGIC; 									-- Write enable signal til SRAM
           sram_OE 			: inout  STD_LOGIC; 									-- output enable signal til SRAM
           clk 				: in  STD_LOGIC; 										-- klok signal
			  rw 					: in std_logic;			  							-- rw signal fra arduino
			  mem 				: in std_logic 										-- memory operation fra arduino
			  --test				: out std_logic
			  );
end component;

signal readWrite : std_logic;
signal addr : std_logic_vector(7 downto 0) := "00000000";
signal addr2 : std_logic_vector(7 downto 0):="00000000";
signal addr3 : std_logic_vector(7 downto 0):="00000000";
signal addr4 : std_logic_vector(7 downto 0):="00000000";
signal addr5 : std_logic_vector(7 downto 0):="00000000";
signal cnt 	 : std_logic_vector(30 downto 0);
signal sclk	 : std_logic;
signal reset1 : std_logic;
signal reset2 : std_logic;
signal state_next:std_logic_vector(1 downto 0);
signal state_reg: std_logic_vector(1 downto 0);


signal addr_buff_pclk: std_logic_vector(19 downto 0):="00000000000000000000";
signal addr_buff_rpi : std_logic_vector(19 downto 0):= "00000000000000000000"; 

signal test : std_logic_vector(2 downto 0);
signal flagB: std_logic:= '1';
signal flagA: std_logic:= '1';
signal flagS: std_logic:= '0';
signal flagD: std_logic:= '0';
signal dannebro: std_logic := '0';

begin				
u1: exram port map(sram_data => sram_data, Di => Di2, led => led2, RWMEMLED => RWMEMLED2, sram_ce => sram_ce, sram_oe => sram_oe, sram_we => sram_we, clk=>clk, rw => readwrite, mem => mem2);

sclk <= cnt(13);

Checksignal <= flagd;

--sram_addr <= "00001000";


process (clk)
-- clk process, der driver sclk (slowclk) --
	begin 
		if (clk'event and clk = '1') then
			cnt <= cnt + 1; -- til at lave slowclock. Incrementer. 
		end if;
end process;
--

process(clk)
begin
	if rising_edge(clk) then
		if (rpi = '1') then
				test <= "011";
				readWrite <= '1';
		elsif (rpi = '0') then
				readWrite <= '0';
				if vsync = '1' and flagD = '0' and flags = '0' then
					test <= "100";
				
				elsif vsync = '1' and flagd = '0' and flags = '1' then
					test <= "101";
						x19 <= '1';
				elsif vsync = '0' and flags = '1' then
					test <= "110";
					
				end if;
				
				
		if  RX = '1' AND flagB = '1' then
						if flagA = '1' then
						addr_buff_rpi <= addr_buff_rpi + 1;
						--addr_buff_rpi <= "1110111001000"; 
--						if sram_addr = "1110111001001" then
--							addr_buff_rpi <= "0000000000000"; 
--						end if;
						flagA <='0'; 
						end if; 
						test <= "001";
				elsif RX = '0'  AND flagB = '0'then 
					test <= "010";
					flagA <= '1';
				end if;
				if reset = '1' then
					addr_buff_rpi <= "00000000000000000000";
				end if;
		--else
			--readWrite <= '1';
		end if;
	end if;
end process;


--process(clk,rpi)
--	begin
--		if rising_edge(clk) then
--			x19 <='1';
--			--end if;
--		end if;
--end process;

--x19 <='1';

--"0000001110111001001"

process(pclk) 
	begin
		if pclk'event and pclk = '1' and dannebro = '1' then
						if addr_buff_pclk = "10010010011111000000" then
				addr_buff_pclk <= "00000000000000000000";
			else	
				addr_buff_pclk <= addr_buff_pclk + 1;
			end if;
		end if;
end process;


--process(clk)
--	begin
--			if rising_edge(clk) then	
--				if  RX = '1' AND flagB = '1' then
--						if flagA = '1' then
--						addr_buff_rpi <= addr_buff_rpi + 1;
--						--addr_buff_rpi <= "1110111001000"; 
----						if sram_addr = "1110111001001" then
----							addr_buff_rpi <= "0000000000000"; 
----						end if;
--						flagA <='0'; 
--						end if; 
--						test <= "001";
--				elsif RX = '0'  AND flagB = '0'then 
--					test <= "010";
--					flagA <= '1';
--				end if;
--				if reset = '1' then
--					addr_buff_rpi <= "00000000000000000000";
--				end if;
--			end if;
--end process;

process(clk) 
	begin
		if rising_edge(clk) then
			case test is
				when "001" =>
					flagB <= '0';
					TX <= '1';
				when "010" => 
					TX <= '0';
					flagB <= '1';
				
				when "011" =>					
					sram_addr <= addr_buff_rpi;
					--x19 <= '0';
				when "100" =>
					flags <= '1';
					flagd <= '1';
					dannebro <= '0';
				when "101" =>
					
					flags <= '0';
					flagd <= '1';
				when "110" =>
					flagd <= '0';
					sram_addr <= addr_buff_pclk;	
						if href = '1' then
							Dannebro <= '1';
					end if;
				when others => 
					
			end case;
		end if; 
end process;		
	
	
--process(clk) 
--	begin
--		if rising_edge(clk) then
--			case state_reg is
--				when "01" =>
--					TX <= '1';
--					state_reg <= test;
--				when "10" => 
--					TX <= '0';
--					state_reg <= test;
--				when others => 
--					state_reg <= test;
--			end case;
--		end if; 
--end process;





























































































































--
--
--
--process(clk)
--	begin
--		if rising_edge(clk) then
--			if RX = '1' then
--				TX <= '1';
--				sram_addr <= addr5;
--			elsif RX = '0' then
--				TX <= '0';
--			end if;
--		end if;
--end process;

				
--
--process(clk)
--	begin
--		if rising_edge(clk) then
--		case state_reg is
--			when "01" =>
--			if ( sram_addr /= addr) then
--					sram_addr <= sram_addr + 1;
--			elsif sram_addr = "11111111" then
--					sram_addr <= "00000000";
--			end if;
--			TX <= '1';
--			state_reg <= "00";
--			
--			when "10" =>
--			TX <= '0'; 
--			state_reg <= "00";
--			
--			
--			when "11" => 
--			sram_addr <= addr; 
--			state_reg <= "00";
--			
--			
--			when others =>
--			state_reg <= state_next;
--		end case;
--		end if;
--end process;


--process(clk)
--	begin
--		if rising_edge(clk) then
--			if counter = '1' then
--				pclk_buffer <= pclk_buffer +1;
--				
--				
--process(rpi_clk
--			elsif counter = '0' then
--				rpi_buffer <= rpi_buffer + 1;	
--			end if;
--		end if;
--end process;


--

--process(RX)
--	begin
--		if RX'event and RX = '1' then
--				if ( rpi_buffer /= addr) then
--					rpi_buffer <= rpi_buffer + 1;
--				elsif sram_addr = "11111111" then
--					rpi_buffer <= "00000000";
--					reset2 <= '1';
--		end if;
--	end if;
--end process;





--process(pclk, rpi_clk)
--	begin
--		if rising_edge(pclk) then
--			sram_addr <= sram_addr + 1;
--			addr <= sram_addr;--		elsif sram_addr = "11111111" then
--			sram_addr <= "00000000";
--			
--		end if
--		if rising_edge(rpi_clk) then
--
--		if ( sram_addr /= addr) then
--			sram_addr <= sram_addr + 1;
--		elsif sram_addr = "11111111" then
--			sram_addr <= "00000000";
--		end if;
--	end if;
--end process;








--process(pclk, rpi_clk)
--	begin
--	if rising_edge(clk) then
--	if readWrite = '0' then
--	 if rising_edge(pclk) then
--		sram_addr <= sram_addr + 1;
--		addr <= sram_addr;
--	 elsif vsync = '1' then
--		sram_addr <= "00000000";
--	 end if;
--	end if;
--	if readWrite = '1' then
--	if rising_edge(rpi_clk) then
--		if sram_addr /= addr  then
--			sram_addr <= sram_addr + 1;
--			x19 <= '0';
--		elsif sram_addr = addr then
--			sram_addr <= "00000000";
--			addr <= "00000000";
--		end if;
--		end if;
--	end if;
--	end if;
--end process;		






------nyt forsøg
--state_reg <= state_next; 
--
--process(pclk,clk)
--	begin
--		if rising_edge(pclk) then
--			state_next <= "01";
--		
--		else 
--			state_next <= "00";
--		end if;
--		
--		
--		
--end process;
--
--
--
--
--
--
--process(clk)
--	begin
--		if rising_edge(clk) then
--			
--			case state_reg is 
--			
--			when "01" =>
--			addr2 <= addr2 + 1;
--			sram_addr <= addr2;--			if sram_addr = "11111111" then
--				addr2 <= "00000000";
--			end if;		
--				
--			
--			when others =>
--			-- idle do nothing. 
--			end case;
--		end if; 
--	end process;
end Behavioral;
--
