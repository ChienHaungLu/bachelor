--本題核心解釋程式尾端
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity mul3 is
	port( A,B:in std_logic_vector(2 downto 0); --A和B位元都是3位元
			X:out std_logic_vector(5 downto 0)); --3位元相乘可能會出現到需要6個bit ex:111*111=110001
end mul3;

architecture behavior of mul3 is

	component full_adder3 is
		port ( A,B :in std_logic_vector(2 downto 0);
				 cin:in std_logic;
				 sum:out std_logic_vector(2 downto 0); 
				 cout:out std_logic);
	end component;
	
signal line1,line2,line3: std_logic_vector(2 downto 0);
signal reg: std_logic_vector(3 downto 0); --line1+line2的結果暫時存放於reg，最多4bits

begin
		X(0)<=line1(0); --A0*B0的結果可以直接先輸出到X
		X(1)<=reg(0);   --A1B0+A0B1的結果在存入reg後就可以輸出了
			
		line1<=(A(2) and B(0)) & (A(1) and B(0)) & (A(0) and B(0)); --相乘之後的直式第一行
		line2<=(A(2) and B(1)) & (A(1) and B(1)) & (A(0) and B(1));
		line3<=(A(2) and B(2)) & (A(1) and B(2)) & (A(0) and B(2));
		
							--port map(A,B, Cin ,Sum,Cout); 因為本題需要兩個三位元adder，A為被加數，B為加數，Cout為進位
		FA1: full_adder3 port map(line2, ("0" & line1(2 downto 1)) , '0' , reg(2 downto 0), reg(3));  --因為cin沒有指定0或1，故填0
		FA2: full_adder3 port map(line3,      reg(3 downto 1)      , '0' ,   X(4 downto 2),   X(5));
	   
end behavior;

------------------------------------解釋區域------------------------------------

--                              A2      A1      A0
--                           *) B2      B1      B0
---------------------------------------------------------
--line1                 0      A2B0    A1B0    A0B0

--line2               A2B1     A1B1    A0B1
      
--reg        reg[3]  reg[2]   reg[1]  reg[0]	 	      -- line1 + line2 存到reg(3 downto0),3bit相加有進位可能，所以要4bits
		
--line3       A2B2    A1B2     A0B2
---------------------------------------------------------
--      X[5]   X[4]    X[3]     X[2]   X[1]    X[0]
	