-- RED(in wiki)
-- this the essentialnode is carring the initial state of the adder 
-- its input is the first input carry 
-------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

entity essentialnode is 
	port (
		x : IN std_logic ;-- node input terminal 
		y : IN std_logic ;-- node input terminal 
		g : OUT std_logic ;-- g output terminlal of node 
		p : OUT std_logic );-- P output terminal  of node 
end essentialnode;

architecture behaviour of essentialnode is 
begin 
g <= x and y;
p <= x xor y;
end behaviour;
-------------------------------------------------------------------