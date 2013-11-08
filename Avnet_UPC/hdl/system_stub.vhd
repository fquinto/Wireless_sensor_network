-------------------------------------------------------------------------------
-- system_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity system_stub is
  port (
    fpga_0_USB_UART_RX_pin : in std_logic;
    fpga_0_USB_UART_TX_pin : out std_logic;
    fpga_0_LEDS_4BIT_GPIO_IO_pin : inout std_logic_vector(0 to 3);
    fpga_0_CS_PUSH_3BIT_GPIO_IO_I_pin : in std_logic_vector(0 to 2);
    fpga_0_TEMP_SENSOR_Sda_pin : inout std_logic;
    fpga_0_TEMP_SENSOR_Scl_pin : inout std_logic;
    fpga_0_FLASH_2Mx16_Mem_A_pin : out std_logic_vector(10 to 30);
    fpga_0_FLASH_2Mx16_Mem_RPN_pin : out std_logic;
    fpga_0_FLASH_2Mx16_Mem_CEN_pin : out std_logic;
    fpga_0_FLASH_2Mx16_Mem_OEN_pin : out std_logic;
    fpga_0_FLASH_2Mx16_Mem_WEN_pin : out std_logic;
    fpga_0_FLASH_2Mx16_Mem_DQ_pin : inout std_logic_vector(0 to 15);
    fpga_0_FLASH_2Mx16_MEM_BYTEn_pin : out std_logic;
    fpga_0_clk_1_sys_clk_pin : in std_logic;
    fpga_0_rst_1_sys_rst_pin : in std_logic;
    fpga_0_MSP430_UART_TX_pin : out std_logic;
    fpga_0_MSP430_UART_RX_pin : in std_logic
  );
end system_stub;

architecture STRUCTURE of system_stub is

  component system is
    port (
      fpga_0_USB_UART_RX_pin : in std_logic;
      fpga_0_USB_UART_TX_pin : out std_logic;
      fpga_0_LEDS_4BIT_GPIO_IO_pin : inout std_logic_vector(0 to 3);
      fpga_0_CS_PUSH_3BIT_GPIO_IO_I_pin : in std_logic_vector(0 to 2);
      fpga_0_TEMP_SENSOR_Sda_pin : inout std_logic;
      fpga_0_TEMP_SENSOR_Scl_pin : inout std_logic;
      fpga_0_FLASH_2Mx16_Mem_A_pin : out std_logic_vector(10 to 30);
      fpga_0_FLASH_2Mx16_Mem_RPN_pin : out std_logic;
      fpga_0_FLASH_2Mx16_Mem_CEN_pin : out std_logic;
      fpga_0_FLASH_2Mx16_Mem_OEN_pin : out std_logic;
      fpga_0_FLASH_2Mx16_Mem_WEN_pin : out std_logic;
      fpga_0_FLASH_2Mx16_Mem_DQ_pin : inout std_logic_vector(0 to 15);
      fpga_0_FLASH_2Mx16_MEM_BYTEn_pin : out std_logic;
      fpga_0_clk_1_sys_clk_pin : in std_logic;
      fpga_0_rst_1_sys_rst_pin : in std_logic;
      fpga_0_MSP430_UART_TX_pin : out std_logic;
      fpga_0_MSP430_UART_RX_pin : in std_logic
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of system : component is "user_black_box";

begin

  system_i : system
    port map (
      fpga_0_USB_UART_RX_pin => fpga_0_USB_UART_RX_pin,
      fpga_0_USB_UART_TX_pin => fpga_0_USB_UART_TX_pin,
      fpga_0_LEDS_4BIT_GPIO_IO_pin => fpga_0_LEDS_4BIT_GPIO_IO_pin,
      fpga_0_CS_PUSH_3BIT_GPIO_IO_I_pin => fpga_0_CS_PUSH_3BIT_GPIO_IO_I_pin,
      fpga_0_TEMP_SENSOR_Sda_pin => fpga_0_TEMP_SENSOR_Sda_pin,
      fpga_0_TEMP_SENSOR_Scl_pin => fpga_0_TEMP_SENSOR_Scl_pin,
      fpga_0_FLASH_2Mx16_Mem_A_pin => fpga_0_FLASH_2Mx16_Mem_A_pin,
      fpga_0_FLASH_2Mx16_Mem_RPN_pin => fpga_0_FLASH_2Mx16_Mem_RPN_pin,
      fpga_0_FLASH_2Mx16_Mem_CEN_pin => fpga_0_FLASH_2Mx16_Mem_CEN_pin,
      fpga_0_FLASH_2Mx16_Mem_OEN_pin => fpga_0_FLASH_2Mx16_Mem_OEN_pin,
      fpga_0_FLASH_2Mx16_Mem_WEN_pin => fpga_0_FLASH_2Mx16_Mem_WEN_pin,
      fpga_0_FLASH_2Mx16_Mem_DQ_pin => fpga_0_FLASH_2Mx16_Mem_DQ_pin,
      fpga_0_FLASH_2Mx16_MEM_BYTEn_pin => fpga_0_FLASH_2Mx16_MEM_BYTEn_pin,
      fpga_0_clk_1_sys_clk_pin => fpga_0_clk_1_sys_clk_pin,
      fpga_0_rst_1_sys_rst_pin => fpga_0_rst_1_sys_rst_pin,
      fpga_0_MSP430_UART_TX_pin => fpga_0_MSP430_UART_TX_pin,
      fpga_0_MSP430_UART_RX_pin => fpga_0_MSP430_UART_RX_pin
    );

end architecture STRUCTURE;

