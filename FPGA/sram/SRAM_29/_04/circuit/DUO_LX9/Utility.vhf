--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.6
--  \   \         Application : sch2hdl
--  /   /         Filename : Utility.vhf
-- /___/   /\     Timestamp : 04/29/2021 12:58:21
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -sympath C:/DesignLab-1.0.8/libraries/Benchy -sympath C:/DesignLab-1.0.8/libraries/BitCoin_Miner -sympath C:/DesignLab-1.0.8/libraries/Building_Blocks -sympath C:/DesignLab-1.0.8/libraries/Clocks -sympath C:/DesignLab-1.0.8/libraries/Gameduino -sympath C:/DesignLab-1.0.8/libraries/HQVGA -sympath C:/DesignLab-1.0.8/libraries/Papilio_Hardware -sympath C:/DesignLab-1.0.8/libraries/RGB_Matrix -sympath C:/DesignLab-1.0.8/libraries/Robot_Control_Library -sympath C:/DesignLab-1.0.8/libraries/VGA_ZPUino -sympath C:/DesignLab-1.0.8/libraries/VGA_ZXSpectrum -sympath C:/DesignLab-1.0.8/libraries/ZPUino_2 -sympath C:/DesignLab-1.0.8/libraries/ZPUino_Wishbone_Peripherals -sympath C:/Users/jakob/OneDrive/Documents/DesignLab/SRAM_29/_04/circuit/DUO_LX9 -intstyle ise -family spartan6 -flat -suppress -vhdl C:/Users/jakob/OneDrive/Documents/DesignLab/SRAM_29/_04/circuit/DUO_LX9/Utility.vhf -w C:/DesignLab-1.0.8/examples/00.Papilio_Schematic_Library/Libraries/ZPUino_1/Utility.sch
--Design Name: Utility
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

entity Utility is
   port ( CLK            : in    std_logic; 
          DUO_SW1        : in    std_logic; 
          ext_pins_in    : in    std_logic_vector (100 downto 0); 
          RXD            : in    std_logic; 
          ARD_RESET      : out   std_logic; 
          DUO_LED        : out   std_logic; 
          ext_pins_out   : out   std_logic_vector (100 downto 0); 
          LED            : out   std_logic; 
          TXD            : out   std_logic; 
          Arduino_0      : inout std_logic; 
          Arduino_1      : inout std_logic; 
          Arduino_2      : inout std_logic; 
          Arduino_3      : inout std_logic; 
          Arduino_4      : inout std_logic; 
          Arduino_5      : inout std_logic; 
          Arduino_6      : inout std_logic; 
          Arduino_7      : inout std_logic; 
          Arduino_8      : inout std_logic; 
          Arduino_9      : inout std_logic; 
          Arduino_10     : inout std_logic; 
          Arduino_11     : inout std_logic; 
          Arduino_12     : inout std_logic; 
          Arduino_13     : inout std_logic; 
          Arduino_14     : inout std_logic; 
          Arduino_15     : inout std_logic; 
          Arduino_16     : inout std_logic; 
          Arduino_17     : inout std_logic; 
          Arduino_18     : inout std_logic; 
          Arduino_19     : inout std_logic; 
          Arduino_20     : inout std_logic; 
          Arduino_21     : inout std_logic; 
          Arduino_22     : inout std_logic; 
          Arduino_23     : inout std_logic; 
          Arduino_24     : inout std_logic; 
          Arduino_25     : inout std_logic; 
          Arduino_26     : inout std_logic; 
          Arduino_27     : inout std_logic; 
          Arduino_28     : inout std_logic; 
          Arduino_29     : inout std_logic; 
          Arduino_30     : inout std_logic; 
          Arduino_31     : inout std_logic; 
          Arduino_32     : inout std_logic; 
          Arduino_33     : inout std_logic; 
          Arduino_34     : inout std_logic; 
          Arduino_35     : inout std_logic; 
          Arduino_36     : inout std_logic; 
          Arduino_37     : inout std_logic; 
          Arduino_38     : inout std_logic; 
          Arduino_39     : inout std_logic; 
          Arduino_40     : inout std_logic; 
          Arduino_41     : inout std_logic; 
          Arduino_42     : inout std_logic; 
          Arduino_43     : inout std_logic; 
          Arduino_44     : inout std_logic; 
          Arduino_45     : inout std_logic; 
          Arduino_46     : inout std_logic; 
          Arduino_47     : inout std_logic; 
          Arduino_48     : inout std_logic; 
          Arduino_49     : inout std_logic; 
          Arduino_50     : inout std_logic; 
          Arduino_51     : inout std_logic; 
          Arduino_52     : inout std_logic; 
          Arduino_53     : inout std_logic; 
          ext_pins_inout : inout std_logic_vector (100 downto 0); 
          WING_AH0       : inout std_logic; 
          WING_AH1       : inout std_logic; 
          WING_AH2       : inout std_logic; 
          WING_AH3       : inout std_logic; 
          WING_AH4       : inout std_logic; 
          WING_AH5       : inout std_logic; 
          WING_AH6       : inout std_logic; 
          WING_AH7       : inout std_logic; 
          WING_AL0       : inout std_logic; 
          WING_AL1       : inout std_logic; 
          WING_AL2       : inout std_logic; 
          WING_AL3       : inout std_logic; 
          WING_AL4       : inout std_logic; 
          WING_AL5       : inout std_logic; 
          WING_AL6       : inout std_logic; 
          WING_AL7       : inout std_logic; 
          WING_BH0       : inout std_logic; 
          WING_BH1       : inout std_logic; 
          WING_BH2       : inout std_logic; 
          WING_BH3       : inout std_logic; 
          WING_BH4       : inout std_logic; 
          WING_BH5       : inout std_logic; 
          WING_BH6       : inout std_logic; 
          WING_BH7       : inout std_logic; 
          WING_BL0       : inout std_logic; 
          WING_BL1       : inout std_logic; 
          WING_BL2       : inout std_logic; 
          WING_BL3       : inout std_logic; 
          WING_BL4       : inout std_logic; 
          WING_BL5       : inout std_logic; 
          WING_BL6       : inout std_logic; 
          WING_BL7       : inout std_logic; 
          WING_CH0       : inout std_logic; 
          WING_CH1       : inout std_logic; 
          WING_CH2       : inout std_logic; 
          WING_CH3       : inout std_logic; 
          WING_CH4       : inout std_logic; 
          WING_CH5       : inout std_logic; 
          WING_CH6       : inout std_logic; 
          WING_CH7       : inout std_logic; 
          WING_CL0       : inout std_logic; 
          WING_CL1       : inout std_logic; 
          WING_CL2       : inout std_logic; 
          WING_CL3       : inout std_logic; 
          WING_CL4       : inout std_logic; 
          WING_CL5       : inout std_logic; 
          WING_CL6       : inout std_logic; 
          WING_CL7       : inout std_logic);
