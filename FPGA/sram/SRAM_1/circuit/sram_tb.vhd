--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   11:26:36 04/23/2021
-- Design Name:   
-- Module Name:   C:/Users/jakob/OneDrive/Documents/DesignLab/SRAM_1/circuit/sram_tb.vhd
-- Project Name:  PSL_Papilio_DUO_LX9
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: sramtester
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
USE ieee.std_logic_unsigned.all;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY sram_tb IS
END sram_tb;
 
ARCHITECTURE behavior OF sram_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT sramtester
    PORT(
         clk : IN  std_logic;
         reset : IN  std_logic;
         mem : IN  std_logic;
         rw : IN  std_logic;
         sram_addr : IN  std_logic_vector(20 downto 0);
         data_f2s : IN  std_logic_vector(15 downto 0);
         ready : OUT  std_logic;
         data_s2f_r : OUT  std_logic_vector(15 downto 0);
         data_s2f_ur : OUT  std_logic_vector(15 downto 0);
         ad : OUT  std_logic_vector(20 downto 0);
         we_n : OUT  std_logic;
         oe_n : OUT  std_logic;
         dio_a : INOUT  std_logic_vector(15 downto 0);
         ce_a_n : OUT  std_logic;
         ub_a_n : OUT  std_logic;
         lb_a_n : OUT  std_logic
			);
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal reset : std_logic := '0';
   signal mem : std_logic := '0';
   signal rw : std_logic := '0';
   signal sram_addr : std_logic_vector(20 downto 0) := (others => '0');
   signal data_f2s : std_logic_vector(15 downto 0) := (others => '0');

	--BiDirs
   signal dio_a : std_logic_vector(15 downto 0);

 	--Outputs
   signal ready : std_logic;
   signal data_s2f_r : std_logic_vector(15 downto 0);
   signal data_s2f_ur : std_logic_vector(15 downto 0);
   signal ad : std_logic_vector(20 downto 0);
   signal we_n : std_logic;
   signal oe_n : std_logic;
   signal ce_a_n : std_logic;
   signal ub_a_n : std_logic;
   signal lb_a_n : std_logic;
	

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: sramtester PORT MAP (
          clk => clk,
          reset => reset,
          mem => mem,
          rw => rw,
          sram_addr => sram_addr,
          data_f2s => data_f2s,
          ready => ready,
          data_s2f_r => data_s2f_r,
          data_s2f_ur => data_s2f_ur,
          ad => ad,
          we_n => we_n,
          oe_n => oe_n,
          dio_a => dio_a,
          ce_a_n => ce_a_n,
          ub_a_n => ub_a_n,
          lb_a_n => lb_a_n
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
		mem <= '1';
		sram_addr <= "000000000000000000001";
		data_f2s <= "0101010101010101";
		rw <= '0';
		wait until ready = '1';
		mem <= '1';
		rw <= '1';


		




      wait;
   end process;

END;
