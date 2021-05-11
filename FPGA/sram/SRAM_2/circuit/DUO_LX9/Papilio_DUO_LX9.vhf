--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.6
--  \   \         Application : sch2hdl
--  /   /         Filename : Papilio_DUO_LX9.vhf
-- /___/   /\     Timestamp : 04/26/2021 12:18:15
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -sympath C:/DesignLab-1.0.8/libraries/Benchy -sympath C:/DesignLab-1.0.8/libraries/BitCoin_Miner -sympath C:/DesignLab-1.0.8/libraries/Building_Blocks -sympath C:/DesignLab-1.0.8/libraries/Clocks -sympath C:/DesignLab-1.0.8/libraries/Gameduino -sympath C:/DesignLab-1.0.8/libraries/HQVGA -sympath C:/DesignLab-1.0.8/libraries/Papilio_Hardware -sympath C:/DesignLab-1.0.8/libraries/RGB_Matrix -sympath C:/DesignLab-1.0.8/libraries/Robot_Control_Library -sympath C:/DesignLab-1.0.8/libraries/VGA_ZPUino -sympath C:/DesignLab-1.0.8/libraries/VGA_ZXSpectrum -sympath C:/DesignLab-1.0.8/libraries/ZPUino_2 -sympath C:/DesignLab-1.0.8/libraries/ZPUino_Wishbone_Peripherals -sympath C:/Users/jakob/OneDrive/Documents/DesignLab/SRAM_2/circuit/DUO_LX9 -intstyle ise -family spartan6 -flat -suppress -vhdl C:/Users/jakob/OneDrive/Documents/DesignLab/SRAM_2/circuit/DUO_LX9/Papilio_DUO_LX9.vhf -w C:/Users/jakob/OneDrive/Documents/DesignLab/SRAM_2/circuit/Papilio_DUO_LX9.sch
--Design Name: Papilio_DUO_LX9
--Device: spartan6
--Purpose:
--    This vhdl netlist is translated from an ECS schematic. It can be 
--    synthesized and simulated, but it should not be modified. 
--

library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity Papilio_DUO_LX9 is
   port ( DUO_SW1   : in    std_logic; 
          ARD_RESET : out   std_logic);
end Papilio_DUO_LX9;

architecture BEHAVIORAL of Papilio_DUO_LX9 is
   attribute BOX_TYPE   : string ;
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
begin
   XLXI_60 : INV
      port map (I=>DUO_SW1,
                O=>ARD_RESET);
   
end BEHAVIORAL;


