library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
use IEEE.NUMERIC_STD.ALL;
 

 

 
entity exram is
    Port ( D 			: inout  STD_LOGIC_VECTOR (7 downto 0); 		-- Databus imellem, FSM og SRAM
			  Di			: in std_logic_vector(7 downto 0); 				-- Input Data
			  --DATA_out	: out std_logic_vector(7 downto 0); 			-- Output til LED'er til at vise output data
           led 		: out  STD_LOGIC_VECTOR (7 downto 0); 			-- Bliver ikke brugt i denne kode
           ADR 		: out  STD_LOGIC_VECTOR (18 downto 0); 		-- ADR signal til SRAM
			  RWMEMLED 	: out STD_LOGIC_VECTOR(1 downto 0); 			-- midlertidigt output der bruges til fejlfinding
           CS 			: out  STD_LOGIC; 									-- Chip select signal til SRAM
           WE 			: inout  STD_LOGIC; 									-- Write enable signal til SRAM
           OE 			: inout  STD_LOGIC; 									-- output enable signal til SRAM
           clk 		: in  STD_LOGIC; 										-- klok signal
			  rw 			: in std_logic; 										-- rw signal fra arduino
			  mem 		: in std_logic 										-- memory operation fra arduino
			  );
end exram;
 
architecture Behavioral of exram is
	signal sclk			: STD_LOGIC;
	signal cnt			: STD_LOGIC_VECTOR (30 downto 0); 					-- bruges til en clk-divider
	signal DO			: STD_LOGIC_VECTOR (7 downto 0) := "00000001"; 	-- signal der bruges til at overf�re input signalet til D
	signal state_reg	: STD_LOGIC_VECTOR (1 downto 0) :="00"; 			-- state for testing
	signal state_next	: STD_LOGIC_VECTOR (1 downto 0); 					-- next state i FSM
	signal WEint		: STD_LOGIC := '1'; 										-- internal state for WE initially 1 (read)

begin
-- inititaliserer v�rdier --
ADR <= "0000000000000000001"; 	--address no 1
OE <= not WE; 							-- OE m� ikke v�re det samme som WE, og t�ndes og slukkes i to forskelliges states
sclk <= cnt(5); 						-- slow clk
WE <= WEint;
--DO <= "00000001";
LED <= d; 							-- init til Write Enable

--Tristate buffer
with WE select D <= 
		DO when '0', -- s�tter DO p� D
      (others=>'Z') when others; -- s�tter D til h�j impedant


process (clk)
-- clk process, der driver sclk (slowclk) --
	begin 
		if (clk'event and clk = '1') then
			cnt <= cnt + 1; -- til at lave slowclock. Incrementer. 
		end if;
end process;


process(clk,state_next)
-- next state logic
	begin
		if (clk'event and clk = '1')then
			case (mem) is  -- mem sikrer at vi �nsket en memory operation. Derved kan rw kun �ndres hvis mem = 1
				when '1' =>
					if (rw = '1') then		--	READ
						state_next <= "10";  -- rw er sat til 1 og vi l�ser derfor fra SRAM
					elsif (rw = '0') then	-- WRITE
						state_next <= "01"; 	-- rw er sat til 0 og vi skriver derfor til SRAM
					end if;
				when others => 
					state_next <= "00";		-- IDLE
			end case;
		end if;
end process;



-- FSM
process (sclk)
begin 
   if (sclk'event and sclk = '1') then
      case (state_reg) is
			when "00" => 						-- IDLE case
				state_reg <= state_next;	-- skifter state
				RWMEMLED(0) <= '1';			-- LED til debugging..
				RWMEMLED(1) <= '0';
				CS <= '1';						-- t�nder og slukker chip. Holdes idle indtil CS =/= 1
			
			when "01" => 						-- Skrive-Case
				WEint <= '0'; 					-- WEint styrer b�de OE og WE, OE er WE negeret
				state_reg <= state_next; 	-- skifter state
				CS <= '0';						-- tillader at idle forlades
				RWMEMLED(1) <= '0';			-- LED til debugging...
				RWMEMLED(0) <= '0'; 
				DO <= DI;
			when "10" => 						-- l�se-case 
				WEint <= '1'; 					-- WEint styrer b�de OE og WE, OE er WE negeret
				RWMEMLED(1) <= '1';			-- LED til debugging...
				RWMEMLED(0) <= '0';
				state_reg <= state_next;	-- skifter state
				CS <= '0';						-- CS er 0, s� vi er ikke i idle
				
			when others =>
				state_reg <= "00";			-- ved fejl skal vi g� i idle
			
		end case;  
   end if;
end process;
end Behavioral;



--process (CLK) 
---- skriver data til SRAM, eller l�ser den og s�tter p� output pins --
--		begin
--			if rising_edge(clk) then
--				case (oe) is 			-- output enable er casen
--					when '0' => 		-- OE er 0, og vi skriver til SRAM ved at s�tte DO p� D som g�r til SRAM
--						D <= Di;			-- SRAM-bussen tager data_input fra arduino
--					when '1' => 		-- OE er 1 (og WE er '0'). 
--						data_out <= D;	-- Data tager v�rdi fra D, og skriver det til Data_out, som er vist p� LED'er.
--					when others =>		-- skal d�kke alle cases, s� er irrelevant for programmet, men smider Z hvis output er andet end 0 el. 1
--						D <= (others => 'Z');
--				end case;
--			end if;
--end process;


