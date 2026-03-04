library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity DFF_circuit is
	port(
			Serial_in,LOAD,CLOCK:in std_logic;
			Parallel_in : in std_logic_vector(3 downto 0);
			Q: out std_logic_vector(3 downto 0));
end DFF_circuit;

architecture beh of DFF_circuit is
	
	component D_Filp_Flop is
		port(D,CLK:in std_logic;
			O:out std_logic);
	end component;
	
	component ADD2_OR is
		port(
		  A,B,C,D:in std_logic;
		  E: out std_logic);
	end component;
	
signal s1: std_logic_vector(4 downto 0); --用於輸入addor存放的暫存
signal s2: std_logic_vector(3 downto 0); --將addor結果輸出後並用於輸入DFF存放的暫存

begin

	s1(4)<=Serial_in;--先將輸入訊號傳入s1(4)，s1[3 DOWNTO 0]為for-generate用
		G1:for i in 3 downto 0 generate
				ADD2OR: ADD2_OR port map(s1(i+1),NOT LOAD,LOAD,Parallel_in(i),s2(i)); 
				--port map(從FF輸出只有用到前三個,NOT LOAD,LOAD,,Parallel_in(i)ADD2OR結果對應DFF輸入)
				
				DFF:D_Filp_Flop port map(s2(i),CLOCK,s1(i)); -- port map(ADD2OR結果對應DFF輸入,CLOCK,將DFF輸出連結到addor左邊AND的第一個輸入)
				Q(i)<=s1(i);
		 end generate G1;
		 
end beh;