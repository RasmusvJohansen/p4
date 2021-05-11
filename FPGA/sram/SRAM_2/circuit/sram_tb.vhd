--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   12:18:17 04/26/2021
-- Design Name:   
-- Module Name:   C:/Users/jakob/OneDrive/Documents/DesignLab/SRAM_2/circuit/sram_tb.vhd
-- Project Name:  PSL_Papilio_DUO_LX9
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: sram_ctrl
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
 
ENTITY sram_tb IS
END sram_tb;
 
ARCHITECTURE behavior OF sram_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT sram_ctrl
    PORT(
         clk : IN  std_logic;
         reset : IN  std_logic;
         mem : IN  std_logic;
         rw : IN  std_logic;
         addr : IN  std_logic_vector(18 downto 0);
         data_f2s : IN  std_logic_vector(3 downto 0);
         ready : OUT  std_logic;
         data_s2f_r : OUT  std_logic_vector(3 downto 0);
         data_s2f_ur : OUT  std_logic_vector(3 downto 0);
         sram_we : OUT  std_logic;
         sram_oe : OUT  std_logic;
         sram_data : INOUT  std_logic_vector(3 downto 0);
         sram_ce : OUT  std_logic;
         sram_addr : OUT  std_logic_vector(18 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal reset : std_logic := '0';
   signal mem : std_logic := '0';
   signal rw : std_logic := '0';
   signal addr : std_logic_vector(18 downto 0) := (others => '0');
   signal data_f2s : std_logic_vector(3 downto 0) := (others => '0');

	--BiDirs
   signal dio : std_logic_vector(3 downto 0);

 	--Outputs
   signal ready : std_logic;
   signal data_s2f_r : std_logic_vector(3 downto 0);
   signal data_s2f_ur : std_logic_vector(3 downto 0);
   signal we_n : std_logic;
   signal oe_n : std_logic;
   signal ce_n : std_logic;
   signal ad : std_logic_vector(18 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: sram_ctrl PORT MAP (
          clk => clk,
          reset => reset,
          mem => mem,
          rw => rw,
          addr => addr,
          data_f2s => data_f2s,
          ready => ready,
          data_s2f_r => data_s2f_r,
          data_s2f_ur => data_s2f_ur,
          sram_we => we_n,
          sram_oe => oe_n,
          sram_data => dio,
          sram_ce => ce_n,
          sram_addr => ad
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
		
		wait for 10 ns;
		addr <= "0000000000000000010";
		data_f2s <= "0101";
		rw <= '0';		
		mem <= '1';
		wait until ready = '1';
		mem <= '0';
		wait for 1 us;
		addr <= "0000000000000000001";
		data_f2s <= "1111";		
		mem <= '1';
		rw <= '0';
		wait until ready = '1';
		data_f2s <= "ZZZZ";
		mem <= '0';
		wait for 1 us;
		addr <= "0000000000000000001";
		mem <= '1';
		rw <= '1';
		wait for 10 us;
		addr <= "0000000000000000010";
		mem <= '1';
		rw <= '1';

      wait;
   end process;

END;
