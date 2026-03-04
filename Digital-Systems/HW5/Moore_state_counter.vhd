------------------------------------------------解釋區------------------------------------------------

--一圖表判斷有兩種方法可選  1.Moore machine  2. Mealy machine
--  1.Moore Machine： 這種狀態機的輸出訊號只與目前的狀態有關而與輸入的訊號無關。
--  2.Mealy machine： Mealy machine的輸出訊號會同時考慮目前的狀態及輸入的訊號。

------------------------------------------------解釋區------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity Moore_state_counter is  
	port(
			CLK: in std_logic; 
			x: in std_logic;   -- x=1為順時針走向，反之為逆時針走向
			present_state_output: out std_logic_vector(2 downto 0); --當前狀態輸出
			next_state_output: out std_logic_vector(2 downto 0)  --下一個狀態輸出
		);
end Moore_state_counter;

architecture behavior of Moore_state_counter is
	signal present_state:  std_logic_vector(2 downto 0);
	signal next_state:  std_logic_vector(2 downto 0);
begin
	process(CLK,present_state)
	begin
		if CLK'event and CLK='1' then
			present_state<=next_state;
		end if;
		
		case present_state is --使用case敘述撰寫，易理解方法撰寫，但缺點為PROGRAM可讀性不高
		
			when "000" =>
				present_state_output<=present_state;  --將目前訊號所在狀態傳入目前狀態並且輸出
				if x='0' then 
					next_state<="100";
				else	
					next_state<="001";
				end if;
				next_state_output<=next_state;   --將目前訊號傳入下一個狀態並輸出
				
			when "001" =>
				present_state_output<=present_state;
				if x='0' then 
					next_state<="000";
				else
					next_state<="011";
				end if;
				next_state_output<=next_state;
				
			when "010" =>
				present_state_output<=present_state;
				if x='0' then
					next_state<="011";
				else
					next_state<="110";
				end if;
				next_state_output<=next_state;
				
			when "011" =>
				present_state_output<=present_state;
				if x='0' then
					next_state<="001";
				else
					next_state<="010";
				end if;
				next_state_output<=next_state;
				
			when "100" =>
				present_state_output<=present_state;
				if x='0' then
					next_state<="101";
				else 
					next_state<="000";
			   end if;
				next_state_output<=next_state;
				
			when "101" =>
				present_state_output<=present_state;
				if x='0' then 
					next_state<="111";
				else
					next_state<="100";
				end if;
				next_state_output<=next_state;
				
			when "110" =>
				present_state_output<=present_state;
				if x='0' then
					next_state<="010";
				else
					next_state<="111";
				end if;
				next_state_output<=next_state;
				
			when "111" =>
				present_state_output<=present_state;
				if x='0' then
					next_state<="110";
				else
					next_state<="101";
				end if;
				next_state_output<=next_state;
				
			when others=> --此行為其他可能，若不寫則compile會出錯，它為case敘述的一部份
			
		end case;
		
	end process;

end behavior;
				