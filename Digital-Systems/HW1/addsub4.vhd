library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity addsub4 is
	port(
		x,y : in bit_vector(3 downto 0);
		control: in bit; --控制加減法，當control=0為加，control=1為減
		sum : out bit_vector(3 downto 0);
		ncarry: out bit
		);
end addsub4;

--原理和製作4bit-adder是一樣的，唯一不同就是要寫control判斷加法/減法運算
architecture behavior of addsub4 is
	component full_adder
		port(
		X,Y,Z :in bit;
		Sum,Carry: out bit
		);
	end component;


signal CARRY: bit_vector(4 downto 0);
begin
		CARRY(0)<=control;
		G1:for I in 3 downto 0 generate 
		FA:full_adder port map(x(I),y(I) xor control,CARRY(I) ,sum(I),CARRY(I+1)); --對應角位
		end generate G1;
		ncarry<=CARRY(4);
		
end behavior;