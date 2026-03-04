--若將so以及carry的std_logic_vector同時改成downto，則資料會邏輯右移進來
--若將so以及carry的std_logic_vector同時改成to，則資料會邏輯左移進來。
--每更改一次to或downto就創立新的波形檔來看結果，否則結果會停留在前一次的設定

--但依據本題的圖Q的順序回Q0 to Q3，所以推測為邏輯左移進來，本題為SIPO移位暫存
library ieee;
use ieee.std_logic_1164.all;

entity DFF4 is
  port (
    si,CLOCK : in std_logic; --用serial_input取代原本的輸出名input
    so : out std_logic_vector(0 to 3) --0遞增到3將資料邏輯左移，用serial_output取代原本的輸出名稱Q
  );
end DFF4; 

architecture behavior of DFF4 is      
	component D_Filp_Flop is
		port(
				D,CLK:in std_logic;
				Q:out std_logic);
	end component;
signal carry: std_logic_vector(0 to 4);  --carry就是將目前的DFF的輸出及下一個DFF輸入的連結橋梁
begin
	carry(0)<=si; --carry(0)為INPUT連結到第一個DFF輸入之訊號
	G1:for i in 0 to 3 generate
			DFF:D_Filp_Flop port map(carry(i),CLOCK,carry(i+1)) ;  
			so(i)<=carry(i+1); --carry(1)就是O(0)，carry(2)就是O(1)
	end generate G1;   

end behavior;