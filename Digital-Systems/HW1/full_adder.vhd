library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity full_adder is
	port(X,Y,Z :in bit;
		Sum,Carry: out bit);
end full_adder;

architecture behavior of full_adder is
begin
	Carry<=(X AND Y) XOR ((X XOR Y) AND Z);
	Sum<=(X XOR Y) XOR Z;
end behavior;