end Utility;

architecture BEHAVIORAL of Utility is
   attribute BOX_TYPE   : string ;
   signal XLXN_325       : std_logic_vector (7 downto 0);
   signal XLXN_326       : std_logic_vector (7 downto 0);
   signal XLXN_327       : std_logic_vector (7 downto 0);
   signal XLXN_328       : std_logic_vector (7 downto 0);
   signal XLXN_329       : std_logic_vector (7 downto 0);
   signal XLXN_330       : std_logic_vector (7 downto 0);
   signal XLXN_331       : std_logic_vector (7 downto 0);
   signal XLXN_332       : std_logic_vector (7 downto 0);
   signal XLXN_333       : std_logic_vector (7 downto 0);
   signal XLXN_334       : std_logic_vector (7 downto 0);
   signal XLXN_335       : std_logic_vector (7 downto 0);
   signal XLXN_336       : std_logic_vector (7 downto 0);
   component Wing_GPIO
      port ( wt_miso : inout std_logic_vector (7 downto 0); 
             wt_mosi : inout std_logic_vector (7 downto 0));
   end component;
   
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
begin
   XLXI_22 : Wing_GPIO
      port map (wt_miso(7 downto 0)=>XLXN_325(7 downto 0),
                wt_mosi(7 downto 0)=>XLXN_326(7 downto 0));
   
   XLXI_23 : Wing_GPIO
      port map (wt_miso(7 downto 0)=>XLXN_327(7 downto 0),
                wt_mosi(7 downto 0)=>XLXN_328(7 downto 0));
   
   XLXI_24 : Wing_GPIO
      port map (wt_miso(7 downto 0)=>XLXN_329(7 downto 0),
                wt_mosi(7 downto 0)=>XLXN_330(7 downto 0));
   
   XLXI_25 : Wing_GPIO
      port map (wt_miso(7 downto 0)=>XLXN_331(7 downto 0),
                wt_mosi(7 downto 0)=>XLXN_332(7 downto 0));
   
   XLXI_26 : Wing_GPIO
      port map (wt_miso(7 downto 0)=>XLXN_333(7 downto 0),
                wt_mosi(7 downto 0)=>XLXN_334(7 downto 0));
   
   XLXI_27 : Wing_GPIO
      port map (wt_miso(7 downto 0)=>XLXN_335(7 downto 0),
                wt_mosi(7 downto 0)=>XLXN_336(7 downto 0));
   
   XLXI_48 : INV
      port map (I=>DUO_SW1,
                O=>ARD_RESET);
   
end BEHAVIORAL;


