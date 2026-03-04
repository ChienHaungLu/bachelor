library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity mul5 is
	port( A,B:in bit_vector(4 downto 0); --A和B位元都是5位元
			X:out bit_vector(9 downto 0)); --5位元相乘可能會出現到需要6個bit ex:111*111=110001
end mul5;

architecture beh of mul5 is

	component full_adder_nbits is
	port ( A,B :in bit_vector(4 downto 0);
			cin:in bit;
			sum:out bit_vector(4 downto 0); 
			cout:out bit);
	end component;
	
signal line1,line2,line3,line4,line5: bit_vector(4 downto 0);
signal reg1,reg2,reg3: bit_vector(5 downto 0); --最多只會用到6bits

begin
	x(0)<=line1(0);
	x(1)<=reg1(0);
	x(2)<=reg2(0);
	x(3)<=reg3(0);

	line1<=(A(4) and B(0)) & (A(3) and B(0)) & (A(2) and B(0)) & (A(1) and B(0)) & (A(0) and B(0));
	line2<=(A(4) and B(1)) & (A(3) and B(1)) & (A(2) and B(1)) & (A(1) and B(1)) & (A(0) and B(1));
	line3<=(A(4) and B(2)) & (A(3) and B(2)) & (A(2) and B(2)) & (A(1) and B(2)) & (A(0) and B(2));
	line4<=(A(4) and B(3)) & (A(3) and B(3)) & (A(2) and B(3)) & (A(1) and B(3)) & (A(0) and B(3));
	line5<=(A(4) and B(4)) & (A(3) and B(4)) & (A(2) and B(4)) & (A(1) and B(4)) & (A(0) and B(4));
	
	
	FA1: full_adder_nbits port map(line2,'0'&line1(4 downto 1),'0',reg1(4 downto 0),reg1(5));
	FA2: full_adder_nbits port map(line3,reg1(5 downto 1),'0',reg2(4 downto 0),reg2(5));
	FA3: full_adder_nbits port map(line4,reg2(5 downto 1),'0',reg3(4 downto 0),reg3(5));
	FA4: full_adder_nbits port map(line5,reg3(5 downto 1),'0',X(8 downto 4),X(9));
	
end beh;