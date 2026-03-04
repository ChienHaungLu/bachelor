-- yellow(in wiki)
-- this dynamic node get the previous state 
-- its input is p , g of previous state 
-- it generates new state holding new p , g 
-- and supply them to next node 
------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

entity dynamicnode is 
	port (
		Pprevious : IN std_logic ; 
		Gprevious : IN std_logic ;
		pcurrent  : IN std_logic ;
		gcurrent  : IN std_logic ;
		pout : OUT std_logic ;
		gout : OUT std_logic );
end dynamicnode;

------------------calculate---------------------
architecture behaviour of dynamicnode is 
begin 
	gout <= gcurrent or (gprevious and pcurrent);
	pout <= pcurrent and Pprevious;
end behaviour ;
------------------------------------------------------