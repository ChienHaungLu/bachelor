library ieee; 
use ieee.std_logic_1164.all; 

entity full_adder3 IS 
	port ( A,B :in bit_vector(2 downto 0);
			cin:in bit;
			sum:out bit_vector(2 downto 0); 
			cout:out bit);
end full_adder3; 

architecture a of full_adder3 IS 	
	component full_add
		port(SA,SB,SCin:in bit;Scout,SUM:out bit);  
	end component; 
signal CARRY:bit_vector(2 downto 0); 

begin 
			FA1:full_add port map (A(0), B(0), cin,CARRY(1), SUM(0)); 
			FA2:full_add port map (A(1), B(1), CARRY(1),CARRY(2), SUM(1)); 
			FA3:full_add port map (A(2), B(2), CARRY(2),cout, SUM(2)); 
end a; 