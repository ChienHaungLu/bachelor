library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity mux_2to1_ff is
	port(
		A,B,IN1,IN2: in bit;
		clk:in std_logic;
		Q:out bit);
end mux_2to1_ff;

architecture behavior of mux_2to1_ff is
begin 
	process(IN1,IN2,A,B,clk)
	begin
		if clk'event and clk='1' then --正緣觸發
			if(A and B)='0' then --若a和b做and後得到的訊號為0 
				Q<=IN1;  --將IN1傳給正反器
			else
				Q<=IN2;  --將IN2傳給正反器
			end if;
		end if;
	end process;
end behavior;