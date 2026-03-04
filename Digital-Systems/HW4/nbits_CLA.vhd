
library ieee;
use ieee.std_logic_1164.all;

entity nbits_CLA is
	generic(BITS:integer:=4);
    port
        (
         x      :  in   std_logic_vector(BITS-1 downto 0);
         y      :  in   std_logic_vector(BITS-1 downto 0);
         carry_in  :  in   std_logic;
         sum       :  out  std_logic_vector(BITS-1 downto 0);
         carry_out :  out  std_logic
        );
end nbits_CLA;

architecture behavioral of nbits_CLA is
signal    h_sum              : std_logic_vector(BITS-1 downto 0);
signal    carry_generate     : std_logic_vector(BITS-1 downto 0);
signal    carry_propagate    : std_logic_vector(BITS-1 downto 0);
signal    carry_in_internal  : std_logic_vector(BITS-1 downto 1);

begin
    h_sum <= x XOR y;
    carry_generate <= x AND y;
    carry_propagate <= x OR y;
	 
    process (carry_generate,carry_propagate,carry_in_internal)
    begin
	 
		carry_in_internal(1) <= carry_generate(0) OR (carry_propagate(0) AND carry_in);
		
      G1: for i in 1 to (BITS-2) loop
				carry_in_internal(i+1) <= carry_generate(i) OR (carry_propagate(i) AND carry_in_internal(i));
          end loop;
			 
		carry_out <= carry_generate(BITS-1) OR (carry_propagate(BITS-1) AND carry_in_internal(BITS-1));
		
    end process;

    sum(0) <= h_sum(0) XOR carry_in;
    sum(BITS-1 downto 1) <= h_sum(BITS-1 downto 1) XOR carry_in_internal(BITS-1 downto 1);
	 
end behavioral; 