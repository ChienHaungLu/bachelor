library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity D_Filp_Flop is    -- 一個DFF
	port(D,CLK:in std_logic;
			O:out std_logic);
end D_Filp_Flop;

architecture beh of D_Filp_Flop is
begin 
	process(CLK,D)
	begin
		if CLK'event and CLK='1' then
			O<=D;
		end if;
	end process;
end beh;

