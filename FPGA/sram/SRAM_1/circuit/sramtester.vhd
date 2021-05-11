----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    09:55:24 04/21/2021 
-- Design Name: 
-- Module Name:    sramtester - Behavioral 
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity sramtester is
	port(
	clk, reset: in std_logic; -- Papilio clk
	-- to / from main system
	mem: in std_logic; -- memory operation
	rw: in std_logic; -- om den skriver eller læser / skriver på 0 og læser på 1
	sram_addr: in std_logic_vector(20 downto 0); -- papilio SRAM pins
	data_f2s: in std_logic_vector(15 downto 0); -- 16 bit data der kan skrives til sram FPGA til SRAM. S2F er sram til FPGA
	ready: out std_logic; -- et signal der indikere om kontrolleren er klar til at få en ny kommando. Der må kun være en memory operation pr. clk cycle.
	data_s2f_r, data_s2f_ur: out std_logic_vector(15 downto 0);-- (0) 8 bit data der er registreret modtaget fra SRAM, (1) uregistreret data fra SRAM.
	-- to / from chip
	ad: out std_logic_vector(20 downto 0); -- output adresser 
	we_n, oe_n: out std_logic; --we (write enable), oe (output enable)
	-- SRAM chip a
	dio_a: inout std_logic_vector(15 downto 0); -- SRAM bus / sram_data i ucf filen
	ce_a_n, ub_a_n, lb_a_n : out std_logic --ce (chip enable), upper byte, lower byte
	);
end sramtester;

architecture Behavioral of sramtester is
	type state_type is (idle, rd1, rd2, wr1, wr2);
	signal state_reg, state_next: state_type;
	signal data_f2s_reg, data_f2s_next:	std_logic_vector(15 downto 0);
	signal data_s2f_reg, data_s2f_next:	std_logic_vector(15 downto 0);
	signal addr_reg, addr_next: std_logic_vector(20 downto 0);
	signal we_buf, oe_buf, tri_buf: std_logic;
	signal we_reg, oe_reg, tri_reg: std_logic;
begin
	-- state & data registers
	process(clk,reset)
	begin
		if (reset = '1') then
			state_reg <= idle;
			addr_reg <= (others=>'0');
			data_f2s_reg <= (others=>'0');
			data_s2f_reg <= (others => '0');
			tri_reg <= '1';
			we_reg <= '1';
			oe_reg <= '1';
		elsif(clk'event and clk='1') then
			state_reg <= state_next;
			addr_reg <= addr_next;
			data_f2s_reg <= data_f2s_next;
			data_s2f_reg <= data_s2f_next;
			tri_reg <= tri_buf;
			we_reg <= we_buf;
			oe_reg <= oe_buf;
		end if;
	end process;
-- next state logic

process(state_reg,mem,rw,dio_a,sram_addr,data_f2s,data_f2s_reg, data_s2f_reg, addr_reg)

begin
		addr_next <= addr_reg;
		data_f2s_next <= data_f2s_reg;
		data_s2f_next <= data_s2f_reg;
		ready <= '0';
		case state_reg is
			when idle =>
				if mem='0' then --write
					state_next <= idle;
					--data_f2s_next <= data_f2s;
				else --read
					addr_next <= sram_addr;
					if rw='0' then --write
						state_next <= wr1;
						data_f2s_next <= data_f2s;
					else --read
						state_next <= rd1;
					end if;
				
				end if;
			ready <= '1';
		when wr1 =>
			state_next <= wr2;
		when wr2 =>
			state_next <= idle;
		when rd1 =>
			state_next <= rd2;
		when rd2 =>
			data_s2f_next <= dio_a;
			state_next <= idle;
	end case;
end process;
-- 'look-ahead' output logic
process(state_next)
begin
	tri_buf <= '1';
	we_buf <= '1';
	oe_buf <= '1';
	case state_next is
		when idle =>
		when wr1 =>
			tri_buf <= '0';
			we_buf <= '0';
		when wr2 =>
			tri_buf <= '0';
		when rd1 =>
			oe_buf <= '0';
		when rd2 =>
			oe_buf <= '0';
	end case;
end process;
-- to main system
data_s2f_r <= data_s2f_reg;
data_s2f_ur <= dio_a;
-- to SRAM
we_n <= we_reg;
oe_n <= oe_reg;
ad <= addr_reg;
--i/o for SRAM chop a
ce_a_n <= '0';
ub_a_n <= '0';
lb_a_n <= '0';
dio_a <= data_f2s_reg when tri_reg='0' else (others =>'Z');



				


end Behavioral;

