--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   12:58:23 04/29/2021
-- Design Name:   
-- Module Name:   C:/Users/jakob/OneDrive/Documents/DesignLab/SRAM_29/_04/circuit/exram_tb.vhd
-- Project Name:  PSL_Papilio_DUO_LX9
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: exram
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY exram_tb IS
END exram_tb;
 
ARCHITECTURE behavior OF exram_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT exram
    PORT(
         D : INOUT  std_logic_vector(7 downto 0);
         led : OUT  std_logic_vector(7 downto 0);
         ADR : INOUT  std_logic_vector(18 downto 0);
         CS : OUT  std_logic;
         WE : INOUT  std_logic;
         OE : INOUT  std_logic;
         a : OUT  std_logic;
         b : OUT  std_logic;
         clk : IN  std_logic;
         rw : IN  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal rw : std_logic := '0';

	--BiDirs
   signal D : std_logic_vector(7 downto 0);
   signal WE : std_logic;
   signal OE : std_logic;

 	--Outputs
   signal led : std_logic_vector(7 downto 0);
   signal ADR : std_logic_vector(18 downto 0);
   signal CS : std_logic;
   signal a : std_logic;
   signal b : std_logic;

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: exram PORT MAP (
          D => D,
          led => led,
          ADR => ADR,
          CS => CS,
          WE => WE,
          OE => OE,
          a => a,
          b => b,
          clk => clk,
          rw => rw
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for clk_period*10;

      -- insert stimulus here 
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
			wait for 100 ns;
			rw <= '1';
			wait for 100 ns;
			rw <= '0';
      wait;
   end process;

END;
