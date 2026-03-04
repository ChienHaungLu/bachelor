library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity ADD2_OR is  -- 將2個AND及1個OR看成一個block
	port(
		  A,B,C,D:in std_logic;
		  E: out std_logic);
end ADD2_OR;

architecture beh of ADD2_OR is
begin
	E<=(A AND B) OR (C AND D);
end beh;