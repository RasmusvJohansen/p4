----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:22:01 04/26/2021 
-- Design Name: 
-- Module Name:    sram_ctrl - Behavioral 
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

entity sram_ctrl is
port(
clk, reset : in std_logic;
mem : in std_logic;
rw: in std_logic;
--addr: in std_logic_vector(18 downto 0);
data_f2s: in std_logic_vector(3 downto 0);
ready: out std_logic;
data_s2f_r, data_s2f_ur: out std_logic_vector(3 downto 0);
sram_we, sram_oe: out std_logic;
sram_data: inout std_logic_vector(3 downto 0);
sram_ce: out std_logic;
sram_addr : out std_logic_vector(18 downto 0);
test_output : out std_logic
);
end sram_ctrl;

architecture Behavioral of sram_ctrl is
type state_type is (idle, r1, r2, w1, w2);
signal state_reg, state_next: state_type;
signal data_f2s_reg, data_f2s_next: std_logic_vector(3 downto 0);
signal data_s2f_reg, data_s2f_next: std_logic_vector(3 downto 0);
signal addr_reg, addr_next: std_logic_vector(18 downto 0);
signal we_buf, oe_buf, tri_buf: std_logic;
signal we_reg, oe_reg, tri_reg: std_logic;
signal addr : std_logic_vector(18 downto 0) := "0000000000000000001";
signal counter : integer :=0;
signal divider : integer :=27350;
signal stateC : std_logic;


begin


process(clk)
	begin
		if(clk = '1' and clk'event) then
			counter <= counter + 1;
			stateC <= '0';
            if counter = divider then 
                counter <= 0;
					 stateC <= '1';
            end if;
      end if;
end process;



process(clk, reset)
	begin
		if (reset = '1') then
			state_reg <= idle;
			addr_reg <= (others => '0');
			data_f2s_reg <= (others => '0');
			data_s2f_reg <= (others => '0');
			tri_reg <= '1';
			we_reg <= '1';
			oe_reg <= '1';
		elsif(clk'event and clk = '1') then
			if stateC ='1' then
			state_reg <= state_next;
			addr_reg <= addr_next;
			data_f2s_reg <= data_f2s_next;
			data_s2f_reg <= data_s2f_next;
			tri_reg <= tri_buf;
			we_reg <= we_buf;
			oe_reg <= oe_buf;
			end if;
		end if;
	end process;
	
process(state_reg, mem, rw, sram_data, addr, data_f2s, data_f2s_reg, data_s2f_reg, addr_reg)
	begin
	addr_next <= addr_reg;
	data_f2s_next <= data_f2s_reg;
	data_s2f_next <= data_s2f_reg;
	ready <= '0';
		case state_reg is
			when idle =>
				if (mem = '0') then
					state_next <= idle;
				else
					addr_next <= addr;
					if ( rw = '0') then
						state_next <= w1;
						data_f2s_next <= data_f2s;
					else
						state_next <= r1;
					end if;
				end if;
				ready <= '1';
			when w1 =>
				state_next <= w2;
			when w2 =>
				state_next <= idle;
			when r1 =>
				state_next <= r2;
			when r2 =>
				data_s2f_next <= sram_data;
				state_next <= idle;
			end case;
		end process;
	process(state_next, tri_buf, we_buf, oe_buf)
		begin
					tri_buf <= '1';
					we_buf <= '1';
					oe_buf <= '1';
			case state_next is					
				when idle =>			
				when w1 =>
					tri_buf <= '0';
					we_buf <= '0';
				when w2 =>
					tri_buf <= '0';
				when r1 =>
					oe_buf <= '0';
				when r2 =>
					oe_buf <= '0';
			end case;
		end process;
	
	data_s2f_ur <= sram_data;
	sram_we <= we_reg;
	sram_oe <= oe_reg;
	sram_addr <= addr_reg;
	sram_ce <= '0';
	sram_data <= data_f2s_reg when tri_reg='0' else (others => 'Z');
	data_s2f_r <= data_s2f_reg;
	
	
end Behavioral;

