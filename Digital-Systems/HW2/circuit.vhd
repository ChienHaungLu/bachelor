library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity circuit is
	generic(
        LENGTH : integer := 8);
	port(
			reset     , clk,start,din : in std_logic;
			count_out , dout_valid,dout : out std_logic;
			count_one : out std_logic_vector(3 downto 0));
end circuit;

architecture behavior of circuit is
------------------依波形圖結果宣告訊號(16進制)------------------
	signal state     : std_logic_vector(2 downto 0);    --0數到4，所以三個位元即可
	signal count     : std_logic_vector(2 downto 0);    --0數到7只要3bits
	signal counter1  : std_logic_vector(3 downto 0);    
begin

	process(reset,clk)
		variable rreg  : std_logic_vector(LENGTH - 1 downto 0);   
		begin
			if reset='1' then
				count_out <='0';
				dout_valid <='0';
				dout <='0';
				state <="000";
				rreg:="00000000";
				count <="000";
				counter1 <="0000";
				
			elsif clk'event and clk='1' then --如果正緣觸發就執行以下敘述
				case state is
				
					when "000" =>
						if start='1' then
							state<="001";
						end if;
					
					when "001" =>
						count<=count+1;
						rreg:=din & rreg(LENGTH-1 downto 1);
						
						if din='1' then
							counter1<=counter1+1;
						end if;
						if count="111" then
							count<="000";
							state<="010";
						end if;
						
					when "010" =>
						count_one<=counter1;
						count_out<='1';
						state<="011";
					
					when  "011" =>
						dout_valid<='1';
						count_out<='0';
						count<=count+1;
						dout<=rreg(7); --先將MSB位元的那筆資料送出，避免後面在合併時資料被shift_left出去
						rreg:=rreg(LENGTH-2 downto 0) & '0';
						
						if count = "111" then 
							count <="000"; 
							state <="100"; 
						end if;
					
					when 	"100" =>
						dout_valid <= '0';
						state <= "000";
				
					when others =>
					
				end case;
			end if;
	end process;
end behavior;