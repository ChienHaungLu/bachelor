library ieee; 
use ieee.std_logic_1164.all; 

entity full_adder_nbits is 
	port ( A,B :in bit_vector(4 downto 0);
			cin:in bit;
			sum:out bit_vector(4 downto 0); 
			cout:out bit);
end full_adder_nbits; 

architecture a of full_adder_nbits IS 	
	
	component full_add
		port(SA,SB,SCin:in bit;Scout,SUM:out bit);  
	end component; 
	
signal CARRY:bit_vector(5 downto 0);
begin
 CARRY(0)<=cin;
	G1:for I in 4 downto 0 generate
		FA:full_add port map (A(I), B(I), CARRY(I),CARRY(I+1), SUM(I));
	end generate G1;
 cout<=CARRY(5);
end a;