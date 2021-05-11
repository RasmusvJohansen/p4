--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   10:05:30 05/11/2021
-- Design Name:   
-- Module Name:   C:/Users/jakob/OneDrive/Documents/DesignLab/SRAM_pi_10_05/circuit/tp_tb.vhd
-- Project Name:  PSL_Papilio_DUO_LX9
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: topmodul
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
 
ENTITY tp_tb IS
END tp_tb;
 
ARCHITECTURE behavior OF tp_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT topmodul
    PORT(
         sram_data : INOUT  std_logic_vector(7 downto 0);
         Di2 : IN  std_logic_vector(7 downto 0);
         led2 : OUT  std_logic_vector(7 downto 0);
         sram_addr : INOUT  std_logic_vector(7 downto 0);
         RWMEMLED2 : OUT  std_logic_vector(1 downto 0);
         sram_Ce : INOUT  std_logic;
         sram_WE : INOUT  std_logic;
         sram_OE : INOUT  std_logic;
         clk : IN  std_logic;
         mem2 : IN  std_logic;
         rpi : IN  std_logic;
         rpi_clk : IN  std_logic;
         vsync : IN  std_logic;
         href : IN  std_logic;
         pclk : IN  std_logic;
         test2 : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal Di2 : std_logic_vector(7 downto 0) := (others => '0');
   signal clk : std_logic := '0';
   signal mem2 : std_logic := '0';
   signal rpi : std_logic := '0';
   signal rpi_clk : std_logic := '0';
   signal vsync : std_logic := '0';
   signal href : std_logic := '0';
   signal pclk : std_logic := '0';

	--BiDirs
   signal sram_data : std_logic_vector(7 downto 0);
   signal sram_addr : std_logic_vector(7 downto 0);
   signal sram_Ce : std_logic;
   signal sram_WE : std_logic;
   signal sram_OE : std_logic;

 	--Outputs
   signal led2 : std_logic_vector(7 downto 0);
   signal RWMEMLED2 : std_logic_vector(1 downto 0);
   signal test2 : std_logic;

   -- Clock period definitions
   constant clk_period : time := 10 ns;
   constant rpi_clk_period : time := 10 ns;
   constant pclk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: topmodul PORT MAP (
          sram_data => sram_data,
          Di2 => Di2,
          led2 => led2,
          sram_addr => sram_addr,
          RWMEMLED2 => RWMEMLED2,
          sram_Ce => sram_Ce,
          sram_WE => sram_WE,
          sram_OE => sram_OE,
          clk => clk,
          mem2 => mem2,
          rpi => rpi,
          rpi_clk => rpi_clk,
          vsync => vsync,
          href => href,
          pclk => pclk,
          test2 => test2
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 
   rpi_clk_process :process
   begin
		rpi_clk <= '0';
		wait for rpi_clk_period/2;
		rpi_clk <= '1';
		wait for rpi_clk_period/2;
   end process;
 
   pclk_process :process
   begin
		pclk <= '0';
		wait for pclk_period/2;
		pclk <= '1';
		wait for pclk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for clk_period*10;

      -- insert stimulus here 

      wait;
   end process;

END;
