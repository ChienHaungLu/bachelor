LIBRARY ieee; 
USE ieee.std_logic_1164.all; 

ENTITY full_add IS     --全加器
PORT ( SA,SB,SCin :in bit; 
	Scout:out bit; 
	Sum :out bit); 
END full_add; 

ARCHITECTURE a OF full_add IS 
BEGIN 
	Sum <= SA xor SB xor SCin; 
	Scout<=(SA and SB) or (SB and SCin) or (SCin and SA); 
END a;