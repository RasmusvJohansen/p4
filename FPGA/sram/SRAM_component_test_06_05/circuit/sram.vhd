----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    15:29:48 05/06/2021 
-- Design Name: 
-- Module Name:    sram - Behavioral 
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

entity sram is
    Port ( sram_data			: inout  STD_LOGIC_VECTOR (7 downto 0); 		-- Databus imellem, FSM og SRAM
			  Di					: in std_logic_vector(7 downto 0); 				-- Input Data
			  --DATA_out	: out std_logic_vector(7 downto 0); 			-- Output til LED'er til at vise output data
			  AD					: in std_logic_vector(7 downto 0);
           led 				: out  STD_LOGIC_VECTOR (7 downto 0); 			-- Bliver ikke brugt i denne kode
           sram_addr 		: inout  STD_LOGIC_VECTOR (7 downto 0); 		-- ADR signal til SRAM
			  RWMEMLED 			: out STD_LOGIC_VECTOR(1 downto 0); 			-- midlertidigt output der bruges til fejlfinding
           sram_Ce 			: inout  STD_LOGIC; 									-- Chip select signal til SRAM
           sram_WE 			: inout  STD_LOGIC; 									-- Write enable signal til SRAM
           sram_OE 			: inout  STD_LOGIC; 									-- output enable signal til SRAM
           clk 				: in  STD_LOGIC; 										-- klok signal
			  rw 					: in std_logic; 										-- rw signal fra arduino
			  mem 				: in std_logic; 										-- memory operation fra arduino
			  test				: out std_logic
			  --adi					: inout STD_LOGIC_VECTOR(18 downto 0)
			  );
end sram;

architecture Behavioral of sram is

component exram is
    Port ( sram_data			: inout  STD_LOGIC_VECTOR (7 downto 0); 		-- Databus imellem, FSM og SRAM
			  Di					: in std_logic_vector(7 downto 0); 				-- Input Data
			  --DATA_out	: out std_logic_vector(7 downto 0); 			-- Output til LED'er til at vise output data
			  AD					: in std_logic_vector(7 downto 0);
           led 				: out  STD_LOGIC_VECTOR (7 downto 0); 			-- Bliver ikke brugt i denne kode
           sram_addr 		: inout  STD_LOGIC_VECTOR (7 downto 0); 		-- ADR signal til SRAM
			  RWMEMLED 			: out STD_LOGIC_VECTOR(1 downto 0); 			-- midlertidigt output der bruges til fejlfinding
           sram_Ce 			: inout  STD_LOGIC; 									-- Chip select signal til SRAM
           sram_WE 			: inout  STD_LOGIC; 									-- Write enable signal til SRAM
           sram_OE 			: inout  STD_LOGIC; 									-- output enable signal til SRAM
           clk 				: in  STD_LOGIC; 										-- klok signal
			  rw 					: in std_logic; 										-- rw signal fra arduino
			  mem 				: in std_logic; 										-- memory operation fra arduino
			  test				: out std_logic
			  --adi					: inout STD_LOGIC_VECTOR(18 downto 0)
			  );
end component;


begin
u1: exram port map(sram_data => sram_data, Di => Di, AD => AD, led => led, sram_addr => sram_addr, RWMEMLED => RWMEMLED, sram_ce => sram_ce, sram_oe => sram_oe, sram_we => sram_we, clk=>clk, rw => rw, mem => mem);

end Behavioral;

